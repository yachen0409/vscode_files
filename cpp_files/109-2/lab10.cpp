#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int index;
    bool isvisited;
    Node* next;
    Node(){}
    Node(int index) : index(index), isvisited(false), next(nullptr) {};
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int num = 0;
    cin >> num;
    int value;
    vector<vector<int>> arr(num, vector<int>(num, 0));

    Node* ptr[num];
    for(int i = 0; i < num; i++)
    {
        ptr[i] = new Node(i);
    }

    for(int x = 0; x < num; x++){
        for(int y = 0; y < num; y++){
            cin >> value;
            arr[x][y] = value;
        }
    }

    vector<vector<int>> prtList(arr.size());
    bool visited[arr.size()] = {false};

    for (int i = 0; i < arr.size(); i++)
    {   
        Node* temp = ptr[i];
        for(int j = i+1; j < arr[i].size(); j++)
            {   

            if(arr[i][j] == 1){
                temp->next = ptr[j];
                temp = temp->next;
            }
        }
    }
 
    for (int i = 0; i < prtList.size(); i++)
    {
        Node* current = ptr[i];
        bool next = false;
        while(!current->isvisited && current != nullptr)
        {
            next = true;
            cout << current->index << " ";
            current->isvisited = true;
            if(current->next == nullptr)
                break;
            current = current->next;
        }
        if(next)
            cout << endl;
        
    }
    return 0;
}
// vector<int> bubblesort(int length, vector<int> arr){      //? find the BIGGEST one and swap it to the end one by one
//     int temp;
//     for(int i = 0; i < length-1; i++){              // for size n arr, only need n-1 times full sort
//         for(int j = 0; j < length-i-1; j++){        // since every time we sort it, the last i bubbles hsa been sorted
//                                                     //! without -1 will lead to an error isnce *(arr+length) = eof
//             if(arr[j+1] < arr[j]){
//                 temp = arr[j+1];
//                 arr[j+1] = arr[j];
//                 arr[j] = temp;
//             }
//         }
//     }
//     return arr;
// }

// vector<vector<int>> convert( vector<vector<int>> a)
// {
//     vector<vector<int>> adjList(a.size());
//     for (int i = 0; i < a.size(); i++)
//     {
//         for (int j = 0; j < a[i].size(); j++)
//         {
//             if (a[i][j] == 1)
//             {
//                 adjList[i].push_back(j);
//             }
//         }
//     }
//     return adjList;
// }