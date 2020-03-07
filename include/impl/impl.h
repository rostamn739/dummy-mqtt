#ifndef DUMMYMQTT_IMPL_H
#define DUMMYMQTT_IMPL_H

#include "mqtt/mqtt.h"

namespace dummymqtt::impl {
namespace detail {

struct Stateless {
    virtual ~Stateless() = default;;
};
}

/**
 * interface to various utility functions
 */
class Beaver {
public:
    virtual int encode_length(unsigned char *, size_t)                              = 0;
    virtual unsigned long long decode_length(const unsigned char**)                 = 0;
    virtual int
    unpack_packet(const unsigned char *, mqtt::packets::Generic *)                  = 0;
    virtual unsigned char
    *pack_packet(const mqtt::packets::Generic *, unsigned int)                      = 0;
    virtual common::MqttHeader packet_header(unsigned char)                         = 0;
    virtual mqtt::packets::Ack  *packet_ack(unsigned char, unsigned short)          = 0;
    virtual mqtt::packets::ConnAck
    *packet_connack(unsigned char, unsigned char, unsigned char)                    = 0;
    virtual mqtt::packets::SubAck
    *packet_suback(
            unsigned char, unsigned short, unsigned char *, unsigned short
            ) = 0;

    virtual mqtt::packets::Pub
    *packet_publish(
            unsigned char, unsigned short, size_t,
            unsigned char *, size_t, unsigned char *
            ) = 0;
    virtual void
    packet_release(mqtt::packets::Generic *, unsigned int)                          = 0;

    virtual ~Beaver() = default;
};

template <typename TEncoder, typename TPacker>
class BeaverImpl:
        public Beaver,
        public detail::Stateless,
        protected TEncoder,
        protected TPacker {
public:
    ~BeaverImpl() override { };
private:
};
}

#endif //DUMMYMQTT_IMPL_H
