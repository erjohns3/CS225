/**
 * @file binary_tree.tcc
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class T>
int binary_tree<T>::height() const
{
    // Call recursive helper function on root
    return height(root_.get());
}

template <class T>
int binary_tree<T>::height(const node* subRoot) const
{
    // Base case
    if (!subRoot)
        return -1;

    // Recursive definition
    auto left = height(subRoot->left.get());
    auto right = height(subRoot->right.get());
    return std::max(left, right) + 1;
}

template <class T>
void binary_tree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root_.get());

    // Finish the line
    std::cout<< std::endl;
}

template <class T>
void binary_tree<T>::printLeftToRight(const node* subRoot) const
{
    // Base case - null node
    if (!subRoot)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left.get());

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right.get());
}

template <class T>
void binary_tree<T>::mirror()
{
    /// @todo your code here
    mirror(root_.get());
}

template <class T>
void binary_tree<T>::mirror(node* sub_root)
{
    /// @todo your code here
    if(!sub_root)
    	return;
    
    sub_root->left.swap(sub_root->right);
    mirror(sub_root->left.get());
    mirror(sub_root->right.get());
}

template <class T>
bool binary_tree<T>::isOrdered() const
{
    /// @todo your code here
    return isOrdered(root_.get(), true) != -1;
    	
}

template <class T>
T binary_tree<T>::isOrdered(node* sub_root, bool max) const
{
    /// @todo your code here
    if(!(sub_root->left) && !(sub_root->right))
        return sub_root->elem;
    if(sub_root->left && sub_root->elem < sub_root->left->elem)
        return -1;
    if(sub_root->right && sub_root->elem > sub_root->right->elem)
        return -1;
    T left;
    T right;
    if(sub_root->left)
        left = isOrdered(sub_root->left.get(),true);
    else
        left = sub_root->elem;
    if(sub_root->right)
        right = isOrdered(sub_root->right.get(),false);
    else
        right = sub_root->elem;
    if(left == -1 || right == -1)
    	return -1;
    if(sub_root->elem < left || sub_root->elem > right)
    	return -1;
    if(max)
    	return right;
    else
    	return left;
}

template <class T>
void binary_tree<T>::printPaths() const
{
    /// @todo your code here
    std::vector<int> path;
    printPaths(root_.get(),path);
}

template <class T>
void binary_tree<T>::printPaths(node* sub_root, std::vector<T> path) const
{
    /// @todo your code here
    std::vector<T> tmp = path;
    tmp.push_back(sub_root->elem);
    if(sub_root->left.get() == NULL && sub_root->right.get() == NULL){
        std::cout<<"Path:";
        for(int i=0; i<tmp.size(); i++)
            std::cout<<" "<<tmp[i];
        std::cout<<std::endl;
        return;
    }
    if(sub_root->left.get() != NULL)
        printPaths(sub_root->left.get(), tmp);
    if(sub_root->right.get() != NULL)
        printPaths(sub_root->right.get(), tmp);
}

template <class T>
uint64_t binary_tree<T>::sumDistances() const
{
    /// @todo your code here
    return sumDistances(root_.get(),0);
}

template <class T>
uint64_t binary_tree<T>::sumDistances(node* sub_root, uint64_t x) const
{
    /// @todo your code here
    if(!sub_root)
        return 0;
    return sumDistances(sub_root->left.get(),x+1) + sumDistances(sub_root->right.get(),x+1) + x;
}