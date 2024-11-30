#include <cstdint>
#include <cstring>

struct DataPacket {
    uint32_t counter;
    uint32_t timestamp;
    uint8_t padding[1500 - 64]; // Variable size padding
};

struct EthernetPacket {
    uint8_t destinationMAC[6];
    uint8_t sourceMAC[6];
    uint16_t ethertype;
    DataPacket data;
    //uint8_t data[1500];
    uint16_t sz;
};

void reverseEndianMemcpy(void* dest, const void* src, size_t n) {
    uint8_t* d = static_cast<uint8_t*>(dest);
    const uint8_t* s = static_cast<const uint8_t*>(src);
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[n - 1 - i];
    }
}

