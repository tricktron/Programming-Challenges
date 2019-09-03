//
// Created by Thibault Gagnaux on 07.10.17.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    int cases, length, value, median, min_dist;
    std::cin >> cases;
    for (int k = 0; k < cases; k++) {
        //std::cin >> length, scanf is faster
        scanf("%d", &length);
        std::vector<int> arr;
        for (int i = 0; i < length; i++) {
            //std::cin >> value;, scanf is faster
            scanf("%d", &value);
            arr.push_back(value);
        }
        // the select algorithm from the standard library
        std::nth_element(arr.begin(), arr.begin() + arr.size() / 2, arr.end());
        median = arr[arr.size() / 2];
        min_dist = 0;
        for (int j = 0; j < length; j++) {
            min_dist += abs(arr[j] - median);
        }
        std::cout << min_dist << '\n';
    }
    return 0;
}
