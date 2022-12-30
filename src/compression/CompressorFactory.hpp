#ifndef COMPRESSORFACTORY_HPP
#define COMPRESSORFACTORY_HPP

#include "compression/Compressor.hpp"
#include <string>

namespace compression {

/**
 * @brief Singleton factory class for creating instances of compression algorithms.
 */
class CompressorFactory
{
private:
    CompressorFactory();

public:
    /**
     * @brief Returns the instance of the factory.
     * @return Instance of the factory.
     */
    static CompressorFactory &getCompressorFactory();

    /**
     * @brief Creates Compressor of a given type.
     * @param type Type of the compressor.
     * @return Created compressor.
     */
    static Compressor &createCompressor(std::string type);
};
} // namespace compression

#endif // COMPRESSORFACTORY_HPP
