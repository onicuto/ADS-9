// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <iomanip>
#include "tree.h"

int main() {
    std::cout << std::setw(5) << "n" 
              << std::setw(15) << "getAllPerms" 
              << std::setw(15) << "getPerm1" 
              << std::setw(15) << "getPerm2" << std::endl;

    for (int n = 1; n <= 10; ++n) {
        std::vector<char> in;
        for (int i = 0; i < n; ++i) in.push_back('0' + i);

        PMTree tree(in);

        // Measure getAllPerms
        auto start = std::chrono::high_resolution_clock::now();
        auto all = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_all = end - start;

        // Random permutation number
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, all.size());
        int num = dis(gen);

        // Measure getPerm1
        start = std::chrono::high_resolution_clock::now();
        getPerm1(tree, num);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff1 = end - start;

        // Measure getPerm2
        start = std::chrono::high_resolution_clock::now();
        getPerm2(tree, num);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff2 = end - start;

        std::cout << std::setw(5) << n 
                  << std::setw(15) << diff_all.count() 
                  << std::setw(15) << diff1.count() 
                  << std::setw(15) << diff2.count() << std::endl;
    }

    return 0;
}
