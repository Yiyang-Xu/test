//
//  sort.hpp
//  P1-part1
//
//  Created by Michael Xu on 2020/10/29.
//

#ifndef VE281P1_SORT_HPP
#define VE281P1_SORT_HPP
#include <random>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;

template<typename T>
void mySwap(T& left, T& right){
    T temp(left);
    left = right;
    right = temp;
}

template<typename T, typename Compare = std::less<T>>
void bubble_sort(std::vector<T> &vector, Compare comp = Compare()) {
    steady_clock::time_point start = steady_clock::now();
    //--------------------------------------------------------------//
    for (int i = 0; i < (int) vector.size()-1; i++){
            for (int j = 0; j < (int) vector.size()-i-1; ++j) {
                if (comp(vector[j+1],vector[j])){
                    mySwap(vector[j],vector[j+1]);
                }
            }
        }
    //--------------------------------------------------------------//
    steady_clock::time_point end = steady_clock::now();
    duration<double> bs_time_used = duration_cast<duration<double>>(end - start);
    cout <<  "Bubble sort costs " << double(bs_time_used.count()) << "second" << endl;
}

template<typename T, typename Compare = std::less<T>>
void insertion_sort(std::vector<T> &vector, Compare comp = Compare()) {
    steady_clock::time_point start = steady_clock::now();
    //--------------------------------------------------------------//
    int j = 0;
    for (int i = 1; i < (int) vector.size(); ++i) {
        T key = vector[i];
        j = i - 1;
        while (j >= 0 && comp(key, vector[j])){// while key < vector[j]
            vector[j+1] = vector[j];         // move the key ahead of vector[j]
            j--;
        }
        vector[j+1] = key;
    }
    //--------------------------------------------------------------//
    steady_clock::time_point end = steady_clock::now();
    duration<double> bs_time_used = duration_cast<duration<double>>(end - start);
    cout <<  "Insertion sort costs " << double(bs_time_used.count()) << "second" << endl;
}

template<typename T, typename Compare = std::less<T>>
void selection_sort(std::vector<T> &vector, Compare comp = Compare()) {
    steady_clock::time_point start = steady_clock::now();
    //--------------------------------------------------------------//
    for(int i = 0; i < (int) vector.size()-1; i++){
        int min_addr = i;
        for(int j = i+1; j < (int) vector.size(); j++){ // find the address of the min element in the remaining vector
            if (comp(vector[j],vector[min_addr])) min_addr = j;
        }
        mySwap(vector[i], vector[min_addr]);
    }
    //--------------------------------------------------------------//
    steady_clock::time_point end = steady_clock::now();
    duration<double> bs_time_used = duration_cast<duration<double>>(end - start);
    cout <<  "Selection sort costs " << double(bs_time_used.count()) << "second" << endl;
}

//***================== merge sort ==================***//
template<typename T, typename Compare = std::less<T>>
void merge(std::vector<T> &vector, int left, int mid, int right, Compare comp = Compare()){
    //create two vectors for left and right.
    std::vector<T> v_left(vector.begin()+left,vector.begin()+mid+1);
    std::vector<T> v_right(vector.begin()+mid+1,vector.begin()+right+1);
    int i = 0, j = 0, k = left;

    // choose the smaller one to add to the left most side of vector
    while (i < (int) v_left.size() && j < (int) v_right.size()){
        if (!comp(v_right[j],v_left[i])){
            vector[k] = v_left[i++];
        }
        else vector[k] = v_right[j++];
        k++;
    }
    // if one vector is not used up, append the elements to the end.
    while (i < (int) v_left.size()){
        vector[k] = v_left[i++];
        k++;
    }
    while (j < (int) v_right.size()){
        vector[k] = v_right[j++];
        k++;
    }
}

template<typename T, typename Compare = std::less<T>>
void ms_helper(std::vector<T> &vector, int left, int right, Compare comp = Compare()){
    if (left>=right) return;
    int mid = (left + right)/2;
    ms_helper(vector, left, mid, comp);
    ms_helper(vector, mid+1, right, comp);
    merge(vector, left, mid, right, comp);
}

template<typename T, typename Compare = std::less<T>>
void merge_sort(std::vector<T> &vector, Compare comp = Compare()) {
    steady_clock::time_point start = steady_clock::now();
    //--------------------------------------------------------------//
    ms_helper(vector, 0, (int) vector.size()-1, comp);
    //--------------------------------------------------------------//
    steady_clock::time_point end = steady_clock::now();
    duration<double> bs_time_used = duration_cast<duration<double>>(end - start);
    cout <<  "Merge sort costs " << double(bs_time_used.count()) << "second" << endl;
}

//***================== quick sort inplace ==================***//
template<typename T, typename Compare = std::less<T>>
int extra_partition(std::vector<T> &vector, int left, int right, Compare comp = Compare()){
    T pivot = vector[left];
    std::vector<T> leftV;
    std::vector<T> rightV;
    for (int i = left + 1; i <= right; ++i) {
        if (comp(vector[i],pivot)) leftV.push_back(vector[i]);
        else rightV.push_back(vector[i]);
    }
    for (int i = 0; i < (int) leftV.size(); ++i) vector[left + i] = leftV[i];
    int pivotAt = left + (int) leftV.size();
    vector[pivotAt] = pivot;
    for (int i = 0; i < (int) rightV.size(); ++i) vector[pivotAt+1+i] = rightV[i];
    return pivotAt;
}

template<typename T, typename Compare = std::less<T>>
void qs_extra_helper(std::vector<T> &vector, int left, int right, Compare comp){
    if (left >= right) return;
    int pvt_idx = extra_partition(vector, left, right, comp); // pivot index
    qs_extra_helper(vector, left, pvt_idx-1, comp);
    qs_extra_helper(vector, pvt_idx+1, right, comp);
}

template<typename T, typename Compare = std::less<T>>
void quick_sort_extra(std::vector<T> &vector, Compare comp = Compare()) {
    steady_clock::time_point start = steady_clock::now();
    //--------------------------------------------------------------//
    qs_extra_helper(vector, 0, (int) vector.size()-1, comp);
    //--------------------------------------------------------------//
    steady_clock::time_point end = steady_clock::now();
    duration<double> bs_time_used = duration_cast<duration<double>>(end - start);
    cout <<  "Extra palce quick sort costs " << double(bs_time_used.count()) << "second" << endl;
}

//***================== quick sort inplace ==================***//
template<typename T, typename Compare = std::less<T>>
int partition(std::vector<T> &vector, int left, int right, Compare comp = Compare()){
    T pivot = vector[left];        //choose the left most one as pivot
    int i = left + 1, j = right;
    while (i != j){
        while (i < j && comp(pivot,vector[j])) j--;
        while (i < j && !comp(pivot,vector[i])) i++;
        if (i >= j) break;
        swap(vector[i],vector[j]);
    }
    if(comp(vector[i],pivot)){// only swap the pivot when vector[i] <= pivot
        swap(vector[left],vector[i]);
        return i;
    }
    else return i-1;
}

template<typename T, typename Compare = std::less<T>>
void qs_inplace_helper(std::vector<T> &vector, int left, int right, Compare comp){
    if (left >= right) return;
    int pvt_idx = partition(vector, left, right, comp); // pivot index
    qs_inplace_helper(vector, left, pvt_idx-1, comp);
    qs_inplace_helper(vector, pvt_idx+1, right, comp);
}

template<typename T, typename Compare = std::less<T>>
void quick_sort_inplace(std::vector<T> &vector, Compare comp = Compare()) {
    steady_clock::time_point start = steady_clock::now();
    //--------------------------------------------------------------//
    qs_inplace_helper(vector, 0, (int) vector.size()-1, comp);
    //--------------------------------------------------------------//
    steady_clock::time_point end = steady_clock::now();
    duration<double> bs_time_used = duration_cast<duration<double>>(end - start);
    cout <<  "In-place quick sort costs " << double(bs_time_used.count()) << "second" << endl;
}

#endif //VE281P1_SORT_HPP
