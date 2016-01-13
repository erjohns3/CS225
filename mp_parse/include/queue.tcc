/**
 * @file queue.tcc
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "queue.h"

namespace cs225
{

	template <class T>
	const T& queue<T>::front() const
	{
	    /// @todo mp_parse.2
	    return arr_[0];
	}

	template <class T>
	T& queue<T>::front()
	{
	    /// @todo mp_parse.2
	    return arr_[0];
	}

	template <class T>
	void queue<T>::push(const T& elem)
	{
	    /// @todo mp_parse.2
	    arr_.push_back(elem);
	}

	template <class T>
	void queue<T>::push(T&& elem)
	{
	    /// @todo mp_parse.2
	    arr_.push_back(NULL);
		arr_[arr_.size()-1] = std::move(elem);
	}

	template <class T>
	void queue<T>::pop()
	{
	    /// @todo mp_parse.2
	    arr_.pop_front();
	}

	template <class T>
	uint64_t queue<T>::size() const
	{
	    /// @todo mp_parse.2
	    return arr_.size();
	}

	template <class T>
	bool queue<T>::empty() const
	{
	    /// @todo mp_parse.2
	    return arr_.empty();
	}
}
