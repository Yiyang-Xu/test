//
//  main.cpp
//  P1-part1
//
//  Created by Michael Xu on 2020/10/29.
//

#include <iostream>
#include <algorithm>
#include <functional>
#include <random>
#include <chrono>
#include "sort.hpp"

using namespace std;
using namespace chrono;
//using namespace steady_clock;

void show (const vector<int>& vector, const string& str);

int main() {
    
    vector<int> intV = {1872,4215,4022,4833,5396,5545,5782,6921,7281,7480,29,82,33,26,8790,27309};
    show(intV, "Original:");
    
    vector<int> intV1(intV);
    bubble_sort (intV1);
    show(intV1,"Bubble sort:");

    vector<int> intV2(intV);
    insertion_sort(intV2);
    show(intV2, "Insertion sort:");

    vector<int> intV3(intV);
    selection_sort(intV3);
    show(intV3, "Selection sort:");

    vector<int> intV4(intV);
    merge_sort(intV4);
    show(intV4,"Merge sort:");
    
    vector<int> intV5(intV);
    quick_sort_inplace(intV5);
    show(intV5,"In-place qsort:");
    
    vector<int> intV6(intV);
    quick_sort_extra(intV6);
    show(intV6,"Extra-place qsort:");

    sort(intV.begin(),intV.end());
    show(intV,"STL:");
}

void show (const vector<int>& vector, const string& str){
    cout << str << endl;
    for(int i : vector){
        cout << i << " ";
    }
    cout << endl << endl;
}

template<typename T>
bool less(const T &lhs, const T &rhs){
    return lhs < rhs;
}
