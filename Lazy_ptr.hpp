#ifndef LAZY_PTR_HPP
#define LAZY_PTR_HPP
#include <stdexcept>
#include <iostream>
#include <cassert>

template< typename T >

class lazy_array_ptr {

	const int m_size;

	T * m_pData;

public:

	lazy_array_ptr(const int _size);

	~lazy_array_ptr();

	operator bool () const;

	lazy_array_ptr (const lazy_array_ptr < T > & ) = delete;

	lazy_array_ptr < T > & operator = (const lazy_array_ptr < T > &) = delete;

	lazy_array_ptr (lazy_array_ptr < T > && _lazy);

	lazy_array_ptr < T > &  operator = (lazy_array_ptr < T > && _lazy);

	const T * getAdress() const;

	void reset();

	T operator [] (int _index) const;

	T & operator [] (int _index);

	T operator * () const;

	T & operator * ();

private:

	void fill();

};

/**************************************************/

template <typename T>

lazy_array_ptr < T >::lazy_array_ptr(const int _size) : m_size (_size)
{
	if (!_size)
		throw std::logic_error("Bad size");
	m_pData = nullptr;
	
}

template <typename T>
lazy_array_ptr < T >::~lazy_array_ptr() {

	if (m_pData == nullptr)
		return;

	reset();
}

template <typename T>
lazy_array_ptr < T > :: operator bool()const {

	return m_pData != nullptr;

}


template<typename T>
lazy_array_ptr < T >::lazy_array_ptr<T>(lazy_array_ptr < T > && _lazy) : m_size (_lazy.m_size) {

	m_pData = _lazy.m_pData;
	_lazy.m_pData = nullptr;

}

template<typename T>
lazy_array_ptr < T > & lazy_array_ptr < T > :: operator = (lazy_array_ptr < T > && _lazy)  {

	if (this == &_lazy)
		return *this;

	std::swap(m_size, _lazy.m_size);
	std::swap(m_pData, _lazy.mpData);
	
	return *this;
}

template <typename T>
T lazy_array_ptr < T >::operator [] (int _index) const
{
	if (_index < 0 || _index >= m_size)
		throw std::logic_error("Bad index");

	if (!m_Data) {
		m_pData = new T[m_size];
		fill();
	}
	return m_pData[_index];

}

template <typename T>
T lazy_array_ptr <T> :: operator * () const {

	if (!m_pData) {
		m_pData = new T[m_size];
		fill();
	}

	return *m_pData;
}

template <typename T>
T & lazy_array_ptr <T> :: operator * () {
	
	if (!m_pData) {
		m_pData = new T[m_size];
		fill();
	}

	return * m_pData;
}

template <typename T>

inline const T * lazy_array_ptr <T> ::getAdress() const {

	return m_pData;

}

template <typename T>
void lazy_array_ptr <T> ::reset() {

	if (m_pData) {
		delete[] m_pData;
		m_pData = nullptr;
	}
	else return;
}

template <typename T>
T & lazy_array_ptr < T > ::operator [] (int _index) {

	if (_index < 0 || _index >= m_size)
		throw std::logic_error("Bad index");

	if (!m_pData) {
		m_pData = new T[m_size];
		fill();
	}
	return m_pData[_index];

}


template <typename T>
void lazy_array_ptr < T > :: fill() {
	
	T f{};

	for (int i = 0; i < m_size; i++)
		m_pData[i] = f;

}





#endif