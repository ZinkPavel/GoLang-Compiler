#include "OperatorsRedefinition.h"

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