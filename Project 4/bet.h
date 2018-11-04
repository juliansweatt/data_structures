#ifndef BET_H
#define BET_H

using namespace std;
#include <string>

struct BinaryNode
{
    char *element;                                              // Element stored as CString
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode(char e [])                                       // Number Node
    {
        this->element=e;
        this->right=NULL;
        this->left=NULL;
    }

    BinaryNode(char e [], BinaryNode* l, BinaryNode* r)        // Operator Node
    {
        this->element=e;
        this->right=r;
        this->left=l;
    }

};

class BET
{
public:
    BET(); //default zero-parameter constructor.
    BET(const string postfix); //one-parameter constructor, where parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by space.
    BET(const BET&); //copy constructor.
    ~BET(); //destructor.
    bool buildFromPostfix(const string postfix); //parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by space. If the tree contains nodes before the function is called, you need to first delete the existing nodes. Return true if the new tree is built successfully. Return false if an error is encountered.
    const BET & operator= (const BET &); //assignment operator.
    void printInfixExpression(); //call the private version of the printInfixExpression function to print out the infix expression.
    void printPostfixExpression(); //call the private version of the printPostfixExpression function to print out the postfix expression.
    size_t size(); //call the  private version of the size function to return the number of nodes in the tree.
    size_t leaf_nodes(); //call the private version of the leaf_nodes function to return the number of leaf nodes in the tree.
    bool empty(); //return true if the tree is empty. Return false otherwise.

private: //(all the required private member functions must be implemented recursively):
    void printInfixExpression(BinaryNode *n); //print to the standard output the corresponding infix expression. Note that you may need to add parentheses depending on the precedence of operators. You should not have unnecessary parentheses.
    void makeEmpty(BinaryNode* &t); // delete all nodes in the subtree pointed to by t. Called by functions such as the destructor.
    BinaryNode * clone(BinaryNode *t) const; //clone all nodes in the subtree pointed to by t. Called by functions such as the assignment operator=.
    void printPostfixExpression(BinaryNode *n); //print to the standard output the corresponding postfix expression.
    size_t size(BinaryNode *t); //return the number of nodes in the subtree pointed to by t.
    size_t leaf_nodes(BinaryNode *t); //return the number of leaf nodes in the subtree pointed to by t.
    BinaryNode* root = NULL;    // Private root node is used to determine the top of the tree. A tree is empty if root ==NULL.
};

// Global Functions
int getType(char * in);
int getPrecedence(string in);
#endif
