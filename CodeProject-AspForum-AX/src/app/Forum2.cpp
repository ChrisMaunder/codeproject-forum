// ###########################################################################
// #
// # file:
// #	forum2.cpp
// #
// ###########################################################################

#include "stdafx.h"
#pragma warning(disable:4786)
#include "resource.h"

#include "forum2.h"
#include "..\common\memoryex.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// global helpers.

std::_tstring UrlEncode( LPCTSTR url )
{
	const unsigned int size=500;
	auto_ptr_array<TCHAR> buf(new TCHAR[size]);
	memset( buf.get(), 0, size );
	DWORD buf_len=size-1;
	unsigned int loop_cnt=0;

	while ( true ) {
		if ( !::InternetCanonicalizeUrl( 
			url, 
			buf.get(), 
			&buf_len, 
			0//ICU_NO_META//
			) ) {

			if ( GetLastError()==ERROR_INSUFFICIENT_BUFFER ) {
				loop_cnt++;
				if ( loop_cnt>1 )
					throw Xept( _T("error canonicalizing the URL "
						"\"%s\" (looped %d times)"), url, loop_cnt );
				else {
					buf_len += 1;
					buf = auto_ptr_array<TCHAR>(new TCHAR[buf_len]);
					continue;
				}
			} else
				throw Xept( _T("error canonicalizing the URL \"%s\""), url );
		} else
			break;
	}

	return buf.get();

	/*//-todo: replace things like '%' with its encoded from ('%' => '%25', etc.)
	// a good way to check the encoding is to enter words in the search box on
	// the page "http://info.internet.isi.edu/7c/in-notes/rfc/.cache" and look
	// for the encoded results.
	return url;*/
}

// extracts a (name|value)-token pair. returns the remaining string.
// call e.g.: ExtractFirstToken( name, value, "firstname=john;lastname=doe;", "=", ";" )
std::_tstring ExtractFirstToken( 
	std::_tstring& name, std::_tstring& value, LPCTSTR txt, 
	LPCTSTR sep, LPCTSTR end )
{
	std::_tstring text( txt );
	std::_tstring::size_type sep_pos = text.find( sep );

	if ( sep_pos==text.npos ) {
		return text;

	} else {
		// extract name.
		name = text.substr( 0, sep_pos );
		text.erase( 0, sep_pos+1 );

		// try to extract value.
		std::_tstring::size_type end_pos = text.find( end );

		if ( end_pos==text.npos ) {
			value = text;
			return _T("");

		} else {
			value = text.substr( 0, end_pos );
			text.erase( 0, end_pos+1 );
			return text;
		}
	}
}

#define CATCH_AND_RET_CONN() \
	catch ( Xept &e ) { \
		return CATCH_AND_LOG_XEPT( e ); \
	} catch ( _com_error &e ) { \
		return CATCH_AND_LOG_COM_ERROR_XEPT( e, conn ); \
	} catch ( ... ) { \
		return CATCH_AND_LOG_UNKNOWN_XEPT(); \
	} \

#define CATCH_AND_RET() \
	catch ( Xept &e ) { \
		return CATCH_AND_LOG_XEPT( e ); \
	} catch ( _com_error &e ) { \
		return CATCH_AND_LOG_COM_ERROR_XEPT( e ); \
	} catch ( ... ) { \
		return CATCH_AND_LOG_UNKNOWN_XEPT(); \
	} \


/////////////////////////////////////////////////////////////////////////////
// forum class.

CForum2::CForum2()
{
	m_pUnkMarshaler   = 0;
	m_ForumID         = 0;
	m_MapModified     = true;

	m_FilterStartDate = _T("01/01/1900");
	m_FilterEndDate   = _T("01/01/2900");

	m_DebugMode       = DEBUG_MODE_OFF;
	m_RetrieveStart   = 0;
	m_RetrieveCount   = 0;
}

CForum2::~CForum2()
{
	try {
		EmptyAll();

	} catch ( ... ) {
		// no throws in d'tors.
	}
}

STDMETHODIMP CForum2::InterfaceSupportsErrorInfo(REFIID riid)
{
	try {
		// see KB Q243298.

		static const IID* arr[] = {
			&IID_IForum2,
		};

		for ( int i=0; i<sizeof(arr)/sizeof(arr[0]); i++ ) {
			if ( ::ATL::InlineIsEqualGUID(*arr[i],riid) )
				return S_OK;
		}

	} CATCH_AND_RET();

	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// internal helpers.

std::_tstring CForum2::GetSqlWhereString() const
{
	std::_tstring result=_T("");

	// handle start-date filter.
	if ( !m_FilterStartDate.empty() ) {
		result += Format(_T("(Date>=#%s#)"), m_FilterStartDate.c_str());
	}

	// handle end-date filter.
	if ( !m_FilterEndDate.empty() ) {
		if ( !result.empty() )
			result += _T(" AND ");
		result += Format(_T("(Date<=#%s#)"), m_FilterEndDate.c_str());
	}

	// handle keyword filter.
	if ( !m_FilterKeywords.empty() ) {
		if ( !result.empty() )
			result += _T(" AND ");
		result += Format(_T("(Subject LIKE '%%%s%%' OR "
			"AuthorName LIKE '%%%s%%' OR "
			"Text LIKE '%%%s%%' )"), 
			m_FilterKeywords.c_str(), 
			m_FilterKeywords.c_str(), 
			m_FilterKeywords.c_str());
	}

	return result;
}

void CForum2::EmptyAll()
{
	hdr_lst_t::iterator it;
	for ( it=m_Headers.begin(); it!=m_Headers.end(); ++it ) {
		delete *it;
		*it = 0;
	}

	m_IDs.clear();
	m_Headers.clear();
	m_Tree.clear();
}

CForum2::hdr_lst_t::iterator CForum2::FindHeaderWithParent( const long parent_id )
{
	for ( hdr_lst_t::iterator it=m_Headers.begin(); 
		it!=m_Headers.end(); ++it ) {

			if ( (*it)->m_ParentID==parent_id )
				// found.
				return it;
	}

	// not found.
	return m_Headers.end();
}

CForum2::hdr_lst_t::iterator CForum2::FindHeaderWithNoParent()
{
	for ( hdr_lst_t::iterator it=m_Headers.begin(); 
		it!=m_Headers.end(); ++it ) {

			if ( (*it)->m_ParentID==0 || !IdExists((*it)->m_ParentID) )
				// found.
				return it;
	}

	// not found.
	return m_Headers.end();
}

void CForum2::InsertList()
{
	tree::node *nd = m_Tree.get_root();

	// seek to begin.
	for ( int i=0; i<m_RetrieveStart; ++i )
		nd = nd->goto_next();

	// read wanted count.
	if ( m_RetrieveCount>0 ) {
		int cnt=0;
		while ( nd && cnt<m_RetrieveCount ) {
			m_Headers.push_back( (Header*)nd->data );
			nd->data = 0;

			nd = nd->goto_next();
			cnt++;
		}

	// read unlimited.
	} else {
		while ( nd ) {
			m_Headers.push_back( (Header*)nd->data );
			nd->data = 0;

			nd = nd->goto_next();
		}
	}

	// tree not needed any more.
	m_Tree.clear();
}

tree::node *CForum2::InsertTreeChild( tree::node *const parent, CForum2::Header *const child )
{
	// parent is zero, insert at top-level.
	if ( !parent ) {
		tree::node *nd = m_Tree.get_root();

		// no root yet.
		if ( nd==0 ) {
			// insert.
			tree::node *nd = m_Tree.insert_root();

			// set data.
			nd->data = child;
			return nd;

		// already items at root. sort descending by date.
		// (newest topmost, oldest bottommost).
		} else {
			// seek.
			while ( nd->next && child->m_Date<((Header*)nd->data)->m_Date )
				nd = nd->next;

			// insert.
			if ( child->m_Date>((Header*)nd->data)->m_Date )
				nd = nd->insert_sibling_before();
			else
				nd = nd->insert_sibling_after();

			// set data.
			nd->data = child;
			return nd;
		}

	// parent is not zero. no childs yet.
	} else if ( !parent->child ) {
		// insert.
		tree::node *nd = parent->insert_after_last_child();

		// set data.
		nd->data = child;
		return nd;

	// parent is not zero.
	// has childs yet, insert sorted, ascending by date.
	// (newest topmost, oldest bottommost).
	} else {
		tree::node *nd = parent->child;

		// seek.
		while ( nd->next && child->m_Date>((Header*)nd->data)->m_Date )
			nd = nd->next;

		// insert.
		if ( child->m_Date<((Header*)nd->data)->m_Date )
			nd = nd->insert_sibling_before();
		else
			nd = nd->insert_sibling_after();

		// set data.
		nd->data = child;
		return nd;
	}
}

void CForum2::InsertTree( tree::node *const parent, const long ind_lvl )
{
	// no more to insert.
	if ( m_Headers.empty() )
		return;

	const long parent_id = parent==0?0:((Header*)(parent->data))->m_ID;

	// insert all childs of the current parent.

	// no parent.
	if ( parent_id==0 ) {
		hdr_lst_t::iterator it;

		// move all childs from list to tree.
		while ( (it=FindHeaderWithNoParent())!=m_Headers.end() ) {

			// move.
			tree::node *nd = InsertTreeChild( parent, (*it) );
			m_Headers.erase( it );

			// set data.
			((Header*)(nd->data))->m_IndentLevel = ind_lvl;

			// recurse into.
			InsertTree( nd, ind_lvl+1 );
		}

	// specified parent.
	} else {
		hdr_lst_t::iterator it;

		// move all childs from list to tree.
		while ( (it=FindHeaderWithParent(parent_id))!=m_Headers.end() ) {

			// move.
			tree::node *nd = InsertTreeChild( parent, (*it) );
			m_Headers.erase( it );

			// set data.
			((Header*)(nd->data))->m_IndentLevel = ind_lvl;

			// recurse into.
			InsertTree( nd, ind_lvl+1 );
		}
	}
}

bool CForum2::IdExists( const long id ) const
{
	return m_IDs.find(id)!=m_IDs.end();
}

void CForum2::HelpDeleteBranch( ADODB::_ConnectionPtr conn, const long id )
{
	ADODB::_RecordsetPtr rs;

	// look whether childs exist.
	std::_tstring sql;
	sql = Format( _T("SELECT ID FROM Article WHERE ParentID=%d"), id );
	rs = conn->Execute( sql.c_str(), 0, ADODB::adCmdText );

	// recurse into all childs.
	if ( rs->BOF==VARIANT_FALSE )
		rs->MoveFirst();
	while ( rs->adoEOF==VARIANT_FALSE ) {
		HelpDeleteBranch( conn, rs->Fields->Item[_bstr_t( L"ID" )]->Value );

		rs->MoveNext();
	}

	rs->Close();

	// delete myself.
	sql = Format( _T("DELETE FROM Article WHERE ID=%d"), id );
	conn->Execute( sql.c_str(), 0, ADODB::adCmdText );
}

std::_tstring CForum2::ToUrl()
{
	std::_tstring ret;

	// can't use cache.
	if ( m_MapModified ) {
		map_string_to_variant_t::const_iterator it;
		for ( it=m_Map.begin(); it!=m_Map.end(); ++it ) {
			if ( ret.length()>0 )
				ret += _T("&");
			ret += UrlEncode(it->first.c_str()).c_str();
			ret += _T("=");
			ret += UrlEncode(_bstr_t(it->second)).c_str();
		}

		ret += _T("&");

		m_MapUrl = ret.c_str();
		m_MapModified = false;

	// use cached value.
	} else {
		ret = m_MapUrl;
	}

	return ret;
}

/////////////////////////////////////////////////////////////////////////////
// interface implementations.

STDMETHODIMP CForum2::ReadArticles( BSTR conn_str, BSTR id, BSTR pw )
{
	// for an ADO sample, see ADOVC.EXE from 
	// Microsoft's softlib (Q174565).

	ADODB::_ConnectionPtr	conn;
	ADODB::_RecordsetPtr	rs;

	try {
		m_ConnStr = (LPCTSTR)_bstr_t(conn_str);
		m_ID      = (LPCTSTR)_bstr_t(id);
		m_PW      = (LPCTSTR)_bstr_t(pw);

		// create connection object (ADO 1.5 version)
		CREATE_INSTANCE( conn, __uuidof( ADODB::Connection ) );
		conn->ConnectionString = conn_str;
		conn->Open( L"", id, pw, -1 );

		// the full sql-where string.
		std::_tstring sql_where=GetSqlWhereString();
		if ( !sql_where.empty() )
			sql_where = std::_tstring(_T(" AND (")) + sql_where +
				std::_tstring(_T(")"));

		EmptyAll();
		std::_tstring sql;

		// ------------------------------------------
		// read all records, store them unordered.

		// get all records, store the headers UNordered.
		sql = Format( _T("SELECT * FROM Article WHERE ForumID=%d %s"),
			m_ForumID, sql_where.c_str() );

		rs = conn->Execute( sql.c_str(), 0, ADODB::adCmdText );

		if ( rs->BOF==VARIANT_FALSE )
			rs->MoveFirst();
        _variant_t var_id       ( _bstr_t(L"ID") );
        _variant_t var_parent_id( _bstr_t(L"ParentID") );
        _variant_t var_date     ( _bstr_t(L"Date") );

		/*
		long cnt = 0;
		*/
		while ( rs->adoEOF==VARIANT_FALSE ) {

			/*
			// skip first n recordsets.
			if ( cnt>=m_RetrieveStart ) {
			*/

				std::auto_ptr<Header> hdr( new Header );
				hdr->m_ID			= rs->Fields->Item[var_id       ]->Value;
				hdr->m_ParentID		= rs->Fields->Item[var_parent_id]->Value;
				hdr->m_Date			= rs->Fields->Item[var_date     ]->Value;
				hdr->m_IndentLevel	= -1; // not yet set.

				m_IDs[hdr->m_ID] = hdr.get();
				m_Headers.push_back( hdr.release() );
			/*
			}
			*/

			rs->MoveNext();

			/*
			// limit to count.
			cnt++;
			if ( m_RetrieveCount>0 && cnt>=m_RetrieveStart+m_RetrieveCount )
				break;
			*/
		}

		rs->Close();
		conn->Close();

		// ------------------------------------------
		// sort the unordered headers.

		// put from unordered list into tree.
		InsertTree( 0, 0 );
		ASSERT(m_Headers.size()==0);

		// put back from tree into list for cutting off
		// unwanted messages.
		InsertList();
		ASSERT(m_Headers.size()>0);
		m_HeaderPos = m_Headers.begin();

	} CATCH_AND_RET_CONN();

	return S_OK;
}

STDMETHODIMP CForum2::get_BeginOfList(BOOL *pVal)
{
	try {
		*pVal = m_HeaderPos==m_Headers.begin()?VB_TRUE:VB_FALSE;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_EndOfList(BOOL *pVal)
{
	try {
		*pVal = m_HeaderPos==m_Headers.end()?VB_TRUE:VB_FALSE;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::MoveNext()
{
	try {
		m_HeaderPos++;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_GetCurID(long *pVal)
{
	try {
		*pVal=(*m_HeaderPos)->m_ID;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_GetCurIndentLevel(long *pVal)
{
	try {
		*pVal=(*m_HeaderPos)->m_IndentLevel;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::put_ForumID(long newVal)
{
	try {
		m_ForumID = newVal;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_FilterStartDate(BSTR *pVal)
{
	try {
		*pVal = _bstr_t(m_FilterStartDate.c_str()).copy();

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::put_FilterStartDate(BSTR newVal)
{
	try {
		if ( lstrlen((LPCTSTR)_bstr_t(newVal))==0 )
			return S_OK;

		m_FilterStartDate = (LPCTSTR)_bstr_t(newVal);

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::put_FilterKeywords(BSTR newVal)
{
	try {
		m_FilterKeywords = (LPCTSTR)_bstr_t(newVal);

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_FilterKeywords(BSTR *pVal)
{
	try {
		*pVal = _bstr_t(m_FilterKeywords.c_str()).copy();

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_FilterEndDate(BSTR *pVal)
{
	try {
		*pVal = _bstr_t(m_FilterEndDate.c_str()).copy();

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::put_FilterEndDate(BSTR newVal)
{
	try {
		if ( lstrlen((LPCTSTR)_bstr_t(newVal))==0 )
			return S_OK;

		m_FilterEndDate = (LPCTSTR)_bstr_t(newVal);

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::DeleteID(long id, BOOL single)
{
	ADODB::_ConnectionPtr	conn;
	ADODB::_RecordsetPtr	rs;

	try {
		// create connection object (ADO 1.5 version)
		CREATE_INSTANCE( conn, __uuidof( ADODB::Connection ) );
		conn->ConnectionString = m_ConnStr.c_str();
		conn->Open( L"", m_ID.c_str(), m_PW.c_str(), -1 );

		if ( single==VB_TRUE ) {			// delete one entry.
			std::_tstring sql;
			sql = Format( _T("DELETE FROM Article WHERE ID=%d"), id );
			conn->Execute( sql.c_str(), 0, ADODB::adCmdText );

		} else {							// delete whole branch.
			HelpDeleteBranch( conn, id );
		}

	} CATCH_AND_RET_CONN();

	return S_OK;
}

STDMETHODIMP CForum2::put_DbConnStr(BSTR newVal)
{
	try {
		m_ConnStr = (LPCTSTR)_bstr_t(newVal);

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::put_DbID(BSTR newVal)
{
	try {
		m_ID = (LPCTSTR)_bstr_t(newVal);

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::put_DbPW(BSTR newVal)
{
	try {
		m_PW = (LPCTSTR)_bstr_t(newVal);

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_Value(BSTR name, VARIANT *pVal)
{
	try {
		map_string_to_variant_t::const_iterator it =
			m_Map.find( (LPCTSTR)_bstr_t(name) );

		if ( it==m_Map.end() ) {
			// create empty.
			put_Value( name, _variant_t() );
			_variant_t value;
			*pVal = value.Detach();

		} else {
			_variant_t value(it->second);
			*pVal = value.Detach();
		}

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::put_Value(BSTR name, VARIANT newVal)
{
	try {
		m_Map[std::_tstring(_bstr_t(name))] = _bstr_t(newVal);
		m_MapModified = true;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::FromUrl(BSTR url)
{
	try {
		// -------------------------------------------
		// get from url.

		TCHAR extra[1000];

		URL_COMPONENTS comps;
		memset( &comps, 0, sizeof comps );
		comps.dwStructSize      = sizeof comps;
		comps.lpszExtraInfo     = extra;
		comps.dwExtraInfoLength = 1000;

		if ( !InternetCrackUrl( _bstr_t(url), 0,
			/*ICU_DECODE*/ICU_ESCAPE,
			&comps ) )
			throw Xept( _T("error cracking url \'%s\'"), 
				(LPCTSTR)_bstr_t(url) );

		// remove anything before the parameters.
		std::_tstring all( extra );
		while ( all[0]==_T('?') || all[0]==_T('&') )
			all.erase( 0, 1 );

		// remove any anchors.
		const int anchor_pos=all.find( '#' );
		if ( anchor_pos!=std::_tstring::npos )
			all.erase( anchor_pos );

		// -------------------------------------------
		// get components.

		while ( all.size()>0 ) {
			std::_tstring name;
			std::_tstring value;

			const std::_tstring all_before=all;
			all = ExtractFirstToken( 
				name, value, all.c_str(), _T("="), _T("&") );
			if (all_before==all )
				break;

			m_Map[name] = _bstr_t(value.c_str());
		}

		m_MapModified = true;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_ToUrl(BSTR *pVal)
{
	ADODB::_ConnectionPtr	conn;

	try {
		_bstr_t ret;
		ret = ToUrl().c_str();

		*pVal = ret.copy();

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_ToUrlValue(BSTR name, VARIANT newVal, BSTR *pVal)
{
	ADODB::_ConnectionPtr	conn;

	try {
		_bstr_t ret;

		// store current value for 'name' for later restore.
		const bool was_mod = m_MapModified;
		const std::_tstring cur_mapurl = m_MapUrl;
		const _variant_t cur_value = m_Map[std::_tstring(_bstr_t(name))];

		// insert into map.
		m_Map[std::_tstring(_bstr_t(name))] = _bstr_t(newVal);
		m_MapModified = true;

		// generate url.
		ret = ToUrl().c_str();

		// restore old value.
		m_Map[std::_tstring(_bstr_t(name))] = _bstr_t(cur_value);
		if ( !was_mod ) {
			m_MapModified = false;
			m_MapUrl = cur_mapurl;

		} else
			m_MapModified = true;

		*pVal = ret.copy();

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_ToUrlValue2(BSTR name1, VARIANT value1, BSTR name2, VARIANT value2, BSTR *pVal)
{
	ADODB::_ConnectionPtr	conn;

	try {
		_bstr_t ret;

		// store current value for 'name' for later restore.
		const bool was_mod = m_MapModified;
		const std::_tstring cur_mapurl = m_MapUrl;
		const _variant_t cur_value1 = m_Map[std::_tstring(_bstr_t(name1))];
		const _variant_t cur_value2 = m_Map[std::_tstring(_bstr_t(name2))];

		// insert into map.
		m_Map[std::_tstring(_bstr_t(name1))] = _bstr_t(value1);
		m_Map[std::_tstring(_bstr_t(name2))] = _bstr_t(value2);
		m_MapModified = true;

		// generate url.
		ret = ToUrl().c_str();

		// restore old value.
		m_Map[std::_tstring(_bstr_t(name1))] = _bstr_t(cur_value1);
		m_Map[std::_tstring(_bstr_t(name2))] = _bstr_t(cur_value2);
		if ( !was_mod ) {
			m_MapModified = false;
			m_MapUrl = cur_mapurl;

		} else
			m_MapModified = true;

		*pVal = ret.copy();

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_DebugMode(long *pVal)
{
	try {
		*pVal = m_DebugMode;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::put_DebugMode(long newVal)
{
	try {
		m_DebugMode = newVal;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_RetrieveCount(long *pVal)
{
	try {
		*pVal = m_RetrieveCount;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::put_RetrieveCount(long newVal)
{
	try {
		m_RetrieveCount = newVal;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::get_RetrieveStart(long *pVal)
{
	try {
		*pVal = m_RetrieveStart;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::put_RetrieveStart(long newVal)
{
	try {
		m_RetrieveStart = newVal;

	} CATCH_AND_RET();

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
