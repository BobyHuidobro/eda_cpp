#ifndef __UTILS_HPP__
#define __UTILS_HPP__
#include "poscode.hpp"
#include <string>
#pragma once
#include <vector>
void quick_sort(Poscode *A, size_t n);
void merge_sort(Poscode *A, size_t n);
void radix_sort(Poscode *A, size_t n);
bool is_sorted(Poscode *A, size_t n);

Poscode *readCodes(const std::string &strfile, size_t n);
void deleteCodes(Poscode *codes);

void countingSortByPosition(std::vector<Poscode>& arr, int pos, int M);
#endif

