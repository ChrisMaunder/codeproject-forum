// ###########################################################################
// #
// # file:
// #	StdAfx.h
// #
// # history:
// #	1999-12-25 Uwe Keim		file created.
// #
// ###########################################################################

#ifndef __STDAFX_H__
#define __STDAFX_H__


//////////////////////////////////////////////////////////////////////////////
// includes and defines.

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

/*
#pragma warning(disable:4786)
#define VC_EXTRALEAN
#include <afxwin.h>
*/
#define DEBUG_NEW new

#include <atlbase.h>
// Sie können eine Klasse von CComModule ableiten und diese verwenden, 
// um etwas zu überschreiben,
// Sie sollten jedoch den Namen von _Module nicht ändern
extern CComModule _Module;
#include <atlcom.h>

#include <comdef.h>

// Include ADO Interface/Class Descriptions (ADO 1.0 Version)
// #import "msado10.dll" /*rename( "EOF", "adoEOF" )*/
// Include ADO Interface/Class Descriptions (ADO 1.5 Version)
#pragma warning(disable:4146)
#import "msado15.dll" rename( "EOF", "adoEOF" )
#pragma warning(default:4146)

#include <memory>
#include <algorithm>
#include <string>
#include <list>
#include <set>

#include "..\common\xept.h"
#include "..\common\error.h"
#include "..\common\logging.h"
#include "..\common\common.h"

#include "..\foreign\hightime.h"

#include "wininet.h"
#pragma comment( lib, "wininet.lib" )


//////////////////////////////////////////////////////////////////////////////
// constants.

enum { 
	VB_TRUE		= (-1),
	VB_FALSE	= 0
};


//////////////////////////////////////////////////////////////////////////////


#endif