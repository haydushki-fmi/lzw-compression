#ifndef DECOMPRESSORFACTORY_HPP
#define DECOMPRESSORFACTORY_HPP

#include "compression/Decompressor.hpp"
#include <string>

namespace compression {

/**
 * @brief Singleton factory class for creating instances of decompression algorithms.
 */
class DecompressorFactory
{
private:
    DecompressorFactory();

public:
    /**
     * @brief Returns the instance of the factory.
     * @return Instance of the factory.
     */
    static DecompressorFactory &getDecompressorFactory();

    /**
     * @brief Creates Dompressor of a given type.
     * @param type Type of the decompressor.
     * @return Created decompressor.
     */
    static Decompressor &createDecompressor(std::string type);
};
} // namespace compression

#endif // DECOMPRESSORFACTORY_HPP
