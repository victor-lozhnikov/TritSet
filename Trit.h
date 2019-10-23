#ifndef TRITSET_TRIT_H
#define TRITSET_TRIT_H

#include <utility>
#include <iostream>

enum Trit {False, Unknown, True};

/*Оператор вывода одного трита*/
std::ostream& operator<<(std::ostream& os, const Trit &trit);

/*Логическое "НЕ"*/
Trit operator~ (Trit a);

/*Логическое "И"*/
Trit operator& (Trit a, Trit b);

/*Логическое "ИЛИ"*/
Trit operator| (Trit a, Trit b);

#endif //TRITSET_TRIT_H
