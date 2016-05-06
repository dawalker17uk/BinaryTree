#ifndef BTREE_H
#define BTREE_H
#endif // BTREE_H

// Resources used for this solution:
//
//      http://www.cprogramming.com/tutorial/lesson18.html


struct node
{
    int dataValue;
    node *left;
    node *right;
};

class btree
{
    public:
        btree();
        ~btree();

        void add(int valueIn);
        void destroyTree();

        //A simple overload method for the == operator
        bool operator==(btree& inTree);
        bool treeSame(btree* inTree);

    private:
        void destroyTree(node *leaf);
        void add(int valueIn, node *leaf);
        //node *searchNode(int valueIn, node *leaf);
        bool treeSame(node *leafA, node *leafB);

        node *root;
};
