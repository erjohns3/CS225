/**
 * @file dl_list.tcc
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cassert>
#include <utility>
#include <iostream>
#include "dl_list.h"

namespace cs225
{

	template <class T>
	dl_list<T>::dl_list()
		:head_{}, tail_{NULL}, size_{0}
	{
		/// @todo mp_list.1
		
	}

	template <class T>
	dl_list<T>::dl_list(const dl_list& other)
		:head_{}, tail_{NULL}, size_{0}
	{
		/*
		cout<<""<<std::endl;
		cout<<""<<std::endl;
		cout<<"head: "<<head_.get()<<std::endl;
		cout<<""<<std::endl;
		cout<<""<<std::endl;
		*/
		/// @todo mp_list.1
		/// hint: re-use your push_X function(s)!
		node* tmp = other.head_.get();
		while(tmp != NULL){
			push_back(tmp->data);
			tmp = tmp->next.get();
		}
	}

	template <class T>
	dl_list<T>::dl_list(dl_list&& other)
		:head_{}, tail_{NULL}, size_{0}
	{
		/// @todo mp_list.1
		swap(other);
	}

	template <class T>
	dl_list<T>& dl_list<T>::operator=(dl_list rhs)
	{
		/// @todo mp_list.1
		swap(rhs);
		return *this;		
	}

	template <class T>
	void dl_list<T>::swap(dl_list& other)
	{
		/// @todo mp_list.1
		std::swap(head_, other.head_);
		std::swap(tail_, other.tail_);
		std::swap(size_, other.size_);
	}

	template <class T>
	void dl_list<T>::push_back(T data)
	{
		/// @todo mp_list.1
		std::unique_ptr<node> tmp (new node(data));
		if(size_ == 0){
			head_.swap(tmp);
			tail_ = head_.get();
		}else{
			(tail_->next).swap(tmp);
			(tail_->next)->prev = tail_;
			tail_ = tail_->next.get();
		}
		size_++;
	}

	template <class T>
	void dl_list<T>::push_front(T data)
	{
		/// @todo mp_list.1
		std::unique_ptr<node> tmp(new node(data));
		if(size_ == 0){
			tail_ = tmp.get();
		}
		tmp->next.swap(head_);
		head_.swap(tmp);
		size_++;		
	}

	template <class T>
	void dl_list<T>::reverse()
	{
		reverse(head_, tail_);
	}
	
/*
	template <class T>
	void dl_list<T>::reverse(std::unique_ptr<node>& first, node*& last)
	{
		std::unique_ptr<node>& x = first->next;
		first.swap(last->next);
		if(last->next.get() != last)
			reverse((last->next)->next, last);
		first.swap(x);		
	}
*/

	template <class T>
	void dl_list<T>::reverse(std::unique_ptr<node>& first, node*& last)
	{
		node* tmp;
		tmp = first.get();
		int size = 0;
		while(tmp != last){
			size++;
			tmp = tmp->next.get();
		}
		size = size + 2;
		
		node*** rp_ptrs = new node**[size-1]; 
		std::unique_ptr<node>** up_ptrs = new std::unique_ptr<node>*[size];
		
		tmp = last;
		for(int i=0; i<size-1; i++){
			rp_ptrs[i] = &tmp;
			tmp = tmp->prev;
		}
		
		tmp = first.get();
		up_ptrs[0] = &first;
		for(int i=1; i<size; i++){
			up_ptrs[i] = &(tmp->next);
			tmp = tmp->next.get();
		}
		for(int i=0; i<size; i++)
			up_ptrs[i]->swap(*up_ptrs[size-1]);
		for(int i=0; i<size-1; i++)
			std::swap(*rp_ptrs[i], *rp_ptrs[size-2]);
		for(int i=size-2; i>=0; i--)
			up_ptrs[i]->swap(*up_ptrs[i+1]);
		for(int i=size-3; i>=0; i--)
			std::swap(*rp_ptrs[i], *rp_ptrs[i+1]);
	}

	template <class T>
	void dl_list<T>::reverse_nth(unsigned n)
	{
		/// @todo mp_list.1
		int x=1;
		std::unique_ptr<node>* up_ptr = &head_;
		node* ptr = head_.get();
		while(ptr->next != NULL && ptr != NULL){
			if(x%n == 0 || ptr == tail_){
				reverse(*up_ptr, ptr);
				up_ptr = &(ptr->next);
			}
			ptr = ptr->next.get();
			x++;
		}
	}


	template <class T>
	void dl_list<T>::waterfall()
	{
		/// @todo mp_list.1
		node* tmp = head_.get();
		node* tmp2;
		while(tmp->next != NULL && (tmp->next)->next != NULL){
			tmp = tmp->next.get();
			tmp2 = tmp->next.get();
			(tmp->prev)->next.swap(tmp->next);
			std::swap((tmp->next)->prev, tmp->prev);
			tail_->next.swap(tmp->next);
			std::swap(tail_, tmp->prev);
			tail_ = tmp;
			tmp = tmp2;
		}
		tmp = NULL;
		tmp2 = NULL;
	}

	template <class T>
	auto dl_list<T>::split(unsigned split_point) -> dl_list
	{
		if (split_point >= size_)
		    return {};

		if (split_point == 0)
		{
		    dl_list lst;
		    swap(*this);
		    return lst;
		}

		auto old_size = size_;
		auto new_head = split(head_.get(), split_point);

		// set up current list
		size_ = split_point;
		for (tail_ = head_.get(); tail_->next; tail_ = tail_->next.get())
			;

		// set up returned list
		dl_list ret;
		ret.head_ = std::move(new_head);
		for (ret.tail_ = ret.head_.get(); ret.tail_->next;
		     ret.tail_ = ret.tail_->next.get())
		    ;
		ret.size_ = old_size - split_point;
		return ret;
	}

	template <class T>
	auto dl_list<T>::split(node* start, unsigned split_point)
		-> std::unique_ptr<node>
	{
		assert(split_point > 0);
		/// @todo mp_list.2
		std::unique_ptr<node> start2 = NULL;
		while(split_point > 1 && start->next != NULL){
			start = start->next.get();
			split_point--;
		}
		start2.swap(start->next);
		return start2;
	}

	template <class T>
	void dl_list<T>::merge(dl_list& to_merge)
	{
		head_ = merge(std::move(head_), std::move(to_merge.head_));

		for (tail_ = head_.get(); tail_->next; tail_ = tail_->next.get())
		    ;
		size_ += to_merge.size_;

		to_merge.tail_ = nullptr;
		to_merge.size_ = 0;
	}

	template <class T>
	auto dl_list<T>::merge(std::unique_ptr<node> first,
		                   std::unique_ptr<node> second) -> std::unique_ptr<node>
	{
		/// @todo mp_list.2
		std::unique_ptr<node>* back = &first;
		node* b = second.get();
		while(true){
			if(second != NULL && *back != NULL && second->data < (*back)->data){
				tail_ = (*back).get();
				second.swap(b->next);
				if(second != NULL)
					second->prev = NULL;
				back->swap(b->next);
				b->prev = (b->next)->prev;
				(b->next)->prev = b;
				back = &((*back)->next);
				b = second.get();
			}else if(second != NULL && *back == NULL){
				second.swap(b->next);
				if(second != NULL)
					second->prev = NULL;
				back->swap(b->next);
				b->prev = tail_;
				tail_ = b;
				back = &((*back)->next);
				b = second.get();
			}else if(second != NULL && *back != NULL){
				tail_ = (*back).get();
				back = &((*back)->next);
			}else{
				back = NULL;
				return first;
			}
		}
	}

	template <class T>
	void dl_list<T>::sort()
	{
		if (!head_)
		    return;

		head_ = mergesort(std::move(head_), size_);
		for (tail_ = head_.get(); tail_->next; tail_ = tail_->next.get())
		    ;
	}

	template <class T>
	auto dl_list<T>::mergesort(std::unique_ptr<node> start, uint64_t length)
		-> std::unique_ptr<node>
	{
		/// @todo mp_list.2		
		std::cout<<"length: "<<length<<std::endl;
		std::unique_ptr<node> start2 = NULL;	
		if(length == 2){
			std::cout<<"0"<<std::endl;
			std::unique_ptr<node> start2 = split(start.get(), 1);
			std::cout<<"1"<<std::endl;
			return merge(std::move(start), std::move(start2));

		}else if(length == 1){
			std::cout<<"2"<<std::endl;
			return start;
		}else{
			std::cout<<"3"<<std::endl;
			std::unique_ptr<node> start2 = split(start.get(), length/2);
			std::cout<<"4"<<std::endl;
		}
		return merge(mergesort(std::move(start), length/2), mergesort(std::move(start2), length/2));
	}
}
