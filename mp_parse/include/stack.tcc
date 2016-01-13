/**
 * @file stack.tcc
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "stack.h"

namespace cs225
{

	template <class T>
	const T& stack<T>::top() const
	{
	    /// @todo mp_parse.2
	    return arr_[arr_.size()-1];
	}

	template <class T>
	T& stack<T>::top()
	{
	    /// @todo mp_parse.2
	    return arr_[arr_.size()-1];
	}

	template <class T>
	void stack<T>::push(const T& elem)
	{
	    /// @todo mp_parse.2
	    arr_.push_back(elem);
	}

	template <class T>
	void stack<T>::push(T&& elem)
	{
	    /// @todo mp_parse.2
	    arr_.push_back(NULL);
	    arr_[arr_.size()-1] = std::move(elem);
	}

	template <class T>
	void stack<T>::pop()
	{
	    /// @todo mp_parse.2
	    arr_.pop_back();
	}

	template <class T>
	uint64_t stack<T>::size() const
	{
	    /// @todo mp_parse.2
	    return arr_.size();
	}

	template <class T>
	bool stack<T>::empty() const
	{
	    /// @todo mp_parse.2
	    return arr_.empty();
	}
}
