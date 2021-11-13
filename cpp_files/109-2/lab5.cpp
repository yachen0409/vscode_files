#include <vector>
#include <iostream>
using namespace std;

class Object{
public:
    virtual void response() = 0;
    
    virtual ~Object() = default;
};

class IceMonster : public Object{
	//add constructor or functions if you need
    void response(){
        cout << "fire attack" << endl;
    }
};

class FireMonster : public Object{
	//add constructor or functions if you need
    void response(){
        cout << "ice attack" << endl;
    }
};

class Treasure : public Object{
	//add constructor or functions if you need
    void response(){
        cout << "ya" << endl;
    }
};
class Empty : public Object{
	//add constructor or functions if you need
    void response(){
        cout << " " << endl;
    }
};


class Room{
public:
    Room *up_room;
    Room *down_room;
    Room *left_room;
    Room *right_room;
    int index;
    Object *o;
    //add constructor or functions if you need

    Room(){
    }
    Room(int index){
        this->index = index;
    }
    void put(char type, int dirc[], Room* r[]){
        if (dirc[0] == -1){
            up_room = nullptr;
        }
        else{
            up_room = r[dirc[0]];
        }
        if (dirc[1] == -1){
            down_room = nullptr;
        }
        else{
            down_room = r[dirc[1]];
        }
        if (dirc[2] == -1){
            left_room = nullptr;
        }
        else{
            left_room = r[dirc[2]];
        }
        if (dirc[3] == -1){
            right_room = nullptr;
        }
        else{
            right_room = r[dirc[3]];
        }

        if(type == 'i'){
            this->o = new IceMonster;
        }
        else if(type == 'f'){
            this->o = new FireMonster;
        }
        else if(type == 't'){
            this->o = new Treasure;
        }
        else{
            this->o = new Empty;
        }
    }
    void output(){
        cout << index <<" ";
        this->o->response();
        this->o->~Object();
        this->o = new Empty;
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int num_of_rooms, test_times;
    
    cin >> num_of_rooms >> test_times;
    Room* r[num_of_rooms];

    for(int i = 0; i < num_of_rooms; ++i){
        r[i] = new Room(i);
    }
    for (int i = 0; i < num_of_rooms; ++i){
        char type;
        int dirc[4];
        cin >> type;
        for(int j = 0 ; j < 4; j++){
            cin >> dirc[j];
        }

        r[i]->put(type, dirc, r);
    }
    Room* tmp = r[0];
    for (int i = 0; i < test_times; ++i){
        char dire;
        cin >> dire;
        if (i == 0){
            tmp->output();
        }
        if (dire == 'u'){
            if (tmp->up_room != nullptr){
                tmp = tmp->up_room;
            }
            else{
                cout << "-1" << endl;
                continue;
            }
        }
        if (dire == 'd'){
            if (tmp->down_room != nullptr){
                tmp = tmp->down_room;
            }
            else{
                cout << "-1" << endl;
                continue;
            }
        }
        if (dire == 'l'){
            if (tmp->left_room != nullptr){
                tmp = tmp->left_room;
            }
            else{
                cout << "-1" << endl;
                continue;
            }
        }
        if (dire == 'r'){
            if (tmp->right_room != nullptr){
                tmp = tmp->right_room;
            }
            else{
                cout << "-1" << endl;
                continue;
            }
        }
        tmp->output();

    }

    return 0;
}