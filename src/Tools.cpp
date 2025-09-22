#include "../include/Tools.h"

namespace Tools {
    string CurrentDateTime() {
        using namespace std::chrono;
        auto now = system_clock::now();
        std::time_t t = system_clock::to_time_t(now);
        
        auto us = duration_cast<microseconds>(now.time_since_epoch()) % seconds(1);
        std::tm tm{};
        gmtime_r(&t, &tm);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S") << '.' << std::setw(6) << std::setfill('0') << us.count() << "Z";
        
        return oss.str();
    }

    uint32_t crc32_update(uint32_t crc, const uint8_t* data, size_t len) {
        crc = ~crc;
        for (size_t i = 0; i < len; ++i) {
            crc ^= data[i];
            for (int k = 0; k < 8; ++k)
                crc = (crc >> 1) ^ (0xEDB88320U & (-(int)(crc & 1)));
        }
        return ~crc;
    }

    bool hex_to_u32(const std::string& hex, uint32_t& out) {
        if (hex.empty() || hex.size() > 8) return false;
        out = 0;
        for (char c : hex) {
            out <<= 4;
            if (c >= '0' && c <= '9') out |= (uint32_t)(c - '0');
            else if (c >= 'a' && c <= 'f') out |= (uint32_t)(c - 'a' + 10);
            else if (c >= 'A' && c <= 'F') out |= (uint32_t)(c - 'A' + 10);
            else return false;
        }
        return true;
    }
}