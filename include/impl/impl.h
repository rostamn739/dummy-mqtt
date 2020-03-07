#ifndef DUMMYMQTT_IMPL_H
#define DUMMYMQTT_IMPL_H

#include "mqtt/mqtt.h"
#include "./pack.h"
#include "./encode.h"

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
    size_t unpack_mqtt_connect(
            const unsigned char *raw,
            common::MqttHeader *hdr,
            mqtt::packets::Generic *pkt
            ) {
        mqtt::packets::Conn connect = { .header = *hdr };
        pkt->connect = connect;

        const unsigned char *init = raw;
        size_t len = TEncoder::decode_length(&raw);

        raw = init + 8;
        pkt->connect.byte = TPacker::unpack_u8(&raw);
        pkt->connect.payload.keepalive =
                TPacker::unpack_u16(&raw);

        uint16_t cid_len = TPacker::unpack_u16(&raw);
        if (cid_len > 0) {
            pkt->connect.payload.client_id =
                    static_cast<unsigned char *>(operator new(cid_len + 1));
            TPacker::unpack_bytes(&raw, cid_len,
                    pkt->connect.payload.client_id);
        }
        if (pkt->connect.bits.will == 1U) {
            uint16_t will_topic_len = TPacker::unpack_u16(&raw);
            pkt->connect.payload.will_topic =
                    static_cast<unsigned char *>(operator new(will_topic_len + 1));
            TPacker::unpack_bytes(&raw, will_topic_len,
                    pkt->connect.payload.will_topic);

            uint16_t will_message_len = TPacker::unpack_u16(&raw);
            pkt->connect.payload.will_message =
                    static_cast<unsigned char *>(operator new(will_message_len + 1));
            TPacker::unpack_bytes(&raw, will_message_len,
                    pkt->connect.payload.will_message);
        }
        if (pkt->connect.bits.username == 1U) {
            uint16_t username_len = TPacker::unpack_u16(&raw);
            pkt->connect.payload.username =
                    static_cast<unsigned char *>(operator new(username_len + 1));
            TPacker::unpack_bytes(&raw, username_len,
                    pkt->connect.payload.username);
        }

        if (pkt->connect.bits.password == 1U) {
            uint16_t password_len = TPacker::unpack_u16(&raw);
            pkt->connect.payload.password =
                    static_cast<unsigned char *>(operator new(password_len + 1));
            TPacker::unpack_bytes(&raw, password_len,
                    pkt->connect.payload.password);
        }
        return len;
    }
    ~BeaverImpl() override { }; // NOLINT(hicpp-use-equals-default,modernize-use-equals-default)
private:
};
using DefaultBeaverImpl = BeaverImpl<impl::Encoder, impl::Packer>;
}

#endif //DUMMYMQTT_IMPL_H
