// ###########################################################################
// #
// # file:
// #	forum2.h
// #
// # remarks:
// #	copyright © 1999, 2000 zeta software GbR.
// #
// # history:
// #	2000-01-02 Uwe Keim		removed anchors from urls in FromUrl().
// #	1999-12-25 Uwe Keim		file created.
// #
// ###########################################################################

#ifndef __FORUM2_H__
#define __FORUM2_H__

#include "resource.h"
#include "aspforum.h"
#include "..\common\tree.h"

#include <map>


//////////////////////////////////////////////////////////////////////////////
// forum helpers.

// for use with the property "DebugMode".
enum {
	DEBUG_MODE_OFF = 0,
	DEBUG_MODE_ON  = 1
};


//////////////////////////////////////////////////////////////////////////////
// the forum class.

class ATL_NO_VTABLE CForum2 : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CForum2, &CLSID_Forum2>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CForum2>,
	public IDispatchImpl<IForum2, &IID_IForum2, &LIBID_ASPFORUMLib> {
public:
	CForum2();
	~CForum2();

	DECLARE_REGISTRY_RESOURCEID(IDR_FORUM2)
	DECLARE_GET_CONTROLLING_UNKNOWN()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CForum2)
		COM_INTERFACE_ENTRY(IForum2)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	END_COM_MAP()
	BEGIN_CONNECTION_POINT_MAP(CForum2)
	END_CONNECTION_POINT_MAP()

	HRESULT FinalConstruct() {
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease() {
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	// the interface.
public:
	STDMETHOD(get_DebugMode)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_DebugMode)(/*[in]*/ long newVal);
	STDMETHOD(get_FilterKeywords)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FilterKeywords)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ToUrlValue2)(BSTR name1, VARIANT value1, BSTR name2, VARIANT value2, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ToUrlValue)(BSTR name, VARIANT newVal, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ToUrl)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(FromUrl)(BSTR url);
	STDMETHOD(get_Value)(BSTR name, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Value)(BSTR name, /*[in]*/ VARIANT newVal);

	STDMETHOD(put_DbPW)(/*[in]*/ BSTR newVal);
	STDMETHOD(put_DbID)(/*[in]*/ BSTR newVal);
	STDMETHOD(put_DbConnStr)(/*[in]*/ BSTR newVal);
	STDMETHOD(DeleteID)(long id, BOOL single);
	STDMETHOD(get_FilterEndDate)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FilterEndDate)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_FilterStartDate)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FilterStartDate)(/*[in]*/ BSTR newVal);
	STDMETHOD(put_ForumID)(/*[in]*/ long newVal);
	STDMETHOD(get_GetCurIndentLevel)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_GetCurID)(/*[out, retval]*/ long *pVal);
	STDMETHOD(MoveNext)();
	STDMETHOD(get_BeginOfList)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_EndOfList)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(ReadArticles)(BSTR conn_str, BSTR id, BSTR pw);
	STDMETHOD(get_RetrieveCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_RetrieveCount)(/*[in]*/ long newVal);
	STDMETHOD(get_RetrieveStart)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_RetrieveStart)(/*[in]*/ long newVal);

public:
	struct Header : public tree::node_data {
		long	m_ID;
		long	m_ParentID;

		double	m_Date;

		long	m_IndentLevel;
	};

	typedef std::list<Header*>						hdr_lst_t;
	hdr_lst_t										m_Headers;				// unordered by list order.
	hdr_lst_t::iterator								m_HeaderPos;

	tree											m_Tree;					// ordered structure.

	long											m_ForumID;
	std::_tstring									m_FilterStartDate;		// in english format.
	std::_tstring									m_FilterEndDate;
	std::_tstring									m_FilterKeywords;
								                
	std::_tstring									m_ConnStr;
	std::_tstring									m_ID;
	std::_tstring									m_PW;

	typedef std::map<long,Header*>					ids_t;
	ids_t											m_IDs;					// lookup for id's.

	typedef std::map<std::_tstring,_variant_t>		map_string_to_variant_t;
	map_string_to_variant_t							m_Map;					// (name|value)-pairs.
	bool											m_MapModified;			// whether new values are inserted
																			// since the last call to ToUrl().
	std::_tstring									m_MapUrl;				// the last result from ToUrl().

	int												m_DebugMode;			// DEBUG_MODE_OFF or DEBUG_MODE_ON.
	long											m_RetrieveStart;		// 0 for first.
	long											m_RetrieveCount;		// 0 for unlimited.

	void EmptyAll();														// clears the list.

	tree::node *InsertTreeChild( tree::node *const parent, Header *const child );
	void InsertTree( tree::node *const parent, const long ind_lvl );
	void InsertList();

	hdr_lst_t::iterator FindHeaderWithParent( const long parent_id );
	hdr_lst_t::iterator FindHeaderWithNoParent();

	std::_tstring ToUrl();

	bool IdExists( const long id ) const;
	void HelpDeleteBranch( 
		ADODB::_ConnectionPtr conn, const long id );

	std::_tstring GetSqlWhereString() const;
};


//////////////////////////////////////////////////////////////////////////////

#endif