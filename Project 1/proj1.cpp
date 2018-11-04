#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include "proj1.h"
using namespace std;

// Default Constructor
Sorter::Sorter()
{
  alphaTally = 0;
  wordTally = 0;
  numTally = 0;
};

// Accessors
const int Sorter::getAlphaTally() const{
  long unsigned int alphaTally{Characters.size()};
  return alphaTally;
};

const int Sorter::getWordTally() const{
  long unsigned int wordTally{Words.size()};
  return wordTally;
};

const int Sorter::getNumTally() const{
  long unsigned int numTally{Numbers.size()};
  return numTally;
};

// Checks for existance of the string in the vector list
// Returns index if present, returns -1 if not present
int Sorter::stringExist(const string potential, const vector<stringNode> typeList) const {
  long unsigned int vectorSize{typeList.size()};
  int existance = -1;

  for(int i = 0; i < vectorSize; i++)
  {
    if((typeList.at(i).title).compare(potential) == 0)
      existance = i;
  }
  return existance;
};

// Same format as stringExist, but modified for char type only
int Sorter::charExist(const char potential, const vector<charNode> typeList) const {
  long unsigned int vectorSize{typeList.size()};
  int existance = -1;

  for(int i = 0; i < vectorSize; i++)
  {
    if((typeList.at(i).title) == potential)
      existance = i;
  }
  return existance;
};


// Main Sorting Mechanic
void Sorter::Import(){
  char target;
  string str;

  target = cin.peek();

  while( !cin.eof() )     // Imput run will continue until End of File is reached
  {
    str = "";

    // Handling for Words
    if(isalpha(target))
    {
      while(isalpha(target))
      {
        cin.get(target);

        // Handling for Characters Within Words
        int exist = charExist(target, Characters);
        if(exist >= 0)
        {
          Characters[exist].occurances = Characters[exist].occurances+1;
        }
        else
        {
          charNode newChar = {.title = target, .occurances = 1};
          Characters.push_back(newChar);
        }
        // End of Handling for Characters Within Words

        target = tolower(target,std::locale()); // Converts all word components to lowercase

        str = str + target;
        target = cin.peek();
      }

      // Checks for existance of the string in Words vector
      int exist = stringExist(str,Words);
      if(exist >= 0)
      {
        Words[exist].occurances = Words[exist].occurances+1;
      }
      else
      {
        stringNode newWord = {.title = str, .occurances = 1};
        Words.push_back(newWord);
      }
    }

    // Handling for Digits
    else if (isdigit(target))
    {
      while (isdigit(target))
      {
        cin.get(target);

        // Handling for Numeric Characters
        int exist = charExist(target, Characters);
        if(exist >= 0)
        {
          Characters[exist].occurances = Characters[exist].occurances+1;
        }
        else
        {
          charNode newChar = {.title = target, .occurances = 1};
          Characters.push_back(newChar);
        }

        str = str + target;
        target = cin.peek();
      }
      int exist = stringExist(str,Numbers);
      if(exist >= 0)
      {
        Numbers[exist].occurances = Numbers[exist].occurances+1;
      }
      else
      {
        stringNode newNumber = {.title = str, .occurances = 1};
        Numbers.push_back(newNumber);
      }

    }

    // Handlign for Other Characters
    else
    {
      cin.get(target);
      int exist = charExist(target, Characters);
      if(exist >= 0)
      {
        Characters[exist].occurances = Characters[exist].occurances+1;
      }
      else
      {
        charNode newChar = {.title = target, .occurances = 1};
        Characters.push_back(newChar);
      }
      target = cin.peek();
    }
  }
};

// Used for printing characters after Import/Sort has completed
// iterates through the characters vector and returns the index
// of the most used character, returning the occurance value of
// the item to 0 so that running the function again will return
// the next most used character
charNode Sorter::leadAlpha()
{
  int leaderOcc{0};
  int leaderMem{0};
  long unsigned int vectorSize{Characters.size()};

  for(int i = 0; i < vectorSize; i++)
  {
    if((Characters.at(i).occurances) > leaderOcc)
    {
      leaderOcc = Characters.at(i).occurances;
      leaderMem = i;
    }
    else if((Characters.at(i).occurances) == leaderOcc)
    {
      char asciiContender = Characters.at(i).title;
      char asciiLeader = Characters.at(leaderMem).title;
      if(asciiContender < asciiLeader)
      {
        leaderOcc = Characters.at(i).occurances;
        leaderMem = i;
      }
    }
  }
  charNode retVal = {.title = Characters.at(leaderMem).title, .occurances = leaderOcc};

  Characters[leaderMem].occurances = 0; // Removes Top Item From Sorting After Returning

  return retVal;
};

// Same concept as Sorter::leadAlpha() but for the Words vector
stringNode Sorter::leadWord()
{
  int leaderOcc{0};
  int leaderMem{0};
  long unsigned int vectorSize{Words.size()};

  for(int i = 0; i < vectorSize; i++)
  {
    if((Words.at(i).occurances) > leaderOcc)
    {
      leaderOcc = Words.at(i).occurances;
      leaderMem = i;
    }
  }
  stringNode retVal = {.title = Words.at(leaderMem).title, .occurances = leaderOcc};

  Words[leaderMem].occurances = 0; // Removes Top Item From Sorting After Returning

  return retVal;
};

// Same concept as Sorter::leadAlpha() but for the Numbers vector
stringNode Sorter::leadNumber()
{
  int leaderOcc{0};
  int leaderMem{0};
  long unsigned int vectorSize{Numbers.size()};

  for(int i = 0; i < vectorSize; i++)
  {
    if((Numbers.at(i).occurances) > leaderOcc)
    {
      leaderOcc = Numbers.at(i).occurances;
      leaderMem = i;
    }
  }
  stringNode retVal = {.title = Numbers.at(leaderMem).title, .occurances = leaderOcc};

  Numbers[leaderMem].occurances = 0; // Removes Top Item From Sorting After Returning

  return retVal;
};
