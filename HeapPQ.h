#include <vector>

template <typename T>
class HeapPQ {
public:
    HeapPQ() : V(1) {}

    typedef typename std::vector<T>::iterator Position;

    int size() const { return V.size() - 1; }
    Position left(const Position& p) { return pos(2*idx(p)); }
    Position right(const Position& p) { return pos(2*idx(p) + 1); }
    Position parent(const Position& p) { return pos(idx(p)/2); }
    bool hasLeft(const Position& p) const { return 2*idx(p) <= size(); }
    bool hasRight(const Position& p) const { return 2*idx(p) + 1 <= size(); }
    bool isRoot(const Position& p) const { return idx(p) == 1; }
    Position root() { return pos(1); }
    Position last() { return pos(size()); }
    void swap(const Position& p, const Position& q) {
        T e = *q;
        *q = *p;
        *p = e;
    }

    bool empty() const { return size() == 0; }
    //void insert(const T& e);
    int insert(std::vector<int> e);
    void remove(Position& p);
    void removeMin();
    const T& min() { return *pos(1); };

public:
    Position pos(int i) { return V.begin() + i; }
    int idx(const Position& p) const { return p - V.begin(); }

public:
    std::vector<T> V;
};

/*
template <typename T>
void HeapPQ<T>::insert(const T& e) {
    V.push_back(e);
    Position v = pos(size());
    while (!isRoot(v)) {
        Position u = parent(v);
        if (*v > *u) break;
        swap(u, v);
        v = u;
    }
}
*/

template <>
int HeapPQ<std::vector<int> >::insert(std::vector<int> e) {
    V.push_back(e);
    Position v = pos(size());
    while (!isRoot(v)) {
        Position u = parent(v);
        if ((*v)[1] > (*u)[1]) break;
        swap(u, v);
        v = u;
    }
    return idx(v);
}

/*
template <typename T>
void HeapPQ<T>::removeMin() {
    if (size() == 1) {
        V.pop_back();
    }
    else {
        Position u = pos(1);
        swap(u, last());
        V.pop_back();
        while (hasLeft(u)) {
            Position v = left(u);
            if (hasRight(u) && *v > *right(u))
                v = right(u);
            if (*u > *v) {
                swap(u, v);
                u = v;
            }
            else break;
        }
    }
}
*/

template <>
void HeapPQ<std::vector<int> >::removeMin() {
    if (size() == 1) {
        V.pop_back();
    }
    else {
        Position u = pos(1);
        swap(u, last());
        V.pop_back();
        while (hasLeft(u)) {
            Position v = left(u);
            if (hasRight(u) && (*v)[1] > (*right(u))[1])
                v = right(u);
            if ((*u)[1] > (*v)[1]) {
                swap(u, v);
                u = v;
            }
            else break;
        }
    }
}

template <typename T>
void HeapPQ<T>::remove(Position& u) {
    if (size() == 1) {
        V.erase(u);
    }
    else {
        swap(u, last());
        V.pop_back();
        while (hasLeft(u)) {
            Position v = left(u);
            if (hasRight(u) && (*v)[1] > (*right(u))[1])
                v = right(u);
            if ((*u)[1] > (*v)[1]) {
                swap(u, v);
                u = v;
            }
            else break;
        }
    }
}