// ###########################################################################
// #
// # file:
// #	Logging.cpp
// #
// ###########################################################################

#include "stdafx.h"
#pragma warning(disable:4786)
#include <string>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include "logging.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////////
// additional helper functions.

std::_tstring GetWindowsDirectory()
{
	TCHAR buf[MAX_PATH+1];
	if ( GetWindowsDirectory( buf, MAX_PATH )==0 )
		throw Xept( _T("error retrieving windows directory") );
	std::_tstring dir( buf );

	if ( dir.length()>0 && dir[dir.length()-1]!=_T('\\') )
		dir += _T('\\');
	return dir;
}

std::_tstring GetWindowsDrive()
{
	enum { size=1000 };
	TCHAR buf[size];
	if ( GetWindowsDirectory( buf, size-1 ) ) {
		TCHAR drive[size];
		_splitpath( buf, drive, 0, 0, 0 );

		std::_tstring drv( drive );
		if ( drv.length()>0 && drv[drv.length()-1]!=_T('\\') )
			drv += _T('\\');
		return drv;

	} else
		return _T("");
}

std::_tstring GetModuleFilename()
{
	TCHAR buf[MAX_PATH];
	const DWORD result=GetModuleFileName( 
		GetModuleHandle(0), buf, sizeof buf );
	if ( result==0 )
		throw Xept( _T("error retrieving module filename") );
	return buf;
}

std::_tstring GetModuleDir()
{
	TCHAR drive[MAX_PATH];
	TCHAR dir[MAX_PATH];
	_tsplitpath( GetModuleFilename().c_str(), drive, dir, 0, 0 );

	std::_tstring str( std::_tstring(drive)+std::_tstring(dir) );
	if ( str.length()>0 && str[str.length()-1]!=_T('\\') )
		str += _T('\\');
	return str;
}


//////////////////////////////////////////////////////////////////////////////
// internal logging variables/routines.

#pragma warning( disable:4073 )
#pragma init_seg( lib )
#pragma warning( default:4073 )

#if defined( LOGGING )

class LogHelper {
public:
	LogHelper();
	~LogHelper();

public:
	LOGLVL				m_LogLvl;
	int					m_LogDst;

	USERDEF_LOG_FUNC	*m_LogFunc;

	enum				{ LOG_FN_SIZE=1000 };
	TCHAR				LogFileName[ LOG_FN_SIZE+1 ];

	bool				m_Console;
};

LogHelper g_LogHlp;

LogHelper::LogHelper() :
	m_LogLvl(d3),
	m_LogDst(debugger),
	m_LogFunc(0),
	m_Console(false)
{
	memset( LogFileName, 0, sizeof LogFileName );

	// set a default log-filename.
	enum { size=1000 };
	TCHAR buf[size];
	if ( GetWindowsDirectory( buf, size-1 ) ) {
		TCHAR drive[size];
		_splitpath( buf, drive, 0, 0, 0 );
		std::string name = drive;
		if ( name.size()>0 && 
			name[name.size()-1]!=_T('\\') )
			name += _T('\\');
		name += _T("log.txt");

		strncpy( LogFileName, name.c_str(), LOG_FN_SIZE );
	}
}

LogHelper::~LogHelper()
{
	if ( m_Console )
		FreeConsole();
}

void LogToFile( const TCHAR *text )
{
	static bool inlog=false;	// single entry!
	if ( inlog ) return;
	inlog=true;

	try {
		FILE *file=fopen( g_LogHlp.LogFileName, _T("a") );
		if ( file ) {
			static bool first=true;
			if ( first ) {
				first=false;
				_ftprintf( file, _T("\n\n") );
				_ftprintf( file, _T("----------------------------------"
					"--------------------------\n") );
				TCHAR tmpbuf[200];
				_strdate( tmpbuf );
				_ftprintf( file, _T("%s, "), tmpbuf );
				_strtime( tmpbuf );    
				_ftprintf( file, _T("%s\n"), tmpbuf );
			}

			_ftprintf( file, text );
			fclose( file );
		}

	} catch ( ... ) {
		// no exceptions during logging!
	}

	inlog=false;
}

void LogToConsole( const TCHAR *text )
{
	static bool inlog=false;	// single entry!
	if ( inlog ) return;
	inlog=true;

	try {
		if ( !g_LogHlp.m_Console ) {
			g_LogHlp.m_Console = AllocConsole()!=0;
			_tfreopen( _T("CONOUT$"), _T("a"), stdout );
		}

		const int result = _ftprintf( stdout, text );

	} catch ( ... ) {
		// no exceptions during logging!
	}

	inlog=false;
}

void LogToDebugger( const TCHAR *text )
{
	static bool inlog=false;	// single entry!
	if ( inlog ) return;
	inlog=true;

	try {
		OutputDebugString( text );

	} catch ( ... ) {
		// no exceptions during logging!
	}

	inlog=false;
}

void LogToMsgBox( const TCHAR *text )
{
	static bool inlog=false;	// single entry!
	if ( inlog ) return;
	inlog=true;

	try {
		HWND parent = GetActiveWindow();
		if ( parent!=0 )
			parent = GetLastActivePopup( parent );

		MessageBox( parent, text, _T("logging message"), MB_ICONINFORMATION );

	} catch ( ... ) {
		// no exceptions during logging!
	}

	inlog=false;
}

void LogToUserDefFunc( const TCHAR *text )
{
	static bool inlog=false;	// single entry!
	if ( inlog ) return;
	inlog=true;

	try {
		if ( g_LogHlp.m_LogFunc!=0 )
			g_LogHlp.m_LogFunc( text );

	} catch ( ... ) {
		// no exceptions during logging!
	}

	inlog=false;
}


//////////////////////////////////////////////////////////////////////////////
// logging routines.

void LOGINSTALL_USERDEFLOGFUNC( USERDEF_LOG_FUNC *const func )
{
	g_LogHlp.m_LogFunc = func;
}

void LOGSET_LVL( const LOGLVL lvl )
{
	g_LogHlp.m_LogLvl = lvl;
}

void LOGSET_DST( const int dst )
{
	g_LogHlp.m_LogDst = dst;
}

void LOGSET_FILENAME( const TCHAR *name )
{
	strncpy( g_LogHlp.LogFileName, name, LogHelper::LOG_FN_SIZE );
}

int LOGGET_LVL()
{
	return g_LogHlp.m_LogLvl;
}

int LOGGET_DST()
{
	return g_LogHlp.m_LogDst;
}

void LOGV( const TCHAR *text, va_list argptr )
{
	enum { bufsize=10000 };
	TCHAR buf[bufsize];
	memset( buf, 0, sizeof buf );
	vsprintf( buf, text, argptr );

	if ( g_LogHlp.m_LogDst & file )
		LogToFile( buf );
	if ( g_LogHlp.m_LogDst & console )
		LogToConsole( buf );
	if ( g_LogHlp.m_LogDst & debugger )
		LogToDebugger( buf );
	if ( g_LogHlp.m_LogDst & msgbox )
		LogToMsgBox( buf );
	if ( g_LogHlp.m_LogDst & userdef )
		LogToUserDefFunc( buf );
}

void LOG( const TCHAR *text, ... )
{
	try {
		va_list lst;
		va_start( lst, text );

		LOGV( text, lst );

		va_end( lst );

	} catch ( ... ) {
		// no exceptions during logging!
	}
}

// convert a "..." to a string buffer.
#define PPP_TO_STR( text ) \
	va_list lst; \
	va_start( lst, text ); \
	enum { bufsize=10000 }; \
	TCHAR buf[bufsize]; \
	memset( buf, 0, sizeof buf ); \
	vsprintf( buf, text, lst ); \
	va_end( lst );

#if defined( _DEBUG )

void LOG_D1( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d1 ||
		g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LOG( buf );
	}
}

void LOGF_D1( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d1 ||
		g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToFile( buf );
	}
}

void LOGC_D1( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d1 ||
		g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToConsole( buf );
	}
}

void LOGD_D1( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d1 ||
		g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToDebugger( buf );
	}
}

void LOGM_D1( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d1 ||
		g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToMsgBox( buf );
	}
}

void LOGU_D1( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d1 ||
		g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToUserDefFunc( buf );
	}
}

void LOG_D2( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LOG( buf );
	}
}

void LOGF_D2( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToFile( buf );
	}
}

void LOGC_D2( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToConsole( buf );
	}
}

void LOGD_D2( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToDebugger( buf );
	}
}

void LOGM_D2( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToMsgBox( buf );
	}
}

void LOGU_D2( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToUserDefFunc( buf );
	}
}

void LOG_D3( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LOG( buf );
	}
}

void LOGF_D3( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToFile( buf );
	}
}

void LOGC_D3( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToConsole( buf );
	}
}

void LOGD_D3( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToDebugger( buf );
	}
}

void LOGM_D3( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToMsgBox( buf );
	}
}

void LOGU_D3( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d3 ) {
		PPP_TO_STR( text );
		LogToUserDefFunc( buf );
	}
}

#else

void LOG_R1( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d1 ||
		g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r1 ||
		g_LogHlp.m_LogLvl==r2 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LOG( buf );
	}
}

void LOGF_R1( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d1 ||
		g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r1 ||
		g_LogHlp.m_LogLvl==r2 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToFile( buf );
	}
}

void LOGC_R1( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d1 ||
		g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r1 ||
		g_LogHlp.m_LogLvl==r2 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToConsole( buf );
	}
}

void LOGD_R1( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d1 ||
		g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r1 ||
		g_LogHlp.m_LogLvl==r2 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToDebugger( buf );
	}
}

void LOGM_R1( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d1 ||
		g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r1 ||
		g_LogHlp.m_LogLvl==r2 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToMsgBox( buf );
	}
}

void LOGU_R1( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d1 ||
		g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r1 ||
		g_LogHlp.m_LogLvl==r2 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToUserDefFunc( buf );
	}
}

void LOG_R2( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r2 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LOG( buf );
	}
}

void LOGF_R2( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r2 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToFile( buf );
	}
}

void LOGC_R2( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r2 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToConsole( buf );
	}
}

void LOGD_R2( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r2 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToDebugger( buf );
	}
}

void LOGM_R2( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r2 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToMsgBox( buf );
	}
}

void LOGU_R2( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d2 ||
		g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r2 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToUserDefFunc( buf );
	}
}

void LOG_R3( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LOG( buf );
	}
}

void LOGF_R3( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToFile( buf );
	}
}

void LOGC_R3( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToConsole( buf );
	}
}

void LOGD_R3( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToDebugger( buf );
	}
}

void LOGM_R3( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToMsgBox( buf );
	}
}

void LOGU_R3( const TCHAR *text, ... )
{
	if ( g_LogHlp.m_LogLvl==d3 ||
		g_LogHlp.m_LogLvl==r3 ) {
		PPP_TO_STR( text );
		LogToUserDefFunc( buf );
	}
}

#endif	// _DEBUG
#endif	// LOGGING


//////////////////////////////////////////////////////////////////////////////