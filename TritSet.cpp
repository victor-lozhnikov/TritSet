#include <iostream>
#include <vector>
#include <cmath>
#include "TritSet.h"
#include "Trit.h"

#define FALSE 2
#define TRUE 3
#define UNKNOWN 0

TritSet::TritSet (int _size) {
    vec = new std::vector <uint> (ceil((double)_size / (4 * sizeof(uint))), 0);
    size = _size;
    first_size = vec->size();
}

TritSet::~TritSet() {
    delete vec;
}

int TritSet::capacity() const {
    return vec->capacity();
}

int TritSet::getSize() const {
    return size;
}

uint TritSet::at (int index) const {
    return vec->at(index);
}

void TritSet::shrink() {
    int new_size = first_size;
    for (int k = vec->size() - 1; k > first_size; --k) {
        if (vec->at(k) > 0) {
            new_size = k + 1;
            break;
        }
    }
    vec->resize(new_size);

    int first_i = 4 * sizeof(uint) * (new_size - 1);
    int last_i = 4 * sizeof(uint) * new_size;
    for (int i = first_i; i < last_i; ++i) {
        if (!(getValue(i) == Unknown)) {
            size = i + 1;
        }
    }
    vec->shrink_to_fit();
}

Trit TritSet::getValue(int index) const {
    if (index >= size) {
        return Unknown;
    }
    int pos1 = index / (4 * sizeof(uint));
    int pos2 = index % (4 * sizeof(uint));

    uint tmp = (*vec)[pos1];
    tmp >>= 2 * pos2;
    tmp &= 3;
    switch (tmp) {
        case FALSE:
            return False;
        case TRUE:
            return True;
        default:
            return Unknown;
    }
}

void TritSet::setValue(int index, Trit val) {
    int pos1 = index / (4 * sizeof(uint));
    int pos2 = index % (4 * sizeof(uint));

    uint tmp1, tmp2;
    tmp1 = 3;
    switch (val) {
        case False:
            tmp2 = FALSE;
            break;
        case True:
            tmp2 = TRUE;
            break;
        default:
            tmp2 = UNKNOWN;
            break;
    }

    tmp1 <<= 2 * pos2;
    tmp2 <<= 2 * pos2;
    tmp1 = ~tmp1;
    (*vec)[pos1] &= tmp1;
    (*vec)[pos1] |= tmp2;
}

TritSet::ProxyTritSet::ProxyTritSet(TritSet *_set, int _index) : set(*_set), index(_index) {}

TritSet::ProxyTritSet &TritSet::ProxyTritSet::operator=(Trit val) {
    if (index < set.size) {
        set.setValue(index, val);
    }
    else if (val != Unknown) {
        set.vec->resize(ceil((double)(index + 1) / (4 * sizeof(uint))), 0);
        set.size = index + 1;
        set.setValue(index, val);
    }
}

std::ostream& operator<<(std::ostream &os, const TritSet::ProxyTritSet &prx) {
    switch (prx.set.getValue(prx.index)) {
        case False:
            os << "False";
            break;
        case True:
            os << "True";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}

bool TritSet::ProxyTritSet::operator==(const TritSet::ProxyTritSet &a) const {
    if (index < set.size && a.index < a.set.size) {
        return (set.getValue(index) == a.set.getValue(a.index));
    }
    else if (index >= set.size && a.set.getValue(a.index) == Unknown) {
        return true;
    }
    else if (a.index >= a.set.size && set.getValue(index) == Unknown) {
        return true;
    }
    return false;
}

bool TritSet::ProxyTritSet::operator==(const Trit &a) const {
    if (index > set.size) {
        if (a == Unknown) {
            return true;
        }
        else {
            return false;
        }
    }
    return (set.getValue(index) == a);
}

TritSet::ProxyTritSet TritSet::operator[] (int index) {
    return ProxyTritSet(this, index);
}

std::ostream& operator<<(std::ostream& os, const TritSet &set) {
    os << "[\n";
    for (int i = 0; i < set.getSize(); ++i) {
        os << " " << i << " : " << set.getValue(i) << "\n";
    }
    os << "]\n";
    return os;
}

TritSet operator~ (const TritSet &a) {
    TritSet b (a.getSize());

    for (int i = 0; i < a.capacity(); ++i) {
        if (a.at(i) == 0) continue;

        int first_i = i * 4 * sizeof(uint);
        int last_i = (i + 1) * 4 * sizeof(uint);

        for (int j = first_i; j < last_i; ++j) {
            b[j] = ~a.getValue(j);
        }
    }

    return b;
}

TritSet operator& (const TritSet &a, const TritSet &b) {
    TritSet res (std::max(a.getSize(), b.getSize()));
    for (int i = 0; i < std::max (a.capacity(), b.capacity()); ++i) {
        if (a.at(i) == 0 && b.at(i) == 0) {
            continue;
        }

        int first_i = i * 4 * sizeof(uint);
        int last_i = (i + 1) * 4 * sizeof(uint);

        for (int j = first_i; j < last_i; ++j) {
            if (j > std::min(a.getSize(), b.getSize())) {
                if (a.getSize() > b.getSize()) {
                    res[j] = b.getValue(j) & Unknown;
                }
                else {
                    res[j] = a.getValue(j) & Unknown;
                }
            }
            else {
                res[j] = a.getValue(j) & b.getValue(j);
            }
        }
        return res;
    }
}

TritSet operator| (const TritSet &a, const TritSet &b) {
    TritSet res (std::max(a.getSize(), b.getSize()));
    for (int i = 0; i < std::max (a.capacity(), b.capacity()); ++i) {
        if (a.getSize() > b.getSize()) {

        }

        int first_i = i * 4 * sizeof(uint);
        int last_i = (i + 1) * 4 * sizeof(uint);

        for (int j = first_i; j < last_i; ++j) {
            if (j > std::min(a.getSize(), b.getSize())) {
                if (a.getSize() > b.getSize()) {
                    res[j] = b.getValue(j) | Unknown;
                }
                else {
                    res[j] = a.getValue(j) & Unknown;
                }
            }
            else {
                res[j] = a.getValue(j) & b.getValue(j);
            }
        }
        return res;
    }
}