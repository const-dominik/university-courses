#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Scenario
{
    int id;
    int start;
    int step;
    int total_weight;
};

int main()
{
    int num_cows;
    cin >> num_cows;
    vector<int> weights(num_cows);
    for (int i = 0; i < num_cows; i++)
    {
        cin >> weights[i];
    }

    int num_scenarios;
    cin >> num_scenarios;
    vector<Scenario> scenarios(num_scenarios);
    for (int i = 0; i < num_scenarios; i++)
    {
        cin >> scenarios[i].start >> scenarios[i].step;
        scenarios[i].start--;
        scenarios[i].id = i;
        scenarios[i].total_weight = 0;
    }

    sort(scenarios.begin(), scenarios.end(), [](const Scenario &a, const Scenario &b)
         { return a.step < b.step; });

    int sqrt_num_cows = sqrt(num_cows);
    vector<int> cumulative_weights(num_cows);

    for (int i = 0; i < num_scenarios; i++)
    {
        if (scenarios[i].step > sqrt_num_cows)
        {
            for (int j = scenarios[i].start; j < num_cows; j += scenarios[i].step)
            {
                scenarios[i].total_weight += weights[j];
            }
        }
        else
        {
            for (int j = num_cows - 1; j >= 0; j--)
            {
                cumulative_weights[j] = weights[j];
                if (j + scenarios[i].step < num_cows)
                {
                    cumulative_weights[j] += cumulative_weights[j + scenarios[i].step];
                }
            }
            scenarios[i].total_weight = cumulative_weights[scenarios[i].start];
        }
    }

    sort(scenarios.begin(), scenarios.end(), [](const Scenario &a, const Scenario &b)
         { return a.id < b.id; });

    for (int i = 0; i < num_scenarios; i++)
    {
        cout << scenarios[i].total_weight << endl;
    }

    return 0;
}