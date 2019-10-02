#include <iostream>
#include <vector>
#include <cmath>
#include "TritSet.h"
#include "Trit.h"

TritSet::TritSet (int _size) {
    vec = new std::vector <uint> (ceil((double)_size / (4 * sizeof(uint))), 0);
    size = _size;
}

TritSet::~TritSet() {
    delete vec;
}

int TritSet::capacity() {
    return vec->capacity();
}

Trit TritSet::getValue(int index) {
    if (index >= size) {
        return Unknown;
    }
    int pos1 = index / (4 * sizeof(uint));
    int pos2 = index % (4 * sizeof(uint));

    uint tmp = (*vec)[pos1];
    for (int i = 0; i < pos2; i+= 2)
}

void TritSet::setValue(int index, Trit val) {

}

TritSet::ProxyTritSet::ProxyTritSet(TritSet *_set, int _index) : set(*_set), index(_index) {}

TritSet::ProxyTritSet &TritSet::ProxyTritSet::operator=(Trit val) {
    if (index < set.size) {
        set.setValue(index, val);
    }
    else if (val != Unknown) {
        set.vec->resize(ceil((double)(index + 1) / (4 * sizeof(uint))));
        set.size = index + 1;
        set.setValue(index, val);
    }
}

/*std::ostream& TritSet::ProxyTritSet::operator<<(std::ostream &os, ProxyTritSet &prx) {
    switch (set.uMap[index]) {
        case Trit::False:
            os << "False";
            break;
        case Trit::True:
            os << "True";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}*/

/*bool TritSet::ProxyTritSet::operator==(TritSet::ProxyTritSet a) {
    if (index < set.capacity() && a.index < a.set.capacity()) {
        return (set.uMap[index] == a.set.uMap[a.index]);
    }
    else if (index >= set.capacity() && a.set.uMap[a.index] == Unknown) {
        return true;
    }
    else if (a.index >= a.set.capacity() && set.uMap[index] == Unknown) {
        return true;
    }
    return false;
}

bool TritSet::ProxyTritSet::operator==(Trit a) {
    if (index > set.capacity()) {
        if (a == Unknown) {
            return true;
        }
        else {
            return false;
        }
    }
    return (set.uMap[index] == a);
}*/


TritSet::ProxyTritSet TritSet::operator[] (int index) {
    return ProxyTritSet(this, index);
}