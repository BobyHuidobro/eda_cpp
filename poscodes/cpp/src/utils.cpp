#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include "poscode.hpp"
#include "queue.hpp"
#include <iostream>


void quick_sort(Poscode *A, size_t n){
    if (A == nullptr || n == 0) return;
    if (!A || n == 0) return;
    quick_sort_impl(A, 0, n - 1);
}

void quick_sort_impl(Poscode *A, int low, int high) {
    while (low < high) {
        int i = low;
        int j = high;
        Poscode pivot = A[low + (high - low) / 2];
        
        while (i <= j) {
            while (less_poscode(A[i], pivot)) i++;
            while (less_poscode(pivot, A[j])) j--;
            if (i <= j) {
                if (i != j) {
                    std::swap(A[i], A[j]);
                }
                i++;
                j--;
            }
        }

        if (j - low < high - i) {
            if (low < j) {
                quick_sort_impl(A, low, j);
            }
            low = i;
        } else {
            if (i < high){
                quick_sort_impl(A, i, high);
            }
            high = j;
        }
    }
}

void merge_sort(Poscode *A, size_t n){
    if ( A == nullptr || n == 0) return;
    if (!A || n == 0) return;
    std::vector<Poscode> V(n);
    merge_sort_impl(A, V, 0, n - 1);
}

void merge_sort_impl(Poscode *A, std::vector<Poscode>& V, int l, int r) {
    if (l >= r) return;

    int m = l + (r - l) / 2;
    merge_sort_impl(A, V, l, m);
    merge_sort_impl(A, V, m + 1, r);
    if(!less_poscode(A[m + 1], A[m])) return;
    merge(A, V, l, m, r);
}

void merge(Poscode *A, std::vector<Poscode>& V, int l, int m, int r) {
    for (int t = l; t <= r; t++) {
        V[t] = A[t];
    }
    int i = l;
    int j = m + 1;
    int k = l;

    while (i <= m && j <= r) {
        if (less_poscode(V[j], V[i])) {
            A[k] = V[j];
            j++;
        } else {
            A[k] = V[i];
            i++;
        }
        k++;
    }

    while (i <= m) {
        A[k] = V[i];
        i++;
        k++;
    }
    while (j <= r) {
        A[k] = V[j];
        j++;
        k++;
    }
}

void radix_sort(Poscode *A, size_t n){
    if (A == nullptr || n == 0) return;
    if (!A || n == 0) return;
    std::vector<Poscode> V(n);
    for (size_t i = 0; i < n; i++){
        V[i] = A[i];
    }
    for (int pos = 5; pos >= 0; pos--) {
        if (pos > 3) {
            countingSortByPosition(V, pos, 26);
        } else {
            countingSortByPosition(V, pos, 10);
        }
    }
    for (size_t i = 0; i < n; i++){
        A[i] = V[i];
    }
}

Poscode *readCodes(const std::string &strfile, size_t n){
    // Replace "example.txt" with the actual path to your text file.
    Poscode *codes = new Poscode[n];

    std::ifstream inputFile(strfile);    
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file!" << std::endl;        
        return nullptr;
    }
    // 3. Read the file content line by line.
    std::string line;
    for(size_t i = 0; i < n; i++){
        std::getline(inputFile, line); 
        codes[i] = Poscode(line);
    }
    
    inputFile.close();
    return codes;
}

void deleteCodes(Poscode *codes){
    if (codes != nullptr) {
        delete[] codes;
    }    
}

static inline bool less_poscode(Poscode& a, Poscode& b){
    return a.getData() < b.getData();
}

static inline int char_to_bucket(char c, int M){
    if (M==10) {
        if (c>='0' && c<='9') return c - '0';
        return -1;
    } else if (M == 26) {
        if (c>='A' && c<='Z') return c - 'A';
        return -1;
    }
    return -1;
}
void countingSortByPosition(std::vector<Poscode>& arr, int pos, int M){
    std::vector<eda::Queue> buckets(M);
    for(int i = 0; i < arr.size() ; i++){
        char a = arr[i].getData()[pos];
        int bucket = char_to_bucket(a, M);
        if (bucket >= 0 && bucket < M) {  
            buckets[bucket].push(i);
        }
    };
    std::vector<Poscode> buffer;
    buffer.reserve(arr.size());
    for (int j = 0; j < M; j++){
        while (!buckets[j].isEmpty()){
            int idx = buckets[j].top()->getData();
            buffer.push_back(arr[idx]);
            buckets[j].pop();
        }
    }
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = buffer[i];
    }
}