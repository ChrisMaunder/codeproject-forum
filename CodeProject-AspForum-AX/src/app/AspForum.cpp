// ###########################################################################
// #
// # file:
// #	AspForum.cpp
// #
// ###########################################################################


//////////////////////////////////////////////////////////////////////////////
// Implementierung der DLL-Exporte.

// Hinweis: Proxy/Stub-Information
//      Zur Aufnahme des Proxy/Stub-Codes in die Objekt-DLL fügen Sie die Datei 
//      dlldatax.c dem Projekt hinzu.  Stellen Sie sicher, dass vorcompilierte Header 
//      für diese Datei deaktiviert sind und fügen Sie _MERGE_PROXYSTUB zu 
//      den Projektdefinitionen hinzu.  
//
//      Wenn Sie WinNT4.0 oder Win95 nicht mit DCOM ausführen,
//      müssen Sie die folgende define-Anweisung aus dlldatax.c entfernen.
//      #define _WIN32_WINNT 0x0400
//
//      Wenn Sie darüber hinaus MIDL ohne den Schalter /Oicf ausführen, 
//      müssen Sie auch die folgende define-Anweisung aus dlldatax.c entfernen.
//      #define USE_STUBLESS_PROXY
//
//      Ändern Sie die benutzerspezifische Build-Regel für zeta_forum_asp.idl durch Hinzufügen 
//      folgender Dateien.
//          zeta_forum_asp_p.c
//          dlldata.c
//      Um eine eigene Proxy/Stub-DLL zu erstellen, 
//      führen Sie nmake -f zeta_forum_aspps.mk im Projektverzeichnis aus.

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
// Liefert eine Klassenfabrik zurück, um ein Objekt des angeforderten Typs anzulegen

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
    if (PrxDllGetClassObject(rclsid, riid, ppv)==S_OK)
        return S_OK;
#endif
    return _Module.GetClassObject(rclsid, riid, ppv);
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Fügt der Systemregistrierung Einträge hinzu

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
// DllUnregisterServer - Entfernt Einträge aus der Systemregistrierung

STDAPI DllUnregisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
    PrxDllUnregisterServer();
#endif
    return _Module.UnregisterServer(true);
}


//////////////////////////////////////////////////////////////////////////////