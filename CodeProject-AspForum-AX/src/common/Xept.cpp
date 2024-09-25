// ###########################################################################
// #
// # file:
// #	Xept.cpp
// #
// ###########################################################################

#include "stdafx.h"
#pragma warning(disable:4786)
#include "xept.h"
#include "error.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static TCHAR THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////////
// base exception class.

Xept::Xept() :
	m_Value(0),
	m_Severity(0),
	m_LastError(::GetLastError())
{
}

Xept::Xept( const TCHAR *const text, ... ) :
	m_Value(0),
	m_Severity(0),
	m_LastError(::GetLastError())
{
	XEPT_FMT();
}

std::_tstring Xept::Whole()
{
	std::_tstring last_error;
	const std::_tstring last_error_msg=::GetLastErrorMsg( m_LastError );
	if ( !last_error_msg.empty() )
		last_error = std::_tstring(_T(" ("))+last_error_msg+std::_tstring(_T(")"));
	//last_error.replace( _T("\r"), _T("") );
	//last_error.replace( _T("\n"), _T("") );

	return m_Text+last_error;
}

void Xept::Fmt( const TCHAR *const text, va_list arg_list )
{
	enum { bufsize=10000 };
	TCHAR buf[bufsize];
	memset( buf, 0, sizeof buf );
	vsprintf( buf, text, arg_list );
	va_end( arg_list );

	m_Text = buf;
}


//////////////////////////////////////////////////////////////////////////////