#include <iostream>
#include <string>
#include "utils.hpp"
#include "poscode.hpp"
#include <chrono>
#include <cmath>
#include <vector>

using SortFunction = void(*)(Poscode*, size_t);

double calcProm(const std::vector<double>& tiempos){
    double suma = 0.0;
    for (size_t i = 0; i < tiempos.size(); i++) {
        suma += tiempos[i];
    }
    return suma / tiempos.size();
}

double calcDesv(const std::vector<double>& tiempos, double promedio){
    double sum_diference = 0.0;
    for (size_t i = 0; i < tiempos.size(); i++) {
        double diference = tiempos[i] - promedio;
        sum_diference += diference * diference; 
    }
    double varianza = sum_diference/ tiempos.size();
    double desv = std::sqrt(varianza);

    return desv;
}

double measureTime(SortFunction sortFunc, Poscode* data, size_t n){
    auto start = std::chrono::high_resolution_clock::now();

    sortFunc(data,n);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    return duration.count();
}

int main (int argc,char** argv){
    if(argc != 4){
        std::cerr << "Uso: "<< argv[0] << " <archivo> <n> <runs>" <<std::endl;
        return 1;
    }

    std::string filepath = argv[1];
    size_t n = std::stoi(argv[2]);
    int runs = std::stoi(argv[3]);

    std::cout << "Archivo: " << filepath << std::endl;
    std::cout << "Tamaño: " << n << std::endl;
    std::cout << "Runs: " << runs << std::endl;

    Poscode* data = readCodes(filepath, n);
    if(data == nullptr){
        std::cerr << "Error del archivo"<< std::endl;
        return 1;
    }
    std::cout <<"Datos cargados" << std:: endl;

    //RadixSort
    std::cout << "\n Radix Sort " << std::endl;
    std::vector<double> tiempos_radix;
    
    for (int i = 0; i < runs; i++) {
        std::cout << "Corrida " << (i+1) << "... ";
    
        Poscode* copia = new Poscode[n];
        for (size_t j = 0; j < n; j++) {
            copia[j] = data[j];
        }

        double tiempo = measureTime(radix_sort, copia, n);

        if (is_sorted(copia, n)) {
            std::cout << "OK - " << tiempo << " ms" << std::endl;
            tiempos_radix.push_back(tiempo);
        } else {
            std::cout << "ERROR: No quedó ordenado" << std::endl;
        }

        delete[] copia;
    }

    double promedio_radix = calcProm(tiempos_radix);
    double desviacion_radix = calcDesv(tiempos_radix, promedio_radix);
    std::cout << "Radix Sort: " << promedio_radix << " ± " << desviacion_radix << " ms" << std::endl;
    // QuickSort
    std::cout << "\n QuickSort " << std::endl;
    std::vector<double> tiempos_quick;
    
    for (int i = 0; i < runs; i++) {
        std::cout << "Corrida " << (i+1) << "... ";
    
        Poscode* copia = new Poscode[n];
        for (size_t j = 0; j < n; j++) {
            copia[j] = data[j];
        }

        double tiempo = measureTime(quick_sort, copia, n);

        if (is_sorted(copia, n)) {
            std::cout << "OK - " << tiempo << " ms" << std::endl;
            tiempos_quick.push_back(tiempo);
        } else {
            std::cout << "ERROR: No quedó ordenado" << std::endl;
        }

        delete[] copia;
    }

    double promedio_quick = calcProm(tiempos_quick);
    double desviacion_quick = calcDesv(tiempos_quick, promedio_quick);
    std::cout << "QuickSort : " << promedio_quick << " ± " << desviacion_quick << " ms" << std::endl;

    //MergeSort
    std::cout << "\n MergeSort " << std::endl;
    std::vector<double> tiempos_merge;
    
    for (int i = 0; i < runs; i++) {
        std::cout << "Corrida " << (i+1) << "... ";
    
        Poscode* copia = new Poscode[n];
        for (size_t j = 0; j < n; j++) {
            copia[j] = data[j];
        }

        double tiempo = measureTime(merge_sort, copia, n);

        if (is_sorted(copia, n)) {
            std::cout << "OK - " << tiempo << " ms" << std::endl;
            tiempos_merge.push_back(tiempo);
        } else {
            std::cout << "ERROR: No quedó ordenado" << std::endl;
        }

        delete[] copia;
    }

    double promedio_merge = calcProm(tiempos_merge);
    double desviacion_merge = calcDesv(tiempos_merge, promedio_merge);
    std::cout << "MergeSort : " << promedio_merge << " ± " << desviacion_merge << " ms" << std::endl;

    deleteCodes(data);
    return 0;
}
