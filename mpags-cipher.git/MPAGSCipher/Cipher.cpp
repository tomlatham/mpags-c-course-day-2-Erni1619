#include "Cipher.hpp"

int chartoint (const char in_char){
    
    return (int) in_char-65; //-65 sets 'A' to 0 in ascii so the module can be computed with no problems
    

}
char inttochar (const int in_int){
    return (char) in_int+65;
    
}

std::string cipher (std::string in_string, const int key){
    
    std::string out_string {""};
    for(char& in_char : in_string) {
        out_string += inttochar((chartoint(in_char)+key)%26);
    }    

    return out_string;
}

std::string decipher (std::string in_string, const int key){
    
    std::string out_string {""};
    for(char& in_char : in_string) {
        out_string += inttochar(((chartoint(in_char)-key)+26)%26);
    }    

    return out_string;
}

