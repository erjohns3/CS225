/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
 #include <iostream>

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::left_child(size_t idx) const
{
    /// @todo Update to return the index of the left child.
        return 2*idx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::right_child(size_t idx) const
{
    /// @todo Update to return the index of the left child.
        return 2*idx+2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t idx) const
{
    /// @todo Update to return the parent index.
        return (idx-1)/2;
}

template <class T, class Compare>
bool heap<T, Compare>::has_child(size_t idx) const
{
    /// @todo Update to return whether the node at index has a child.
    return 2*idx+1 < elems_.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::max_priority_child(size_t idx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if(right_child(idx) >= elems_.size())
        return left_child(idx);
    else if(higher_priority_(elems_[left_child(idx)], elems_[right_child(idx)]))
        return left_child(idx);
    else
        return right_child(idx);
}

template <class T, class Compare>
void heap<T, Compare>::heapify_down(size_t idx)
{
    /// @todo Implement the heapifyDown algorithm.
    if(!has_child(idx))
        return;
    size_t mpc = max_priority_child(idx);
    if(higher_priority_(elems_[mpc], elems_[idx])){
        std::swap(elems_[idx],elems_[mpc]);
        heapify_down(mpc);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapify_up(size_t idx)
{
    if (idx == root())
        return;
    size_t parentIdx = parent(idx);
    if (higher_priority_(elems_[idx], elems_[parentIdx])){
        std::swap(elems_[idx], elems_[parentIdx]);
        heapify_up(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    
    for(int i=0; i<elems.size(); i++)
        elems_.push_back(elems[i]);
    for(size_t i = elems_.size()-1; i>0; i--)
        heapify_down(i);
    heapify_down(0);
}

template <class T, class Compare>
void heap<T, Compare>::pop()
{
    /// @todo Remove the element with the highest priority.
    size_t hpIdx = 0;
    for(int i=0; i<elems_.size(); i++){
        if(higher_priority_(elems_[i],elems_[hpIdx]))
            hpIdx = i;
    }
    std::swap(elems_[hpIdx], elems_[elems_.size()-1]);
    elems_.pop_back();
    heapify_down(hpIdx);
}

template <class T, class Compare>
const T& heap<T, Compare>::peek() const
{
    /// @todo Return the element with the highest priority (do *not* remove!)
    size_t hpIdx = 0;
    for(int i=0; i<elems_.size(); i++){
        if(higher_priority_(elems_[i],elems_[hpIdx]))
            hpIdx = i;
    }
    return elems_[hpIdx];
}

template <class T, class Compare>
void heap<T, Compare>::push(T elem)
{
    /// @todo Add an element to the heap
    elems_.push_back(elem);
    heapify_up(elems_.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    return elems_.size() == 0;
}
