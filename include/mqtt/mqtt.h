#ifndef DUMMYMQTT_MQTT_H
#define DUMMYMQTT_MQTT_H

#include "common.h"
namespace dummymqtt::mqtt { // NOLINT(modernize-concat-nested-namespaces)
namespace packets::detail {

using dummymqtt::common::MqttHeader;
struct MqttConnect {
    MqttHeader header;
    union {
        unsigned char byte;
        struct {
            int reserved                : 1;
            unsigned int clean_session  : 1;
            unsigned int will           : 1;
            unsigned int will_qos       : 2;
            unsigned int will_retain    : 1;
            unsigned int password       : 1;
            unsigned int username       : 1;
        } bits;
    };
    struct {
        unsigned short keepalive;
        unsigned char *client_id;
        unsigned char *username;
        unsigned char *password;
        unsigned char *will_topic;
        unsigned char *will_message;
    } payload;

};

struct MqttConnack {
    MqttHeader header;
    union {
        unsigned char byte;;
        struct {
            unsigned int session_present    : 1;
            unsigned int reserved           : 7;
        } bits;
    };
    unsigned char rc;
};

struct MqttSubscribe {
    MqttHeader header;
    unsigned short pkt_id;
    unsigned short tuples_len;
    struct {
        unsigned short topic_len;
        unsigned char *topic;
        unsigned int qos;
    } *tuples;
};

struct MqttUnsubsribe {
    MqttHeader header;
    unsigned short pkt_id;
    unsigned short tuples_len;
    struct {
        unsigned short topic_len;
        unsigned char *topic;
    } *tuples;
};

struct MqttSuback {
    MqttHeader header;
    unsigned short pkt_id;
    unsigned short rcslen;
    unsigned char *rcs;
};

struct MqttPublish {
    MqttHeader header;
    unsigned short pkt_id;
    unsigned short topiclen;
    unsigned char *topic;
    unsigned short payloadlen;
    unsigned char *payload;
};

struct MqttAck {
    MqttHeader header;
    unsigned short pkt_id;
};
}
namespace packets {
using Ack = detail::MqttAck;
using Pub = detail::MqttPublish;
using SubAck = detail::MqttSuback;
using Unsub = detail::MqttUnsubsribe;
using Sub = detail::MqttSubscribe;
using ConnAck = detail::MqttConnack;
using Conn = detail::MqttConnect;
}
}

#endif //DUMMYMQTT_MQTT_H
