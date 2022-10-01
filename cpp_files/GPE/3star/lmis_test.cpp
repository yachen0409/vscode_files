// C++ implementation
// to find LIS
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
 
// Return length of LIS in arr[] of size N
int lis(int arr[], int N)
{
    int i;
    set<int> s;
    set<int>::iterator k;
    for (i=0; i<N; i++)
    {
        // Check if the element was actually inserted
        // An element in set is not inserted if it is
        // already present. Please see
        // https://www.geeksforgeeks.org/set-insert-function-in-c-stl/
        if (s.insert(arr[i]).second)
        {
            // Find the position of inserted element in iterator k
            k = s.find(arr[i]);
 
            k++;  // Find the next greater element in set
 
            // If the new element is not inserted at the end, then
            // remove the greater element next to it (This is tricky)
            if (k!=s.end()) s.erase(k);
        }
    }
 
    // Note that set s may not contain actual LIS, but its size gives
    // us the length of LIS
    return s.size();
}
 
int main()
{
    int arr[] = {2, 6, 1, 9, 7, 3, 5, 4, 8};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << lis(arr, n)<< endl;
}