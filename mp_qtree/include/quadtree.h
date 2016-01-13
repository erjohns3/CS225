/**
 * @file quadtree.h
 * quadtree class definition.
 * @date Spring 2008
 * @date Modified Summer 2014
 */
#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <iostream>
#include <math.h>
#include "epng.h"

namespace cs225
{
/**
* A tree structure that is used to compress epng::png images.
*/
    class quadtree
    {

    private:

        class node
        {
        public:

            node() {}

            std::unique_ptr<node> northwest;
            std::unique_ptr<node> northeast;
            std::unique_ptr<node> southwest;
            std::unique_ptr<node> southeast;

            epng::rgba_pixel element; // the pixel stored as this node's "data"
        };

        epng::rgba_pixel & find(const std::unique_ptr<node> & subroot, uint64_t x_find, uint64_t y_find, uint64_t x_curr, uint64_t y_curr, uint64_t resolution) const;

        void copy_tree(std::unique_ptr<node> & copy, std::unique_ptr<node> & original);

        void build_tree(const epng::png & source, std::unique_ptr<node> & subroot, uint64_t resolution, uint64_t x, uint64_t y);

        void decompress(epng::png & img, const std::unique_ptr<node> & subroot, uint64_t x, uint64_t y, uint64_t resolution) const;

        void rotate_clockwise(std::unique_ptr<node> & subroot);

        void prune(std::unique_ptr<node> & subroot, uint32_t tolerance);

        uint64_t pruned_size(const std::unique_ptr<node> & subroot, uint32_t tolerance) const;

        bool isLeaf(const std::unique_ptr<node> & subroot) const;

        uint32_t ideal_prune(uint64_t num_leaves, uint32_t min, uint32_t max) const;

        bool isPrunable(const std::unique_ptr<node> & subroot, uint32_t tolerance) const;

        uint64_t max_diff(const std::unique_ptr<node> & subroot, const std::unique_ptr<node> & leaf) const;
        /**
        * A simple class representing a single node of a quadtree.
        * You may want to add to this class; in particular, it could
        * probably use a constructor or two...
        */
        std::unique_ptr<node> root_; // the root of the tree

        uint64_t resolution_;

    public:

        quadtree();

        quadtree(const epng::png & source, uint64_t resolution);

        quadtree(quadtree & other);

        quadtree(quadtree && other);

        ~quadtree() = default;

        quadtree & operator=(quadtree rhs);

        void swap(quadtree & other);

        void build_tree(const epng::png & source, uint64_t resolution);

        const epng::rgba_pixel & operator()(uint64_t x, uint64_t y) const;

        epng::png decompress() const;

        void rotate_clockwise();

        void prune(uint32_t tolerance);

        uint64_t pruned_size(uint32_t tolerance) const;

        uint32_t ideal_prune(uint64_t num_leaves) const;
    
    /**** Do not remove this line or copy its contents here! ****/

    #include "quadtree_given.h"

    };
}
#endif
