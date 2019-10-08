#ifndef TRITSET_TRITSET_H
#define TRITSET_TRITSET_H

#include <vector>
#include "Trit.h"

class TritSet {
public:
    explicit TritSet (int _size);
    ~TritSet();
    int capacity();
    Trit getValue (int index);

    class ProxyTritSet {
        friend class TritSet;
    public:
        TritSet &set;
        int index;
        ProxyTritSet(TritSet *_set, int _index);
        ProxyTritSet &operator= (Trit val);
        friend std::ostream& operator<<(std::ostream& os, const ProxyTritSet &prx) {
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
        bool operator== (ProxyTritSet a);
        bool operator== (Trit a);
    };

    ProxyTritSet operator[] (int _index);

private:
    std::vector <uint> *vec;
    int size;
    void setValue (int index, Trit val);
};


#endif //TRITSET_TRITSET_H
