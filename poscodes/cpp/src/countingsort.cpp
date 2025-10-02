#include <iostream>
#include "poscode.hpp"
#include "queue.hpp"
#include "node.hpp"


void countingSortByPosition(std::vector<Poscode>& arr, int pos, int M){
    std::vector<eda::Queue<int>> buckets(M);
    for(int i = 0; i < arr.size(); i++){
        char a = arr[i].getData()[pos];
        int bucket = char_to_bucket(a, M);
        buckets[bucket].push(i);
    };
    std::vector<Poscode> buffer;
    buffer.reserve(arr.size());
    for (int j = 0; j < M; j++){
        while (!buckets[b].empty()){
            int idx = buckets[b].top();
            buffer.push_back(arr[idx]);
            buckets[j].pop();
        }
    }
    for (int i = 0; i < arr.size(); i++) {
    arr[i] = buffer[i];
    }

};