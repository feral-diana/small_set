//          Copyright Diana Feral 2022
// Distributed under the MIT License, see accompanying file LICENSE

#pragma once

#include <cstdint>
#include <utility>
#include <iterator>

class small_set
{
public:
    constexpr const static unsigned MAX_SIZE = 64;
    using value_type = unsigned;

    class iterator
    {
    public:
        using value_type = unsigned;
        using pointer = unsigned*;
        using reference = unsigned&;
        using difference_type = ptrdiff_t;
        //using iterator_category = std::bidirectional_iterator_tag;
        using iterator_category = std::forward_iterator_tag;

        bool operator==(iterator const& it);
        bool operator!=(iterator const& it);
        iterator& operator++();
        iterator operator++(int);
        unsigned operator*();
        iterator(iterator const&) = default;
        iterator(iterator&&) = default;
        iterator& operator=(iterator const&);
        iterator& operator=(iterator&&);

    private:
        small_set const& _set;
        unsigned _pos;

        inline iterator(small_set const& set, unsigned pos);

        friend class small_set;
    };

    using const_iterator = iterator;

    small_set();
    small_set(small_set&&) = default;
    small_set(small_set const&) = default;
    small_set& operator=(small_set&&) = default;
    small_set& operator=(small_set const&) = default;
    iterator find(unsigned el) const;
    std::pair<iterator, bool> insert(unsigned el);
    iterator insert(iterator, unsigned el);
    void erase(unsigned el);
    unsigned size() const;
    bool empty() const;
    unsigned count(unsigned el) const;
    bool operator==(small_set const& ss) const;
    bool operator!=(small_set const& ss) const;

    iterator begin() const;
    iterator end() const;

private:
    uint64_t _bits = 0;
    unsigned _size = 0;

    inline unsigned _first() const;
    inline unsigned _last() const;
    inline unsigned _next(unsigned pos) const;

    friend class iterator;
};
