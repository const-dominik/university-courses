#ifndef wejscie
#define wejscie

#include <fstream>
#include <iostream>

class in
{
    std::ifstream file;
    public:
        in(const char *filename);
        ~in();
        std::string next_line();
        bool isPeekEOF();
};

#endif