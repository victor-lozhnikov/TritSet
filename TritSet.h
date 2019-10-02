#ifndef TRITSET_TRITSET_H
#define TRITSET_TRITSET_H

#include <vector>
#include "Trit.h"

class TritSet {
public:
    explicit TritSet (int _size);
    ~TritSet();
    int capacity();

    class ProxyTritSet {
    public:
        TritSet &set;
        int index;
        ProxyTritSet(TritSet *_set, int _index);
        ProxyTritSet &operator= (Trit val);
        //friend std::ostream& TritSet::ProxyTritSet::operator<<(std::ostream& os, const ProxyTritSet &prx);
        //bool operator== (ProxyTritSet a);
        //bool operator== (Trit a);
    };

    ProxyTritSet operator[] (int _index);

private:
    std::vector <uint> *vec;
    int size;
    Trit getValue (int index);
    void setValue (int index, Trit val);
};


#endif //TRITSET_TRITSET_H
