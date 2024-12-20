#include <iostream>
#include <vector>
#include <algorithm>

int search_rotated(std::vector<int>& arr, int target) {
    int len = static_cast<int>(arr.size());
    int left = 0;
    int right = len - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == target) return mid;

        if (arr[left] <= arr[mid]) {
            if (arr[left] <= target && target < arr[mid]) {
                right = mid - 1;
            }
            else left = mid + 1;
        }
        else {
            if (arr[mid] < target && target <= arr[right]) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
    }

    return -1;
}