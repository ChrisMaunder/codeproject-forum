// ###########################################################################
// #
// # file:
// #	MemoryEx.h
// #
// # remarks:
// #	extended auto_ptr_array template class.
// #
// # history:
// #	1998-12-27 Uwe Keim		file created.
// #
// ###########################################################################

#ifndef __MEMORYEX_H__
#define __MEMORYEX_H__


//////////////////////////////////////////////////////////////////////////////
// works the same as std::auto_ptr, except that instead of delete,
// delete[] is called. therefore, use only for arrays allocated with new[].

template<class T>
	class auto_ptr_array {
public:
	explicit auto_ptr_array( T *const ptr=0 );
	auto_ptr_array( const auto_ptr_array<T>& src );
	auto_ptr_array<T>& operator=( const auto_ptr_array<T>& src );
	~auto_ptr_array();

	T& operator[]( const unsigned int idx ) const;
	T& operator*() const;
	T* operator->() const;
	T* get() const;
	T* release() const;

private:
	bool	m_Owns;
	T		*m_Ptr;
};


//////////////////////////////////////////////////////////////////////////////

#include "memoryex.inl"

#endif