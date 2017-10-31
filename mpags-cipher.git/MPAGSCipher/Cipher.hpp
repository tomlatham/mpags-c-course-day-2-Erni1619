#ifndef MPAGSCIPHER_CIPHER_HPP
#define MPAGSCIPHER_CIPHER_HPP

#include <string>

int chartoint (const char in_char);
char inttochar (const int in_int);
std::string cipher (std::string in_string, const int key);
std::string decipher (std::string in_string, const int key);

#endif
