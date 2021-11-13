#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void trim(string &str){
	//TODO
    string temp;
    getline(cin, str);
    size_t found = str.find_first_not_of(" ");
    size_t found_last = str.find_last_not_of(" ");
    str = str.erase(found_last+1, str.size());
    str = str.erase(0,found);
}
//  + str.erase(found_last+1, str.size())

void reverse(string &str){
	//TODO 
    int n = str.length();
  
    // Swap character starting from two
    // corners
    for (int i = 0; i < n / 2; i++){
        swap(str[i], str[n - i - 1]);
    }

}

int main()
{
    string input_line;
  	//TODO 
    trim(input_line);
    reverse(input_line);
    cout << input_line;
    return 0;
}