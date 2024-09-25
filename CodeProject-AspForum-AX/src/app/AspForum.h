/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed May 17 16:20:35 2000
 */
/* Compiler settings for C:\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\src\app\AspForum.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AspForum_h__
#define __AspForum_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IForum2_FWD_DEFINED__
#define __IForum2_FWD_DEFINED__
typedef interface IForum2 IForum2;
#endif 	/* __IForum2_FWD_DEFINED__ */


#ifndef ___IForum2Events_FWD_DEFINED__
#define ___IForum2Events_FWD_DEFINED__
typedef interface _IForum2Events _IForum2Events;
#endif 	/* ___IForum2Events_FWD_DEFINED__ */


#ifndef __Forum2_FWD_DEFINED__
#define __Forum2_FWD_DEFINED__

#ifdef __cplusplus
typedef class Forum2 Forum2;
#else
typedef struct Forum2 Forum2;
#endif /* __cplusplus */

#endif 	/* __Forum2_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IForum2_INTERFACE_DEFINED__
#define __IForum2_INTERFACE_DEFINED__

/* interface IForum2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IForum2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9BEA98F0-BAD6-11D3-A5C1-00105AEFABBE")
    IForum2 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadArticles( 
            BSTR conn_str,
            BSTR id,
            BSTR pw) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EndOfList( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BeginOfList( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveNext( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetCurID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetCurIndentLevel( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ForumID( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FilterStartDate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FilterStartDate( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FilterEndDate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FilterEndDate( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteID( 
            long id,
            BOOL single) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DbConnStr( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DbID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DbPW( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            BSTR name,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            BSTR name,
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FromUrl( 
            BSTR url) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ToUrl( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ToUrlValue( 
            BSTR name,
            VARIANT newVal,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ToUrlValue2( 
            BSTR name1,
            VARIANT value1,
            BSTR name2,
            VARIANT value2,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FilterKeywords( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FilterKeywords( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DebugMode( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DebugMode( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RetrieveCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RetrieveCount( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RetrieveStart( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RetrieveStart( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IForum2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IForum2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IForum2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IForum2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadArticles )( 
            IForum2 __RPC_FAR * This,
            BSTR conn_str,
            BSTR id,
            BSTR pw);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EndOfList )( 
            IForum2 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BeginOfList )( 
            IForum2 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveNext )( 
            IForum2 __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetCurID )( 
            IForum2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetCurIndentLevel )( 
            IForum2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ForumID )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FilterStartDate )( 
            IForum2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FilterStartDate )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FilterEndDate )( 
            IForum2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FilterEndDate )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteID )( 
            IForum2 __RPC_FAR * This,
            long id,
            BOOL single);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DbConnStr )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DbID )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DbPW )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IForum2 __RPC_FAR * This,
            BSTR name,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            IForum2 __RPC_FAR * This,
            BSTR name,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FromUrl )( 
            IForum2 __RPC_FAR * This,
            BSTR url);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ToUrl )( 
            IForum2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ToUrlValue )( 
            IForum2 __RPC_FAR * This,
            BSTR name,
            VARIANT newVal,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ToUrlValue2 )( 
            IForum2 __RPC_FAR * This,
            BSTR name1,
            VARIANT value1,
            BSTR name2,
            VARIANT value2,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FilterKeywords )( 
            IForum2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FilterKeywords )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DebugMode )( 
            IForum2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DebugMode )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RetrieveCount )( 
            IForum2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RetrieveCount )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RetrieveStart )( 
            IForum2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RetrieveStart )( 
            IForum2 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IForum2Vtbl;

    interface IForum2
    {
        CONST_VTBL struct IForum2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IForum2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IForum2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IForum2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IForum2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IForum2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IForum2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IForum2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IForum2_ReadArticles(This,conn_str,id,pw)	\
    (This)->lpVtbl -> ReadArticles(This,conn_str,id,pw)

#define IForum2_get_EndOfList(This,pVal)	\
    (This)->lpVtbl -> get_EndOfList(This,pVal)

#define IForum2_get_BeginOfList(This,pVal)	\
    (This)->lpVtbl -> get_BeginOfList(This,pVal)

#define IForum2_MoveNext(This)	\
    (This)->lpVtbl -> MoveNext(This)

#define IForum2_get_GetCurID(This,pVal)	\
    (This)->lpVtbl -> get_GetCurID(This,pVal)

#define IForum2_get_GetCurIndentLevel(This,pVal)	\
    (This)->lpVtbl -> get_GetCurIndentLevel(This,pVal)

#define IForum2_put_ForumID(This,newVal)	\
    (This)->lpVtbl -> put_ForumID(This,newVal)

#define IForum2_get_FilterStartDate(This,pVal)	\
    (This)->lpVtbl -> get_FilterStartDate(This,pVal)

#define IForum2_put_FilterStartDate(This,newVal)	\
    (This)->lpVtbl -> put_FilterStartDate(This,newVal)

#define IForum2_get_FilterEndDate(This,pVal)	\
    (This)->lpVtbl -> get_FilterEndDate(This,pVal)

#define IForum2_put_FilterEndDate(This,newVal)	\
    (This)->lpVtbl -> put_FilterEndDate(This,newVal)

#define IForum2_DeleteID(This,id,single)	\
    (This)->lpVtbl -> DeleteID(This,id,single)

#define IForum2_put_DbConnStr(This,newVal)	\
    (This)->lpVtbl -> put_DbConnStr(This,newVal)

#define IForum2_put_DbID(This,newVal)	\
    (This)->lpVtbl -> put_DbID(This,newVal)

#define IForum2_put_DbPW(This,newVal)	\
    (This)->lpVtbl -> put_DbPW(This,newVal)

#define IForum2_get_Value(This,name,pVal)	\
    (This)->lpVtbl -> get_Value(This,name,pVal)

#define IForum2_put_Value(This,name,newVal)	\
    (This)->lpVtbl -> put_Value(This,name,newVal)

#define IForum2_FromUrl(This,url)	\
    (This)->lpVtbl -> FromUrl(This,url)

#define IForum2_get_ToUrl(This,pVal)	\
    (This)->lpVtbl -> get_ToUrl(This,pVal)

#define IForum2_get_ToUrlValue(This,name,newVal,pVal)	\
    (This)->lpVtbl -> get_ToUrlValue(This,name,newVal,pVal)

#define IForum2_get_ToUrlValue2(This,name1,value1,name2,value2,pVal)	\
    (This)->lpVtbl -> get_ToUrlValue2(This,name1,value1,name2,value2,pVal)

#define IForum2_get_FilterKeywords(This,pVal)	\
    (This)->lpVtbl -> get_FilterKeywords(This,pVal)

#define IForum2_put_FilterKeywords(This,newVal)	\
    (This)->lpVtbl -> put_FilterKeywords(This,newVal)

#define IForum2_get_DebugMode(This,pVal)	\
    (This)->lpVtbl -> get_DebugMode(This,pVal)

#define IForum2_put_DebugMode(This,newVal)	\
    (This)->lpVtbl -> put_DebugMode(This,newVal)

#define IForum2_get_RetrieveCount(This,pVal)	\
    (This)->lpVtbl -> get_RetrieveCount(This,pVal)

#define IForum2_put_RetrieveCount(This,newVal)	\
    (This)->lpVtbl -> put_RetrieveCount(This,newVal)

#define IForum2_get_RetrieveStart(This,pVal)	\
    (This)->lpVtbl -> get_RetrieveStart(This,pVal)

#define IForum2_put_RetrieveStart(This,newVal)	\
    (This)->lpVtbl -> put_RetrieveStart(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IForum2_ReadArticles_Proxy( 
    IForum2 __RPC_FAR * This,
    BSTR conn_str,
    BSTR id,
    BSTR pw);


void __RPC_STUB IForum2_ReadArticles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_EndOfList_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_EndOfList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_BeginOfList_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_BeginOfList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IForum2_MoveNext_Proxy( 
    IForum2 __RPC_FAR * This);


void __RPC_STUB IForum2_MoveNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_GetCurID_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_GetCurID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_GetCurIndentLevel_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_GetCurIndentLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IForum2_put_ForumID_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IForum2_put_ForumID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_FilterStartDate_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_FilterStartDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IForum2_put_FilterStartDate_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IForum2_put_FilterStartDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_FilterEndDate_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_FilterEndDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IForum2_put_FilterEndDate_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IForum2_put_FilterEndDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IForum2_DeleteID_Proxy( 
    IForum2 __RPC_FAR * This,
    long id,
    BOOL single);


void __RPC_STUB IForum2_DeleteID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IForum2_put_DbConnStr_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IForum2_put_DbConnStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IForum2_put_DbID_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IForum2_put_DbID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IForum2_put_DbPW_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IForum2_put_DbPW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_Value_Proxy( 
    IForum2 __RPC_FAR * This,
    BSTR name,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IForum2_put_Value_Proxy( 
    IForum2 __RPC_FAR * This,
    BSTR name,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IForum2_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IForum2_FromUrl_Proxy( 
    IForum2 __RPC_FAR * This,
    BSTR url);


void __RPC_STUB IForum2_FromUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_ToUrl_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_ToUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_ToUrlValue_Proxy( 
    IForum2 __RPC_FAR * This,
    BSTR name,
    VARIANT newVal,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_ToUrlValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_ToUrlValue2_Proxy( 
    IForum2 __RPC_FAR * This,
    BSTR name1,
    VARIANT value1,
    BSTR name2,
    VARIANT value2,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_ToUrlValue2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_FilterKeywords_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_FilterKeywords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IForum2_put_FilterKeywords_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IForum2_put_FilterKeywords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_DebugMode_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_DebugMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IForum2_put_DebugMode_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IForum2_put_DebugMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_RetrieveCount_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_RetrieveCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IForum2_put_RetrieveCount_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IForum2_put_RetrieveCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IForum2_get_RetrieveStart_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IForum2_get_RetrieveStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IForum2_put_RetrieveStart_Proxy( 
    IForum2 __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IForum2_put_RetrieveStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IForum2_INTERFACE_DEFINED__ */



#ifndef __ASPFORUMLib_LIBRARY_DEFINED__
#define __ASPFORUMLib_LIBRARY_DEFINED__

/* library ASPFORUMLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ASPFORUMLib;

#ifndef ___IForum2Events_DISPINTERFACE_DEFINED__
#define ___IForum2Events_DISPINTERFACE_DEFINED__

/* dispinterface _IForum2Events */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IForum2Events;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("9BEA98F2-BAD6-11D3-A5C1-00105AEFABBE")
    _IForum2Events : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IForum2EventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IForum2Events __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IForum2Events __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IForum2Events __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IForum2Events __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IForum2Events __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IForum2Events __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IForum2Events __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IForum2EventsVtbl;

    interface _IForum2Events
    {
        CONST_VTBL struct _IForum2EventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IForum2Events_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IForum2Events_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IForum2Events_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IForum2Events_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IForum2Events_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IForum2Events_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IForum2Events_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IForum2Events_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Forum2;

#ifdef __cplusplus

class DECLSPEC_UUID("9BEA98F1-BAD6-11D3-A5C1-00105AEFABBE")
Forum2;
#endif
#endif /* __ASPFORUMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
