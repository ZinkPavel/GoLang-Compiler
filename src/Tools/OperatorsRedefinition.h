#pragma once 

# include <iostream>
# include <vector>
# include <map>
# include <sstream>
# include <utility>
#include <functional>

template <typename Collection, typename CollectionItem>
std::string Join(const Collection& collection, char delim, std::function<std::string(const CollectionItem& item)> func);

template <typename First, typename Second>
std::ostream& operator << (std::ostream& out, const std::pair<First, Second>& p);

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vi);

template <typename Key, typename Value>
std::ostream& operator << (std::ostream& out, const std::map<Key, Value>& m);