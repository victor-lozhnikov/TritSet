#ifndef TRITSET_TRITSET_H
#define TRITSET_TRITSET_H

#include <set>

class TritSet {
    public:
        TritSet (int set_size) {
            size = set_size;

        }

    private:
        int size;
        std::set <std::pair<int, bool>> pair_set;
};


#endif //TRITSET_TRITSET_H
