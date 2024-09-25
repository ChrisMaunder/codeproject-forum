// ###########################################################################
// #
// # file:
// #	Forum2.cpp
// #
// ###########################################################################

#include "stdafx.h"
#pragma warning(disable:4786)
#include "resource.h"
#include "Forum2.h"
#include "..\common\memoryex.h"


/////////////////////////////////////////////////////////////////////////////
// helpers.

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
	std::_tstring text(txt);
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

#define CATCH_AND_RET() \
	catch ( Xept &e ) { \
		return CATCH_AND_LOG_XEPT( e ); \
	} catch ( _com_error &e ) { \
		return CATCH_AND_LOG_COM_ERROR_XEPT( e, conn ); \
	} catch ( ... ) { \
		return CATCH_AND_LOG_UNKNOWN_XEPT(); \
	} \


/////////////////////////////////////////////////////////////////////////////
// CForum2

CForum2::CForum2() :
	m_pUnkMarshaler(0),
	m_ForumID(0),
	m_MapModified(true)
{
	m_FilterStartDate = "01/01/1900";
	m_FilterEndDate   = "01/01/2900";

	m_DebugMode = DEBUG_MODE_OFF;
}

CForum2::~CForum2()
{
	try {
		EmptyHeaders();
		EmptyTmpHeaders();

	} catch ( ... ) {
	}
}

STDMETHODIMP CForum2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IForum2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


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

STDMETHODIMP CForum2::ReadArticles( BSTR conn_str, BSTR id, BSTR pw )
{
	// for an ADO sample, see ADOVC.EXE from Microsoft's softlib
	// (Q174565).

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

		EmptyIDs();
		EmptyHeaders();
		EmptyTmpHeaders();
		m_HdrPos = m_Headers.begin();
		std::_tstring sql;

		// -------------------------------------------------------------------------
		// read all records (NEWEST FIRST) that are top-level, store them unordered.

		// get all records, store the headers UNordered.
		sql = Format( _T("SELECT * FROM Article WHERE ForumID=%d "
			" %s "
			/*"ORDER BY Date ASC"*/),
			m_ForumID,
			sql_where.c_str() );

		rs = conn->Execute( sql.c_str(), 0, ADODB::adCmdText );

		if ( rs->BOF==VARIANT_FALSE )
			rs->MoveFirst();
        _variant_t var_id          ( _bstr_t( L"ID" ) );
        _variant_t var_parent_id   ( _bstr_t( L"ParentID" ) );
        _variant_t var_subject     ( _bstr_t( L"Subject" ) );
        _variant_t var_author_name ( _bstr_t( L"AuthorName" ) );
        _variant_t var_author_email( _bstr_t( L"AuthorEmail" ) );
        _variant_t var_date        ( _bstr_t( L"Date" ) );

		while ( rs->adoEOF==VARIANT_FALSE ) {
			std::auto_ptr<Header> hdr( new Header );
			hdr->m_ID			=                  rs->Fields->Item[var_id          ]->Value;
			hdr->m_ParentID		=                  rs->Fields->Item[var_parent_id   ]->Value;
			hdr->m_Subject		= (TCHAR*)(_bstr_t)rs->Fields->Item[var_subject     ]->Value;
			hdr->m_AuthorName	= (TCHAR*)(_bstr_t)rs->Fields->Item[var_author_name ]->Value;
			hdr->m_AuthorEMail	= (TCHAR*)(_bstr_t)rs->Fields->Item[var_author_email]->Value;
			hdr->m_Date			=                  rs->Fields->Item[var_date        ]->Value;
			hdr->m_IndentLevel	= -1; // not yet set.
			m_TmpHeaders.push_back( hdr.release() );

			m_IDs.insert( hdr->m_ID );

			rs->MoveNext();
		}

		rs->Close();
		conn->Close();

		// ---------------------------------------------------------
		// now remove all entries that are NOT toplevel entries.

		hdr_lst_t::iterator it_src=m_TmpHeaders.begin();

		while ( it_src!=m_TmpHeaders.end() ) {
			const bool has_parent = IdExists((*it_src)->m_ParentID);

			if ( has_parent ) {
				delete *it_src;
				it_src = m_TmpHeaders.erase( it_src ); // move to next!
			} else {
				++it_src;
			}
		}

		// ---------------------------------------------------------
		// read all non-top-level (NEWST LAST) records.

		// get all records, store the headers UNordered.
		sql = Format( _T("SELECT * FROM Article WHERE ForumID=%d "
			" %s "
			/*"ORDER BY Date DESC"*/),
			m_ForumID,
			sql_where.c_str() );

		rs = conn->Execute( sql.c_str(), 0, ADODB::adCmdText );

		if ( rs->BOF==VARIANT_FALSE )
			rs->MoveFirst();

		while ( rs->adoEOF==VARIANT_FALSE ) {
			std::auto_ptr<Header> hdr( new Header );
			hdr->m_ID			=                  rs->Fields->Item[var_id          ]->Value;
			hdr->m_ParentID		=                  rs->Fields->Item[var_parent_id   ]->Value;
			hdr->m_Subject		= (TCHAR*)(_bstr_t)rs->Fields->Item[var_subject     ]->Value;
			hdr->m_AuthorName	= (TCHAR*)(_bstr_t)rs->Fields->Item[var_author_name ]->Value;
			hdr->m_AuthorEMail	= (TCHAR*)(_bstr_t)rs->Fields->Item[var_author_email]->Value;
			hdr->m_Date			=                  rs->Fields->Item[var_date        ]->Value;
			hdr->m_IndentLevel	= -1; // not yet set.
			m_TmpHeaders2.push_back( hdr.release() );

			m_IDs.insert( hdr->m_ID );

			rs->MoveNext();
		}

		rs->Close();
		conn->Close();

		// ---------------------------------------------------------
		// move all entries that are NOT toplevel entries to the other list.

		it_src=m_TmpHeaders2.begin();

		while ( it_src!=m_TmpHeaders2.end() ) {
			const bool has_parent = IdExists((*it_src)->m_ParentID);

			if ( has_parent ) {
				m_TmpHeaders.push_back( *it_src );
				*it_src = 0;
			}

			++it_src;
		}

		// ---------------------------------------------------------

		SortHeaders();
		m_HdrPos = m_Headers.begin();

	} CATCH_AND_RET();

	return S_OK;
}

void CForum2::EmptyTmpHeaders()
{
	hdr_lst_t::iterator it;
	for ( it=m_TmpHeaders.begin(); it!=m_TmpHeaders.end(); ++it ) 
		delete *it;
	m_TmpHeaders.clear();

	for ( it=m_TmpHeaders2.begin(); it!=m_TmpHeaders2.end(); ++it ) 
		delete *it;
	m_TmpHeaders2.clear();
}

void CForum2::EmptyHeaders()
{
	hdr_lst_t::iterator it;
	for ( it=m_Headers.begin(); it!=m_Headers.end(); ++it ) 
		delete *it;

	m_Headers.clear();
}

void CForum2::Insert( const long ind_lvl,
	hdr_lst_t::iterator it_parent,
	hdr_lst_t& lst_src, hdr_lst_t& lst_dst )
{
	const long parent_id=lst_dst.empty()?0:(*it_parent)->m_ID;

	hdr_lst_t::iterator it_src=lst_src.begin();
	Header *hdr;

	while ( it_src!=lst_src.end() ) {
		// a top-level item is one with indent-level==0 or
		// with no parent present.
		const bool no_parent = ind_lvl==0 && 
			!IdExists((*it_src)->m_ParentID);

		// found a child for the specified parent.
		// or found no parent at level 0.
		if ( (*it_src)->m_ParentID==parent_id || no_parent ) {

			if ( no_parent )
				(*it_src)->m_ParentID = 0;

			// move from src to dst list.
			hdr = *it_src;
			it_src = lst_src.erase( it_src ); // move to next!
			hdr_lst_t::iterator it_tmp;
//			if ( no_parent ) { it_parent--; it_tmp=it_parent; it_parent++; }
/*			else*/             { it_parent++; it_tmp=it_parent; it_parent--; }
			hdr_lst_t::iterator it_new_parent=lst_dst.insert( it_tmp, hdr ); // insert AFTER it_parent.

			hdr->m_IndentLevel = ind_lvl;

			// recurse into.
			Insert( ind_lvl+1, it_new_parent, lst_src, lst_dst );

			it_src=lst_src.begin(); // again from start after recursion into.

		// found no child for the specified parent.
		} else
			++it_src;
	}
}

void CForum2::SortHeaders()
{
	EmptyHeaders();	// clear the destination.

	hdr_lst_t& lst_src = m_TmpHeaders;
	hdr_lst_t& lst_dst = m_Headers;

	hdr_lst_t::const_iterator it_src=lst_src.begin();
	hdr_lst_t::iterator       it_dst=lst_dst.begin();

	Insert( 0/*ind_lvl*/, it_dst, lst_src, lst_dst );
}

STDMETHODIMP CForum2::get_EndOfList(BOOL *pVal)
{
	*pVal = m_HdrPos==m_Headers.end()?VB_TRUE:VB_FALSE;
	return S_OK;
}

STDMETHODIMP CForum2::get_BeginOfList(BOOL *pVal)
{
	*pVal = m_HdrPos==m_Headers.begin()?VB_TRUE:VB_FALSE;
	return S_OK;
}

STDMETHODIMP CForum2::MoveNext()
{
	/*
	const bool from_top = (m_HdrPos==m_Headers.begin() || m_HdrPos==m_Headers.end());

	// just about entering a thread.
	// go to LAST 
	if ( from_top ) {
		// seek next top-level.
		int distance = 0;
		hdr_lst_t::iterator it_tmp = m_HdrPos;

		while ( it_tmp->

	// allready inside a thread.
	} else {
		--m_HdrPos;
	}
	*/

	++m_HdrPos;
	return S_OK;
}

STDMETHODIMP CForum2::get_GetCurID(long *pVal)
{
	*pVal=(*m_HdrPos)->m_ID;
	return S_OK;
}

STDMETHODIMP CForum2::get_GetCurIndentLevel(long *pVal)
{
	*pVal=(*m_HdrPos)->m_IndentLevel;

	return S_OK;
}

STDMETHODIMP CForum2::get_GetCurArticleCount(long *pVal)
{
	try {
		if ( m_HdrPos==m_Headers.end() )
			throw Xept( "readpointer is behind end of list" );
		if ( m_Headers.empty() )
			throw Xept( "headerlist is empty" );

		hdr_lst_t::const_iterator it=m_HdrPos;

		// a list of all parents that are valid.
		std::set<long> parent_ids;
		parent_ids.insert((*m_HdrPos)->m_ID);

		// count until I reach a parent that is not valid.
		int cnt=0;
		do {
			parent_ids.insert((*it)->m_ID);

			++cnt;
			++it;
		} while ( it!=m_Headers.end() && parent_ids.find((*it)->m_ParentID)!=parent_ids.end() );

		*pVal=cnt;

	} catch ( Xept &e ) {
		return CATCH_AND_LOG_XEPT( e );
	} catch ( ... ) {
		return CATCH_AND_LOG_UNKNOWN_XEPT();
	}

	return S_OK;

	/*
	try {
		if ( m_HdrPos==m_Headers.end() )
			throw Xept( "readpointer is behind end of list" );
		if ( m_Headers.empty() )
			throw Xept( "headerlist is empty" );

		const long start_parent_id=(*m_HdrPos)->m_ParentID;
		hdr_lst_t::const_iterator it=m_HdrPos;

		// count until I reach the next in the same level entry or the end.
		int cnt=0;
		do {
			++cnt;
			++it;

		} while ( it!=m_Headers.end() && (*it)->m_ParentID!=start_parent_id );

		*pVal=cnt;

	} catch ( Xept &e ) {
		return CATCH_AND_LOG_XEPT( e );
	} catch ( ... ) {
		return CATCH_AND_LOG_UNKNOWN_XEPT();
	}

	return S_OK;
	*/
}

void CForum2::EmptyIDs()
{
	m_IDs.clear();
}

void CForum2::RemoveId( const long id )
{
	HIER;
}

bool CForum2::IdExists( const long id ) const
{
	return m_IDs.find(id)!=m_IDs.end();
}

CForum2::hdr_lst_t::const_iterator CForum2::GetIteratorByID( const long id ) const
{
	hdr_lst_t::const_iterator it=m_Headers.begin();

	while ( it!=m_Headers.end() ) {
		if ( (*it)->m_ID==id )
			break;

		++it;
	}

	return it;
}

STDMETHODIMP CForum2::put_ForumID(long newVal)
{
	m_ForumID = newVal;

	return S_OK;
}

STDMETHODIMP CForum2::get_FilterStartDate(BSTR *pVal)
{
	*pVal = _bstr_t(m_FilterStartDate.c_str()).copy();

	return S_OK;
}

STDMETHODIMP CForum2::put_FilterStartDate(BSTR newVal)
{
	if ( lstrlen((LPCTSTR)_bstr_t(newVal))==0 )
		return S_OK;

	m_FilterStartDate = (LPCTSTR)_bstr_t(newVal);

	return S_OK;
}

STDMETHODIMP CForum2::put_FilterKeywords(BSTR newVal)
{
	m_FilterKeywords = (LPCTSTR)_bstr_t(newVal);

	return S_OK;
}

STDMETHODIMP CForum2::get_FilterKeywords(BSTR *pVal)
{
	*pVal = _bstr_t(m_FilterKeywords.c_str()).copy();

	return S_OK;
}

STDMETHODIMP CForum2::get_FilterEndDate(BSTR *pVal)
{
	*pVal = _bstr_t(m_FilterEndDate.c_str()).copy();

	return S_OK;
}

STDMETHODIMP CForum2::put_FilterEndDate(BSTR newVal)
{
	if ( lstrlen((LPCTSTR)_bstr_t(newVal))==0 )
		return S_OK;

	m_FilterEndDate = (LPCTSTR)_bstr_t(newVal);

	return S_OK;
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

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::put_DbConnStr(BSTR newVal)
{
	m_ConnStr = (LPCTSTR)_bstr_t(newVal);

	return S_OK;
}

STDMETHODIMP CForum2::put_DbID(BSTR newVal)
{
	m_ID = (LPCTSTR)_bstr_t(newVal);

	return S_OK;
}

STDMETHODIMP CForum2::put_DbPW(BSTR newVal)
{
	m_PW = (LPCTSTR)_bstr_t(newVal);

	return S_OK;
}

STDMETHODIMP CForum2::get_Value(BSTR name, VARIANT *pVal)
{
	ADODB::_ConnectionPtr	conn;
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
	ADODB::_ConnectionPtr	conn;
	try {
		m_Map[std::_tstring(_bstr_t(name))] = _bstr_t(newVal);
		m_MapModified = true;

	} CATCH_AND_RET();

	return S_OK;
}

STDMETHODIMP CForum2::FromUrl(BSTR url)
{
	ADODB::_ConnectionPtr	conn;
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

STDMETHODIMP CForum2::get_ToUrl(BSTR *pVal)
{
	ADODB::_ConnectionPtr	conn;
	_bstr_t ret;

	try {
		ret = ToUrl().c_str();

	} CATCH_AND_RET();

	*pVal = ret.copy();

	return S_OK;
}

STDMETHODIMP CForum2::get_ToUrlValue(BSTR name, VARIANT newVal, BSTR *pVal)
{
	ADODB::_ConnectionPtr	conn;
	_bstr_t ret;

	try {
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

	} CATCH_AND_RET();

	*pVal = ret.copy();

	return S_OK;
}

STDMETHODIMP CForum2::get_ToUrlValue2(BSTR name1, VARIANT value1, BSTR name2, VARIANT value2, BSTR *pVal)
{
	ADODB::_ConnectionPtr	conn;
	_bstr_t ret;

	try {
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

	} CATCH_AND_RET();

	*pVal = ret.copy();

	return S_OK;
}

STDMETHODIMP CForum2::get_DebugMode(long *pVal)
{
	*pVal = m_DebugMode;

	return S_OK;
}

STDMETHODIMP CForum2::put_DebugMode(long newVal)
{
	m_DebugMode = newVal;

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
