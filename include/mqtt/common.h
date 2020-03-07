#ifndef DUMMYMQTT_COMMON_H
#define DUMMYMQTT_COMMON_H

namespace dummymqtt::common {
struct Def {
    inline constexpr static int mqtt_header_len    = 2;
    inline constexpr static int mqtt_ack_len       = 4;
    inline constexpr static int max_len_bytes      = 4;
    struct GenBytes {
        inline constexpr static int connack    = 0x20;
        inline constexpr static int publish    = 0x30;
        inline constexpr static int puback     = 0x40;
        inline constexpr static int pubrec     = 0x50;
        inline constexpr static int pubrel     = 0x60;
        inline constexpr static int pubcomp    = 0x70;
        inline constexpr static int suback     = 0x90;
        inline constexpr static int unsuback   = 0xB0;
        inline constexpr static int pingresp   = 0xD0;
    };
    enum class Qos : int {
        at_most_once,
        at_least_once,
        exactly_one
    };
    enum class PacketType : int {
        connect     = 1,
        connack     = 2,
        publish     = 3,
        puback      = 4,
        pubrec      = 5,
        pubrel      = 6,
        pubcomp     = 7,
        subscribe   = 8,
        suback      = 9,
        unsubscribe = 10,
        unsuback    = 11,
        pingreq     = 12,
        pingresp    = 13,
        disconnnect = 14
    };
};

union MqttHeader {
    unsigned char byte;
    struct {
        unsigned int retain     : 1;
        unsigned int qos        : 2;
        unsigned int dup        : 1;
        unsigned int type       : 4;
    } bits;
};
}

#endif //DUMMYMQTT_COMMON_H
