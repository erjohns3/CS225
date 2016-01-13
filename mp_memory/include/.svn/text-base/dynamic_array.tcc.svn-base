#include <dynamic_array.h>
#include <iostream>
#include <cstdint>

namespace cs225
{
	template <class T>
	dynamic_array<T>::dynamic_array()
	:arr_{NULL}, size_{0}
	{
		
	}
	
	template <class T>	
	dynamic_array<T>::dynamic_array(uint64_t sze)
	:size_{sze}
	{
		arr_ = new T[size_];
		for(uint64_t i=0; i<size_; i++)
			arr_[i] = NULL;
	}

	template <class T>
	dynamic_array<T>::dynamic_array(const dynamic_array &other)
	:size_{other.size_}
	{
		arr_ = new T[other.size_];
		for(uint64_t i=0; i<size_; i++){
			arr_[i] = other.arr_[i];
		}
	}

	template <class T>
	dynamic_array<T>::dynamic_array(dynamic_array &&other)
	:arr_{NULL}, size_{0}
	{
		swap(other);
	}


	template <class T>
	dynamic_array<T>& dynamic_array<T>::operator=(dynamic_array rhs)
	{
		swap(rhs);
		return *this;
	}

	template <class T>
	dynamic_array<T>::~dynamic_array()
	{
		clear();
	}

	template <class T>
	void dynamic_array<T>::clear()
	{
		if(!empty())
			delete [] arr_;
		arr_ = NULL;
		size_ = 0;
	}

	template <class T>
	void dynamic_array<T>::swap(dynamic_array &other)
	{
		std::swap(size_, other.size_);
		std::swap(arr_, other.arr_);	
	}

	template <class T>
	void dynamic_array<T>::resize(uint64_t size)
	{
		dynamic_array<T> tmp{size};
		for(uint64_t i=0; i<size; i++){
			if(i<size_ && i<tmp.size_)
				std::swap(tmp[i], (*this)[i]);
			else
				tmp.arr_[i] = NULL;
		}
		swap(tmp);
	}


	template <class T>
	const T& dynamic_array<T>::operator[](uint64_t idx) const
	{	
		return arr_[idx];
	}

	template <class T>
	T& dynamic_array<T>::operator[](uint64_t idx)
	{
		return arr_[idx];
	}

	template <class T>
	const T& dynamic_array<T>::at(uint64_t idx) const
	{	
		if(idx >= size_)
			throw std::out_of_range("index is invalid");
		return arr_[idx];
	
	}

	template <class T>
	T& dynamic_array<T>::at(uint64_t idx)
	{
		if(idx >= size_)
			throw std::out_of_range("index is invalid");
		return arr_[idx];
	}

	template <class T>
	uint64_t dynamic_array<T>::size() const
	{
		return size_;
	}

	template <class T>
	bool dynamic_array<T>::empty() const
	{
		return arr_ == NULL;
	}
}
