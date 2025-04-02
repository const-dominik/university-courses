#include <iostream>
#include <vector>
#include <algorithm>

void calculate(int n, int q, std::vector<int> &a)
{
    std::vector<int> sums(n + 1, 0);
    int l, r;
    for (int i = 0; i < q; i++)
    {
        std::cin >> l >> r;
        sums[l - 1] += 1;
        sums[r] -= 1;
    }
    for (int i = 0; i < n; i++)
    {
        sums[i + 1] += sums[i];
    }
    a.insert(a.begin(), 0);
    std::sort(a.begin(), a.end());
    std::sort(sums.begin(), sums.end());
    long long max_sum = 0;
    for (int i = 0; i <= n; i++)
    {
        max_sum += (long long)a[i] * sums[i];
    }
    std::cout << max_sum << std::endl;
}

int main()
{
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    calculate(n, q, a);
    return 0;
}