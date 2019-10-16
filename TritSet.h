#ifndef TRITSET_TRITSET_H
#define TRITSET_TRITSET_H

#include <vector>
#include "Trit.h"

class TritSet {
public:
    explicit TritSet (int _size);
    ~TritSet();
    int capacity() const;
    Trit getValue (int index) const;
    void shrink();
    int getSize() const;
    uint at (int index) const;

    class ProxyTritSet {
        friend class TritSet;
    public:
        TritSet &set;
        int index;
        ProxyTritSet(TritSet *_set, int _index);
        ProxyTritSet &operator= (Trit val);
        friend std::ostream& operator<<(std::ostream& os, const ProxyTritSet &prx);
        bool operator== (const ProxyTritSet &a) const;
        bool operator== (const Trit &a) const;
    };

    ProxyTritSet operator[] (int _index);

private:
    std::vector <uint> *vec;
    int first_size;
    void setValue (int index, Trit val);
    int size;
};

std::ostream& operator<<(std::ostream& os, const TritSet &set);
TritSet operator~ (const TritSet &a);
TritSet operator& (const TritSet &a, const TritSet &b);
TritSet operator| (const TritSet &a, const TritSet &b);

#endif //TRITSET_TRITSET_H
