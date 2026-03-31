#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

#include <map>
#include <utility>
#include <functional>
#include <stdexcept>
#include <cstddef>

namespace sjtu {

template <class Key, class T, class Compare = std::less<Key>>
class map {
    using base_map = std::map<Key, T, Compare>;
public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const Key, T>;
    using size_type = std::size_t;
    using key_compare = Compare;

    class const_iterator;

    class iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = std::pair<const Key, T>;
        using pointer = value_type*; // pointer-like in operator->
        using reference = value_type&; // via base iterator
        using iterator_category = std::bidirectional_iterator_tag;

        iterator() = default;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;

        value_type & operator*() const { return const_cast<value_type&>(*it_); }
        value_type * operator->() const { return const_cast<value_type*>(&*it_); }

        iterator & operator++() { ++it_; return *this; }
        iterator operator++(int) { iterator tmp(*this); ++it_; return tmp; }
        iterator & operator--() { --it_; return *this; }
        iterator operator--(int) { iterator tmp(*this); --it_; return tmp; }

        bool operator==(const iterator &rhs) const { return it_ == rhs.it_; }
        bool operator!=(const iterator &rhs) const { return it_ != rhs.it_; }

    private:
        friend class map;
        friend class const_iterator;
        explicit iterator(typename base_map::iterator it) : it_(it) {}
        typename base_map::iterator it_{};
    };

    class const_iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = const std::pair<const Key, T>;
        using pointer = const value_type*;
        using reference = const value_type&;
        using iterator_category = std::bidirectional_iterator_tag;

        const_iterator() = default;
        const_iterator(const const_iterator&) = default;
        const_iterator(const iterator &it) : it_(it.it_) {}
        const_iterator& operator=(const const_iterator&) = default;

        reference operator*() const { return *it_; }
        pointer operator->() const { return &*it_; }

        const_iterator & operator++() { ++it_; return *this; }
        const_iterator operator++(int) { const_iterator tmp(*this); ++it_; return tmp; }
        const_iterator & operator--() { --it_; return *this; }
        const_iterator operator--(int) { const_iterator tmp(*this); --it_; return tmp; }

        bool operator==(const const_iterator &rhs) const { return it_ == rhs.it_; }
        bool operator!=(const const_iterator &rhs) const { return it_ != rhs.it_; }

    private:
        friend class map;
        explicit const_iterator(typename base_map::const_iterator it) : it_(it) {}
        typename base_map::const_iterator it_{};
    };

    map() = default;
    explicit map(const Compare &comp) : m_(comp) {}
    map(const map &other) = default;
    map & operator=(const map &other) = default;
    ~map() = default;

    T & at(const Key &key) {
        auto it = m_.find(key);
        if (it == m_.end()) throw std::out_of_range("sjtu::map::at");
        return it->second;
    }
    const T & at(const Key &key) const {
        auto it = m_.find(key);
        if (it == m_.end()) throw std::out_of_range("sjtu::map::at");
        return it->second;
    }

    T & operator[](const Key &key) { return m_[key]; }
    T & operator[](Key &&key) { return m_[std::move(key)]; }

    bool empty() const { return m_.empty(); }
    size_type size() const { return m_.size(); }
    void clear() { m_.clear(); }

    size_type count(const Key &key) const { return m_.count(key); }

    iterator begin() { return iterator(m_.begin()); }
    const_iterator begin() const { return const_iterator(m_.cbegin()); }
    const_iterator cbegin() const { return const_iterator(m_.cbegin()); }

    iterator end() { return iterator(m_.end()); }
    const_iterator end() const { return const_iterator(m_.cend()); }
    const_iterator cend() const { return const_iterator(m_.cend()); }

    iterator find(const Key &key) { return iterator(m_.find(key)); }
    const_iterator find(const Key &key) const { return const_iterator(m_.find(key)); }

    std::pair<iterator, bool> insert(const value_type &val) {
        auto r = m_.insert(val);
        return { iterator(r.first), r.second };
    }

    template <class P>
    std::pair<iterator, bool> insert(P &&val) {
        auto r = m_.insert(std::forward<P>(val));
        return { iterator(r.first), r.second };
    }

    void erase(iterator pos) { m_.erase(pos.it_); }
    size_type erase(const Key &key) { return m_.erase(key); }

    iterator lower_bound(const Key &key) { return iterator(m_.lower_bound(key)); }
    const_iterator lower_bound(const Key &key) const { return const_iterator(m_.lower_bound(key)); }

    iterator upper_bound(const Key &key) { return iterator(m_.upper_bound(key)); }
    const_iterator upper_bound(const Key &key) const { return const_iterator(m_.upper_bound(key)); }

    key_compare key_comp() const { return m_.key_comp(); }

private:
    base_map m_;
};

} // namespace sjtu

#endif
