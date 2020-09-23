#include "OperatorsRedefinition.h"

template <typename Collection, typename CollectionItem>
std::string Join(const Collection& collection, char delim, std::function<std::string(const CollectionItem& item)> func) {
    std::stringstream ss;
    bool first = true;
    
    for (const auto& item : collection) {
        if (!first) {
            ss << delim;
        }
        first = false;
        ss << func(item);
    }
    return ss.str();
}

template <typename First, typename Second>
std::ostream& operator << (std::ostream& out, const std::pair<First, Second>& p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vector) {
    return out << '[' << Join(vector, ',') << ']';
}

template <typename Key, typename Value>
std::ostream& operator << (std::ostream& out, const std::map<Key, Value>& m) {
    return out << '{' << Join(m, ',') << '}';
}