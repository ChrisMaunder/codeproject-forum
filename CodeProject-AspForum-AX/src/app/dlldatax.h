// ###########################################################################
// #
// # file:
// #	dlldatax.h
// #
// # remarks:
// #	copyright © 1999, 2000 zeta software GbR.
// #
// # history:
// #	1999-12-25 Uwe Keim		file created.
// #
// ###########################################################################

#ifndef __DLLDATAX_H__
#define __DLLDATAX_H__


//////////////////////////////////////////////////////////////////////////////
// .

#ifdef _MERGE_PROXYSTUB

	extern "C" {
		BOOL WINAPI PrxDllMain(HINSTANCE hInstance, DWORD dwReason, 
			LPVOID lpReserved);
		STDAPI PrxDllCanUnloadNow(void);
		STDAPI PrxDllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
		STDAPI PrxDllRegisterServer(void);
		STDAPI PrxDllUnregisterServer(void);
	}

#endif


//////////////////////////////////////////////////////////////////////////////

#endif