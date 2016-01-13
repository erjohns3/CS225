/**
 * @file kdtree.tcc
 * Implementation of kd_tree class.
 */

#include "kdtree.h"

template <int Dim>
bool kd_tree<Dim>::smaller_in_dimension(const point<Dim>& first,
                                       const point<Dim>& second,
                                       int curDim) const
{
    /**
    * @todo Implement this function!
    */
    if(first[curDim] < second[curDim])
        return true;
    else if(first[curDim] > second[curDim])
        return false;
    else
        return first < second;
}

template <int Dim>
bool kd_tree<Dim>::should_replace(const point<Dim>& target,
                                 const point<Dim>& current_best,
                                 const point<Dim>& potential) const
{
    /**
    * @todo Implement this function!
    */

    double cur_dist = 0;
    double pot_dist = 0;
    for(int i=0; i<Dim; i++){
        cur_dist += pow(target[i] - current_best[i], 2);
        pot_dist += pow(target[i] - potential[i], 2);
    }

    if(pot_dist < cur_dist)
        return true;
    else if(pot_dist > cur_dist)
        return false;
    return potential < current_best;
}

template <int Dim>
kd_tree<Dim>::kd_tree(const std::vector<point<Dim>>& newpoints)
{
    /**
    * @todo Implement this function!
    */
    if(newpoints.size() == 0)
        return;
    points = newpoints;
    build(0, points.size()-1, 0);
}

template<int Dim>
void kd_tree<Dim>::build(size_t left, size_t right, int dimension)
{
    if(left == right)
        return;
    size_t new_right = (left+right)/2-1;
    size_t new_left = (left+right)/2+1;
    if(left+1 == right)
        new_right = (left+right)/2;
    quick_select(left, right, (left+right)/2, dimension);
    build(left, new_right, (dimension+1)%Dim);
    build(new_left, right, (dimension+1)%Dim);
}

template<int Dim>
size_t kd_tree<Dim>::partition(size_t left, size_t right, int dimension)
{
    size_t storeIndex = left;
    for(size_t i=left; i<right; i++){
        if(smaller_in_dimension(points[i], points[right], dimension)){
            std::swap(points[i], points[storeIndex]);
            storeIndex++;
        }
    }
    std::swap(points[storeIndex], points[right]);
    return storeIndex;
}

template<int Dim>
void kd_tree<Dim>::quick_select(size_t left, size_t right, size_t median, int dimension)
{
    if(left == right)
        return;
    size_t pivotIndex = partition(left, right, dimension);
    if(median == pivotIndex)
        return;
    else if(median < pivotIndex)
        quick_select(left, pivotIndex-1, median, dimension);
    else
        quick_select(pivotIndex+1, right, median, dimension);
}

template <int Dim>
point<Dim> kd_tree<Dim>::find_nearest_neighbor(const point<Dim>& query) const
{
    /**
    * @todo Implement this function!
    */
    return points[find_nearest_neighbor(query, 0, points.size()-1, 0)];
}

template <int Dim>
size_t kd_tree<Dim>::find_nearest_neighbor(const point<Dim>& query, size_t left, size_t right, int dimension) const
{
    if(left == right)
        return left;

    size_t new_right = (left+right)/2-1;
    size_t new_left = (left+right)/2+1;
    if(left+1 == right)
        new_right = (left+right)/2;
    
    size_t primary_idx;
    size_t secondary_idx;

    if(smaller_in_dimension(query, points[(left+right)/2], dimension))
        primary_idx = find_nearest_neighbor(query, left, new_right, (dimension+1)%Dim);
    else
        primary_idx = find_nearest_neighbor(query, new_left, right, (dimension+1)%Dim);

    if(should_replace(query, points[primary_idx], points[(left+right)/2]))
        primary_idx = (left+right)/2;

    if(distance(query, points[primary_idx]) >= pow((points[(left+right)/2])[dimension] - query[dimension], 2)){
        if(smaller_in_dimension(query, points[(left+right)/2], dimension))
            secondary_idx = find_nearest_neighbor(query, new_left, right, (dimension+1)%Dim);
        else
            secondary_idx = find_nearest_neighbor(query, left, new_right, (dimension+1)%Dim);

        if(should_replace(query, points[primary_idx], points[secondary_idx]))
            primary_idx = secondary_idx;    
    }
    return primary_idx;
}

template <int Dim>
double kd_tree<Dim>::distance(const point<Dim> & lhs, const point<Dim> & rhs) const
{
    double dist = 0;
    for(int i=0; i<Dim; i++)
        dist += pow(lhs[i] - rhs[i], 2);
    return dist;
}
