#include "wyjscie.hpp"

out::out(const char *filename)
{
    file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    file.open(filename);
};

out::~out()
{
    file.close();
}

void out::write_line(std::string line)
{
    file << line << std::endl;
}