#ifndef wyjscie
#define wyjscie

#include <fstream>
#include <iostream>

class out
{
    std::ofstream file;
    public:
        out(const char *filename);
        ~out();
        void write_line(std::string line);
};

#endif