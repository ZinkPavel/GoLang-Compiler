#pragma once 

# include <iostream>
# include <vector>
# include <map>
# include <sstream>
# include <utility>

using namespace std;

template <typename Collection >
string Join( const Collection & c, char d);

template <typename First, typename Second >
ostream& operator << (ostream& out, const pair<First, Second>& p);

template <typename T>
ostream& operator << (ostream& out, const vector <T >& vi);

template <typename Key , typename Value >
ostream & operator << (ostream& out, const map <Key , Value >& m);