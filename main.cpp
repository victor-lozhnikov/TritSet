#include <iostream>
#include <assert.h>
#include <vector>
#include "TritSet.h"
#include "Trit.h"

int main() {
    TritSet a (10);
    TritSet b (5);
    a[0] = True;
    a[3] = False;
    a[8] = True;
    b[3] = False;
    b[0] = True;

    TritSet c = a & b;
    std::cout << a << b << ~b << c;
}