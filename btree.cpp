// Obvois inclusion of btree class member declarations and prototypes
#include "btree.h"

// NULL is not a built-in constant of c++, nullpointer can be used in c++ 11 onward, but for readability and that nullpointer may produce
// unexpected results I have included <stdlib.h> in order to use the NULL type.
#include <stdlib.h>

btree::btree()
{
    // On creation of the object no values or nodes are stored, only nodes can hold values, so with no values/nodes set root to NULL/empty.
    this->root = NULL;
}

btree::~btree()
{
    // On delete of btree object the class must run through all nodes and remove them from memory. not doing so would cause a memory leak,
    // where nodes are still held in heap memory but the reference to them is lost.
    // destroyTree() is a high level delete function and passes the root node to deleteTree(node *leaf) to handle deleting children/branches.
    destroyTree();
}

void btree::add(int valueIn)
{
    // The first test is to determine root is null or to start moving down the branches to add a new node to an existing tree structure.
    if(this->root != NULL)
    {
        // root has a value so move to determine left/right logic in add(int valueIn, *leaf)
        add(valueIn, this->root);
    }
    else
    {
        // root is NULL so add create new node in heap and add it's reference to root.
        this->root=new node;
        this->root->dataValue = valueIn;
        this->root->left = NULL;
        this->root->right = NULL;
    }
}

void btree::destroyTree()
{
    // High level public destroy function, call the main destroy function
    destroyTree(this->root);
}

bool btree::operator==(btree& inTree)
{
    // We now have access to two btree object; accessible using this-> and inTree.
    btree* myTree = &inTree;
    return treeSame(myTree);
}

bool btree::treeSame(btree* inTree)
{
    int rootANull = (this->root==NULL) ? 0: 1;
    int rootBNull = (inTree->root==NULL) ? 0: 1;

    // Both root nodes == null, structure and value are a match, as there are none.
    if ( (rootANull == 0) && (rootBNull == 0) )
    {
        return true;
    }
    // one of the trees has a node in root while the other doesn't, so structure not the same.
    else if (rootANull != rootBNull)
    {
        return false;
    }
    // both of the root values has a valid node, check values
    else
    {
        if (this->root->dataValue != inTree->root->dataValue)
        {
            return false;
        }
        else
        {
            int leafAleft = (this->root->left == NULL) ? 0 : 1;      // simple ternary calculation if A node has a left child
            int leafBleft = (inTree->root->left == NULL) ? 0 : 1;      // simple ternary calculation if B node has a left child
            int leafAright = (this->root->right == NULL) ? 0 : 1;    // simple ternary calculation if A node has a right child
            int leafBright = (inTree->root->right == NULL) ? 0 : 1;    // simple ternary calculation if B node has a right child

            if ( leafAleft != leafBleft )
            {
                return false;
            }
            else if (leafAright != leafBright )
            {
                return false;
            }
            else if (leafAleft != 0)
            {
                if ( treeSame(this->root->left, inTree->root->left) == false )
                {
                    return false;
                }
                else
                {
                    if (leafAright != 0)
                    {
                        return treeSame(this->root->right, inTree->root->right);
                    }
                    else
                    {
                        return true;
                    }
                }
            }
            else
            {
                if (leafAright != 0)
                    {
                        return treeSame(this->root->right, inTree->root->right);
                    }
                    else
                    {
                        return true;
                    }
            }
            //treeSame(this->root->right, inTree->root->right) == false)

        }

    }
}


//private members
void btree::destroyTree(node *leaf)
{
    // if leaf is null then there is nothing to do.
    if (leaf!=NULL)
    {
        // Recursive calls to destroyTree(node *leaf) for left node and right node, due to recursion all children/branches will have been deleted
        // before deleting itself.
        // Recursion is suitbale for smaller data sets but has the possibility to hog memory, for large data sets another method would be required.
        destroyTree(leaf->left);
        destroyTree(leaf->right);
        delete leaf;
    }
}

void btree::add(int valueIn, node *leaf)
{
    // As add(int valueIn) instantiates the first value (root) when the first add(int valueIn) is called,
    // after this first element is added we are always going to be using a node with a value within the dataValue member of the passed in node/leaf.
    // Here we determine if the value being added is less (add to left node) or greater then (add to right node) the current leafs dataValue
    if(valueIn < leaf->dataValue)
    {
        // Check if there is a non null node in left, if node is null add a new node if a valid node exists then call the add function again but this time
        // pass the left node pointer as the argument.
        if(leaf->left!=NULL)
        {
            add(valueIn, leaf->left);
        }
        else
        {
            leaf->left=new node;
            leaf->left->dataValue=valueIn;
            leaf->left->left=NULL;
            leaf->left->right=NULL;
        }
    }
    else if(valueIn > leaf->dataValue)
    {
        // Check if there is a non null node in right, if node is null add a new node if a valid node exists then call the add function again but this time
        // pass the right node pointer as the argument.
        if(leaf->right!=NULL)
        {
            add(valueIn, leaf->right);
        }
        else
        {
            leaf->right=new node;
            leaf->right->dataValue=valueIn;
            leaf->right->left=NULL;
            leaf->right->right=NULL;
        }
    }
    else
    {
        //Assumption is all values are unique, in event of multiple same value being added then do nothing.
    }
}

bool btree::treeSame(node *leafA, node *leafB)
{
    // to cut down on code further down the function, and to make in more easily readable, the variables bellow represent if a childe node exists using
    // 1 or 0.

    int leafAleft = (leafA->left == NULL) ? 0 : 1;      // simple ternary calculation if A node has a left child
    int leafBleft = (leafB->left == NULL) ? 0 : 1;      // simple ternary calculation if B node has a left child
    int leafAright = (leafA->right == NULL) ? 0 : 1;    // simple ternary calculation if A node has a right child
    int leafBright = (leafB->right == NULL) ? 0 : 1;    // simple ternary calculation if B node has a right child

    // check data value first, if not the same return false
    if (leafA->dataValue != leafB->dataValue)
    {
        return false;
    }
    // the above integer variables contain a 0 if there is no left/right node, if sum of all values is 0 then
    // the current node has no children nodes, if greater of equal to one then one of the nodes has a child.
    else if (leafAleft+leafBleft+leafAright+leafBright==0)
    {
        return true;
    }
    // check if both nodes A and B are the same, if one has a left child node but the other doesn't then return false as structure is
    // not the same.
    else if (leafAleft != leafBleft)
    {
        return false;

    }
    // check if both nodes A and B are the same, if one has a right child node but the other doesn't then return false as structure is
    // not the same.
    else if (leafAright != leafBright)
    {
        return false;
    }
    else
    {
        // nodes A and B have a left child but not a right
        if ( (leafAleft != 0) && (leafAright == 1) )
        {
            return treeSame(leafA->left, leafB->left);
        }
        // nodes A and B have a right child but not a left
        else if (leafAleft == 0 && leafAright != 1)
        {
            return treeSame(leafA->right, leafB->right);
        }
        // nodes A and B have both a left and right child
        else
        {
            // The bellow first checks the left child node, if false then return false, if true then check the right child node.
            if ( (treeSame(leafA->left, leafB->left)==false) )
            {
                return false;
            }
            else
            {
                    if (treeSame(leafA->right, leafB->right)==false)
                    {
                        return false;
                    }
                    else
                    {
                        // subsequently this function should return true only if the value is the same, and no children exist in either left or right nodes.
                        return true;
                    }
            }
        }

    }
}
