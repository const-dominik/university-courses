//Dominik Kiełbowicz, 329595, lista 5 zadanie 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int current_tab[256] = {0};
    int max_tab[256] = {0};
    FILE *fp;
    fp = fopen(argv[1], "rb");
    int prev = 0;
    int s = 0;
    int len = 0;
    int max_len = 0;
    int i = 0;
    while (prev != EOF)
    {
        s=fgetc(fp);
        if (s > prev)
        {
            len++;
            current_tab[i] = s;
        }
        else
        {
            if (len > max_len)
            {
                max_len = len;
                for (int i = 0; i <= 255; i++) max_tab[i] = current_tab[i];
            };
            memset(current_tab, 0, 256);
            len = 1;
            i = 0;
            current_tab[i] = s;
        }
        prev = s;
        i++;
    }
    int length = strlen(argv[1]) + 5;
    char nazwa[length];
    for (int i = 0; i < length - 5; i++)
        nazwa[i] = argv[1][i];
    strcat(nazwa, ".out");
    FILE *out = fopen(nazwa, "wb");
    for (int i = 0; max_tab[i]; i++)
        fprintf(out, "%c", max_tab[i]);
    fclose(out);
    fclose(fp);
    return argc;
}
