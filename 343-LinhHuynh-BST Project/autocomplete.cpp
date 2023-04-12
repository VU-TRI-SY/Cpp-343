#include "autocomplete.h"
#include <algorithm>
#include <fstream>

using namespace std;

void testBSTAll();

void Autocomplete::readFile(const string &fileName) {
  ifstream ifs(fileName);
  // TODO(student)
  if(ifs.is_open()){
    int no_of_pairs;
    ifs >> no_of_pairs;
    for(int i = 0; i < no_of_pairs; i++){
      BSTMap::mapped_type value; //number
      BSTMap::key_type key; //string
      ifs >> value; 
      getline(ifs, key, '\n');
      key = trim(key);
      phrases[key] = value;
    }
  }
  ifs.close();
  phrases.rebalance();
  // cout << phrases << endl;
}

bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

vector<BSTMap::value_type>
Autocomplete::complete(const BSTMap::key_type &prefix) const {
  vector<BSTMap::value_type> v;
  // TODO(student)
  v = phrases.getAll(prefix);
  sort(v.begin(), v.end(), sortByWeight);
  return v;
}
