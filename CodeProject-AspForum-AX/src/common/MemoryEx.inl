// ###########################################################################
// #
// # file:
// #	MemoryEx.inl
// #
// ###########################################################################


//////////////////////////////////////////////////////////////////////////////
// works the same as std::auto_ptr_array, except that instead of delete,
// delete[] is called.
// therefore, use only for arrays allocated with new[].

template<class T> inline 
auto_ptr_array<T>::auto_ptr_array<T>( T *const ptr ) :
	m_Owns(ptr!=0), 
	m_Ptr(ptr) 
{
}

template<class T> inline 
auto_ptr_array<T>::auto_ptr_array<T>( 
	const auto_ptr_array<T>& src ) :
	m_Owns(src.m_Owns), 
	m_Ptr(src.release())
{
}

template<class T> inline 
auto_ptr_array<T>& auto_ptr_array<T>::operator=( 
	const auto_ptr_array<T>& src )
{
	if ( this!=&src ) {
		if ( m_Ptr!=src.get() ) {
			if ( m_Owns ) {
				delete[] m_Ptr;
				m_Ptr = 0;
			}
			m_Owns = src.m_Owns; 
		
		} else if ( src.m_Owns ) {
			m_Owns = true;
		}
		m_Ptr = src.release(); 
	}
	return *this; 
}

template<class T> inline 
auto_ptr_array<T>::~auto_ptr_array<T>()
{
	if ( m_Owns ) {
		delete[] m_Ptr; 
		m_Ptr = 0;
	}
}

template<class T> inline 
T& auto_ptr_array<T>::operator[]( const unsigned int idx ) const
{
	return get()[idx];
}

template<class T> inline 
T& auto_ptr_array<T>::operator*() const 
{
	return *get();
}

template<class T> inline 
T* auto_ptr_array<T>::operator->() const 
{
	return get(); 
}

template<class T> inline 
T* auto_ptr_array<T>::get() const 
{
	return m_Ptr; 
}

template<class T> inline 
T* auto_ptr_array<T>::release() const 
{
	((auto_ptr_array<T>*)this)->m_Owns = false;
	T *const ptr = m_Ptr;
	((auto_ptr_array<T>*)this)->m_Ptr = 0;
	return ptr; 
}


//////////////////////////////////////////////////////////////////////////////