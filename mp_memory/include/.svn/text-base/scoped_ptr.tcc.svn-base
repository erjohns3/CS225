#include "scoped_ptr.h"
#include <iostream>

namespace cs225
{

	template <class T>
	scoped_ptr<T>::scoped_ptr()
	:ptr_{NULL}
	{
	
	}

	template <class T>
	scoped_ptr<T>::scoped_ptr(T* rawptr)
	:ptr_{rawptr}
	{

	}

	template <class T>
	scoped_ptr<T>::scoped_ptr(scoped_ptr&& other)
	:ptr_{NULL}
	{
		swap(other);
	}

	template <class T>
	scoped_ptr<T>& scoped_ptr<T>::operator=(scoped_ptr&& other)
	{
		if(this != &other){
			clear();
			swap(other);
		}
		return *this;
	}

	template <class T>
	scoped_ptr<T>::~scoped_ptr()
	{
		clear();	
	}

	template <class T>
	void scoped_ptr<T>::clear()
	{
		if(!empty())
			delete ptr_;
		ptr_ = NULL;
	}

	template <class T>
	void scoped_ptr<T>::swap(scoped_ptr<T>& other)
	{
		std::swap(ptr_,other.ptr_);
	}

	template <class T>
	bool scoped_ptr<T>::empty() const
	{
		return ptr_ == NULL;
	}

	template <class T>
	const T& scoped_ptr<T>::operator*() const
	{
		return *ptr_;
	}

	template <class T>
	T& scoped_ptr<T>::operator*()
	{
		return *ptr_;
	}

	template <class T>
	const T* scoped_ptr<T>::operator->() const
	{
		return ptr_;
	}

	template <class T>
	T* scoped_ptr<T>::operator->()
	{
		return ptr_;
	}

	template <class T>
	const T* scoped_ptr<T>::get() const
	{
		return ptr_;
	}

	template <class T>
	T* scoped_ptr<T>::get()
	{
		return ptr_;
	}
}
