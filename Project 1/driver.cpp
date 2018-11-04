#include <iostream>
#include <string>
using namespace std;

#include "proj1.h"

int main()
{
  Sorter a;                 // Forms Sorting Object
  a.Import();               // Makes one run through default imput and transforms to
                            // organized struct vectors

  int printChar{0};         // Variables used for printout organization
  int printWords{0};
  int printNum{0};
  int printSpacing{20};
  int printSpacingModifier{0};

  charNode charPrint;
  stringNode stringPrint;

  if(a.getAlphaTally() > 10)
    printChar = 10;
  else
    printChar = a.getAlphaTally();

  if(a.getWordTally() > 10)
    printWords = 10;
  else
    printWords = a.getWordTally();

  if(a.getNumTally() > 10)
    printNum = 10;
  else
    printNum = a.getNumTally();

  // ---------- Begin Printout ---------- //

  // ----- Begin Character Printout ----- //
  cout << "Total " << a.getAlphaTally() << " different characters, " << printChar << " most used characters:" << endl;
  for(int i = 0; i < printChar; i++)
  {
    charPrint = a.leadAlpha();
    cout << "No. " << i << ": ";
    if(charPrint.title == '\n')          // Allows \n to print as a literal instead of
                                         // creating a new line in the console printout
    {
      cout << "\\n";
      printSpacingModifier = 2;
    }

    else if(charPrint.title == '\t')     // Allows \t to print as a literal instead of
                                         // creating a tab in the console printout
    {
      cout << "\\t";
      printSpacingModifier = 2;
    }
    else
    {
      cout << charPrint.title;
      printSpacingModifier = 1;
    }

    // Character Spacing
    for(int j = 0; j < printSpacing - (stringPrint.title.length()+printSpacingModifier); j++)
    {
      cout << " ";
    }

    cout << charPrint.occurances << endl;
  }
  // ----- End of Character Printout ----- //


  // ----- Begin Word Printout ----- //
  cout << endl << "Total " << a.getWordTally() << " different words, " << printWords << " most used words:" << endl;
  for(int i = 0; i < printWords; i++)
  {
    stringPrint = a.leadWord();
    cout << "No. " << i << ": " << stringPrint.title;

    // Word Spacing
    for(int j = 0; j < printSpacing - stringPrint.title.length(); j++)
    {
      cout << " ";
    }

    cout << stringPrint.occurances << endl;
  }
  // ----- End of  Word Printout ----- //


  // ----- Begin Number Printout ----- //
  cout << endl << "Total " << a.getNumTally() << " different numbers, " << printNum << " most used numbers:" << endl;
  for(int i = 0; i < printNum; i++)
  {
    stringPrint = a.leadNumber();
    cout << "No. " << i << ": " << stringPrint.title;

    // Numbers Spacing
    for(int j = 0; j < printSpacing - stringPrint.title.length(); j++)
    {
      cout << " ";
    }

    cout << stringPrint.occurances << endl;
  }
  // ----- End of Number Printout ----- //
  // ---------- End Printout ---------- //

  return 0;
}
