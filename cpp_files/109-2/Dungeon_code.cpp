#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

class Room{
    private:
        int room_num; 
        Room* up;
        Room* down;
        Room* left;
        Room* right;
    public:
        Room():room_num(0), up(0), down(0), left(0), right(0){};
        Room(int a):room_num(a), up(0), down(0), left(0), right(0){};
        friend class linkedRoom;
        friend class Dungeon;
};

class linkedRoom{
    public: 
        Room* one = new Room(1);
        Room* two = new Room(2);
        Room* thr = new Room(3);
        Room* fou = new Room(4);
        Room* fiv = new Room(5);
        Room* six = new Room(6);
        Room* sev = new Room(7);
        Room* eig = new Room(8);
        Room* nin = new Room(9);

        Room* temp = new Room();
        Room* current = one;
        Room* previous = temp;
        linkedRoom(){};
        void generate_room(){
            one->right = two;
            one->down = fou;

            two->left = one;
            two->down = fiv;

            thr->right = fou;

            fou->up = one;
            fou->down = sev;
            fou->left = thr;
            fou->right = fiv;

            fiv->up = two;
            fiv->left = fou;
            fiv->right = six;

            six->left = fiv;

            sev->up = fou;
            sev->down = nin;
            sev->right = eig;

            eig->left = sev;
            
            nin->up = sev;
        }
};

class NPC{
    public:
    int NPChp, NPCattack, NPCdefense;
    NPC(int a, int b, int c){
        NPChp = a;
        NPCattack = b;
        NPCdefense = c;
    };
    virtual void get_status() = 0;
    virtual char challenge(int &hp, int &attack, int &defense, int &money) = 0;
    virtual char combat() = 0;
};
class Peter : public NPC{ //雜魚，刷等級用
    public:
    Peter():NPC(50, 20, 10){}
    ~Peter(){};
    void get_status(){
        cout << "----------Monster's status-----------" << endl;
        cout << "-- HP: " << NPChp << "/50" << endl;
        cout << "-- Attack: " << NPCattack << endl;
        cout << "-- Defense: " << NPCdefense << endl;
        cout << "-------------------------------------" << endl;
    }
    char combat(){
        char op;
        cout << "What do you want to do now?" << endl;
        cout << "a. Attack it!" << endl;
        cout << "b. Retreat!" << endl;
        cin >> op;
        cout << endl;
        return op;
    }
    char challenge(int &hp, int &attack, int &defense, int &money){
        char op;
        char returnchar;
        bool out = false;
        bool playerdead = false;
        bool monsterdead = false;
        int count = 0;
        while(!out){
            NPChp = NPChp - (attack - NPCdefense);      //player attack
            if(NPChp <= 0){             //monster dead
                cout << "*** Nice!!! The MONSTER is dead! ***" << endl;
                money += 20;
                cout << "*** Money +$20! ***" << endl;
                cout << endl;
                monsterdead = true;
                break;
            }
            else{                       //monster wounded
                cout << "*** The MONSTER is wounded! It has " << NPChp << " hp left. ***" << endl;
                if (NPChp <= 30){       //money reward
                    if (count == 0){
                        money += 20;
                        cout << "*** Money +$20! ***" << endl;
                        ++count;
                    }
                }
                if (NPChp <= 10){
                    if (count == 1){
                        money += 20;
                        cout << "*** Money +$20! ***" << endl;
                        ++count;
                    }
                }
            }
            hp = hp - (NPCattack - defense);    //monster attack
            if(hp <= 0){                //player dead
                cout << "*** Fxxk!!! Your DEAD! ***" << endl;
                playerdead = true;
                break;
            }
            else{                       //player wounded
                cout << "*** The MONSTER attack you! You have " << hp << " hp left. ***" << endl;
                cout << endl;
            }
            get_status();       //display monster's status
            op = combat();      //player decide challenge again or not
            if(op == 'b'){
                out = true;
            }
        }
        if(playerdead){
            exit(EXIT_FAILURE);     //end of program
        }
        else if(monsterdead){
            returnchar = 'a';
        }
        else if(out){
            returnchar = 'r';
        }
        return returnchar;   
    }      
};
class boss : public NPC{ //BOSS
    public:
    boss():NPC(200, 50, 25){}  
    void get_status(){
        cout << "----------Boss's status-----------" << endl;
        cout << "-- HP: " << NPChp << "/200" << endl;
        cout << "-- Attack: " << NPCattack << endl;
        cout << "-- Defense: " << NPCdefense << endl;
        cout << "----------------------------------" << endl;
    }
    char combat(){
        char op;
        
        cout << "What do you want to do now?" << endl;
        cout << "a. Attack it!" << endl;
        cout << "b. Retreat!" << endl;
        cin >> op;
        cout << endl;
        return op;
    }
    char challenge(int &hp, int &attack, int &defense, int &money){
        char op;
        char returnchar;
        bool out = false;
        bool playerdead = false;
        bool monsterdead = false;
        int count = 0;
        while(!out){
            NPChp = NPChp - (attack - NPCdefense);
            if(NPChp <= 0){
                cout << "*** Nice!!! The BOSS is dead! ***" << endl;
                cout << endl;
                cout << "**********************************************************" << endl;
                cout << "*** Congratulations!! You completed the dungeon game!! ***" << endl;
                cout << "**********************************************************" << endl;
                monsterdead = true;
                break;
            }
            else{
                cout << "*** The BOSS is wounded! It has " << NPChp << " hp left. ***" << endl;
                if (NPChp <= 150){
                    if (count == 0){
                        money += 20;
                        cout << "*** Money +$20! ***" << endl;
                        ++count;
                    }
                }
                if (NPChp <= 100){
                    if (count == 1){
                        money += 20;
                        cout << "*** Money +$20! ***" << endl;
                        ++count;
                    }
                }
                if (NPChp <= 50){
                    if (count == 2){
                        money += 20;
                        cout << "*** Money +$20! ***" << endl;
                        ++count;
                    }
                } 
            }
            hp = hp - (NPCattack - defense);
            if(hp <= 0){
                cout << "*** Fxxk!!! Your DEAD! ***" << endl;
                playerdead = true;
                break;
            }
            else{
                cout << "*** The BOSS attack you! You have " << hp << " hp left. ***" << endl;
                cout << endl;
            }
            get_status();
            op = combat();
            if(op == 'b'){
                out = true;
            }
        }
        if(playerdead){
            exit(EXIT_FAILURE);
        }
        else if(monsterdead){
            exit(EXIT_FAILURE);
        }
        else if(out){
            returnchar = 'r';
        }
        return returnchar;   
    }
};

class Dungeon: public linkedRoom
{
    public:
        int hp = 100,
            hpMAX = 100, 
            attack = 30,
            defense = 10,
            money = 100;
        string name; 
        char operation;
        int hp_water = 3;
        bool monster1_dead = false;
        bool monster2_dead = false;
        bool boss_dead = false;
        bool has_key = false;
        bool box_opened = false;
        bool playerdead = false;
        Peter* p2 = new Peter();
        Peter* p1 = new Peter();
        boss* boss1 = new boss();
        Dungeon(){};
        
        void welcome(){
            cout << "Welcome to the Dungeon!" << endl;
            cout << "--- Kill the boss to get out from the dungeon. ---" << endl;
        }
        void record_or_not(){
            cout << "Do you want to load previous data?" << endl;
            cout << "a. Yes" << endl;
            cout << "b. No" << endl;
            cin >> operation;
            if (operation == 'a' || operation == 'A'){
                this->get_record();
            }
        }
        void enter_name(){
            cout << endl;
            cout << "Please enter player's name (DO NOT enter space betweeen letters!): " ;
            cin >> name;
            cout << endl;
        }
        void shop(){
            char op;
            bool out = false;
            while(!out){
                cout << "-- You got $" << money << " now! --"<< endl;
                cout << endl;
                cout << "@@ We sell the following items: @@" << endl;
                cout << "|    Option      |  Price  |    Effect    |" << endl;
                cout << "-------------------------------------------" << endl;
                cout << "| a. SWORD       |  $100   |  +20 attack  |" << endl;
                cout << "| b. SHIELD      |  $100   |  +20 defense |" << endl;
                cout << "| c. EXTRA HEART |  &150   |  +20 Max HP  |" << endl;
                cout << endl;
                cout << "Which item do you want to buy?" << endl;
                cout << "a. Sword" << endl;
                cout << "b. Shield" << endl;
                cout << "c. Heart" << endl;
                cin >> op;
                cout << endl;
                if(op == 'a'){
                    if(money >= 100){
                        money -= 100;
                        attack += 20;
                        cout << "** Deal! You have a SWORD which brings you +20 attack now! **" << endl;
                        cout << endl;
                    }
                    else{
                        cout << "You are too poor to buy the SWORD :((( Go and earn more money!!!" << endl;
                        cout << endl;
                    }
                }
                else if(op == 'b'){
                    if(money >= 100){
                        money -= 100;
                        defense += 20;
                        cout << "** Deal! You have a SHIELD which brings you +20 defense now! **" << endl;
                        cout << endl;
                    }
                    else{
                        cout << "You are too poor to buy the SHIELD :((( Go and earn more money!!!" << endl;
                        cout << endl;
                    }
                }
                else if(op == 'c'){
                    if(money >= 150){
                        money -= 150;
                        hpMAX += 20;
                        cout << "** Deal! You have a EXTRA HEART which brings you +20 attack now! **" << endl;
                        cout << endl;
                    }
                    else{
                        cout << "You are too poor to buy the EXTRA HEART :((( Go and earn more money!!!" << endl;
                        cout << endl;
                    }

                }
                cout << "@@ Need to buy more items? @@" << endl;
                cout << "a. Yes" << endl;
                cout << "b. No" << endl;
                cin >> op;
                cout << endl;
                if(op == 'b'){
                    out = true;
                }
            }
        }
        void game(){
            char op;
            int guess_num ;
            int low_risk_point = 20;
            int high_risk_point = 40;
            bool no_more_game = false;
            cout << "Time to gamble!" << endl;
            cout << "@@ Game rules: @@" << endl;
            cout << "@@ Try to guess the integer number between 1-10 that the Gambler hold @@"<< endl;
            cout << "@@ If you try <= 5 times, you will get a reward. @@" << endl;
            cout << "@@ If you try > 5 times, you will get a punishment. @@" << endl;
            cout << "!! Notice: if your number is OUT OF RANGE, you will also get a punishment. !!" << endl;
            cout << endl;
            cout << "Do you still want to play?" << endl;
            cout << "a. Yes" << endl;
            cout << "b. No" << endl;
            cin >> op;
            cout << endl;
            if(op == 'a'){
                while(!no_more_game){
                    bool win = false;
                    srand(time(NULL));
                    int computer_num = rand() % (10 + 1);

                    cout << "Game Start!" << endl;
                    cout << "--- Choose your risk level first. ---" << endl;
                    cout << "--- It will reflect on rewards and punishments. ---" << endl;
                    cout << "a. low risk" << endl;
                    cout << "b. high risk" << endl;
                    cin >> op;
                    cout << endl;

                    for(int i = 0; i < 5; ++i){
                        cout << "Input your guess Number(1-10): " << endl;
                        cin >> guess_num;
                        cout << endl;
                        if(guess_num > computer_num){
                            cout << "--- Guess LOWER! ---" << endl;
                            cout << 5-i-1 << " chances remain." << endl;
                            cout << endl;
                        }
                        else if (guess_num < computer_num){
                            cout << "--- Guess HIGHER! ---" << endl;
                            cout << 5-i-1 << " chances remain." << endl;
                            cout << endl;
                        }
                        else if ((guess_num < 1) || (guess_num > 10)){
                            cout << "*** Input OUT OF RANGE! You lose!!! ***" << endl;
                            cout << endl;
                            break;
                        }
                        else {
                            win = true;
                            break;
                        }
                    }
                    cout << "Gambler's number is " << computer_num << endl;

                    if(op == 'a'){
                        if(win){
                            cout << "*** You win the game!!! ***" << endl;
                            cout << "*** You got " << low_risk_point << " BONUS now! ***" << endl;
                            cout << "*** You can choose to add it on MAX HP, Attack, or Defense. ***" << endl;
                            cout << "Choose it now: " << endl;
                            cout << "a. MAX HP" << endl;
                            cout << "b. Attack" << endl;
                            cout << "c. Defense" << endl;
                            cin >> op;
                            cout << endl;
                            if(op == 'a'){
                                hpMAX += low_risk_point;
                                cout << "*** Your MAX HP has become " << hpMAX <<" now! ***"<< endl;
                            }
                            else if(op == 'b'){
                                attack += low_risk_point;
                                cout << "*** Your Attack has become " << attack <<" now! ***"<< endl;
                            }
                            else if(op == 'c'){
                                defense += low_risk_point;
                                cout << "*** Your Defense has become " << defense <<" now! ***"<< endl;
                            }
                        }   
                        else{
                            cout << "*** You loss the game...... ***" << endl;
                            cout << "*** Your MAX HP, Attack, and Defense will all be subtracted " << low_risk_point << "...... ***" << endl;
                            hpMAX -= low_risk_point;
                            if(hp > hpMAX){
                                hp = hpMAX;
                            }
                            if(hp <= 0){
                                cout << "*** Fxxk!!! Your DEAD! ***" << endl;
                                playerdead = true;
                                exit(EXIT_FAILURE);
                            }
                            attack += low_risk_point;
                            defense += low_risk_point;
                            cout << endl;
                            cout << "*** Your MAX HP has become " << hpMAX <<" now! ***"<< endl;
                            cout << "*** Your Attack has become " << attack <<" now! ***"<< endl;
                            cout << "*** Your Defense has become " << defense <<" now! ***"<< endl;
                        }    
                        cout << endl;
                        cout << "Want to gamble AGAIN?" << endl;
                        cout << "a. Yes" << endl;
                        cout << "b. No" << endl;
                        cin >> op;
                        cout << endl;
                        if(op == 'b'){
                            no_more_game = true;
                        }    
                    }
                    else{
                        if(win){
                            cout << "*** You win the game!!! ***" << endl;
                            cout << "*** You got " << high_risk_point << " BONUS now! ***" << endl;
                            cout << "*** You can choose to add it on MAX HP, Attack, or Defense. ***" << endl;
                            cout << "Choose it now: " << endl;
                            cout << "a. MAX HP" << endl;
                            cout << "b. Attack" << endl;
                            cout << "c. Defense" << endl;
                            cin >> op;
                            cout << endl;
                            if(op == 'a'){
                                hpMAX += high_risk_point;
                                cout << "*** Your MAX HP has become " << hpMAX <<" now! ***"<< endl;
                            }
                            else if(op == 'b'){
                                attack += high_risk_point;
                                cout << "*** Your Attack has become " << attack <<" now! ***"<< endl;
                            }
                            else if(op ==
                             'c'){
                                defense += high_risk_point;
                                cout << "*** Your Defense has become " << defense <<" now! ***"<< endl;
                            }
                        }   
                        else{
                            cout << "*** You loss the game...... ***" << endl;
                            cout << "*** Your MAX HP, Attack, and Defense will all be subtracted " << high_risk_point << "...... ***" << endl;
                            hpMAX -= high_risk_point;
                            if(hp > hpMAX){
                                hp = hpMAX;
                            }
                            if(hp <= 0){
                                cout << "*** Fxxk!!! Your DEAD! ***" << endl;
                                playerdead = true;
                                exit(EXIT_FAILURE);
                            }
                            attack += high_risk_point;
                            defense += high_risk_point;
                            cout << endl;
                            cout << "*** Your MAX HP has become " << hpMAX <<" now! ***"<< endl;
                            cout << "*** Your Attack has become " << attack <<" now! ***"<< endl;
                            cout << "*** Your Defense has become " << defense <<" now! ***"<< endl;
                        }    
                        cout << endl;
                        cout << "Want to gamble AGAIN?" << endl;
                        cout << "a. Yes" << endl;
                        cout << "b. No" << endl;
                        cin >> op;
                        cout << endl;
                        if(op == 'b'){
                            no_more_game = true;
                        }    
                    }
                }
            }
        }
        void menu(){
            char op;
            bool out = false;
            while(!out){
                cout << "What do you want to do now?" << endl;
                cout << "a. Move" << endl;
                cout << "b. Check Status" << endl;
                cout << "c. Save to file" << endl;
                cin >> op;
                switch (op)
                {
                case 'a':
                case 'A':
                    move(current);
                    out = true;
                    break;
                case 'b':
                case 'B':
                    this-> print_status();
                    break;
                case 'c':
                case 'C':
                    this-> save_record();
                    cout << endl;
                    cout << "Record SAVED!" << endl;
                    break;
                default:
                    break;
                }
            } 
        }
        void move(Room* now){
            char op;
            int mode;
            bool out = true;
            cout << endl;
            cout << "Where do you want to go?" << endl;
            if (now->up == 0){          //option display
                if(now->down == 0){
                    if(now->left == 0){
                        cout << "a. Go RIGHT →" << endl;
                        mode = 1;
                    }
                    else{
                        cout << "a. Go LEFT ←" << endl;
                        mode = 2;
                        if(now->right != 0){
                            cout << "b. Go RIGHT →" << endl;
                            mode = 3;
                        }
                        
                    }
                }
                else{ 
                    cout << "a. Go DOWN ↓" << endl;
                    mode = 4;
                    if(now->left == 0){
                        cout << "b. Go RIGHT →" << endl;
                        mode = 5;
                    }
                    else{
                        cout << "b. Go LEFT ←" << endl;
                        mode = 6;
                        if(now->right != 0){
                            cout << "c. Go RIGHT →" << endl;
                            mode = 7;
                        }
                    }
                }
            }
            else{
                cout << "a. Go UP ↑" << endl;
                mode = 8;
                if(now->down == 0){
                    if(now->left == 0){
                        cout << "b. Go RIGHT →" << endl;
                        mode = 9;
                    }
                    else{
                        cout << "b. Go LEFT ←" << endl;
                        mode = 10;
                        if(now->right != 0){
                            cout << "c. Go RIGHT →" << endl;
                            mode = 11;
                        }
                    }
                }
                else{ 
                    cout << "b. Go DOWN ↓" << endl;
                    mode = 12;
                    if(now->left == 0){
                        cout << "c. Go RIGHT →" << endl;
                        mode = 13;
                    }
                    else{
                        cout << "c. Go LEFT ←" << endl;
                        mode = 14;
                        if(now->right != 0){
                            cout << "d. Go RIGHT →" << endl;
                            mode = 15;
                        }
                    }
                }
            }
            cin >> op;
            do{
                out = true;
                switch (mode) //movement
                {
                case 1:
                    if(op == 'a'){
                        previous = current;
                        current = current->right;
                    }
                    break;
                case 2:
                    if(op == 'a'){
                        previous = current;
                        current = current->left;
                    }
                    break;
                case 3:
                    if(op == 'a'){
                        previous = current;
                        current = current->left;
                    }
                    else if(op == 'b'){
                        previous = current;
                        current = current->right;
                    }
                    break;
                case 4:
                    if(op == 'a'){
                        previous = current;
                        current = current->down;
                    }
                    break;
                case 5:    
                    if(op == 'a'){
                        previous = current;
                        current = current->down;
                    }
                    else if(op == 'b'){
                        previous = current;
                        current = current->right;
                    }
                    break;
                case 6:
                    if(op == 'a'){
                        previous = current;
                        current = current->down;
                    }
                    else if(op == 'b'){
                        previous = current;
                        current = current->left;
                    }
                    break;
                case 7:
                    if(op == 'a'){
                        previous = current;
                        current = current->down;
                    }
                    else if(op == 'b'){
                        previous = current;
                        current = current->left;
                    }
                    else if(op == 'c'){
                        previous = current;
                        current = current->right;
                    }
                    break;
                case 8:
                    if(op == 'a'){
                        previous = current;
                        current = current->up;
                    }
                    break;
                case 9:
                    if(op == 'a'){
                        previous = current;
                        current = current->up;
                    }
                    else if(op == 'b'){
                        previous = current;
                        current = current->right;
                    }
                    break;
                case 10:
                    if(op == 'a'){
                        previous = current;
                        current = current->up;
                    }
                    else if(op == 'b'){
                        previous = current;
                        current = current->left;
                    }
                    break;
                case 11:
                    if(op == 'a'){
                        previous = current;
                        current = current->up;
                    }
                    else if(op == 'b'){
                        previous = current;
                        current = current->left;
                    }
                    else if(op == 'c'){
                        previous = current;
                        current = current->right;
                    }
                    break;
                case 12:
                    if(op == 'a'){
                        previous = current;
                        current = current->up;
                    }
                    else if(op == 'b'){
                        previous = current;
                        current = current->down;
                    }
                    break;
                case 13:
                    if(op == 'a'){
                        previous = current;
                        current = current->up;
                    }
                    else if(op == 'b'){
                        previous = current;
                        current = current->down;
                    }
                    else if(op == 'c'){
                        previous = current;
                        current = current->right;
                    }
                    break;
                case 14:
                    if(op == 'a'){
                        previous = current;
                        current = current->up;
                    }
                    else if(op == 'b'){
                        previous = current;
                        current = current->down;
                    }
                    else if(op == 'c'){
                        previous = current;
                        current = current->left;
                    }
                    break;
                case 15:
                    if(op == 'a'){
                        previous = current;
                        current = current->up;
                    }
                    else if(op == 'b'){
                        previous = current;
                        current = current->down;
                    }
                    else if(op == 'c'){
                        previous = current;
                        current = current->left;
                    }
                    else if(op == 'd'){
                        previous = current;
                        current = current->right;
                    }
                    break;
                default:
                    cout << "input error! please input your move again!" << endl;
                    out = false;
                }
            }while(!out);
        }
        void print_status(){
            cout << endl;
            cout << "-----------------------------" << endl;
            cout << "** Status **" << endl;
            cout << " Name: " << name << endl;
            cout << "-----------------------------" << endl;
            cout << "-- Health: " << hp << "/" << hpMAX << endl;
            cout << "-- Attact: " << attack << endl;
            cout << "-- Defense: " << defense << endl;
            cout << "-- Money: $" << money << endl;
            cout << "-----------------------------" << endl;
            cout << endl;
        }
        void get_record(){
            int num1, num2;
            string myText;
            ifstream myfile ("record.txt");
            if(myfile.is_open()){
                myfile >> hp >> hpMAX >> attack >> defense >> money;
                myfile >> num1 >> num2;
                switch (num1)
                {
                case 1:
                    current = one;
                    break;
                case 2:
                    current = two;
                    break;
                case 3:
                    current = thr;
                    break;
                case 4:
                    current = fou;
                    break;
                case 5:
                    current = fiv;
                    break;
                case 6:
                    current = six;
                    break;
                case 7:
                    current = sev;
                    break;
                case 8:
                    current = eig;
                    break;
                case 9:
                    current = nin;
                    break;
                }
                switch (num2)
                {
                case 2:
                    previous = two;
                    break;
                case 3:
                    previous = thr;
                    break;
                case 4:
                    previous = fou;
                    break;
                case 5:
                    previous = fiv;
                    break;
                case 6:
                    previous = six;
                    break;
                case 7:
                    previous = sev;
                    break;
                case 8:
                    previous = eig;
                    break;
                case 9:
                    previous = nin;
                    break;
                default:
                    previous = one;
                    break;
                }
                myfile >> monster1_dead >> p1->NPChp >> p1->NPCattack >> p1->NPCdefense;
                myfile >> monster2_dead >> p2->NPChp >> p2->NPCattack >> p2->NPCdefense;
                myfile >> boss_dead >> boss1->NPChp >> boss1->NPCattack >> boss1->NPCdefense;
                myfile >> has_key >> box_opened;
                myfile >> hp_water;
            }
            else {
                cout << "*** No saved record before!!! ***" << endl;
                cout << "*** New game has created! ***" << endl;
                cout << endl;
            }
        } 
        void save_record(){
            ofstream myfile ("record.txt");
            if (myfile.is_open())
            {
                myfile << hp << " " << hpMAX << " " << attack << " " << defense << " " << money << endl;
                myfile << current->room_num << " "<< previous->room_num << endl;
                myfile << monster1_dead << " " << p1->NPChp << " " << p1->NPCattack << " " << p1->NPCdefense << endl;
                myfile << monster2_dead << " " << p2->NPChp << " " << p2->NPCattack << " " << p2->NPCdefense << endl;
                myfile << boss_dead << " " << boss1->NPChp << " " << boss1->NPCattack << " " << boss1->NPCdefense << endl;
                myfile << has_key << " " << box_opened << endl;
                myfile << hp_water << endl;
                myfile.close();
            }
            else cout << "*** Unable to save record........try it LATER! ***" << endl;
        }
        void judge_roomtype(){
            char op;
            char challenge_result;
            cout << endl;
            cout << "------------------------" << endl;
            cout << "You're in Room No."<< current->room_num  << " now!" << endl;
            cout << "------------------------" << endl;
            cout << endl;
            switch (current->room_num)
            {
            case 1:{
                cout << "*** This is the starting point! ***" << endl;
                cout << endl;
                break;
            }
            case 2:{
                cout << "@@ Welcome to the Shop! @@" << endl;
                cout << "@@ You can buy some items here~ @@"<< endl;
                cout << endl;
                cout << "@@ Do you want to enter the shop? @@"<< endl;
                cout << "a. Yes!" << endl;
                cout << "b. No!" << endl;
                cin >> op;
                cout << endl;
                if(op == 'a'){
                    shop();
                }
                break;
            }
            case 3:{
                if(!monster2_dead){
                    cout << "-------------------------------------" << endl;
                    cout << "There is a MONSTER in this dungeon!" << endl;
                    cout << "-------------------------------------" << endl;
                    cout << endl;
                    p2->get_status();
                    cout << "Kill it to UPGRADE yourself!" << endl;
                    cout << "-------------------------------------" << endl;
                    cout << endl;
                    op = p2->combat();
                    if (op == 'a'){
                        challenge_result = p2->challenge(hp, attack, defense, money);
                        if(challenge_result == 'r') {
                            current = previous;
                            cout << "*** Rereated! You have returned to Dungeon NO." << current->room_num << " ! ***" << endl;
                        }
                        else if(challenge_result == 'a'){
                            monster2_dead = true;
                            delete p2;
                        }
                    }
                    else if(op == 'b'){
                        current = previous;
                        cout << "*** Retreated! You have returned to Dungeon NO." << current->room_num << " ! ***" << endl;
                    }
                }
                else{
                    cout << "---------------" << endl;
                    cout << "Nothing here~" << endl;
                    cout << "---------------" << endl;
                    cout << endl;
                }
                break;
            }
            case 4:{
                if(!monster1_dead){
                    cout << "-------------------------------------" << endl;
                    cout << "There is a MONSTER in this dungeon!" << endl;
                    cout << "-------------------------------------" << endl;
                    cout << endl;
                    p1->get_status();
                    cout << "Kill it to UPGRADE yourself!" << endl;
                    cout << "-------------------------------------" << endl;
                    cout << endl;
                    op = p1->combat();
                    if (op == 'a'){
                        challenge_result = p1->challenge(hp, attack, defense, money);
                        if(challenge_result == 'r') {
                            current = previous;
                            cout << "*** Retreated! You have returned to Dungeon NO." << current->room_num << " ! ***" << endl;
                        }
                        else if(challenge_result == 'a'){
                            monster1_dead = true;
                            delete p1;
                        }
                    }
                    else if (op == 'b'){
                        current = previous;
                        cout << "*** Retreated! You have returned to Dungeon NO." << current->room_num << " ! ***" << endl;
                    }
                }
                else{
                    cout << "---------------" << endl;
                    cout << "Nothing here~" << endl;
                    cout << "---------------" << endl;
                    cout << endl;
                }
                break;
            }
            case 5:{
                if(!box_opened){
                    cout << "--------------------------------------------" << endl;
                    cout << " There is a Treasure box in this dungeon! " << endl;
                    cout << "--------------------------------------------" << endl;
                    cout << endl;
                    cout << "Do you want to open it?" << endl;
                    cout << "a. Yes!" << endl;
                    cout << "b. No!" << endl;
                    cin >> op;
                    cout << endl;
                    if(op == 'a'){
                        if(has_key){
                            box_opened = true;
                            cout << "*** Congratulations! The box has opened! ***" << endl;

                            attack+=100;
                            cout << "You got a ** Mighty Sword! **, the attack power has +100 !!" << endl;
                            cout << "You can check your current status later~" << endl;
                            cout << endl;
                        }
                        else{
                            cout << "*** Opps! The box is locked! ***" << endl;
                            cout << "Go find the key in other dungeons!" << endl;
                            cout << endl;
                        }
                    }
                }
                else{
                    cout << "--------------------------------------------" << endl;
                    cout << " The box has been opened! Nothing here now~ " << endl;
                    cout << "--------------------------------------------" << endl;
                    cout << endl;
                }
                break;
            }
            case 6:{
                if(hp_water > 0){
                    cout << "-----------------------------------------------" << endl;
                    cout << " There are "<< hp_water <<" HP Water in the Dungeon! " << endl;
                    cout << " Drink a HP Water to recover 50 HP! " << endl;
                    cout << "!!! Notice: HP after healed <= Your maximun HP !!!" << endl;
                    cout << "-----------------------------------------------" << endl;
                    cout << endl;
                    cout << "Do you want to pick it up and drink it?" << endl;
                    cout << "a. Yes!" << endl;
                    cout << "b. No!" << endl;
                    cin >> op;
                    cout << endl;
                    if(op == 'a'){
                        if(hp == hpMAX){
                            cout << "*** You CANNOT pick up the HP water! Because your HP has achived maximun value! ***" << endl;
                            cout << "*** Go fight the Monsters and the Boss! ***" << endl;
                            cout << endl;  
                        }
                        else{
                            hp += 50;
                            if(hp >= hpMAX){
                                hp = hpMAX;
                            }
                            cout << "*** You are cured!, your HP is "<< hp << " now! ***" << endl;
                            cout << endl;
                            hp_water -=1 ;
                        }
                    }
                }
                else{
                    cout << "---------------" << endl;
                    cout << "Nothing here~" << endl;
                    cout << "---------------" << endl;
                    cout << endl;
                }
                break;
            }
            case 7:{
                cout << "---------------------------------------------" << endl;
                cout << "     There is a Casino in this dungeon! " << endl;
                cout << "  If you win, you will gain some rewards~" << endl;
                cout << " If you loss, you will have some punishments~" << endl;
                cout << "---------------------------------------------" << endl;
                cout << endl;
                cout << "Do you want to enter the Casino?" << endl;
                cout << "a. Yes!" << endl;
                cout << "b. No!" << endl;
                cin >> op;
                cout << endl;
                if (op == 'a'){
                    game();
                }
                break;
            }
            case 8:{
                if(!has_key){
                    cout << "---------------------------------" << endl;
                    cout << " There is a key in this dungeon! " << endl;
                    cout << "---------------------------------" << endl;
                    cout << endl;
                    cout << "Do you want to pick it up?" << endl;
                    cout << "a. Yes!" << endl;
                    cout << "b. No!" << endl;
                    cin >> op;
                    cout << endl;
                    if (op == 'a'){
                        has_key = true;
                        cout << "*** Picked! ***" << endl;
                        cout << endl;
                    }
                }
                else{
                    cout << "---------------" << endl;
                    cout << "Nothing here~" << endl;
                    cout << "---------------" << endl;
                    cout << endl;
                }
                break;
            }
            case 9:{
                if(!boss_dead){
                    cout << "------------------------------" << endl;
                    cout << " The BOSS is in this dungeon! " << endl;
                    cout << "------------------------------" << endl;
                    cout << endl;
                    boss1->get_status();
                    cout << "Kill it to get out of the dungeon! " << endl;
                    cout << "----------------------------------" << endl;
                    cout << endl;
                    op = boss1->combat();
                    if (op == 'a'){
                        challenge_result = boss1->challenge(hp, attack, defense, money);
                        // cout << challenge_result << endl;
                        if(challenge_result == 'r') {
                            current = previous;
                            cout << "Retreated! You have returned to Dungeon NO." << current->room_num << " !" << endl;
                        }
                    }
                    else if(op == 'b'){
                        current = previous;
                        cout << "Retreated! You have returned to Dungeon NO." << current->room_num << " !" << endl;
                    }
                }    
                break;
            }    
            default:
                cout << "---------------" << endl;
                cout << "Nothing here~" << endl;
                cout << "---------------" << endl;
                cout << endl;
                break;
            }
        }
};

int main(){
    Dungeon dungeon;
    dungeon.welcome();
    dungeon.generate_room();
    dungeon.enter_name();
    dungeon.record_or_not();
    while(true){
        dungeon.judge_roomtype();
        dungeon.menu();
    }
    return 0;
}