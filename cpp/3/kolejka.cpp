#include "kolejka.hpp"

kolejka::kolejka() : kolejka(1) {};
kolejka::kolejka(int pojemnosc)
{
    if (pojemnosc <= 0)
        throw std::range_error("Kolejka nie może mieć 0 elementów!");
    size = pojemnosc;
    start = 0;
    count = 0;
    tab = new std::string[size];
};

kolejka::kolejka(std::initializer_list<std::string> arr) : kolejka((int)arr.size()) {
    for (const auto &elem : arr)
        wstaw(elem);
};

kolejka::kolejka(const kolejka & q) : kolejka(q.size)
{
    start = q.start;
    count = q.count;
    for (int i = 0; i < count; i++) {
        int curr = (start+i)%size;
        tab[curr] = q.tab[curr];
    }
}

kolejka::kolejka(kolejka&& q)
{
    size = q.size;
    start = q.start;
    count = q.count;
    tab = q.tab;

    q.size = 0;
    q.start = 0;
    q.count = 0;
    q.tab = nullptr;
}

kolejka & kolejka::operator=(const kolejka &q)
{
    if (this == &q) return *this;
    this->~kolejka();
    size = q.size;
    start = q.start;
    count = q.count;
    tab = new std::string[size];
    for (int i = 0; i < count; i++) {
        int curr = (start+i)%size;
        tab[curr] = q.tab[curr];
    }

    return *this;
}

kolejka & kolejka::operator=(kolejka &&q)
{
    if (this == &q) return *this;
    this->~kolejka();

    size = q.size;
    start = q.start;
    count = q.count;
    tab = q.tab;

    q.size = 0;
    q.start = 0;
    q.count = 0;
    q.tab = nullptr;

    return *this;
}

kolejka::~kolejka() {
    delete [] tab;
}

void kolejka::wstaw(std::string text)
{
    if (isFull())
        throw std::range_error("Kolejka jest pełna!");

    int last = (start + count) % size;
    tab[last] = text;
    count++;
};

std::string kolejka::usun()
{
    if (isEmpty())
        throw std::range_error("Kolejka jest pusta!");

    std::string temp = tab[start];

    tab[start] = "";
    start = (start+1)%size;
    count--;
    return temp;
}

std::string kolejka::zprzodu() const
{
    if (isEmpty())
        throw std::range_error("Kolejka jest pusta!");
    
    return tab[start];
}

int kolejka::dlugosc() const
{
    return size;
}

bool kolejka::isEmpty() const
{
    return count == 0;
}

bool kolejka::isFull() const
{
    return count == size;
}

void kolejka::printQueue() const
{
    for (int i = 0; i < count; i++) {
        int curr = (start+i)%size;
        std::cout << tab[curr] << " ";
    }
    std::cout << std::endl;
}