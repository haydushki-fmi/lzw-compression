add_library(compression STATIC)

target_sources(
        compression
        PRIVATE
        Compressor.hpp
        implementations/LZWCompressor.cpp
        implementations/LZWCompressor.hpp
)
