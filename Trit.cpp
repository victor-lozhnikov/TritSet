#include "Trit.h"

std::ostream& operator<<(std::ostream& os, const Trit &trit) {
    switch (trit) {
        case True:
            os << "True";
            break;
        case False:
            os << "False";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}

Trit operator~ (Trit a) {
    switch (a) {
        case True:
            return False;
        case False:
            return True;
        default:
            return Unknown;
    }
}

Trit operator& (Trit a, Trit b) {
    switch (a) {
        case False:
            return False;
        case Unknown:
            switch (b) {
                case False:
                    return False;
                default:
                    return Unknown;
            }
        case True:
            return b;
    }
}

Trit operator| (Trit a, Trit b) {
    switch (a) {
        case True:
            return True;
        case Unknown:
            switch (b) {
                case True:
                    return True;
                default:
                    return Unknown;
            }
        case False:
            return b;
    }
}