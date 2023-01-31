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

void compression_implementations::LZWCompressor::resetDictionaryContents(
    std::vector<std::vector<char>> &dictionary)
{
    dictionary.clear();
    dictionary.reserve(this->dictionaryMaxSize);

    const long int minc = std::numeric_limits<char>::min();
    const long int maxc = std::numeric_limits<char>::max();

    for (long int c = minc; c <= maxc; ++c)
        dictionary.push_back({static_cast<char>(c)});
}

/**
 * @brief Helper operator which adds a char to a char vector.
 * @param vc Vector to add to.
 * @param c Char to be added.
 * @return Resulting vector from appending c to vc
 */
std::vector<char> &operator+(std::vector<char> &vc, char c)
{
    vc.push_back(c);
    return vc;
}

void compression_implementations::LZWCompressor::decompress(std::istream &in,
                                                            unsigned int bytesToRead,
                                                            std::ostream &out)
{
    if (!in.good()) {
        throw std::runtime_error("Error reading input data!");
    }

    if (!out.good()) {
        throw std::runtime_error("Error in output stream!");
    }

    // Initialize dictionary
    std::vector<std::vector<char>> dictionary;
    this->resetDictionaryContents(dictionary);

    std::vector<char> currentString;
    CodeType currentKey;
    unsigned int bytesRead = sizeof(CodeType);

    while (in.read(reinterpret_cast<char *>(&currentKey), sizeof(CodeType))
           && bytesRead <= bytesToRead) {
        bytesRead += sizeof(CodeType);
        // Reset the dictionary codes if full
        if (dictionary.size() == this->dictionaryMaxSize)
            this->resetDictionaryContents(dictionary);

        if (currentKey > dictionary.size())
            throw std::runtime_error("Invalid compressed code");

        if (currentKey == dictionary.size())
            dictionary.push_back(currentString + currentString.front());
        else if (!currentString.empty())
            dictionary.push_back(currentString + dictionary.at(currentKey).front());

        out.write(&dictionary.at(currentKey).front(), dictionary.at(currentKey).size());
        currentString = dictionary.at(currentKey);
    }
}
