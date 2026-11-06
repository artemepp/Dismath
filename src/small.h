#ifndef SMALL_ARITHMETIC_H
#define SMALL_ARITHMETIC_H

#include <map>
#include <vector>
#include <set>
#include <string>

class Small{
    public:
        static const char zero = 'a';
        static const char one = 'b';
        static const char maximum = 'g';
        Small();

        char nextSym(char c) const;
        char getAdd(char x,char y) const;
        char getAdd_c(char x,char y) const;
        char getMul(char x,char y) const;
        char getMul_c(char x,char y) const;
        char getInvers(char x) const;
        bool isLess(char x,char y) const;
        void printTables() const;

        const std::vector<char>& getHasse() const;


    private:
        std::map<char, char> next_sym;
        std::vector<char> hasse;
        std::map<char, std::map<char,char>> add;
        std::map<char, std::map<char,char>> add_c;
        std::map<char, std::map<char,char>> mul;
        std::map<char, std::map<char,char>> mul_c;
        std::map<char, char> invers;

        void buildAdd();
        void buildMul();
        void buildInv();
        
};
#endif