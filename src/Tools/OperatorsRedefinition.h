#pragma once 

# include <iostream>
# include <vector>
# include <map>
# include <sstream>
# include <utility>

template <typename Collection>
std::string Join(const Collection& collection, char delim) {
    std::stringstream ss;
    bool first = true;
    
    for (const auto& item : collection) {
        if (!first) {
            ss << delim;
        }
        first = false;
        ss << item;
    }
    return ss.str();
}

template <typename First, typename Second>
std::ostream& operator << (std::ostream& out, const std::pair<First, Second>& p);

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vi);

template <typename Key, typename Value>
std::ostream& operator << (std::ostream& out, const std::map<Key, Value>& m);