#pragma comment(linker, "/STACK:16777216")

#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
#include <fstream>

static std::pair<int64_t, int64_t> arrayOfDirections[4] = {
    {-1, 0}, {0, -1}, {1,0}, {0,1}
};

int entersHaveBeenDone{ 0 };
int exitsHaveBeenDone{ 0 };
bool personWasExited;

void DFS(int** array, bool** visited, int index1, int index2, const int n, const  int m, int prevPos)
{
    if (personWasExited) {
        return;
    }

    visited[index1][index2] = true;

    if (index1 == n - 1) {
        ++exitsHaveBeenDone;
        personWasExited = true;
        return;
    }


    int64_t direction = (prevPos == 3) ? 0 : prevPos + 1;
    while (direction != prevPos) {
        int64_t x = index1 + arrayOfDirections[direction].first;
        int64_t y = index2 + arrayOfDirections[direction].second;

        if (x >= 0 && x < n && y >= 0 && y < m) {
            if (!visited[x][y] && array[x][y] == 0) {

                int64_t currentPrevPos = direction;
                for (size_t i{ 0 }; i < 2; ++i) {
                    currentPrevPos = (currentPrevPos == 3) ? 0 : currentPrevPos + 1;
                }

                DFS(array, visited, x, y, n, m, currentPrevPos);
            }
        }
        direction = (direction == 3) ? 0 : direction + 1;
    }

    return;
}

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;

    int** array = new int* [n];
    for (size_t i{ 0 }; i < n; ++i) {
        array[i] = new int[m];
    }

    bool** visited = new bool* [n];
    for (size_t i{ 0 }; i < n; ++i) {
        visited[i] = new bool[m];
    }

    for (size_t i{ 0 }; i < n; ++i) {
        for (size_t j{ 0 }; j < m; ++j) {
            char c;
            fin >> c;
            if (c == 49) {
                array[i][j] = 1;
            }
            else {
                array[i][j] = 0;
            }
            visited[i][j] = false;
        }
    }

    for (size_t i{ 0 }; i < m; ++i) {
        if (array[0][i] == 0) {
            ++entersHaveBeenDone;
            if (n == 1) {
                ++exitsHaveBeenDone;
                continue;
            }

            if (array[1][i] == 1 || visited[1][i]) {
                break;
            }


            personWasExited = false;
            DFS(array, visited, 1, i, n, m, 0);
        }
    }

    if (entersHaveBeenDone == 0) {
        fout << "Impossible";
    }
    else {
        if (entersHaveBeenDone != exitsHaveBeenDone) {
            fout << "Impossible";
        }
        else {
            fout << "Possible";
        }
    }

    for (size_t i{ 0 }; i < n; ++i) {
        delete[] array[i];
    }
    delete[] array;

    for (size_t i{ 0 }; i < n; ++i) {
        delete[] visited[i];
    }
    delete[] visited;

    fin.close();
    fout.close();

    return 0;
}