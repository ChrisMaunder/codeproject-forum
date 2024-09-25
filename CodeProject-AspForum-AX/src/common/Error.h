// ###########################################################################
// #
// # file:
// #	error.h
// #
// # history:
// #	1999-03-31 Uwe Keim		file created.
// #
// ###########################################################################

#ifndef __ERROR_H__
#define __ERROR_H__


//////////////////////////////////////////////////////////////////////////////
// error handling.

extern HRESULT CATCH_AND_LOG_XEPT( Xept& e );
extern HRESULT CATCH_AND_LOG_COM_ERROR_XEPT( _com_error& e, ADODB::_ConnectionPtr conn );
extern HRESULT CATCH_AND_LOG_COM_ERROR_XEPT( _com_error& e );
extern HRESULT CATCH_AND_LOG_UNKNOWN_XEPT();

extern std::_tstring GetLastErrorMsg( const DWORD lastError );
extern std::_tstring Format( LPCTSTR txt, ... );

extern void ThrowComError( HRESULT hr );
extern std::_tstring LogCrackHR( HRESULT hr );
extern std::_tstring LogAdoErrorImport( ADODB::_ConnectionPtr conn );


//////////////////////////////////////////////////////////////////////////////

#endif