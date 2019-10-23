#ifndef TRITSET_TRITSET_H
#define TRITSET_TRITSET_H

#include <vector>
#include <unordered_map>
#include "Trit.h"

class TritSet {
public:

    /*Конструктор*/
    explicit TritSet (int _size);

    /*Деструктор*/
    ~TritSet();

    /*Возвращаем вместимость вектора*/
    size_t capacity() const;

    /*Возвращаем размер сета в тритах*/
    size_t getSize() const;

    /*Возвращаем размер вектора в юинтах*/
    size_t getVecSize() const;

    /*Возвращаем значение трита в сете по индексу*/
    Trit getValue (int index) const;

    /*Возвращаем значение юинта в векторе по индексу*/
    uint at (int index) const;

    /*Освобождаем память до первоначального размера или до последнего установленного трита*/
    void shrink();

    /*Возвращаем количество тритов определенного типа в сете*/
    size_t cardinality (Trit val) const;

    /*Возвращаем количество тритов каждого типа в сете*/
    std::unordered_map <Trit, int, std::hash<int>> cardinality();

    /*Забываем содержимое сета, начиная с lastIndex, освобождаем память*/
    void trim (size_t lastIndex);

    /*Возвращаем индекс последнего не Unknown трита + 1*/
    size_t length();

    /*Прокси-класс, необходимый для перегрузки операторов при обращении по индексу*/
    class ProxyTritSet {
        friend class TritSet;
    public:
        TritSet &set;
        int index;
        ProxyTritSet(TritSet *_set, int _index);

        /*Оператор присваивания по индексу*/
        ProxyTritSet &operator= (Trit val);

        /*Оператор вывода трита*/
        friend std::ostream& operator<<(std::ostream& os, const ProxyTritSet &prx);

        /*Операторы сравнения*/
        bool operator== (const ProxyTritSet &a) const;
        bool operator== (const Trit &a) const;
    };

    /*Оператор обращения по индексу*/
    ProxyTritSet operator[] (int _index);

private:
    /*Вектор uint*/
    std::vector <uint> *vec;

    /*Храним первоначальный размер сета для функции shrink*/
    size_t first_size;

    /*Храним размер сета в тритах*/
    size_t size;

    /*Храним количество тритов True в сете*/
    size_t trueCount;

    /*Храним количество тритов False в сете*/
    size_t falseCount;

    /*Устанавливаем значение в сете по индексу*/
    void setValue (int index, Trit val);
};

/*Оператор вывода сета*/
std::ostream& operator<<(std::ostream& os, const TritSet &set);

/*Логическое "НЕ" для всего сета*/
TritSet operator~ (const TritSet &a);

/*Логическое "И" для двух сетов*/
TritSet operator& (const TritSet &a, const TritSet &b);

/*Логическое "ИЛИ" для двух сетов*/
TritSet operator| (const TritSet &a, const TritSet &b);

#endif //TRITSET_TRITSET_H
