#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Student {
public:
	Student( ) { }
	string generate_address(){
    	//TODO 
        string final = "1001 University Road, Hsinchu, Taiwan 300, ROC, dorm " + dormitory + ", (" + ID + ") "+ first_name + " " + last_name;
        return final;        
    }
    void get_info(vector <string> v){
        for(int i = 0; i < v.size(); ++i){
            switch (i)
            {
                case 0: first_name = v[i];
                    break;
                case 1: last_name = v[i];
                    break;
                case 2: dormitory = v[i];
                    break;
                case 3: ID = v[i];
                    break;
                default:
                    break;
            }
        }
    }

  	//Please implement the remain class
private:
	string first_name;
    string last_name;
	string dormitory;
	string ID;
};


int main() {
  	Student mStudent;
    string temp;
    /* Enter your code here. Read input from STDIN */
    vector <string> student_info;
    for (int i = 0; i < 4; ++i){
        cin>>temp;
        student_info.push_back(temp);
    }
    // for (int i = 0; i < student_info.size(); ++i){
    //     cout<<student_info[i]<<" ";
    // }
    mStudent.get_info(student_info);
  	cout << mStudent.generate_address() << endl;
    return 0;
}