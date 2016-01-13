/**
 * @file quadtree.cpp
 * quadtree class implementation.
 * @date Spring 2008
 * @date Modified Summer 2014
 */

#include "quadtree.h"

namespace cs225
{

	quadtree::quadtree()
	:resolution_{0}
	{

	}

    quadtree::quadtree(const epng::png & source, uint64_t resolution)
    :resolution_{resolution}
	{
		build_tree(source, resolution);
	}

    quadtree::quadtree(quadtree & other)
    :resolution_{other.resolution_}
	{
		copy_tree(root_, other.root_);
	}

    quadtree::quadtree(quadtree && other)
    :resolution_{0}
	{
		swap(other);
	}

    quadtree & quadtree::operator=(quadtree rhs)
	{
		root_ = NULL;
		swap(rhs);
		return *this;
	}

	void quadtree::copy_tree(std::unique_ptr<node> & copy, std::unique_ptr<node> & original)
	{
		if(!original)
			return;
		copy.reset(new node());
		copy->element = original->element;
		copy_tree(copy->northwest, original->northwest);
		copy_tree(copy->northeast, original->northeast);
		copy_tree(copy->southwest, original->southwest);
		copy_tree(copy->southeast, original->southeast);
	}

    void quadtree::swap(quadtree & other)
	{
		root_.swap(other.root_);
		std::swap(resolution_, other.resolution_);
	}

    void quadtree::build_tree(const epng::png & source, uint64_t resolution)
	{
		root_ = NULL;
		resolution_ = resolution;
		build_tree(source, root_, resolution_, 0, 0);
	}

	void quadtree::build_tree(const epng::png & source, std::unique_ptr<node> & subroot, uint64_t resolution, uint64_t x, uint64_t y)
	{
		subroot.reset(new node());

		if(resolution == 1){
			subroot->element = *source(x,y);
			return;
		}
		build_tree(source, subroot->northwest, resolution/2, x, y);
		build_tree(source, subroot->northeast, resolution/2, x+resolution/2, y);
		build_tree(source, subroot->southwest, resolution/2, x, y+resolution/2);
		build_tree(source, subroot->southeast, resolution/2, x+resolution/2, y+resolution/2);

		int tmp;
		tmp = (subroot->northwest->element.red + subroot->northeast->element.red + subroot->southwest->element.red + subroot->southeast->element.red)/4;
		subroot->element.red = tmp;
		tmp = (subroot->northwest->element.green + subroot->northeast->element.green + subroot->southwest->element.green + subroot->southeast->element.green)/4;
		subroot->element.green = tmp;
		tmp = (subroot->northwest->element.blue + subroot->northeast->element.blue + subroot->southwest->element.blue + subroot->southeast->element.blue)/4;
		subroot->element.blue = tmp;
	}

    const epng::rgba_pixel & quadtree::operator()(uint64_t x, uint64_t y) const
	{
		if(!root_ || x >= resolution_ || y >= resolution_)
			throw std::out_of_range("");
		return find(root_, x, y, 0, 0, resolution_);
	}

	epng::rgba_pixel & quadtree::find(const std::unique_ptr<node> & subroot, uint64_t x_find, uint64_t y_find, uint64_t x_curr, uint64_t y_curr, uint64_t resolution) const
	{
		if(resolution == 1){
			return subroot->element;
		}else if(x_find < x_curr + resolution/2 && y_find < y_curr + resolution/2){
			if(!subroot->northwest)
				return subroot->element;
			return find(subroot->northwest, x_find, y_find, x_curr, y_curr, resolution/2);
		}else if(x_find >= x_curr + resolution/2 && y_find < y_curr + resolution/2){
			if(!subroot->northeast)
				return subroot->element;
			return find(subroot->northeast, x_find, y_find, x_curr + resolution/2, y_curr, resolution/2);
		}else if(x_find < x_curr + resolution/2 && y_find >= y_curr + resolution/2){
			if(!subroot->southwest)
				return subroot->element;
			return find(subroot->southwest, x_find, y_find, x_curr, y_curr + resolution/2, resolution/2);
		}else if(x_find >= x_curr + resolution/2 && y_find >= y_curr + resolution/2){
			if(!subroot->southeast)
				return subroot->element;
			return find(subroot->southeast, x_find, y_find, x_curr + resolution/2, y_curr + resolution/2, resolution/2);
		}
	}

    epng::png quadtree::decompress() const
	{
		if(!root_)
			throw std::runtime_error("");
		epng::png img {resolution_, resolution_};
		decompress(img, root_, 0, 0, resolution_);
		return img;
	}

	void quadtree::decompress(epng::png & img, const std::unique_ptr<node> & subroot, uint64_t x, uint64_t y, uint64_t resolution) const
	{
		if(resolution == 1){
			*img(x, y) = subroot->element;
			return;
		}
		if(!subroot->northwest)
			for(uint64_t i=x; i<x+resolution/2; i++)
				for(uint64_t j=y; j<y+resolution/2; j++)
					*img(i, j) = subroot->element;
		else
			decompress(img, subroot->northwest, x, y, resolution/2);

		if(!subroot->northeast)
			for(uint64_t i=x+resolution/2; i<x+resolution; i++)
				for(uint64_t j=y; j<y+resolution/2; j++)
					*img(i, j) = subroot->element;
		else
			decompress(img, subroot->northeast, x+resolution/2, y, resolution/2);

		if(!subroot->southwest)
			for(uint64_t i=x; i<x+resolution/2; i++)
				for(uint64_t j=y+resolution/2; j<y+resolution; j++)
					*img(i, j) = subroot->element;
		else
			decompress(img, subroot->southwest, x, y+resolution/2, resolution/2);

		if(!subroot->southeast)
			for(uint64_t i=x+resolution/2; i<x+resolution; i++)
				for(uint64_t j=y+resolution/2; j<y+resolution; j++)
					*img(i, j) = subroot->element;
		else
			decompress(img, subroot->southeast, x+resolution/2, y+resolution/2, resolution/2);
	}

    void quadtree::rotate_clockwise()
	{
		rotate_clockwise(root_);
	}

	void quadtree::rotate_clockwise(std::unique_ptr<node> & subroot)
	{
		if(!subroot)
			return;

		subroot->northeast.swap(subroot->northwest);
		subroot->northwest.swap(subroot->southwest);
		subroot->southwest.swap(subroot->southeast);

		rotate_clockwise(subroot->northwest);
		rotate_clockwise(subroot->northeast);
		rotate_clockwise(subroot->southwest);
		rotate_clockwise(subroot->southeast);
	}

    void quadtree::prune(uint32_t tolerance)
	{
		prune(root_, tolerance);
	}

	void quadtree::prune(std::unique_ptr<node> & subroot, uint32_t tolerance)
	{
		if(isLeaf(subroot))
			return;

		if(isPrunable(subroot, tolerance)){
			subroot->northwest = NULL;
			subroot->northeast = NULL;
			subroot->southwest = NULL;
			subroot->southeast = NULL;
			return;
		}

		prune(subroot->northwest, tolerance);
		prune(subroot->northeast, tolerance);
		prune(subroot->southwest, tolerance);
		prune(subroot->southeast, tolerance);
	}

	uint64_t quadtree::pruned_size(uint32_t tolerance) const
	{
		return pruned_size(root_, tolerance);
	}

    uint64_t quadtree::pruned_size(const std::unique_ptr<node> & subroot, uint32_t tolerance) const
	{
		if(isLeaf(subroot))
			return 1;

		if(isPrunable(subroot, tolerance))
			return 1;

		uint64_t leaves = 0;
		leaves += pruned_size(subroot->northwest, tolerance);
		leaves += pruned_size(subroot->northeast, tolerance);
		leaves += pruned_size(subroot->southwest, tolerance);
		leaves += pruned_size(subroot->southeast, tolerance);

		return leaves;
	}

	bool quadtree::isPrunable(const std::unique_ptr<node> & subroot, uint32_t tolerance) const
	{
		return max_diff(subroot, subroot) <= tolerance;
	}

	uint64_t quadtree::max_diff(const std::unique_ptr<node> & subroot, const std::unique_ptr<node> & leaf) const
	{
		if(isLeaf(leaf)){
			return pow(int(leaf->element.red)-int(subroot->element.red),2)+
			pow(int(leaf->element.green)-int(subroot->element.green),2)+
			pow(int(leaf->element.blue)-int(subroot->element.blue),2);
		}

		int max = 0;
		int tmp;

		tmp = max_diff(subroot, leaf->northwest);
		if(tmp > max)
			max = tmp;
		tmp = max_diff(subroot, leaf->northeast);
		if(tmp > max)
			max = tmp;
		tmp = max_diff(subroot, leaf->southwest);
		if(tmp > max)
			max = tmp;
		tmp = max_diff(subroot, leaf->southeast);
		if(tmp > max)
			max = tmp;

		return max;
	}

	bool quadtree::isLeaf(const std::unique_ptr<node> & subroot) const
	{
		return !subroot->northwest && !subroot->northeast && !subroot->southwest && !subroot->southeast;
	}

    uint32_t quadtree::ideal_prune(uint64_t num_leaves) const
	{
		return ideal_prune(num_leaves, 0, 3*256*256);
	}

	uint32_t quadtree::ideal_prune(uint64_t num_leaves, uint32_t min, uint32_t max) const
	{
		uint32_t guess = (max+min)/2;
		if(pruned_size(guess) <= num_leaves && pruned_size(guess-1) > num_leaves)
			return guess;
		if(pruned_size(guess) <= num_leaves)
			return ideal_prune(num_leaves, min, guess);
		if(pruned_size(guess) > num_leaves)
			return ideal_prune(num_leaves, guess, max);
	}

}
