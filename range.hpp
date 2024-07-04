#pragma once
#include <iterator>
#include <stdexcept>

/*
Example:

for (const auto& i : Range(10))
    std::cout << i << " ";
std::cout << std::endl;

for (const auto& i : Range(10, 0, -3))
    std::cout << i << " ";
std::cout << std::endl;

Output:
0 1 2 3 4 5 6 7 8 9
10 7 4 1
*/

namespace oho {

class Range {
public:
    class iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = std::ptrdiff_t;
        using difference_type = std::ptrdiff_t;
        using pointer   = const value_type*;
        using reference = const value_type&;

        explicit iterator(value_type _cur, value_type _step)
            : current(_cur), step(_step) {}
        iterator(const iterator& it)
            : current(it.current), step(it.step) {}
        iterator& operator=(const iterator& it) {
            current = it.current;
            step = it.step;
            return *this;
        }
        ~iterator() = default;

        bool operator==(const iterator& it) const { return current == it.current; }
        bool operator!=(const iterator& it) const { return !(*this == it); }

        reference operator*() const { return current; }
        iterator& operator++() {
            current += step;
            return *this;
        }
        iterator operator++(int) {
            iterator it = *this;
            ++(*this);
            return it;
        }

    private:
        value_type current;
        value_type step;
    };

    Range(std::ptrdiff_t _start, std::ptrdiff_t _stop, std::ptrdiff_t _step)
    : start(_start), stop(_stop), step(_step), isReverse(_stop - _start < 0) {
        if (_step == 0)
            throw std::invalid_argument("step parametr must be non-zero");
        if (_stop - _start == 0)
            return;

        if (_stop - _start >= 0 && _step < 0)
            throw std::invalid_argument("step for forward range must be positive");
        if (_start - _stop >= 0 && _step > 0)
            throw std::invalid_argument("step for reverse range must be negative");
    }
    Range(std::ptrdiff_t _start, std::ptrdiff_t _stop): Range(_start, _stop, 1) {}
    Range(std::ptrdiff_t _stop): Range(0, _stop, 1) {}

    iterator begin() const {
        return iterator(start, step);
    }
    iterator end() const {
        std::ptrdiff_t range_count;

        if (isReverse) range_count = start - stop;
        else           range_count = stop - start;
        
        if (range_count == 0)
            return iterator(start, step);
        
        std::ptrdiff_t gap = range_count % step;
        if (gap == 0)
            return iterator(stop, step);
        
        return iterator(stop + step - gap * (isReverse ? -1 : 1), step);
    }

    std::ptrdiff_t getStart() const { return start; }
    std::ptrdiff_t getStop()  const { return  stop; }
    std::ptrdiff_t getStep()  const { return  step; }

private:
    std::ptrdiff_t start;
    std::ptrdiff_t stop;
    std::ptrdiff_t step;
    bool isReverse;
};

}