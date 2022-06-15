//Dominik Kiełbowicz, 329595, lista 7 zadanie 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubble_sort(char slowa[100][40], int wystapienia[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n-i-1; j++)
            if (strcmp(slowa[j], slowa[j+1]) > 0)
            {
                char temp[40];
                strcpy(temp, slowa[j]);
                strcpy(slowa[j], slowa[j+1]);
                strcpy(slowa[j+1], temp);
                int temp2 = wystapienia[j];
                wystapienia[j] = wystapienia[j+1];
                wystapienia[j+1] = temp2;
            }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    char slowa[100][40] = {""};
    int wystapienia[100] = {0};
    char slowo[40] = {0};
    int s = 0;
    int i = 0;
    int ile = 0;
    while (1)
    {
        s = fgetc(fp);
        if (s == '\n' || s == ' ' || s == EOF)
        {
            int istnieje = 0;
            int ind = -1;
            for (int j = 0; j < 100; j++)
            {
                if (strcmp(slowa[j], "") == 0) {
                    ind = j;
                    break;
                }
                if (strcmp(slowa[j], slowo) == 0) {
                    istnieje = 1;
                    wystapienia[j]++;
                    break;
                }
             }
            if (!istnieje) {
                strcpy(slowa[ind], slowo);
                wystapienia[ind] = 1;
                ile = ind;
            }
            memset(slowo, 0, 40);
            i = 0;
            if (s == EOF) break;
            continue;
        };
        slowo[i] = (char)s;
        i++;
    };
    bubble_sort(slowa, wystapienia, ile+1);
    for (int i = 0; i <= ile; i++) printf("%s, %d\n", slowa[i], wystapienia[i]);
    fclose(fp);
    return argc;
}
