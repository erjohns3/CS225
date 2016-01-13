#include "dsets.h"

void dsets::add_elements(uint64_t num)
{
	for (uint64_t i = 0; i < num; ++i) {
		arr_.push_back(-1);
	}
}

uint64_t dsets::find(uint64_t elem)
{
	if (arr_[elem] < 0)
		return elem;
	return arr_[elem] = find(arr_[elem]);
}

void dsets::merge(uint64_t a, uint64_t b)
{
	// find the roots of each of the elements
	auto root1 = find(a);
	auto root2 = find(b);
	// if you try to merge two same sets
	if (root1 == root2)
		return;
	// if root1 has a larger size
	else if (arr_[root1] <= arr_[root2]) {
		arr_[root1] += arr_[root2];
		arr_[root2] = root1;
	}
	// if root2 has a larger size
	else {
		arr_[root2] += arr_[root1];
		arr_[root1] = root2;
	}
}