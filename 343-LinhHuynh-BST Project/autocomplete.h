#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "bstmap.h"

using namespace std;

class Autocomplete
{
public:
  Autocomplete() = default;
  void readFile(const string &fileName);
  vector<BSTMap::value_type> complete(const string &prefix) const;

private:
  // BST of phrases and their frequency
  BSTMap phrases;

  // sorter
  bool static sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b);

  string trim(const string &s)
  {
    // Find the first non-whitespace character
    auto start = s.begin();
    while (start != s.end() && isspace(*start))
    {
      ++start;
    }

    // Find the last non-whitespace character
    auto end = s.end();
    do
    {
      --end;
    } while (end != start && isspace(*end));

    // Return the trimmed string
    return string(start, end + 1);
  }
};

#endif // AUTOCOMPLETE_H
