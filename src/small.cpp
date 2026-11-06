#include "small.h"
#include <iostream>

Small::Small() {
    next_sym = {
        {'a', 'b'}, {'b', 'j'}, {'c', 'f'}, {'d', 'e'},
        {'e', 'h'}, {'f', 'g'}, {'g', 'a'}, {'h', 'i'},
        {'i', 'c'}, {'j', 'k'}, {'k', 'd'}
    };
    char c = zero;
    do{
        hasse.push_back(c);
        c = next_sym[c];
    } while(c!=zero);
    
    buildAdd();
    buildMul();
    buildInv();
}

bool Small::isLess(char x, char y) const{
    return (x != y) && (add_c.at(x).at(invers.at(y)) == zero);
}

void Small::buildAdd() {
    for (char x : hasse) {
        char r = x;
        char c = zero;
        for (char y : hasse) {
            add[x][y] = r;
            add_c[x][y] = c;

            r = next_sym[r];
            if (r == zero)
                c = one;
        }
    }
}

void Small::buildMul() {
    for (char x: hasse) {
        char r =zero;
        char c = zero;
        for (char y : hasse) {
            mul[x][y] = r;
            mul_c[x][y] = c;

            char step_c = add_c[r][x];
            r = add[r][x];
            c = add[c][step_c];
        }
    }
}

void Small::buildInv() {
    for (char x : hasse) {
        for (char y : hasse) {
            if (add[x][y] == maximum) {
                invers[x] = y;
                break;
            }
        }
    }
}

const std::vector<char>& Small::getHasse() const {
    return hasse;
}
void Small::printTables() const {
    std::cout << "Цепочка возрастания от '" << zero << "' по правилу +1:\n  ";
    for (char c : hasse) {
        std::cout << c << (c == maximum ? "" : " -> ");
    }
    std::cout << " -> " << one << zero << "\n\n";

    auto printOne = [&](const std::string& title, const auto& table) {
        std::cout << title << "\n   |";
        for (char c : hasse) std::cout << " " << c;
        std::cout << "\n---+----------------------\n";
        for (char r : hasse) {
            std::cout << " " << r << " |";
            for (char c : hasse) {
                std::cout << " " << table.at(r).at(c);
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    };

    printOne("1. Таблица остатков сложения (add):", add);
    printOne("2. Таблица переносов сложения (add_c):", add_c);
    printOne("3. Таблица остатков умножения (mul):", mul);
    printOne("4. Таблица переносов умножения (mul_c):", mul_c);
}

char Small::nextSym(char c) const {
    return next_sym.at(c);
}

char Small::getAdd(char x, char y) const{ return add.at(x).at(y);}
char Small::getAdd_c(char x, char y) const{ return add_c.at(x).at(y);}
char Small::getMul(char x, char y) const{ return mul.at(x).at(y); }
char Small::getMul_c(char x, char y) const{ return mul_c.at(x).at(y);}
char Small::getInvers(char x) const { return invers.at(x);}