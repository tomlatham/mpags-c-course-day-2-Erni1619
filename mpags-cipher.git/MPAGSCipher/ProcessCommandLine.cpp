#include "ProcessComandLine.hpp"

bool processCommandLine(const std::vector<std::string>& args,
                bool& helpRequested,   
                bool& versionRequested,
                std::string& inputFile,
                std::string& outputFile,
                bool& iscipher,
                bool& isdecipher,
                int& key){
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
        key=atoi(args[i+1].c_str());
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
        key=atoi(args[i+1].c_str());
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
    return false;
  }

  // Handle version, if requested
  // Like help, requires no further action,
  // so return from main with zero to indicate success
  if (versionRequested) {
    std::cout << "0.1.0" << std::endl;
    return false;
  }
  if (iscipher && isdecipher){
    std::cout << "cannot select both cipher and decipher options!" <<std::endl;
    return false;   
}
  return true;
}


