#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <tuple>
#include <cstring>

void split_public_key(std::string pk, long long a, long long b)
{
    long long n = pk.length();
    long long pref_mod_a = 0;
    std::vector<long long> tab1(n, 0);
    std::vector<long long> tab2(n, 0);

    for (int i = 0; i < n - 1; i++)
    {

        pref_mod_a = (pref_mod_a * 10 + (pk[i] - '0')) % a;
        if (pref_mod_a == 0 && pk[i + 1] != '0')
        {
            tab1[i] = 1;
        }
    }

    long long p = 1, mid = -1;
    tab2[n - 1] = (pk[n - 1] - '0') % b;

    if (tab2[n - 1] == 0 && tab1[n - 2])
        mid = n - 1;

    for (int i = n - 2; i > 0; i--)
    {
        long long num = pk[i] - '0';
        p = (p * 10) % b;
        tab2[i] = (num * p + tab2[i + 1]) % b;

        if (tab2[i] == 0 && tab1[i - 1])
        {
            mid = i;
        }
    }

    if (mid == -1)
    {
        std::cout << "NO" << std::endl;
        return;
    }

    std::cout << "YES" << std::endl;
    for (int i = 0; i < mid; i++)
    {
        std::cout << pk[i];
    }
    std::cout << std::endl;

    for (int i = mid; i < n; i++)
    {
        std::cout << pk[i];
    }
    std::cout << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string public_key;
    std::cin >> public_key;
    long long a, b;
    std::cin >> a >> b;
    split_public_key(public_key, a, b);

    return 0;
}