#include "wejscie.hpp"
#include <string>

in::in(const char *filename)
{
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.open(filename);
};

in::~in()
{
    file.close();
}

std::string in::next_line()
{
    std::string line;
    std::getline(file, line);
    return line;
}

bool in::isPeekEOF()
{
    return file.peek() == EOF;
}