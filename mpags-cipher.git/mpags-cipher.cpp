// Standard Library includes
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//LOCAL IMPORTS
#include "TransformChar.hpp" //chars to alphabetic upper case ( i.e. a-->A 1-->ONE)
#include "ProcessCommandLine.hpp" //process the different flags accepted by the executable
#include "Cipher.hpp" //cipher and decipher using a given key (caesar algorithm)


//MAIN 
int main(int argc, char* argv[])
{
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

  
  // Options that might be set by the command-line arguments
  bool helpRequested {false};
  bool versionRequested {false};
  std::string inputFile {""};
  std::string outputFile {""};
  bool iscipher {false};
  bool isdecipher {false};
  size_t key{0};

  //flag for errors in arguments
  bool good{true};

  // Process command line arguments - ignore zeroth element, as we know this to
  // be the program name and don't need to worry about it
    
  good=processCommandLine(cmdLineArgs,helpRequested,versionRequested,inputFile,outputFile,iscipher,isdecipher, key);
  if(!good){
    std::cerr << "[error] problem processing command line arguments" << std::endl;
    return 1;
  }
  
  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help         Print this help message and exit\n\n"
      << "  --version         Print version information\n\n"
      << "  -i FILE           Read text to be processed from FILE\n"
      << "                    Stdin will be used if not supplied\n\n"
      << "  -o FILE           Write processed text to FILE\n"
      << "                    Stdout will be used if not supplied\n\n"
      << "  -c|--cipher KEY   cipher a string using the caesar algorithm using the given KEY\n"
      << "  -d|--decipher KEY decipher a string using the caesar algorithm using the given KEy\n";
    // Help requires no further action, so return from main
    // with 0 used to indicate success
    return 0;
  }

  // Handle version, if requested
  // Like help, requires no further action,
  // so return from main with zero to indicate success
  if (versionRequested) {
    std::cout << "0.1.0" << std::endl;
    return 0;
  }

  // Check that we received only one of the cipher/decipher options
  if (iscipher && isdecipher){
    std::cout << "[error] cannot select both cipher and decipher options!" <<std::endl;
    return 1;   
  }

  // Initialise variables for processing input text
  char inputChar {'x'};
  std::string inputText {""};

  //check if input file flag active
	//unactive --> Keyboard input activated
	//active   --> Input from file
  if(inputFile.empty()){//UNACTIVE
    while(std::cin >> inputChar)
    {
      inputText += transformChar(inputChar); //input text to upper case
    }
  }
  else{//ACTIVE
    std::ifstream in_file {inputFile};
    if(!in_file.good()){//check errors on opening file
      std::cerr << "[error] problem opening file " << inputFile << " for reading" << std::endl;
      return 1;
    }
    while(in_file >> inputChar)
    {
      inputText += transformChar(inputChar);//input text to upper case
    }
    in_file.close();
  }

  //ciphering or deciphering
  if(iscipher){
    inputText=runCaesarCipher(inputText,key,true);
  }
  else if(isdecipher){
    inputText=runCaesarCipher(inputText,key,false);    
  }

  //check if output file flag active
	//unactive --> Terminal output
	//active   --> Output to file
  if (!outputFile.empty()) {//ACTIVE
    std::ofstream out_file {outputFile};
    if(!out_file.good()){//check errors on opening/creating file
      std::cerr << "[error] problem opening file " << outputFile << " for writing" << std::endl;
      return 1;
    }
    out_file << inputText << std::endl;
    out_file.close();
  }
  else{//UNACTIVE
    std::cout << inputText << std::endl;
  }

  // END
  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}



