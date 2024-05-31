/*
================================================================================
Взято с https://stackoverflow.com/a/24881903

Перечесление не поддерживает константное перечисление т.е. писать 'const auto&'
бесполезно, и в цикле значение все равно может быть изменино.
Само выражение валидно т.к. это структура, но смысл имеет писать только 'auto'
================================================================================
*/

#pragma once

namespace oho {

template <typename T>
class enumerate_wrap {
public:
    // Возвращаемая структура с индексом и значение
    struct item {
        size_t index;
        typename T::value_type& item;
    };
    typedef item value_type;

    // Простой итератор
    struct iterator {
        iterator(typename T::iterator _it, size_t _counter = 0)
            : it(_it), counter(_counter) {}
        
        iterator operator++() { return iterator(++it, ++counter); }
        bool operator!=(iterator other) { return it != other.it; }
        value_type operator* () { return value_type{counter, *it}; }
        typename T::iterator::value_type item() { return *it; }
        size_t index() { return counter; }

    private:
        typename T::iterator it;
        size_t counter;
    };  // end iterator

    enumerate_wrap(T& t): container(t) {}
    iterator begin() { return iterator(container.begin()); }
    iterator end() { return iterator(container.end()); }

private:
    T& container;
};

template <typename T>
enumerate_wrap<T> enumerate(T& c) { return enumerate_wrap<T>(c); }

};