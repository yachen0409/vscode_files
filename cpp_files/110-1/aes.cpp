#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
using namespace std;
using namespace CryptoPP;

string encrypt_cfb(const string text, const byte key[], const byte iv[]) {
    string cipher, hex_cipher;
    const AlgorithmParameters parameter = MakeParameters(Name::FeedbackSize(), 4)(Name::IV(), ConstByteArrayParameter(iv, 16));

    CFB_Mode<AES>::Encryption ecfb;
    ecfb.SetKey(key, 16, parameter);

    StringSource en(text, true, new StreamTransformationFilter(ecfb, new StringSink(cipher)));
    StringSource s2(cipher, true, new HexEncoder(new StringSink(hex_cipher)));

    return hex_cipher;
}
string encrypt_cbc(const string text, const byte key[], const byte iv[], string padding) {
    string cipher, hex_cipher;
    CBC_Mode<AES>::Encryption ecbc;
    ecbc.SetKeyWithIV(key, 16, iv);

    if (padding == "zero") {
        StringSource en(text, true, new StreamTransformationFilter(ecbc, new StringSink(cipher), StreamTransformationFilter::ZEROS_PADDING));
    }
    else {
        StringSource en(text, true, new StreamTransformationFilter(ecbc, new StringSink(cipher), StreamTransformationFilter::PKCS_PADDING));
    }
    StringSource s2(cipher, true, new HexEncoder(new StringSink(hex_cipher)));

    return hex_cipher;
}
string encrypt_ecb(const string text, const byte key[]) {
    string cipher, hex_cipher;
    ECB_Mode<AES>::Encryption eecb;
    eecb.SetKey(key, 16);

    StringSource en(text, true, new StreamTransformationFilter(eecb, new StringSink(cipher), StreamTransformationFilter::PKCS_PADDING));
    StringSource s2(cipher, true, new HexEncoder(new StringSink(hex_cipher)));
    return hex_cipher;
}
int main() {
    ofstream out("out.txt");
    string text = "AES is the block cipher standard.";
    byte key[17] = "1234567890ABCDEF";
    byte iv0[17] = "0000000000000000";
    byte iv9[17] = "9999999999999999";

    string after_cfb, after_cbc0, after_cbc9, after_ecb;
    after_cfb = encrypt_cfb(text, key, iv0);
    after_cbc0 = encrypt_cbc(text, key, iv0, "zero");
    after_cbc9 = encrypt_cbc(text, key, iv9, "pcks");
    after_ecb = encrypt_ecb(text, key);
    out << after_cfb << '\n';
    out << after_cbc0 << '\n';
    out << after_cbc9 << '\n';
    out << after_ecb << '\n';
}
