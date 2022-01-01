#include<iostream>
#include<vector>
#include<fstream>
#include<set>
#include<algorithm>
#include <stdio.h>
#include <stdlib.h>
#include<numeric>
#include<list>
#include<queue>


void BFS(std::vector<int>& vector, int** array, int start, int& count ) {

    std::queue<int> queue;
    //queue.push(start);
    std::vector<int> visited(vector.size(), false);

    /*
    while (!queue.empty()) {

        int vertex{ queue.front() };
        queue.pop();

        vector[vertex] = count;
        for (int i{ 0 }; i < vector.size(); ++i) {
            if (array[vertex][i] && !visited[i]) {
                queue.push(i);
                visited[i] = true;
            }
        }
        ++count;

    }
    */
    for (size_t i = 0 ; i < vector.size(); ++i) {
        if (vector[i] == 0) {
            queue.push(i);

            while (!queue.empty()) {

                int vertex = queue.front() ;
                queue.pop();


                vector[vertex] = count;
                visited[vertex] = true;
                ++count;

                for (size_t j =0 ; j < vector.size(); ++j) {
                    if (array[vertex][j] && !visited[j]) {
                        queue.push(j);
                        visited[j] = true;

                    }
                }


            }

        }
    }
}

void DFS(std::vector<int> &v, int** array, int &count, std::vector<bool> &visited, int index){
    if(visited[index]){
        return;
    }
    visited[index] = true;
    v[index]  = count;
    ++count;
    for(size_t i = 0; i<v.size(); ++i){
        if(array[index][i] && !visited[i]){

            DFS(v, array, count, visited, i);
        }
    }
}

int main() {
    int n;

    FILE* fr, * fw;
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    fscanf(fr, "%d", &n);

    std::vector<int> vector(n, 0);
    int** array = new int* [n];
    for (size_t i = 0 ; i < n; ++i) {
        array[i] = new int[n];
    }



    for (size_t i = 0 ; i < n*n ; ++i) {
        fscanf(fr, "%d", &array[i / n][i % n]);
    }

    int count = 1 ;
    std::vector<bool> visited(n, false);
    for(size_t i = 0; i<n; ++i){
        DFS(vector, array, count, visited, i);
    }
    for (size_t i = 0 ; i < n;++i) {

        fprintf(fw, "%d ", vector[i]);
    }



    for (size_t i = 0 ; i < n; ++i) {
        delete[] array[i];
    }
    delete[] array;

    fclose(fr);
    fclose(fw);

    return 0;

}