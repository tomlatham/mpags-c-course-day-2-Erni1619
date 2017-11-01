#ifndef MPAGSCIPHER_PROCESSCOMMANDLINE_HPP
#define MPAGSCIPHER_PROCESSCOMMANDLINE_HPP

#include <string>
#include <vector>

bool processCommandLine(const std::vector<std::string>& args,
                bool& helpRequested,   
                bool& versionRequested,
                std::string& inputFile,
                std::string& outputFile,
                bool& iscipher,
                bool& isdecipher,
                size_t& key);

#endif
