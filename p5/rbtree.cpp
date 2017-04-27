// rbtree.cpp 

#include <iostream>
#include <iomanip>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;

// CONSTRUCTORS 

RBTree::RBTree()
{
    nil = new Node();
    root = nil;
}

RBTree::Node::Node()
{
    parent = NULL;
    left = NULL;
    right = NULL;
    key = NULL;
    value = NULL;
    color = 'b';
}

RBTree::Node::Node(const string &key, const string &value)
{
    this->key = new string(key);
    this->value = new string(value);
    parent = NULL;
    left = NULL;
    right = NULL;
    color = 'r';
}

// DESTRUCTORS

RBTree::~RBTree()
{
}

// FUNCTIONS(in alpha order asc)

void RBTree::leftRotate(Node* x)
{
    Node *y = x->right;
    x->right = y->left;
    
    // if y's left child isn't nil, replace y with x
    if(y->left != nil)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if(x->parent == nil)
    {
        root = y;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void RBTree::rbDelete(Node *z)
{
    Node *x;
    Node *y = z;
    char yOGcolor = y->color;

    if(z->left == nil)
    {
        x = z->right;
        rbTransplant(z, z->right);
    }
    else if(z->right == nil)
    {
        x = z->left;
        rbTransplant(z, z->left);
    }
    else
    {
        y = rbTreeMinimum(z->right);
        yOGcolor = y->color;
        x = y->right;
        if(y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(yOGcolor == 'b')
    {
        rbDeleteFixup(x);
    }
}

void RBTree::rbDelete(const string &key, const string &value)
{
    vector<Node*> wordsFound;

    Node *tempNode = rbdTreeSearch(root, key, value);

    while (tempNode != nil)
    {
        wordsFound.push_back(tempNode);
        tempNode = rbdTreeSearch(tempNode->right, key, value);
    }

    while(!wordsFound.empty())
    {
        tempNode = wordsFound.back();
        if(*tempNode->value == value)
        {
            rbDelete(tempNode);
        }
        wordsFound.pop_back();
    }

}

void RBTree::rbDeleteFixup(Node *x)
{
    Node *w;

    while(x != root && x->color == 'b')
    {
        if(x == x->parent->left)
        {
            w = x->parent->right;

            if(w->color == 'r')
            {
                w->color = 'b';
                x->parent->color = 'r';
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if ((w->left->color == 'b') && (w->right->color == 'b'))
            {
                w->color = 'r';
                x = x->parent;
            }
            else
            {
                if (w->right->color == 'b')
                {
                    w->left->color = 'b';
                    w->color = 'r';
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 'b';
                w->right->color = 'b';
                leftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            w = x->parent->left;

            if (w->color == 'r')
            {
                w->color = 'b';
                x->parent->color = 'r';
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if ((w->right->color == 'b') && (w->left->color == 'b'))
            {
                w->color = 'r';
                x = x->parent;
            }
            else
            {
                if (w->left->color == 'b')
                {
                    w->right->color = 'b';
                    w->color = 'r';
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 'b';
                w->left->color = 'b';
                rightRotate(x->parent);
                x = root;
            }
        }
    }
}

vector<const string *> RBTree::rbFind(const string &key)
{
    vector<const string *> wordsFound;
    Node *tempNode = rbTreeSearch(root, key);
    
    while (tempNode != nil)
    {
        wordsFound.push_back(tempNode->value);
        tempNode = rbTreeSearch(tempNode->right, key);
    }

    return wordsFound;
}

void RBTree::rbInsert(Node *z)
{
    Node *y = nil;
    Node *x = root;

    // finds bottom of tree according to BST convention
    while (x != nil)
    {
        y = x;  // trailing pointer
        if(*(z->key) < *(x->key))
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    
    z->parent = y;  // node to insert's parent now = trailing pointer

    if(y == nil)    // if tree is empty
    {
        root = z;
    }
    // if inserted node's value is less than trailing nodes
    else if(*(z->key) < *(y->key))
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    z->left = nil;
    z->right = nil;
    z->color = 'r';

    rbInsertFixup(z);
}

void RBTree::rbInsert(const string &key, const string &value)
{
    Node *node = new Node(key, value);
    rbInsert(node);
}

void RBTree::rbInsertFixup(Node *z)
{
    while(z->parent->color == 'r')
    {
        if(z->parent == z->parent->parent->left)
        {
            Node* y = z->parent->parent->right;
            // case 1
            if(y->color == 'r')
            {
                z->parent->color = 'b';
                y->color = 'b';
                z->parent->parent->color = 'r';
                z = z->parent->parent;
            }
            else
            {
                // case 2
                if(z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                // case 3
                z->parent->color = 'b';
                z->parent->parent->color = 'r';
                rightRotate(z->parent->parent);
            }
        }
        else
        {
            if (z->parent == z->parent->parent->right)
            {
                Node *y = z->parent->parent->left;
                // case 4
                if ((y->color) == 'r')
                {
                    z->parent->color = 'b';
                    y->color = 'b';
                    z->parent->parent->color = 'r';
                    z = z->parent->parent;
                }
                else
                {
                    // case 5
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    // case 6
                    z->parent->color = 'b';
                    z->parent->parent->color = 'r';
                    leftRotate(z->parent->parent);
                }
            }
        }
    }
    root->color = 'b';
}

void RBTree::rbPrintTree()
{
    reverseInOrderPrint(root, 0);
}

void RBTree::rbTransplant(Node *u, Node *v)
{
    if(u->parent == nil)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    
    v->parent = u->parent;
}

RBTree::Node* RBTree::rbTreeMaximum(Node* x)
{
    while(x->right != nil)
    {
        x = x->right;
    }

    return x;
}

RBTree::Node *RBTree::rbTreeMinimum(Node *x)
{
    while(x->left != nil)
    {
        x = x->left;
    }

    return x;
}

RBTree::Node *RBTree::rbTreePredecessor(Node *x)
{
    if (x->left != nil)
    {
        return rbTreeMaximum(x->left);
    }

    Node *y = x->parent;

    while (y != nil && x == y->left)
    {
        x = y;
        y = y->parent;
    }
    return y;
}


RBTree::Node *RBTree::rbTreeSearch(Node *x, const string &key)
{
    while(x != nil && key != *(x->key))
    {
        if(key < *(x->key))
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    return x;
}

RBTree::Node *RBTree::rbTreeSuccessor(Node *x)
{
    if(x->right != nil)
    {
        return rbTreeMinimum(x->right);
    }

    Node *y = x->parent;

    while(y != nil && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

RBTree::Node* RBTree::rbdTreeSearch(Node *x, const string &key, const string &value)
{
    while (x != nil && key != *(x->key))
    {
        x = rbTreeSuccessor(x);
    }

    while (x != nil && value != *(x->value))
    {
        if (value == *(x->value))
        {
            break;
        }
        x = x->right;
    }
    return x;
}

void RBTree::reverseInOrderPrint(Node *x, int depth)
{
    if (x != nil)
    {
        reverseInOrderPrint(x->right, depth + 1);
        cout << setw(depth * 4 + 4) << x->color << " ";
        cout << *(x->key) << " " << *(x->value) << endl;
        reverseInOrderPrint(x->left, depth + 1);
    }
}

void RBTree::rightRotate(Node *x)
{
    Node *y = x->left;
    x->left = y->right;

    // if y's right child isn't nil, replace y with x
    if (y->right != nil)
    {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nil)
    {
        root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}
