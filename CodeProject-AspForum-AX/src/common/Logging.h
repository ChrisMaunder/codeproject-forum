// ###########################################################################
// #
// # file:
// #	Logging.h
// #
// # history:
// #	1998-07-08 Uwe Keim		file created.
// #
// ###########################################################################

#ifndef __LOGGING_H__
#define __LOGGING_H__

#include <tchar.h>


//////////////////////////////////////////////////////////////////////////////
// additional helper functions.

extern std::_tstring GetWindowsDirectory();	// always WITH backslash at the end.
extern std::_tstring GetWindowsDrive();		// always WITH backslash at the end.
extern std::_tstring GetModuleFilename();	// works with MFC DLLs, too.
extern std::_tstring GetModuleDir();		// works with MFC DLLs, too. always WITH backslash at the end.


//////////////////////////////////////////////////////////////////////////////
// logging, i.e. output of text to various destinations.
// logging is only activated if the symbol LOGGING is defined.

// levels.
// call LOGSET_LVL() with one of the following values:
// (level 2 includes level 1, level 3 includes level 1 and 2).
// 
// default is 'd3'.
enum LOGLVL { 
	d1, d2, d3,										// debug version.
	r1, r2, r3										// debug version and release version.
};

// destination.
// call LOGSETDEF_DST() with one of the following values:
// (or multiple, added with bitwise or).
enum LOGDST { 
	none		= 0x00,								// nowhere.
	file		= 0x01,								// into a file.
	console		= 0x02,								// into a console.
	debugger	= 0x04,								// into the debugger.
	msgbox		= 0x08,								// into a msgbox.
	userdef		= 0x10								// user defined.
};

// user defined logging calls a callback.
typedef void (USERDEF_LOG_FUNC)( const TCHAR *text );

#if defined( LOGGING )
	extern void LOGINSTALL_USERDEFLOGFUNC( 
		USERDEF_LOG_FUNC *const func );

	extern void LOGSET_LVL( const LOGLVL lvl );		// the current log level.
	extern void LOGSET_DST( const int dst );		// for a call to LOG().
	extern void LOGSET_FILENAME( const TCHAR *name );

	extern int LOGGET_LVL();
	extern int LOGGET_DST();

	// default with current LOGLVL and current LOGDST.
	extern void LOG( const TCHAR *text, ... );

	#if	defined( _DEBUG )
		extern void LOG_D1 ( const TCHAR *text, ... );
		extern void LOGF_D1( const TCHAR *text, ... );
		extern void LOGC_D1( const TCHAR *text, ... );
		extern void LOGD_D1( const TCHAR *text, ... );
		extern void LOGM_D1( const TCHAR *text, ... );
		extern void LOGU_D1( const TCHAR *text, ... );

		extern void LOG_D2 ( const TCHAR *text, ... );
		extern void LOGF_D2( const TCHAR *text, ... );
		extern void LOGC_D2( const TCHAR *text, ... );
		extern void LOGD_D2( const TCHAR *text, ... );
		extern void LOGM_D2( const TCHAR *text, ... );
		extern void LOGU_D2( const TCHAR *text, ... );

		extern void LOG_D3 ( const TCHAR *text, ... );
		extern void LOGF_D3( const TCHAR *text, ... );
		extern void LOGC_D3( const TCHAR *text, ... );
		extern void LOGD_D3( const TCHAR *text, ... );
		extern void LOGM_D3( const TCHAR *text, ... );
		extern void LOGU_D3( const TCHAR *text, ... );

		#define LOG_R1 ( text )				((void)0)
		#define LOGF_R1( text )				((void)0)
		#define LOGC_R1( text )				((void)0)
		#define LOGD_R1( text )				((void)0)
		#define LOGM_R1( text )				((void)0)
		#define LOGU_R1( text )				((void)0)
										    
		#define LOG_R2 ( text )				((void)0)
		#define LOGF_R2( text )				((void)0)
		#define LOGC_R2( text )				((void)0)
		#define LOGD_R2( text )				((void)0)
		#define LOGM_R2( text )				((void)0)
		#define LOGU_R2( text )				((void)0)
										    
		#define LOG_R3 ( text )				((void)0)
		#define LOGF_R3( text )				((void)0)
		#define LOGC_R3( text )				((void)0)
		#define LOGD_R3( text )				((void)0)
		#define LOGM_R3( text )				((void)0)
		#define LOGU_R3( text )				((void)0)
	#else
		extern void LOG_R1 ( const TCHAR *text, ... );
		extern void LOGF_R1( const TCHAR *text, ... );
		extern void LOGC_R1( const TCHAR *text, ... );
		extern void LOGD_R1( const TCHAR *text, ... );
		extern void LOGM_R1( const TCHAR *text, ... );
		extern void LOGU_R1( const TCHAR *text, ... );

		extern void LOG_R2 ( const TCHAR *text, ... );
		extern void LOGF_R2( const TCHAR *text, ... );
		extern void LOGC_R2( const TCHAR *text, ... );
		extern void LOGD_R2( const TCHAR *text, ... );
		extern void LOGM_R2( const TCHAR *text, ... );
		extern void LOGU_R2( const TCHAR *text, ... );

		extern void LOG_R3 ( const TCHAR *text, ... );
		extern void LOGF_R3( const TCHAR *text, ... );
		extern void LOGC_R3( const TCHAR *text, ... );
		extern void LOGD_R3( const TCHAR *text, ... );
		extern void LOGM_R3( const TCHAR *text, ... );
		extern void LOGU_R3( const TCHAR *text, ... );

		#define LOG_D1 ( text )				((void)0)
		#define LOGF_D1( text )				((void)0)
		#define LOGC_D1( text )				((void)0)
		#define LOGD_D1( text )				((void)0)
		#define LOGM_D1( text )				((void)0)
		#define LOGU_D1( text )				((void)0)
									    
		#define LOG_D2 ( text )				((void)0)
		#define LOGF_D2( text )				((void)0)
		#define LOGC_D2( text )				((void)0)
		#define LOGD_D2( text )				((void)0)
		#define LOGM_D2( text )				((void)0)
		#define LOGU_D2( text )				((void)0)
									    
		#define LOG_D3 ( text )				((void)0)
		#define LOGF_D3( text )				((void)0)
		#define LOGC_D3( text )				((void)0)
		#define LOGD_D3( text )				((void)0)
		#define LOGM_D3( text )				((void)0)
		#define LOGU_D3( text )				((void)0)
	#endif
#else
	#define LOGINSTALL_USERDEFLOGFUNC( f )	((void)0)
	#define LOGSET_DST( dst )				((void)0)
	#define LOGSET_FILENAME( name )			((void)0)

	#define LOGGET_LVL()					((int)0)
	#define LOGGET_DST()					((int)0)

	#define LOG( text )						((void)0)

	#define LOG_D1 ( text )					((void)0)
	#define LOGF_D1( text )					((void)0)
	#define LOGC_D1( text )					((void)0)
	#define LOGD_D1( text )					((void)0)
	#define LOGM_D1( text )					((void)0)
	#define LOGU_D1( text )					((void)0)
										    
	#define LOG_D2 ( text )					((void)0)
	#define LOGF_D2( text )					((void)0)
	#define LOGC_D2( text )					((void)0)
	#define LOGD_D2( text )					((void)0)
	#define LOGM_D2( text )					((void)0)
	#define LOGU_D2( text )					((void)0)
											    
	#define LOG_D3 ( text )					((void)0)
	#define LOGF_D3( text )					((void)0)
	#define LOGC_D3( text )					((void)0)
	#define LOGD_D3( text )					((void)0)
	#define LOGM_D3( text )					((void)0)
	#define LOGU_D3( text )					((void)0)
											    
	#define LOG_R1 ( text )					((void)0)
	#define LOGF_R1( text )					((void)0)
	#define LOGC_R1( text )					((void)0)
	#define LOGD_R1( text )					((void)0)
	#define LOGM_R1( text )					((void)0)
	#define LOGU_R1( text )					((void)0)
											    
	#define LOG_R2 ( text )					((void)0)
	#define LOGF_R2( text )					((void)0)
	#define LOGC_R2( text )					((void)0)
	#define LOGD_R2( text )					((void)0)
	#define LOGM_R2( text )					((void)0)
	#define LOGU_R2( text )					((void)0)
											    
	#define LOG_R3 ( text )					((void)0)
	#define LOGF_R3( text )					((void)0)
	#define LOGC_R3( text )					((void)0)
	#define LOGD_R3( text )					((void)0)
	#define LOGM_R3( text )					((void)0)
	#define LOGU_R3( text )					((void)0)
#endif


//////////////////////////////////////////////////////////////////////////////

#endif