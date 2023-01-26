#ifndef LZWCOMPRESSOR_HPP
#define LZWCOMPRESSOR_HPP

#include "compression/Compressor.hpp"
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace compression_implementations {
class LZWCompressor : public compression::Compressor
{
public:
    LZWCompressor() = default;

    /**
     *  Type in which the codes will be stored.
     */
    using CodeType = std::uint16_t;

    // Compressor interface
public:
    void compress(std::istream &in, std::ostream &out) override;
    void decompress(std::istream &in, unsigned int bytesToRead, std::ostream &out) override;

private:
    const CodeType dictionaryMaxSize{std::numeric_limits<CodeType>::max()};

    /**
     * @brief Sets dictionary contents single char strings and their respective codes (0 - 255).
     * @param dictionary Dictionary to act upon.
     */
    void resetDictionaryContents(std::map<std::vector<char>, CodeType> &dictionary);

    /**
     * @brief Sets the dictionary contents to the first 255 single char strings.
     * @param dictionary Dictionary to act upon.
     */
    void resetDictionaryContents(std::vector<std::vector<char>> &dictionary);
};

} // namespace compression_implementations

#endif // LZWCOMPRESSOR_HPP
