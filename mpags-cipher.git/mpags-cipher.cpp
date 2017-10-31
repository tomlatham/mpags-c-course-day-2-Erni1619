// Standard Library includes
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//LOCAL IMPORTS
#include "TransformChar.hpp" //chars to alphabetic upper case ( i.e. a-->A 1-->ONE)
#include "ProcessComandLine.hpp" //process the different flags accepted by the executable
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
  int key{0};

  //flag for errors in arguments
  bool good{true};

  // Process command line arguments - ignore zeroth element, as we know this to
  // be the program name and don't need to worry about it
    
  good=processCommandLine(cmdLineArgs,helpRequested,versionRequested,inputFile,outputFile,iscipher,isdecipher, key);
  if(!good){return 0;}
  

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
    if(!in_file.good()){return 0;}//check errors on opening file
    while(in_file >> inputChar)
    {
      inputText += transformChar(inputChar);//input text to upper case
    }
    in_file.close();
  }

  //ciphering or deciphering
  if(iscipher){
  inputText=cipher(inputText,key);
    }
  else if(isdecipher){
  inputText=decipher(inputText,key);    
    }

  //check if output file flag active
	//unactive --> Terminal output
	//active   --> Output to file
  if (!outputFile.empty()) {//ACTIVE
    std::ofstream out_file {outputFile};
    if(!out_file.good()){return 0;}//check errors on opening/creating file
    out_file << inputText;
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



