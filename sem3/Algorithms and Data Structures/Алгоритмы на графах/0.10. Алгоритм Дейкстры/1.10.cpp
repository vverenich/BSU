#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <numeric>
#include <queue>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

void getDistances(int64_t start, std::vector<bool>& processed, std::vector<int64_t>& distances, std::vector < std::vector < std::pair<int64_t, int64_t>>> & table)
{
    //std::queue < std::pair<int64_t, int64_t>> q;
    std::priority_queue <std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>, std::greater<std::pair<int64_t, int64_t>> > q;
    q.push(std::make_pair(0, start));

    while (!q.empty()) {
        int64_t dv = q.top().first;
        int64_t v = q.top().second;

        q.pop();

        if (distances[v] > dv) {
            distances[v] = dv;
        }

        if (processed[v]) {
            continue;
        }

        processed[v] = true;

        for (const auto& i : table[v]) {
            int64_t newDv = i.second;
            int64_t newV = i.first;

            if (distances[newV] > newDv + dv) {
                distances[newV] = newDv + dv;
            }

            if (!processed[newV]) {
                q.push(std::make_pair(dv + newDv, newV));
            }
        }
    }
}

int main()
{
    FILE *fr, *fw;
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    int64_t n, m;
    fscanf(fr, "%lld %lld", &n, &m);

    std::vector < std::vector < std::pair<int64_t, int64_t>>> roads(n);

    int64_t a, b, c;
    for (size_t i { 0 }; i < m; ++i) {
        fscanf(fr, "%lld %lld %lld", &a, &b, &c);
        roads[a - 1].emplace_back(std::make_pair(b - 1, c));
        roads[b - 1].emplace_back(std::make_pair(a - 1, c));
    }

    std::vector<bool> processed(n, false);
    std::vector<int64_t> distances(n, INT64_MAX);

    getDistances(0, processed, distances, roads);

    fprintf(fw, "%lld", distances[n - 1]);
    /*
    for (size_t i { 0 }; i < n; ++i) {
        for (const auto& i : roads[i]) {
            fprintf(fw, "%d %d\n", i.first, i.second);
        }
        fprintf(fw, "\n\n");
    }
    */

    fclose(fr);
    fclose(fw);

    return 0;
}