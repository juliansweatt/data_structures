#include <iostream>
#include <stack>
#include <string>
#include <cstring>
#include "bet.h"
#include <vector>

using namespace std;

enum elementType { OPERATOR, OPERAND = 2};        // Enumeration declared to make getType() more easily read

BET::BET()
{
    root=NULL;
}

BET::BET(const string postfix)                    // Single Parameter Constructor
{
    buildFromPostfix(postfix);
}

 BET::BET(const BET& tree)                        // Copy Constructor
 {
 root = clone(tree.root);
 }

BET::~BET()                                       // Destructor
{
    makeEmpty(root);
}

bool BET::buildFromPostfix(const string postfix)  // Populate binary tree in post-order
{
    stack<BinaryNode*> nodeStack;
    int operandCount = 0;
    int operatorCount = 0;
    bool forcedAbort = false;

    // String Tokenization (Inspired by Java's StringTokenizer)
    // postfix string tokenization into a vector of CStrings with delimiter of space
    // Implemented with string tokenization to make operands which begin with operators possible, such as postfix:"+5 *62 /"
    // which would become +5 / *62
    vector<char*> tokenVector;
    char * postfixCSTRING = new char [postfix.length()+1];
    strcpy(postfixCSTRING, postfix.c_str());
    for(char * token = strtok(postfixCSTRING," \t"); token !=NULL; token = strtok(NULL, " \t"))
    {
        tokenVector.push_back(token);
    }

    for(size_t i = 0; i < tokenVector.size(); i++)          // Counts operators/operands for pre-treebuild invalid input detection
    {
        if(getType(tokenVector[i]) == OPERATOR)             // Oporator
        {
            operatorCount++;
        }
        else if(getType(tokenVector[i])==OPERAND)           // Operand
        {
            operandCount++;
        }
    }

    for(size_t i = 0; i < tokenVector.size(); i++)          // Build Tree in Post-Fix Order
    {
        if(getType(tokenVector[i]) == OPERATOR)             // Oporator
        {
            if(nodeStack.size()==0)                         // Abort build and destroy tree if expression is left unbalanced
            {
                forcedAbort = true;
                break;
            }
            BinaryNode* right = nodeStack.top();
            nodeStack.pop();
            if(nodeStack.size()==0)                         // Abort build and destroy tree if expression is right unbalanced
            {
                forcedAbort = true;
                break;
            }
            BinaryNode* left = nodeStack.top();
            nodeStack.pop();
            BinaryNode* newNode = new BinaryNode(tokenVector[i], left, right);
            nodeStack.push(newNode);
        }
        else if(getType(tokenVector[i])==OPERAND)           // Operand
        {
            string variableString = tokenVector[i];
            BinaryNode* newNode = new BinaryNode(tokenVector[i]);
            nodeStack.push(newNode);
        }
    }

    // Unbalanced error handling
    if(forcedAbort)
    {
        cout << "Wrong postfix expression." << endl;
        makeEmpty(root);
        return false;
    }

    root = nodeStack.top();                              // Set stack root as the branch tree root
    return true;
}

const BET&BET::operator= (const BET & tree)
{
 root = clone(tree.root);
 return *this;
}

 void BET::printInfixExpression()
 {
     printInfixExpression(root);
     cout << endl;
 }

void BET::printPostfixExpression()
{
    printPostfixExpression(root);
    cout << endl;
}

size_t BET::size()
{
    return size(root);
}

size_t BET::leaf_nodes()
{
    return leaf_nodes(root);
}

bool BET::empty()                                                       // May also be implemented by checking if root is NULL
{
    if(size() == 0)
        return true;
    else
        return false;
}

// Private (Recrusive) Functions
void BET::printInfixExpression(BinaryNode *n)
{
    if(n->left != NULL || n->right != NULL)                            // If node is NOT a leaf (parenthesis handling)
    {
        if((getPrecedence(n->element) > getPrecedence(n->left->element)))
        {
            cout << "( ";
            printInfixExpression(n->left);
            cout << " )";
        }
        else
            printInfixExpression(n->left);

        cout << ' ' << n->element << ' ';

        if((getPrecedence(n->element) >= getPrecedence(n->right->element)))
        {
            cout << "( ";
            printInfixExpression(n->right);
            cout << " )";
        }
        else
            printInfixExpression(n->right);
    }
    else
        cout <<  n->element;
}

void BET::makeEmpty(BinaryNode* &t)
{
    if(t != NULL)
    {
        makeEmpty(t->left);                                    // Release left child (and subsequent children)
        makeEmpty(t->right);                                   // Release right child (and subsequent children)
        delete t;                                              // Release self once children are released
    }
    t=NULL;                                                    // Release root
}

BinaryNode * BET::clone(BinaryNode *t) const
{
    BinaryNode* node;
    if (t==NULL)
    {
        return NULL;
    }
    else
    {
        node = new BinaryNode(t->element, clone(t->left), clone(t->right));
        return node;
    }
}

void BET::printPostfixExpression(BinaryNode *n)                // Tree already stored in Postfix, just print in order
{
    if( n != NULL)
    {
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        cout << n->element << " ";
    }
}

size_t BET::size(BinaryNode *t)
{
    size_t retsize = 0;

    if(t != NULL)
    {
        retsize += size(t->left);
        retsize += size(t->right);
        retsize++;
    }

    return retsize;
}

size_t BET::leaf_nodes(BinaryNode *t)                          // Similar implementation to size() but don't count nodes with children
{
    size_t leaves = 0;

    if(t != NULL && (t->left == NULL && t->right == NULL))     // Leaves have no children and can be tallied
    {
        leaves++;
        return leaves;
    }
    else                                                       // Nodes with children arent leaves, don't increment
    {
        leaves += leaf_nodes(t->left);
        leaves += leaf_nodes(t->right);
        return leaves;
    }
}

// Global Functions
int getType(char * in)
{
    if(strcmp(in, "+")==0 || strcmp(in, "-")==0 || strcmp(in, "/")==0 || strcmp(in, "*")==0)
        return OPERATOR;
    else
        return OPERAND;
}

int getPrecedence(string in)
{

    if(in == "+" || in == "-")
    {
        return 1;
    }
    else if(in == "*" || in == "/")
    {
        return 2;
    }
    else if(in.length() > 1)
    {
        return 4;
    }
    else
        return 4;
}
