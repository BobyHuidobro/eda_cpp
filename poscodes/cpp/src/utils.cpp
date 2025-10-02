#include "utils.hpp"
#include <iostream>
#include <fstream>


void quick_sort(Poscode *A, size_t n){

}

void merge_sort(Poscode *A, size_t n){

}
void radix_sort(Poscode *A, size_t n){

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