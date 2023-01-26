#include "LZWCompressor.hpp"

void compression_implementations::LZWCompressor::compress(std::istream &in, std::ostream &out)
{
    if (!in.good()) {
        throw std::runtime_error("Error reading input data!");
    }

    if (!out.good()) {
        throw std::runtime_error("Error in output stream!");
    }

    // Initialize dictionary
    std::map<std::vector<char>, CodeType> dictionary;
    this->resetDictionaryContents(dictionary);

    std::vector<char> currentString;
    char currentChar;

    // While can read a char(byte) from the input stream
    while (in.get(currentChar)) {
        // To prevent issues when dictionary is full reset it to the initial 256 values
        if (dictionary.size() == this->dictionaryMaxSize)
            this->resetDictionaryContents(dictionary);

        currentString.push_back(currentChar);

        // If string is not present in the dictionary add it and output previous string code
        if (dictionary.count(currentString) == 0) {
            // Separate to avoid undefined behaviour when reading and modifying the dictionary at the same time.
            const CodeType dictionarySize = dictionary.size();

            dictionary[currentString] = dictionarySize;
            currentString.pop_back();
            out.write(reinterpret_cast<const char *>(&dictionary.at(currentString)),
                      sizeof(CodeType));
            currentString = {currentChar};
        }
    }

    if (!currentString.empty())
        out.write(reinterpret_cast<const char *>(&dictionary.at(currentString)), sizeof(CodeType));
}

void compression_implementations::LZWCompressor::resetDictionaryContents(
    std::map<std::vector<char>, CodeType> &dictionary)
{
    dictionary.clear();

    const long int minc = std::numeric_limits<char>::min();
    const long int maxc = std::numeric_limits<char>::max();

    for (long int c = minc; c <= maxc; ++c) {
        // Separate to avoid undefined behaviour when reading and modifying the dictionary at the same time.
        const CodeType dictionarySize = dictionary.size();

        dictionary[{static_cast<char>(c)}] = dictionarySize;
    }
}
