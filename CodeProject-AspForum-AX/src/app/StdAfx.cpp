//  stdafx.cpp : Quelltextdatei, die nur die Standard-Includes einbindet
//  stdafx.pch ist der vorcompilierte Header
//  stdafx.obj enthält die vorcompilierte Typinformation

#include "stdafx.h"

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#include <atlimpl.cpp>

#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif


