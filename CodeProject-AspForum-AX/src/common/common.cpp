// ###########################################################################
// #
// # file:
// #	Common.cpp
// #
// ###########################################################################

#include "stdafx.h"
#pragma warning(disable:4786)
#include "common.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////////
// com helpers.

CoInit::CoInit()
{
	const HRESULT hr = ::CoInitialize( 0 );
	if ( FAILED( hr ) )
		ThrowComError( hr );
}

CoInit::~CoInit()
{
	CoUninitialize();
}


//////////////////////////////////////////////////////////////////////////////
// misc functions.

std::_tstring Format( LPCTSTR txt, ... )
{
	va_list lst;
	va_start( lst, txt );

	enum { bufsize=10000 };
	TCHAR buf[bufsize];
	memset( buf, 0, sizeof buf );
	vsprintf( buf, txt, lst );

	va_end( lst );
	return buf;
}


//////////////////////////////////////////////////////////////////////////////
// file functions.

bool FileExists( LPCTSTR filename )
{
	const DWORD result=GetFileAttributes( filename );
	return (result&FILE_ATTRIBUTE_DIRECTORY)==0 && result!=0xFFFFFFFF;
}

bool DirExists( LPCTSTR directoryname )
{
	const DWORD result=GetFileAttributes( directoryname );
	return (result&FILE_ATTRIBUTE_DIRECTORY)!=0 && result!=0xFFFFFFFF;
}


//////////////////////////////////////////////////////////////////////////////