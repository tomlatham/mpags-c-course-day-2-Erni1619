#include "ProcessCommandLine.hpp"
#include <iostream>

bool processCommandLine(const std::vector<std::string>& args,
                bool& helpRequested,   
                bool& versionRequested,
                std::string& inputFile,
                std::string& outputFile,
                bool& iscipher,
                bool& isdecipher,
                size_t& key){
    //processes the arguments given
    typedef std::vector<std::string>::size_type size_type;
    const size_type nCmdLineArgs {args.size()};
    for (size_type i {1}; i < nCmdLineArgs; ++i) {

    if (args[i] == "-h" || args[i] == "--help") {
      helpRequested = true;
    }
    else if (args[i] == "--version") {
      versionRequested = true;
    }
    else if (args[i] == "-i") {
      // Handle input file option
      // Next element is filename unless -i is the last argument
      if (i == nCmdLineArgs-1) {
	std::cerr << "[error] -i requires a filename argument" << std::endl;
	// exit main with non-zero return to indicate failure
	return false;
      }
      else if(args[i+1][0]=='-'){
        std::cerr << "[error] -i requires a filename argument" << std::endl;
        return false;
      }
      else {
	// Got filename, so assign value and advance past it
	inputFile = args[i+1];
	++i;
      }
    }
    else if (args[i] == "-o") {
      // Handle output file option
      // Next element is filename unless -o is the last argument
      if (i == nCmdLineArgs-1) {
	std::cerr << "[error] -o requires a filename argument" << std::endl;
	// exit main with non-zero return to indicate failure
	return false;
      }
      else if(args[i+1][0]=='-'){
        std::cerr << "[error] -o requires a filename argument" << std::endl;
        return false;
      }
      else {
	// Got filename, so assign value and advance past it
	outputFile = args[i+1];
	++i;
      }
    }
    else if(args[i]=="-c" || args[i]=="-cipher"){
      if (i == nCmdLineArgs-1) {
        	std::cerr << "[error] -c requires a KEY argument" << std::endl;
        	// exit main with non-zero return to indicate failure
	 return false;
      }
      else if(args[i+1][0]=='-'){
        std::cerr << "[error] -c requires a KEY argument" << std::endl;
        return false;
      }
      
    else {
        iscipher=true;
	// TEL - could do some rudimentary checks that the string represents a positive integer, e.g. each character is a digit
        key=std::stoul(args[i+1]);
        ++i;
    }
    }
    else if(args[i]=="-d" || args[i]=="-decipher"){
      if (i == nCmdLineArgs-1) {
        	std::cerr << "[error] -d requires a KEY argument" << std::endl;
        	// exit main with non-zero return to indicate failure
	 return false;
      }
      else if(args[i+1][0]=='-'){
        std::cerr << "[error] -d requires a KEY argument" << std::endl;
        return false;
      }
      
    else {
        isdecipher=true;
	// TEL - could do some rudimentary checks that the string represents a positive integer, e.g. each character is a digit
        key=std::stoul(args[i+1]);
        ++i;
    }
    }
    
    else {
      // Have an unknown flag to output error message and return non-zero
      // exit status to indicate failure
      std::cerr << "[error] unknown argument '" << args[i] << "'\n";
      return false;
    }
  }

  return true;
}


