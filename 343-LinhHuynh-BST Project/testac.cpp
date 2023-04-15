#include "autocomplete.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testAC01() {
  cout << "Starting AC test01" << endl;
  cout << "* Testing basic autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("hel");
  assert(v.size() == 2);
  assert(v[0].first == "help");
  assert(v[0].second == 20);
  assert(v[1].first == "hello");
  assert(v[1].second == 10);
  cout << "Ending tesAC01" << endl;
}

void testAC02() {
  cout << "Starting AC test02" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Sea");
  assert(v.size() == 47);
  assert(v[0].first == "Seattle, Washington, United States");
  assert(v[0].second == 608660);
  assert(v[46].first == "Seabeck, Washington, United States");
  assert(v[46].second == 1105);
  cout << "Ending tesAC02" << endl;
}

void testAC03() {
  cout << "Starting AC test03" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Seo");
  assert(v.size() == 9);
  assert(v[0].first == "Seoul, South Korea");
  assert(v[0].second == 10349312);
  assert(v[8].first == "Seoni, India");
  assert(v[8].second == 1630);
  cout << "Ending tesAC03" << endl;
}

void testAC04() {
  cout << "Starting AC test04" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Mum");
  assert(v.size() == 5);
  assert(v[0].first == "Mumbai, India");
  assert(v[0].second == 12691836);
  assert(v[4].first == "Mumpf, Switzerland");
  assert(v[4].second == 1425);
  cout << "Ending tesAC04" << endl;
}

void testAC05() {
  cout << "Starting AC test05" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("wiktionary.txt");
  auto v = ac.complete("knee");
  assert(v.size() == 4);
  assert(v[0].first == "knees");
  assert(v[0].second == 4964210);
  assert(v[3].first == "kneel");
  assert(v[3].second == 564711);
  cout << "Ending tesAC05" << endl;
}

void testAC06() {
  cout << "Starting AC test04" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("wiktionary.txt");
  auto v = ac.complete("bee");
  assert(v.size() == 5);
  assert(v[0].first == "been");
  assert(v[0].second == 235765400);
  assert(v[4].first == "bees");
  assert(v[4].second == 975152);
  cout << "Ending tesAC06" << endl;
}

// // Calling all test functions
void testACAll() {
  testAC01();
  testAC02();
  testAC03();
  testAC04();
  testAC05();
  testAC06();
}

int main(){
  testACAll();
}