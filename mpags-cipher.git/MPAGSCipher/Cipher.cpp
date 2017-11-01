#include "Cipher.hpp"
#include <vector>

/*
 The problem with these functions is that they rely on the ASCII values.

int chartoint (const char in_char){
    
    return (int) in_char-65; //-65 sets 'A' to 0 in ascii so the module can be computed with no problems
    

}
char inttochar (const int in_int){
    return (char) in_int+65;
    
}
*/

std::string runCaesarCipher (const std::string& in_string, const size_t key, const bool encrypt){

    // Create the output string
    std::string out_string {""};

    // Create the alphabet container
    const std::vector<char> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    const size_t alphabetSize = alphabet.size();

    // Make sure that the key is in the range 0 - 25
    const size_t truncatedKey { key % alphabetSize };

    // Loop over the input text
    for(const char& in_char : in_string) {
	// For each character in the input text, find the corresponding position in
	// the alphabet by using an indexed loop over the alphabet container
	for ( size_t i{0}; i < alphabetSize; ++i ) {
	    if ( in_char == alphabet[i] ) {
		// Apply the appropriate shift (depending on whether we're encrypting
		// or decrypting) and determine the new character
		// Can then break out of the loop over the alphabet
		if ( encrypt ) {
		    out_string += alphabet[ (i + truncatedKey) % alphabetSize ];
		} else {
		    out_string += alphabet[ (i + alphabetSize - truncatedKey) % alphabetSize ];
		}
		break;
	    }
	}
    }    

    return out_string;
}

/*
std::string decipher (const std::string& in_string, const int key){
    
    std::string out_string {""};
    for(char& in_char : in_string) {
        out_string += inttochar(((chartoint(in_char)-key)+26)%26);
    }    

    return out_string;
}
*/

