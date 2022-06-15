//Dominik Kiełbowicz, 329595, lista 6 zad 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Student {
    char imie[50];
    char nazwisko[50];
    char index[50];
    char rodzaj[50];
} st;

void zapisz_studenta_w_pliku(st student[], char nazwa[], int n)
{
    FILE *fp;
    fp = fopen(nazwa, "wt");
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, student[i].imie);
        fprintf(fp, student[i].nazwisko);
        fprintf(fp, student[i].index);
        fprintf(fp, student[i].rodzaj);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void wypisz_studenta(st student)
{
    printf("Imie     : %s", student.imie);
    printf("Nazwisko : %s", student.nazwisko);
    printf("Index    : %s", student.index);
    printf("Rodzaj   : %s\n", student.rodzaj);
}
bool porownaj(char s1[], char s2[])
{
    int i = 0;
    while (s1[i])
    {
        if (s1[i] < s2[i]) return false;
        if (s1[i] > s2[i]) return true;
        i++;
    }
    if (s2[i]) return false;
    return true;
}

bool dobry_string(st st1, st st2, char k)
{
    char s1[50];
    char s2[50];
    if (k == '1') { strcpy(s1,st1.imie); strcpy(s2,st2.imie); };
    if (k == '2') { strcpy(s1,st1.nazwisko); strcpy(s2,st2.nazwisko); };
    if (k == '3') {
        strcpy(s1,st1.index);
        strcpy(s2,st2.index);
        if (strlen(s1) > strlen(s2)) return true;
        if (strlen(s1) < strlen(s2)) return false;
    };
    if (k == '4') { strcpy(s1,st1.rodzaj); strcpy(s2,st2.rodzaj); };
    bool a = porownaj(s1, s2);
    return a;
}

void bubble_sort(st studenci[], int n, char r, char k)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n-i-1; j++)
        {

            if (dobry_string(studenci[j], studenci[j+1], k) == (r == 'r' ? true : false))
            {
                st temp = studenci[j];
                studenci[j] = studenci[j+1];
                studenci[j+1] = temp;
            }
        }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    st studenci[1000];
    char field[50];
    int s = 0;
    int i = 0;
    int j = 0;
    int line = 0;
    while ((s = fgetc(fp)) != EOF)
    {
        field[j] = (char)s;
        j++;
        if (s == '\n')
        {
            int prop = line % 5;
            if (prop == 0) strcpy(studenci[i].imie, field);
            if (prop == 1) strcpy(studenci[i].nazwisko, field);
            if (prop == 2) strcpy(studenci[i].index, field);
            if (prop == 3) strcpy(studenci[i].rodzaj, field);
            if (prop == 4) i++;
            line++;
            j = 0;
            memset(field, 0, 50);
        };
    };
    if (argc == 4) bubble_sort(studenci, i+1, argv[2][0], argv[3][0]);
    for (int j = 0; j < i+1 && i != 0; j++)
        wypisz_studenta(studenci[j]);
    zapisz_studenta_w_pliku(studenci, "studenci.txt", i+1);
    fclose(fp);
    return argc;
}
