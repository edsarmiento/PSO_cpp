#pragma once

#include <string>

namespace pso {
namespace io {

/**
 * Load sequence from a file in NCBI GenBank-like format.
 * Reads from the line containing "ORIGIN" until "//".
 * Returns the concatenated sequence string, or empty string on error.
 */
std::string load_sequence_from_genbank(const char* filepath);

}  // namespace io
}  // namespace pso
