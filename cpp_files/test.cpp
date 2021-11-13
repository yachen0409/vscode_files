#include <iostream>
using namespace std;

#include <cryptopp/aes.h>
using namespace CryptoPP;

int main()
{
       cout << "hello crypto++" << endl;
       cout << "Aes block size is " << AES::BLOCKSIZE << endl;

 return 0;
}