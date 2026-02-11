#include "io/genbank_reader.h"
#include <fstream>
#include <sstream>
#include <string>

namespace pso {
namespace io {

std::string load_sequence_from_genbank(const char* filepath) {
    std::ifstream fin(filepath);
    if (!fin)
        return std::string();

    std::ostringstream seq;
    std::string line;
    bool in_origin = false;

    while (std::getline(fin, line)) {
        if (line.empty())
            continue;
        if (line.find("ORIGIN") != std::string::npos) {
            in_origin = true;
            continue;
        }
        if (!in_origin)
            continue;
        if (line.find("//") != std::string::npos)
            break;

        std::istringstream sin(line);
        int line_num;
        sin >> line_num;  // skip line number
        std::string token;
        while (sin >> token)
            seq << token;
    }

    return seq.str();
}

}  // namespace io
}  // namespace pso
