#ifndef DUMMYMQTT_ENCODE_H
#define DUMMYMQTT_ENCODE_H

#include "mqtt/common.h"

namespace dummymqtt::impl {
namespace {
class DefaultEncoder {
public:
    int encode_length(unsigned char *, size_t);
    unsigned long long decode_length(const unsigned char **);
};

inline unsigned long long
DefaultEncoder::decode_length(const unsigned char **buf) {
    unsigned char c;
    int multiplier = 1;
    unsigned long long value = 0LL;
    do {
        c = **buf;
        value += (c & 127U) * multiplier;
        multiplier *= 128;
        (*buf)++;
    } while ((c & 128U) != 0);
    return value;
}

inline int
DefaultEncoder::encode_length(unsigned char *buf, size_t len) {
    int bytes = 0;
    do {
        if (bytes + 1 > common::Def::max_len_bytes)
            return bytes;
        short d = len % 128;
        len /= 128;
        if (len > 0) {
            d |= 128;
        }
        buf[bytes++] = d;
    } while (len > 0);
    return bytes;
}
}

using Encoder = DefaultEncoder;
}
#endif //DUMMYMQTT_ENCODE_H
