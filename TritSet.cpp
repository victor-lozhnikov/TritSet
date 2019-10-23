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
    trueCount = 0;
    falseCount = 0;
}


TritSet::~TritSet() {
    delete vec;
}


size_t TritSet::capacity() const {
    return vec->capacity();
}


size_t TritSet::getSize() const {
    return size;
}


size_t TritSet::getVecSize() const {
    return vec->size();
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


uint TritSet::at (int index) const {
    if (index >= vec->size()) {
        return 0;
    }
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


size_t TritSet::cardinality (Trit val) const {
    switch (val) {
        case True:
            return trueCount;
        case False:
            return falseCount;
        default:
            return (size - trueCount - falseCount);
    }
}


std::unordered_map <Trit, int, std::hash<int>> TritSet::cardinality() {
    std::unordered_map <Trit, int, std::hash<int>> res;
    res[True] = cardinality(True);
    res[False] = cardinality(False);
    res[Unknown] = cardinality(Unknown);
    return res;
}


void TritSet::trim(size_t lastIndex) {
    if (lastIndex >= size) {
        return;
    }
    int new_size = ceil((double)lastIndex / (4 * sizeof(uint)));
    int pos1 = new_size * 4 * sizeof(uint);

    for (int i = lastIndex; i < pos1; ++i) {
        setValue(i, Unknown);
    }
    vec->resize(new_size);
    size = lastIndex + 1;
    vec->shrink_to_fit();
}

size_t TritSet::length() {
    int last_ind = -1;
    for (int i = getVecSize() - 1; i >= 0; --i) {
        if (vec->at(i) != 0) {
            last_ind = i;
            break;
        }
    }
    if (last_ind == -1) {
        return 0;
    }

    int first_i = 4 * sizeof(uint) * last_ind;
    int last_i = 4 * sizeof(uint) * (last_ind + 1);

    for (int i = last_i + 1; i >= first_i; --i) {
        if (getValue(i) != Unknown) {
            return i + 1;
        }
    }
}

void TritSet::setValue(int index, Trit val) {
    switch (getValue(index)) {
        case True:
            trueCount--;
            break;
        case False:
            falseCount--;
            break;
        default:
            break;
    }

    switch (val) {
        case True:
            trueCount++;
            break;
        case False:
            falseCount++;
            break;
        default:
            break;
    }

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
    os << prx.set.getValue(prx.index);
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
        return a == Unknown;
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
    TritSet res (a.getSize());

    for (int i = 0; i < a.getVecSize(); ++i) {
        if (a.at(i) == 0) continue;

        int first_i = i * 4 * sizeof(uint);
        int last_i = (i + 1) * 4 * sizeof(uint);

        for (int j = first_i; j < last_i; ++j) {
            res[j] = ~a.getValue(j);
        }
    }
    return res;
}

TritSet operator& (const TritSet &a, const TritSet &b) {
    TritSet res (std::max(a.getSize(), b.getSize()));
    for (int i = 0; i < std::max (a.getVecSize(), b.getVecSize()); ++i) {
        if (a.at(i) == 0 && b.at(i) == 0) {
            continue;
        }

        int first_i = i * 4 * sizeof(uint);
        int last_i = (i + 1) * 4 * sizeof(uint);

        for (int j = first_i; j < last_i; ++j) {
            res[j] = a.getValue(j) & b.getValue(j);
        }
    }
    return res;
}

TritSet operator| (const TritSet &a, const TritSet &b) {
    TritSet res (std::max(a.getSize(), b.getSize()));
    for (int i = 0; i < std::max (a.getVecSize(), b.getVecSize()); ++i) {
        if (a.at(i) == 0 && b.at(i) == 0) {
            continue;
        }

        int first_i = i * 4 * sizeof(uint);
        int last_i = (i + 1) * 4 * sizeof(uint);

        for (int j = first_i; j < last_i; ++j) {
            res[j] = a.getValue(j) | b.getValue(j);
        }
    }
    return res;
}