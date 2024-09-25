// ###########################################################################
// #
// # file:
// #	Xept.h
// #
// # history:
// #	1998-12-20 Uwe Keim		simplified.
// #	1998-07-08 Uwe Keim		file created.
// #
// ###########################################################################

#ifndef __XEPT_H__
#define __XEPT_H__

#include <sstream>
#include <iomanip>
#include <tchar.h>


//////////////////////////////////////////////////////////////////////////////
// some mappings.

#ifdef UNICODE
	#define	_tostringstream		wostringstream
	#define _tostream			wostream
	#define _tios				wios
	#define _tstreambuf			wstreambuf
	#define _tstring			wstring
#else
	#define	_tostringstream		ostringstream
	#define _tostream			ostream
	#define _tios				ios
	#define _tstreambuf			streambuf
	#define _tstring			string
#endif


//////////////////////////////////////////////////////////////////////////////
// exception class.

// use in the constructor of derived classes.
#define XEPT_FMT() \
	va_list lst; \
	va_start( lst, text ); \
	Xept::Fmt( text, lst ); \
	va_end( lst ); \

class Xept {
public:
	Xept();
	Xept( const TCHAR *const text, ... );
	virtual ~Xept()								{}

	virtual std::_tstring Text() const			{ return m_Text; }
	virtual void Text( const TCHAR *text )		{ m_Text = text; }

	virtual int Value() const					{ return m_Value; }
	virtual void Value( const int value )		{ m_Value = value; }

	virtual int Severity() const				{ return m_Severity; }
	virtual void Severity( const int severity )	{ m_Severity = severity; }

	virtual DWORD LastError() const				{ return m_LastError; }

	virtual std::_tstring Whole();

protected:
	void Fmt( const TCHAR *const text, va_list arg_list );

	std::_tstring	m_Text;
	int				m_Value;
	int				m_Severity;
	DWORD			m_LastError;
};


//////////////////////////////////////////////////////////////////////////////

#endif