#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"
#ifndef DUMMYMQTT_PACK_H
#define DUMMYMQTT_PACK_H

#include <cstdint>
#include <netinet/in.h>

#include "mqtt/mqtt.h"

namespace dummymqtt::impl {
namespace {
class DefaultPacker {
public:
    uint8_t unpack_u8(const uint8_t **);
    uint16_t unpack_u16(const uint8_t **);
    uint32_t unpack_u32(const uint8_t **);
    /**
     *
     * @param len is the number of bytes without trailing null byte
     */
    uint8_t *unpack_bytes(const uint8_t **, size_t len, uint8_t *);
    void pack_u8(uint8_t **, uint8_t);
    void pack_u16(uint8_t **, uint16_t);
    void pack_u32(uint8_t **, uint32_t);
    void pack_bytes(uint8_t **, uint8_t *);
};

inline void
DefaultPacker::pack_bytes(uint8_t **buf, uint8_t *in_str) {
    size_t len = strlen(reinterpret_cast<char*>(in_str));
    memcpy(*buf, in_str, len);
    (*buf) += len;
}

inline void
DefaultPacker::pack_u32(uint8_t **buf, uint32_t what) {
    uint32_t net_val = htonl(what);
    memcpy(*buf, &net_val, sizeof(uint32_t));
    (*buf) += sizeof(uint32_t);
}

inline void
DefaultPacker::pack_u16(uint8_t **buf, uint16_t what) {
    uint16_t net_val = htons(what);
    memcpy(*buf, &net_val, sizeof(uint16_t));
    (*buf) += sizeof(uint16_t);
}

inline void
DefaultPacker::pack_u8(uint8_t **buf, uint8_t what) {
    **buf = what;
    (*buf) += sizeof(uint8_t);
}

inline uint8_t
*DefaultPacker::unpack_bytes(
        const uint8_t **buf, size_t len, uint8_t *out_str) {
    memcpy(out_str, *buf, len);
    out_str[len] = '\0';
    (*buf) += len;
    return out_str;
}

inline uint32_t
DefaultPacker::unpack_u32(const uint8_t **buf) {
    uint32_t val;
    memcpy(&val, *buf, sizeof(uint32_t));
    (*buf) += sizeof(uint32_t);
    return ntohl(val);
}

inline uint16_t
DefaultPacker::unpack_u16(const uint8_t **buf) {
    uint16_t val;
    memcpy(&val, *buf, sizeof(uint16_t));
    (*buf) += sizeof(uint16_t);
    return ntohs(val);
}

inline uint8_t
DefaultPacker::unpack_u8(const uint8_t **buf) {
    uint8_t val = **buf;
    (*buf)++;
    return val;
}
}

using Packer = DefaultPacker;
}

#endif //DUMMYMQTT_PACK_H

#pragma clang diagnostic pop