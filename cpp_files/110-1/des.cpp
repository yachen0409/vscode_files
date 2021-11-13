#include<bits/stdc++.h>
using namespace std;
string hex2bin(string s)
{
	// hexadecimal to binary conversion
	unordered_map<char, string> mp;
	mp['0'] = "0000";
	mp['1'] = "0001";
	mp['2'] = "0010";
	mp['3'] = "0011";
	mp['4'] = "0100";
	mp['5'] = "0101";
	mp['6'] = "0110";
	mp['7'] = "0111";
	mp['8'] = "1000";
	mp['9'] = "1001";
	mp['A'] = "1010";
	mp['B'] = "1011";
	mp['C'] = "1100";
	mp['D'] = "1101";
	mp['E'] = "1110";
	mp['F'] = "1111";
	string bin = "";
	for (int i = 0; i < s.size(); i++) {
		bin += mp[s[i]];
	}
	return bin;
}
string bin2hex(string s){
    unordered_map<string, string> table;
    table["0000"] = "0";
    table["0001"] = "1";
    table["0010"] = "2";
    table["0011"] = "3";
    table["0100"] = "4";
    table["0101"] = "5";
    table["0110"] = "6";
    table["0111"] = "7";
    table["1000"] = "8";
    table["1001"] = "9";
    table["1010"] = "A";
    table["1011"] = "B";
    table["1100"] = "C";
    table["1101"] = "D";
    table["1110"] = "E";
    table["1111"] = "F";
    string hex = "";
    for (int i = 0; i < s.length(); i += 4) {
        string ch = "";
        ch += s[i];
        ch += s[i + 1];
        ch += s[i + 2];
        ch += s[i + 3];
        hex += table[ch];
    }
    return hex;
}
string bin2ascii(string s){
    string bin = "";
    for(int i = 0; i < 8; i++){
        int temp1, temp2, temp3, temp4 = 0;
            temp1 = 128 * ((s[i*8])-48)+ 64 * (s[i*8+1]-48)+32 * (s[i*8+2]-48)+ 16*(s[i*8+3]-48)+8*(s[i*8+4]-48)+4*(s[i*8+5]-48)+2*(s[i*8+6]-48)+(s[i*8+7]-48);
            bin += char(temp1);
    }
    return bin;
}
string ascii2bin(string s){
    string bin = "";
    for (int i = 0; i < 8; i++){
        bitset<8> temp(s[i]); 
        bin += temp.to_string();
    }
    return bin;
}
string permute(string before, int* after, int size){    //permutation 
    string temp = "";
    for (int i = 0; i < size; i++) {
        temp += before[after[i] - 1];
    }
    return temp;
}
string xor_function(string a, string b){    //xor two string
    string temp = "";
    for (int i = 0; i < a.size(); i++) {
        temp += (a[i] ^ b[i])?"1":"0";
    }
    return temp;
}
string shift_left(string k, int shift_num){     //shift every round
    
    for (int i = 0; i < shift_num; i++) {
        string temp = "";
        for (int j = 1; j < 28; j++) {
            temp += k[j];
        }
        temp += k[0];
        k = temp;
    }
    return k;
}
string encrypt(string text, vector<string> roundkey_box)
{
    
	text = hex2bin(text);
	int initial_perm[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
							60, 52, 44, 36, 28, 20, 12, 4,
							62, 54, 46, 38, 30, 22, 14, 6,
							64, 56, 48, 40, 32, 24, 16, 8,
							57, 49, 41, 33, 25, 17, 9, 1,
							59, 51, 43, 35, 27, 19, 11, 3,
							61, 53, 45, 37, 29, 21, 13, 5,
							63, 55, 47, 39, 31, 23, 15, 7 };
	text = permute(text, initial_perm, sizeof(initial_perm)/sizeof(*initial_perm));

	string left = text.substr(0, 32);       // Split
	string right = text.substr(32, 32);

	int exp_d[48] = { 32, 1, 2, 3, 4, 5, 4, 5,      // Expansion D-box
					6, 7, 8, 9, 8, 9, 10, 11,
					12, 13, 12, 13, 14, 15, 16, 17,
					16, 17, 18, 19, 20, 21, 20, 21,
					22, 23, 24, 25, 24, 25, 26, 27,
					28, 29, 28, 29, 30, 31, 32, 1 };
	int s[8][4][16] = { { 4, 14, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,     // S-box Table
						0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 8, 3,
						4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
						13, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 15 },
						{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
						3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
						0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
						13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },

						{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
						13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
						13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
						1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
						{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
						13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
						10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
						3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
						{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
						14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
						4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
						11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
						{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
						10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
						9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
						4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
						{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
						13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
						1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
						6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
						{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
						1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
						7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
						2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };
	int per[32] = { 16, 7, 20, 21,  // 32 to 48
					29, 12, 28, 17,
					1, 15, 23, 26,
					5, 18, 31, 10,
					2, 8, 24, 14,
					32, 27, 3, 9,
					19, 13, 30, 6,
					22, 11, 4, 25 };

	for (int i = 0; i < 16; i++){
		string right_expanded = permute(right, exp_d, sizeof(exp_d)/sizeof(*exp_d));    //expand 32 to 48
		string x = xor_function(roundkey_box[i], right_expanded);   		// XOR roundkey_box[i] and right_expanded

		string op = "";     		// S-boxes
		for (int i = 0; i < 8; i++) {
			int row = 2 * int(x[i * 6] - '0') + int(x[i * 6 + 5] - '0');
			int col = 8 * int(x[i * 6 + 1] - '0') + 4 * int(x[i * 6 + 2] - '0') + 2 * int(x[i * 6 + 3] - '0') + int(x[i * 6 + 4] - '0');
			int value = s[i][row][col];
			op += char(value / 8 + '0');
			value = value % 8;
			op += char(value / 4 + '0');
			value = value % 4;
			op += char(value / 2 + '0');
			value = value % 2;
			op += char(value + '0');
		}

		op = permute(op, per, sizeof(per)/sizeof(*per));    // compress 48 to 32
		x = xor_function(op, left);     // XOR left and op

        left = x;               // do the switch
		if (i != 15) {
			swap(left, right);
		}
	}
	string combine = left + right;

	int final_perm[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
						39, 7, 47, 15, 55, 23, 63, 31,
						38, 6, 46, 14, 54, 22, 62, 30,
						37, 5, 45, 13, 53, 21, 61, 29,
						36, 4, 44, 12, 52, 20, 60, 28,
						35, 3, 43, 11, 51, 19, 59, 27,
						34, 2, 42, 10, 50, 18, 58, 26,
						33, 1, 41, 9, 49, 17, 57, 25 };
	string cipher = bin2hex(permute(combine, final_perm, sizeof(final_perm)/sizeof(*final_perm)));  //decrypt in hex
	return cipher;
}
int main(){
	string text, key;
    ifstream input;
    ofstream output;
    input.open("DES-Key-Ciphertext.txt");
    output.open("des-out.txt");
	// while(input >> key >> text){
        key = "37198391";
        text = "2BADF07ADD648074";
        key = ascii2bin(key);   //deal with key
        int keyp[56] = { 57, 49, 41, 33, 25, 17, 9,     // Parity bit drop table
                        1, 58, 50, 42, 34, 26, 18,
                        10, 2, 59, 51, 43, 35, 27,
                        19, 11, 3, 60, 52, 44, 36,
                        63, 55, 47, 39, 31, 23, 15,
                        7, 62, 54, 46, 38, 30, 22,
                        14, 6, 61, 53, 45, 37, 29,
                        21, 13, 5, 28, 20, 12, 4 };
        key = permute(key, keyp, sizeof(keyp)/sizeof(*keyp)); // 64 to 56

        int shift_table[16] = { 1, 1, 2, 2,     // Number of bit shifts
                                2, 2, 2, 2,
                                1, 2, 2, 2,
                                2, 2, 2, 1 };

        int key_comp[48] = { 14, 17, 11, 24, 1, 5,      //56 to 48
                            3, 28, 15, 6, 21, 10,
                            23, 19, 12, 4, 26, 8,
                            16, 7, 27, 20, 13, 2,
                            41, 52, 31, 37, 47, 55,
                            30, 40, 51, 45, 33, 48,
                            44, 49, 39, 56, 34, 53,
                            46, 42, 50, 36, 29, 32 };

        string left = key.substr(0, 28);        	// splitting
        string right = key.substr(28, 28);

        vector<string> roundkey_box; 
        for (int i = 0; i < 16; i++) {
            left = shift_left(left, shift_table[i]);        // Shifting
            right = shift_left(right, shift_table[i]);

            string combine = left + right;

            string RoundKey = permute(combine, key_comp, sizeof(key_comp)/sizeof(*key_comp));
            roundkey_box.push_back(RoundKey);
        }
        // string cipher = encrypt(text, roundkey_box);        //encryption
        // cout << "\nCipher Text: " << cipher << endl;

        reverse(roundkey_box.begin(), roundkey_box.end());  //decreypt
        string decrypt_text = encrypt(text, roundkey_box);
        // cout << decrypt_text << endl;

        decrypt_text = bin2ascii(hex2bin(decrypt_text));
        cout << "\nPlain Text: " << decrypt_text << endl;        //in ascii
        output << decrypt_text << "\n" ;
    // }
    input.close();
    output.close();
    return 0;
}
