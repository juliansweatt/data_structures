#ifndef PROJ1_H
#define PROJ1_H

#include <vector>

using namespace std;

struct stringNode
{
  string title;
  int occurances;
};

struct charNode
{
  char title;
  int occurances;
};

class Sorter{
public:
  Sorter();
  void Import();
  const int getAlphaTally() const;
  const int getWordTally() const;
  const int getNumTally() const;
  charNode leadAlpha();
  stringNode leadWord();
  stringNode leadNumber();

private:
  int stringExist(const string potential, const vector<stringNode> typeList) const;
  int charExist(const char potential, const vector<charNode> typeList) const;
  int alphaTally;
  int wordTally;
  int numTally;
  vector<stringNode> Numbers;
  vector<stringNode> Words;
  vector<charNode> Characters;
};

#endif
