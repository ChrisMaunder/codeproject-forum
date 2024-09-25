// ###########################################################################
// #
// # file:
// #	common.h
// #
// # remarks:
// #	miscellaneous functions.
// #
// # history:
// #	1998-12-02 Uwe Keim		file created.
// #
// ###########################################################################

#ifndef __COMMON_H__
#define __COMMON_H__


//////////////////////////////////////////////////////////////////////////////
// com helpers.

#define CREATE_INSTANCE( com_ptr, clsid ) \
	{ \
		const HRESULT hr = com_ptr.CreateInstance( clsid ); \
		if ( FAILED( hr ) ) \
			ThrowComError( hr ); \
	}

class CoInit {
public:
	CoInit();
	virtual ~CoInit();
};


//////////////////////////////////////////////////////////////////////////////
// misc functions.

extern std::_tstring Format( LPCTSTR txt, ... );


//////////////////////////////////////////////////////////////////////////////
// file functions.

extern bool FileExists( LPCTSTR filename );
extern bool DirExists( LPCTSTR directoryname );


//////////////////////////////////////////////////////////////////////////////

#endif