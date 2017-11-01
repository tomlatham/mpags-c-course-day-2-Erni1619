#ifndef MPAGSCIPHER_CIPHER_HPP
#define MPAGSCIPHER_CIPHER_HPP

#include <string>

//int chartoint (const char in_char);
//char inttochar (const int in_int);
//std::string cipher (const std::string& in_string, const int key);
//std::string decipher (const std::string& in_string, const int key);

// TEL - the slides asked that a single function be implemented with the signature:
std::string runCaesarCipher( const std::string& in_string, const size_t key, const bool encrypt );

#endif
