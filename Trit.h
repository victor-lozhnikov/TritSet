#ifndef TRITSET_TRIT_H
#define TRITSET_TRIT_H

#include <utility>
#include <iostream>

enum Trit {False, Unknown, True};

std::ostream& operator<<(std::ostream& os, const Trit &trit);

Trit operator~ (Trit a);

Trit operator& (Trit a, Trit b);

Trit operator| (Trit a, Trit b);

#endif //TRITSET_TRIT_H
