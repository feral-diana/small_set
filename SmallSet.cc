//          Copyright Diana Feral 2022
// Distributed under the MIT License, see accompanying file LICENSE

#include "SmallSet.hh"

#include <cassert>

small_set::small_set()
    : _bits(0)
    , _size(0)
{
}

small_set::iterator small_set::find(unsigned el) const
{
    assert(el < MAX_SIZE);
    return (_bits & (uint64_t(1) << el)) ? iterator(*this, el) : end();
}

std::pair<small_set::iterator, bool> small_set::insert(unsigned el)
{
    auto it = find(el);
    if (it != end())
        return {it, false};
    _bits |= (uint64_t)1 << el;
    ++_size;
    return {iterator(*this, el), true};
}

small_set::iterator small_set::insert(iterator, unsigned el)
{
    auto it = find(el);
    if (it != end())
        return it;
    _bits |= (uint64_t)1 << el;
    ++_size;
    return iterator(*this, el);
}

void small_set::erase(unsigned el)
{
    if (!count(el))
        return;
    _bits &= ~((uint64_t)1 << el);
    --_size;
}

unsigned small_set::size() const
{
    return _size;
}

bool small_set::empty() const
{
    return !_size;
}

unsigned small_set::count(unsigned el) const
{
    assert(el < MAX_SIZE);
    return (_bits & (uint64_t(1) << el)) ? 1 : 0;
}

unsigned small_set::_first() const
{
    for (unsigned i = 0; i != MAX_SIZE; ++i)
        if (_bits & ((uint64_t)1 << i))
            return i;
    return _last();
}

unsigned small_set::_last() const
{
    return MAX_SIZE;
}

unsigned small_set::_next(unsigned pos) const
{
    if (pos >= _last())
        return _last();
    for (unsigned i = pos + 1; i != _last(); ++i)
        if (_bits & ((uint64_t)1 << i))
            return i;
    return _last();
}

small_set::iterator::iterator(small_set const& set, unsigned pos)
    : _set(set)
    , _pos(pos)
{
}

small_set::iterator& small_set::iterator::operator++()
{
    _pos = _set._next(_pos);
    return *this;
}

small_set::iterator small_set::iterator::operator++(int)
{
    iterator old(_set, _pos);
    _pos = _set._next(_pos);
    return old;
}

bool small_set::iterator::operator==(small_set::iterator const& it)
{
    return _pos == it._pos;
}

bool small_set::iterator::operator!=(small_set::iterator const& it)
{
    return _pos != it._pos;
}

unsigned small_set::iterator::operator*()
{
    return _pos;
}

small_set::iterator& small_set::iterator::operator=(small_set::iterator const& it)
{
    _pos = it._pos;
    return *this;
}

small_set::iterator& small_set::iterator::operator=(small_set::iterator&& it)
{
    _pos = it._pos;
    return *this;
}

small_set::iterator small_set::begin() const
{
    return iterator(*this, _first());
}

small_set::iterator small_set::end() const
{
    return iterator(*this, _last());
}
    
bool small_set::operator==(small_set const& ss) const
{
    return _bits == ss._bits;
}

bool small_set::operator!=(small_set const& ss) const
{
    return _bits != ss._bits;
}
