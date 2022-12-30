#ifndef DECOMPRESSOR_HPP
#define DECOMPRESSOR_HPP

#include <ostream>

namespace compression {

/**
 * @brief Interface for decompression algorithm implementations.
 */
class Decompressor
{
public:
    /**
     * @brief Decompresses data read from input stream and writes it to the output stream.
     * @param in Input data.
     * @param bytesToRead Amount of bytes to read from input stream.
     * @param out Output for decoded data.
     */
    virtual void decompress(std::istream &in, unsigned int bytesToRead, std::ostream &out) = 0;
};
} // namespace compression

#endif // DECOMPRESSOR_HPP
