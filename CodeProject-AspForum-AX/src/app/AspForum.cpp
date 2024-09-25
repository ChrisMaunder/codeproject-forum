// ###########################################################################
// #
// # file:
// #	AspForum.cpp
// #
// ###########################################################################


//////////////////////////////////////////////////////////////////////////////
// Implementierung der DLL-Exporte.

// Hinweis: Proxy/Stub-Information
//      Zur Aufnahme des Proxy/Stub-Codes in die Objekt-DLL f�gen Sie die Datei 
//      dlldatax.c dem Projekt hinzu.  Stellen Sie sicher, dass vorcompilierte Header 
//      f�r diese Datei deaktiviert sind und f�gen Sie _MERGE_PROXYSTUB zu 
//      den Projektdefinitionen hinzu.  
//
//      Wenn Sie WinNT4.0 oder Win95 nicht mit DCOM ausf�hren,
//      m�ssen Sie die folgende define-Anweisung aus dlldatax.c entfernen.
//      #define _WIN32_WINNT 0x0400
//
//      Wenn Sie dar�ber hinaus MIDL ohne den Schalter /Oicf ausf�hren, 
//      m�ssen Sie auch die folgende define-Anweisung aus dlldatax.c entfernen.
//      #define USE_STUBLESS_PROXY
//
//      �ndern Sie die benutzerspezifische Build-Regel f�r zeta_forum_asp.idl durch Hinzuf�gen 
//      folgender Dateien.
//          zeta_forum_asp_p.c
//          dlldata.c
//      Um eine eigene Proxy/Stub-DLL zu erstellen, 
//      f�hren Sie nmake -f zeta_forum_aspps.mk im Projektverzeichnis aus.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "AspForum.h"
#include "dlldatax.h"

#include "AspForum_i.c"
#include "Forum2.h"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_Forum2, CForum2)
END_OBJECT_MAP()

#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// DLL-Einsprungpunkt

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    lpReserved;
#ifdef _MERGE_PROXYSTUB
    if (!PrxDllMain(hInstance, dwReason, lpReserved))
        return false;
#endif
    if (dwReason==DLL_PROCESS_ATTACH) {
        _Module.Init(ObjectMap, hInstance, &LIBID_ASPFORUMLib);
        DisableThreadLibraryCalls(hInstance);

		::CoInitialize( 0 );

		LOGSET_LVL( r3 );
		LOGSET_FILENAME( (GetModuleDir()+std::_tstring(_T("zeta_forum_asp.log"))).c_str() );
		LOGSET_DST( LOGGET_DST()|file );

    } else if (dwReason==DLL_PROCESS_DETACH) {
		::CoUninitialize();

        _Module.Term();
	}

    return true;
}


/////////////////////////////////////////////////////////////////////////////
// Verwendet, um zu entscheiden, ob die DLL von OLE aus dem Speicher entfernt werden kann

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
    if (PrxDllCanUnloadNow()!=S_OK)
        return S_FALSE;
#endif
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// Liefert eine Klassenfabrik zur�ck, um ein Objekt des angeforderten Typs anzulegen

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
    if (PrxDllGetClassObject(rclsid, riid, ppv)==S_OK)
        return S_OK;
#endif
    return _Module.GetClassObject(rclsid, riid, ppv);
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - F�gt der Systemregistrierung Eintr�ge hinzu

STDAPI DllRegisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
    HRESULT hRes = PrxDllRegisterServer();
    if (FAILED(hRes))
        return hRes;
#endif
    // Registriert Objekt, Typelib und alle Schnittstellen in Typelib
    return _Module.RegisterServer(true);
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Entfernt Eintr�ge aus der Systemregistrierung

STDAPI DllUnregisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
    PrxDllUnregisterServer();
#endif
    return _Module.UnregisterServer(true);
}


//////////////////////////////////////////////////////////////////////////////