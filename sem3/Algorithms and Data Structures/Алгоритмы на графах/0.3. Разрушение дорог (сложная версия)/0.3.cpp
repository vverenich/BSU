#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>

#include <stdlib.h>
#include <vector>

struct DSU {
    std::vector<size_t> numbers;
    std::vector<size_t> sizes;
    size_t components;

    DSU(size_t number)
        : components{ number }
    {
        numbers.resize(number + 1);
        std::iota(numbers.begin(), numbers.end(), 0);

        sizes.resize(number + 1);
        std::fill(sizes.begin(), sizes.end(), 1);
    }

    size_t findSet(size_t x)
    {
        if (x == numbers[x]) {
            return x;
        }

        numbers[x] = findSet(numbers[x]);
        return numbers[x];
    }

    void unionCities(size_t x, size_t y)
    {
        x = findSet(x);
        y = findSet(y);

        if (x != y) {
            --components;
            if (sizes[x] < sizes[y]) {
                std::swap(x, y);
            }
            sizes[x] += sizes[y];
            numbers[y] = x;
        }
    }
};

int main()
{

    FILE* fr, * fw;
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    int64_t n, m, q;
    fscanf(fr, "%lld %lld %lld", &n, &m, &q);


    std::vector<std::pair<int64_t, int64_t>> roads(m);
    std::vector<bool> destructedRoads(m, false);
    for (int64_t i{ 0 }; i < m; ++i) {
        fscanf(fr, "%lld %lld", &roads[i].first, &roads[i].second);
    }

    std::vector<int64_t> destructions(q);
    for (int64_t i{ 0 }; i < q; ++i) {
        fscanf(fr, "%lld", &destructions[i]);
        destructedRoads[destructions[i] - 1] = true;
    }

    DSU dsu(n);

    for (int64_t i{ 0 }; i < m; ++i) {
        if (!destructedRoads[i]) {
            dsu.unionCities(roads[i].first, roads[i].second);
        }
    }

    std::vector<int64_t> result(q);

    for (int64_t i{ 0 }; i < q; ++i) {
        if (dsu.components > 1) {
            result[q - i - 1] = 0;
        }
        else {
            result[q - i - 1] = 1;
        }
        dsu.unionCities(roads[destructions[q - i - 1] - 1].first, roads[destructions[q - i - 1] - 1].second);
    }

    for (int64_t i{ 0 }; i < q; ++i) {
        fprintf(fw, "%lld", result[i]);
    }

    fclose(fr);
    fclose(fw);

    return 0;
}