#ifndef Tools_h
#define Tools_h

#include <chrono>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Version.h"

using namespace std;

namespace Tools {
    string CurrentDateTime();
    uint32_t crc32_update(uint32_t crc, const uint8_t* data, size_t len);
    bool hex_to_u32(const std::string& hex, uint32_t& out);
}

#endif