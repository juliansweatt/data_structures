#include <iostream>
#include <string>
#include "stack.h"

using namespace std;
using namespace cop4530;

int getPrecedence(char o);

int main()
{
  string userIn = "";
  string inFix = "";
  bool alive = true;
  bool noVars = true;
  bool valid = true;
  int leftParCount = 0;
  int rightParCount = 0;
  int numNum = 0;
  int numOperand = 0;
  auto previouslyProcessed = '\0';

  Stack<char> operators;
  Stack<double> eval;

  while(alive == true)
  {
    cout << "Enter infix expression (\"exit\" to quit): ";
    getline(cin, userIn);
    cout << endl;
    if(userIn == "exit")
    {
      alive = false;
      break;
    }

    for(int i = 0; i < userIn.length(); i++)
    {
      while(i >= userIn.length()&&(iswspace(userIn.at(i)))!= 0)
      {
        i++;
        if(i >= userIn.length())
        {
          break;
          valid = false;
        }
      }

      if(isalnum(userIn.at(i))!=0 || userIn.at(i)=='_' && valid)
      {
        while((isalnum(userIn.at(i))!=0 || userIn.at(i)=='_' )&& userIn.at(i) != '\0' && userIn.at(i) != ' ')
        {
          if(isdigit(userIn.at(i))==0)
            noVars = false;
          if(i == (userIn.length()-1))
          {
            break;
          }
          if(userIn.at(i) != ' ')
            inFix += userIn.at(i);
          i++;
        }
        if(userIn.at(i) != ' ')
          inFix += userIn.at(i);
        inFix += " ";
      }
      else if(userIn.at(i)=='(' || userIn.at(i)==')' && valid)
      {
        if(userIn.at(i)=='(')
        {
          operators.push(userIn.at(i));
          leftParCount++;
        }

        else if(userIn.at(i)==')')
        {
          rightParCount++;
          if(previouslyProcessed=='*' || previouslyProcessed=='/' || previouslyProcessed=='+' || previouslyProcessed=='-')      // If operator then ), report error
          {
            cout << "Error: Missing operands in the expression" << endl;
            break;
          }
          else
          {
            while(operators.top() != '(' && (!operators.empty()))
            {
              if(operators.top() != ' ')
              {
                inFix += operators.top();
                inFix += " ";
              }
              operators.pop();
            }
          }
          operators.pop();  // Disgards parethesis (
        }
      }
      else if(userIn.at(i)=='+' || userIn.at(i)=='-' || userIn.at(i)=='*' || userIn.at(i)=='/' && valid)
      {
        while(!(operators.empty()) && (operators.top()!='(') && !(getPrecedence(operators.top())<getPrecedence(userIn.at(i))))
        {
          if(operators.top() != ' ')
          {
            inFix += operators.top();
            inFix += " ";
          }
          operators.pop();
        }
        operators.push(userIn.at(i));
      }
       previouslyProcessed = userIn.at(i);
    }
    while(!(operators.empty()))
    {
      if(operators.top() != ' ')
        {
          inFix += (operators.top());
          inFix += " ";
        }
      operators.pop();
    }
    if(leftParCount != rightParCount && userIn.length() > 0 )
      valid = false;

    if(!valid)
    {
      cout<< "Error: Infix expression: " << userIn << " is has mismatched parens!" << endl;
    }

    if(valid)
      {cout << "Postfix expression: " << inFix << endl;}
    // Evaluation:

    if(!noVars && valid)
    {
      cout << "Postfix evaluation: " << inFix << " = " << inFix << endl;
    }
    else
    {
      cout << "Postfix evaluation: " << inFix << " = ";

      for(int i = 0; i < inFix.length(); i++)
      {

        if(inFix.at(i)==' ')
        {
          // Do Nothing
        }
        else if((!(inFix.at(i)=='+' || inFix.at(i)=='-' || inFix.at(i)=='*' || inFix.at(i)=='/')))
        {
          string stringDigit = "";

          double operand = 0;
          while(inFix.at(i)!=' ')
          {
            stringDigit += inFix.at(i);
            i++;
          }

          if(stringDigit != "")
          {
            operand = stod(stringDigit,nullptr);
            eval.push(operand);
            numNum++;
          }
        }
        else if(inFix.at(i)=='+' || inFix.at(i)=='-' || inFix.at(i)=='*' || inFix.at(i)=='/')
        {
          numOperand++;
          double a,b;
          if(!eval.empty())
          {
            a = eval.top();
            eval.pop();
          }
          if(!eval.empty())
          {
            b = eval.top();
            eval.pop();
          }

          if(inFix.at(i)=='+')
          {
            eval.push(a+b);
          }
          else if(inFix.at(i)=='-')
          {
            eval.push(b-a);
          }
          else if(inFix.at(i)=='*')
          {
            eval.push(a*b);
          }
          else if(inFix.at(i)=='/')
          {
            eval.push(b/a);
          }
        }

      }
      double completed;
      if(eval.empty())
      {
        completed = 0;
      }
      else
      {
        completed = eval.top();
        eval.pop();
      }

      if(numOperand > numNum)
      {
        cout << endl << "Error: Missing operands in the expression" << endl;
      }
      else if(numOperand != (numNum - 1))
      {
        cout  <<endl<< "Error: Missing operand in postfix string. Unable to evaluate postfix string!" << endl;
      }
      else if(eval.empty())
      {
        cout << completed << endl;
      }
      else
      {
        cout << completed << endl;
        cout << "Error: Unexpected operand in stack: " << eval << endl;
      }
    }
    // RESET HANDLING
    inFix = "";
    userIn = "";
    previouslyProcessed = '\0';
    operators.clear();
    eval.clear();
    valid = true;
    noVars = true;
    alive = true;
    numNum = 0;
    numOperand = 0;
  }
  return 0;
}

int getPrecedence(char o)
{
  if(o == '*' || o =='/')
    return 1;
  else if(o == '-' || o == '+')
    return 0;
  else if(o == ')')
    return 3;
  else if(o == '(')
    return 2;
  else
    return -1;
}
