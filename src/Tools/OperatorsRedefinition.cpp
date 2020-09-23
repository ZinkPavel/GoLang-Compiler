#include "OperatorsRedefinition.h"

template <typename Collection > // тип коллекции
string Join( const Collection & c, char d) { // передаем коллекцию и разделитель
    stringstream ss; // завели строковый поток
    bool first = true; // первый ли это элемент?
    
    for (const auto& i : c) {
        if (! first ) {
            ss << d; // если вывели не первый элемент - кладем поток в разделитель
        }
        first = false; // т.к. следующий элемент точно не будет первым
        ss << i; // кладем следующий элемент в поток
    }
    return ss.str ();
}

template <typename First, typename Second > // для pair
ostream& operator << (ostream& out, const pair<First, Second>& p) {
    return out << '(' <<p. first << ',' << p. second << ')'; // тоже изменили
}

template <typename T> // для vector изменили код и добавили скобочки
ostream& operator << (ostream& out, const vector <T >& vi) {
    return out << '[' << Join(vi , ',') << ']';
} // оператор вывода возвращает ссылку на поток

template <typename Key , typename Value > // для map убрали аналогично vector
ostream & operator << (ostream& out, const map <Key , Value >& m) {
    return out << '{' << Join(m, ',') << '}'; // и добавили фигурные скобочки
}