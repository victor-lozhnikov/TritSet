#include <iostream>
#include <assert.h>
#include <vector>
#include "TritSet.h"
#include "Trit.h"

int main() {
    //резерв памяти для хранения 1000 тритов
    TritSet set(1000);
// length of internal array
    size_t allocLength = set.capacity();
    std::cout << set.capacity() << " " << 1000*2 / 8 / sizeof(uint) << " " << sizeof(uint) << "\n";
    assert(allocLength >= 1000*2 / 8 / sizeof(uint) );
// 1000*2 - min bits count
// 1000*2 / 8 - min bytes count
// 1000*2 / 8 / sizeof(uint) - min uint[] size

//не выделяет никакой памяти
    set[1'000'000'000] = Unknown;
    assert(allocLength == set.capacity());

// false, but no exception or memory allocation
    if(set[2'000'000'000]==True){}
    assert(allocLength == set.capacity());

//выделение памяти
    set[1'000'000'000] = True;
    assert(allocLength < set.capacity());

//no memory operations
    allocLength = set.capacity();
    set[1'000'000'000] = Unknown;
    //std::cout << set[1'000'000'000] << " ";
    set[1'000'000] = False;
    //std::cout << set[1'000'000] << " ";
    assert(allocLength == set.capacity());


//освобождение памяти до начального значения или
//до значения необходимого для хранения последнего установленного трита
//в данном случае для трита 1000’000
    //set.shrink();
    //assert(allocLength > set.capacity());

}