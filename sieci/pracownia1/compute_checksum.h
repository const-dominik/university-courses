#ifndef COMPUTE_CHECKSUM
#define COMPUTE_CHECKSUM
#include <iostream>
#include <cassert>

uint16_t compute_icmp_checksum(const void* buff, int length) {
    const uint16_t* ptr = static_cast<const uint16_t*>(buff);
    uint32_t sum = 0;
    assert(length % 2 == 0);

    for (; length > 0; length -= 2)
        sum += *ptr++;

    sum = (sum >> 16U) + (sum & 0xffffU);
    return static_cast<uint16_t>(~(sum + (sum >> 16U)));
}
#endif