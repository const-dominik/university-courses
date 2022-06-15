#include <iostream>
#include <string>
#include "wejscie.hpp"
#include "wyjscie.hpp"

void caesar_cipher_files(const char *in_filename, const char *out_filename, int key)
{
    in in_file(in_filename);
    out out_file(out_filename);
    std::string line;
    while (!in_file.isPeekEOF())
    {
        line = in_file.next_line();
        int i = 0;
        for (char ch : line)
        {
            if (ch >= 'a' && ch <= 'z')
                ch = ((ch - 'a' + key) % 26 + 'a');
            else if (ch >= 'A' && ch <= 'Z')
                ch = ((ch - 'A' + key) % 26 + 'A');
            line[i++] = ch;
        }
        out_file.write_line(line);
    }
}

int main(int argc, char *argv[])
{

    if (argc == 4)
    {
        try
        {
            caesar_cipher_files(argv[1], argv[2], atoi(argv[3]));
        } catch (std::ios_base::failure &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Poprawne wywołanie programu to: [nazwa programu] [nazwa pliku wejsciowego] [nazwa pliku wyjsciowego] [klucz]";
    }

    return 0;
}
