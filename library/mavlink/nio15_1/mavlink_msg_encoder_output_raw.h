// MESSAGE ENCODER_OUTPUT_RAW PACKING

#define MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW 150

typedef struct __mavlink_encoder_output_raw_t
{
 uint32_t time_usec; /*< Timestamp (microseconds since system boot)*/
 float encoder1_raw; /*< Encoder output 1 value, in deg*/
 float encoder2_raw; /*< Encoder output 2 value, in deg*/
 float encoder3_raw; /*< Encoder output 3 value, in deg*/
 float encoder4_raw; /*< Encoder output 4 value, in deg*/
 float encoder5_raw; /*< Encoder output 5 value, in deg*/
 float encoder6_raw; /*< Encoder output 6 value, in deg*/
 float encoder7_raw; /*< Encoder output 7 value, in deg*/
 float encoder8_raw; /*< Encoder output 8 value, in deg*/
 float encoder9_raw; /*< Encoder output 9 value, in deg*/
 uint8_t port; /*< Encoder output port (set of 9 outputs = 1 port). Most MAVs will just use one, but this allows to encode more than 9 encoders.*/
} mavlink_encoder_output_raw_t;

#define MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN 41
#define MAVLINK_MSG_ID_150_LEN 41

#define MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_CRC 58
#define MAVLINK_MSG_ID_150_CRC 58



#define MAVLINK_MESSAGE_INFO_ENCODER_OUTPUT_RAW { \
	"ENCODER_OUTPUT_RAW", \
	11, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_encoder_output_raw_t, time_usec) }, \
         { "encoder1_raw", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_encoder_output_raw_t, encoder1_raw) }, \
         { "encoder2_raw", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_encoder_output_raw_t, encoder2_raw) }, \
         { "encoder3_raw", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_encoder_output_raw_t, encoder3_raw) }, \
         { "encoder4_raw", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_encoder_output_raw_t, encoder4_raw) }, \
         { "encoder5_raw", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_encoder_output_raw_t, encoder5_raw) }, \
         { "encoder6_raw", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_encoder_output_raw_t, encoder6_raw) }, \
         { "encoder7_raw", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_encoder_output_raw_t, encoder7_raw) }, \
         { "encoder8_raw", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_encoder_output_raw_t, encoder8_raw) }, \
         { "encoder9_raw", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_encoder_output_raw_t, encoder9_raw) }, \
         { "port", NULL, MAVLINK_TYPE_UINT8_T, 0, 40, offsetof(mavlink_encoder_output_raw_t, port) }, \
         } \
}


/**
 * @brief Pack a encoder_output_raw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (microseconds since system boot)
 * @param port Encoder output port (set of 9 outputs = 1 port). Most MAVs will just use one, but this allows to encode more than 9 encoders.
 * @param encoder1_raw Encoder output 1 value, in deg
 * @param encoder2_raw Encoder output 2 value, in deg
 * @param encoder3_raw Encoder output 3 value, in deg
 * @param encoder4_raw Encoder output 4 value, in deg
 * @param encoder5_raw Encoder output 5 value, in deg
 * @param encoder6_raw Encoder output 6 value, in deg
 * @param encoder7_raw Encoder output 7 value, in deg
 * @param encoder8_raw Encoder output 8 value, in deg
 * @param encoder9_raw Encoder output 9 value, in deg
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_encoder_output_raw_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_usec, uint8_t port, float encoder1_raw, float encoder2_raw, float encoder3_raw, float encoder4_raw, float encoder5_raw, float encoder6_raw, float encoder7_raw, float encoder8_raw, float encoder9_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_float(buf, 4, encoder1_raw);
	_mav_put_float(buf, 8, encoder2_raw);
	_mav_put_float(buf, 12, encoder3_raw);
	_mav_put_float(buf, 16, encoder4_raw);
	_mav_put_float(buf, 20, encoder5_raw);
	_mav_put_float(buf, 24, encoder6_raw);
	_mav_put_float(buf, 28, encoder7_raw);
	_mav_put_float(buf, 32, encoder8_raw);
	_mav_put_float(buf, 36, encoder9_raw);
	_mav_put_uint8_t(buf, 40, port);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN);
#else
	mavlink_encoder_output_raw_t packet;
	packet.time_usec = time_usec;
	packet.encoder1_raw = encoder1_raw;
	packet.encoder2_raw = encoder2_raw;
	packet.encoder3_raw = encoder3_raw;
	packet.encoder4_raw = encoder4_raw;
	packet.encoder5_raw = encoder5_raw;
	packet.encoder6_raw = encoder6_raw;
	packet.encoder7_raw = encoder7_raw;
	packet.encoder8_raw = encoder8_raw;
	packet.encoder9_raw = encoder9_raw;
	packet.port = port;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN);
#endif
}

/**
 * @brief Pack a encoder_output_raw message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (microseconds since system boot)
 * @param port Encoder output port (set of 9 outputs = 1 port). Most MAVs will just use one, but this allows to encode more than 9 encoders.
 * @param encoder1_raw Encoder output 1 value, in deg
 * @param encoder2_raw Encoder output 2 value, in deg
 * @param encoder3_raw Encoder output 3 value, in deg
 * @param encoder4_raw Encoder output 4 value, in deg
 * @param encoder5_raw Encoder output 5 value, in deg
 * @param encoder6_raw Encoder output 6 value, in deg
 * @param encoder7_raw Encoder output 7 value, in deg
 * @param encoder8_raw Encoder output 8 value, in deg
 * @param encoder9_raw Encoder output 9 value, in deg
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_encoder_output_raw_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_usec,uint8_t port,float encoder1_raw,float encoder2_raw,float encoder3_raw,float encoder4_raw,float encoder5_raw,float encoder6_raw,float encoder7_raw,float encoder8_raw,float encoder9_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_float(buf, 4, encoder1_raw);
	_mav_put_float(buf, 8, encoder2_raw);
	_mav_put_float(buf, 12, encoder3_raw);
	_mav_put_float(buf, 16, encoder4_raw);
	_mav_put_float(buf, 20, encoder5_raw);
	_mav_put_float(buf, 24, encoder6_raw);
	_mav_put_float(buf, 28, encoder7_raw);
	_mav_put_float(buf, 32, encoder8_raw);
	_mav_put_float(buf, 36, encoder9_raw);
	_mav_put_uint8_t(buf, 40, port);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN);
#else
	mavlink_encoder_output_raw_t packet;
	packet.time_usec = time_usec;
	packet.encoder1_raw = encoder1_raw;
	packet.encoder2_raw = encoder2_raw;
	packet.encoder3_raw = encoder3_raw;
	packet.encoder4_raw = encoder4_raw;
	packet.encoder5_raw = encoder5_raw;
	packet.encoder6_raw = encoder6_raw;
	packet.encoder7_raw = encoder7_raw;
	packet.encoder8_raw = encoder8_raw;
	packet.encoder9_raw = encoder9_raw;
	packet.port = port;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN);
#endif
}

/**
 * @brief Encode a encoder_output_raw struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param encoder_output_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_encoder_output_raw_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_encoder_output_raw_t* encoder_output_raw)
{
	return mavlink_msg_encoder_output_raw_pack(system_id, component_id, msg, encoder_output_raw->time_usec, encoder_output_raw->port, encoder_output_raw->encoder1_raw, encoder_output_raw->encoder2_raw, encoder_output_raw->encoder3_raw, encoder_output_raw->encoder4_raw, encoder_output_raw->encoder5_raw, encoder_output_raw->encoder6_raw, encoder_output_raw->encoder7_raw, encoder_output_raw->encoder8_raw, encoder_output_raw->encoder9_raw);
}

/**
 * @brief Encode a encoder_output_raw struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param encoder_output_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_encoder_output_raw_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_encoder_output_raw_t* encoder_output_raw)
{
	return mavlink_msg_encoder_output_raw_pack_chan(system_id, component_id, chan, msg, encoder_output_raw->time_usec, encoder_output_raw->port, encoder_output_raw->encoder1_raw, encoder_output_raw->encoder2_raw, encoder_output_raw->encoder3_raw, encoder_output_raw->encoder4_raw, encoder_output_raw->encoder5_raw, encoder_output_raw->encoder6_raw, encoder_output_raw->encoder7_raw, encoder_output_raw->encoder8_raw, encoder_output_raw->encoder9_raw);
}

/**
 * @brief Send a encoder_output_raw message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (microseconds since system boot)
 * @param port Encoder output port (set of 9 outputs = 1 port). Most MAVs will just use one, but this allows to encode more than 9 encoders.
 * @param encoder1_raw Encoder output 1 value, in deg
 * @param encoder2_raw Encoder output 2 value, in deg
 * @param encoder3_raw Encoder output 3 value, in deg
 * @param encoder4_raw Encoder output 4 value, in deg
 * @param encoder5_raw Encoder output 5 value, in deg
 * @param encoder6_raw Encoder output 6 value, in deg
 * @param encoder7_raw Encoder output 7 value, in deg
 * @param encoder8_raw Encoder output 8 value, in deg
 * @param encoder9_raw Encoder output 9 value, in deg
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_encoder_output_raw_send(mavlink_channel_t chan, uint32_t time_usec, uint8_t port, float encoder1_raw, float encoder2_raw, float encoder3_raw, float encoder4_raw, float encoder5_raw, float encoder6_raw, float encoder7_raw, float encoder8_raw, float encoder9_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_float(buf, 4, encoder1_raw);
	_mav_put_float(buf, 8, encoder2_raw);
	_mav_put_float(buf, 12, encoder3_raw);
	_mav_put_float(buf, 16, encoder4_raw);
	_mav_put_float(buf, 20, encoder5_raw);
	_mav_put_float(buf, 24, encoder6_raw);
	_mav_put_float(buf, 28, encoder7_raw);
	_mav_put_float(buf, 32, encoder8_raw);
	_mav_put_float(buf, 36, encoder9_raw);
	_mav_put_uint8_t(buf, 40, port);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW, buf, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW, buf, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN);
#endif
#else
	mavlink_encoder_output_raw_t packet;
	packet.time_usec = time_usec;
	packet.encoder1_raw = encoder1_raw;
	packet.encoder2_raw = encoder2_raw;
	packet.encoder3_raw = encoder3_raw;
	packet.encoder4_raw = encoder4_raw;
	packet.encoder5_raw = encoder5_raw;
	packet.encoder6_raw = encoder6_raw;
	packet.encoder7_raw = encoder7_raw;
	packet.encoder8_raw = encoder8_raw;
	packet.encoder9_raw = encoder9_raw;
	packet.port = port;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW, (const char *)&packet, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW, (const char *)&packet, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_encoder_output_raw_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_usec, uint8_t port, float encoder1_raw, float encoder2_raw, float encoder3_raw, float encoder4_raw, float encoder5_raw, float encoder6_raw, float encoder7_raw, float encoder8_raw, float encoder9_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_float(buf, 4, encoder1_raw);
	_mav_put_float(buf, 8, encoder2_raw);
	_mav_put_float(buf, 12, encoder3_raw);
	_mav_put_float(buf, 16, encoder4_raw);
	_mav_put_float(buf, 20, encoder5_raw);
	_mav_put_float(buf, 24, encoder6_raw);
	_mav_put_float(buf, 28, encoder7_raw);
	_mav_put_float(buf, 32, encoder8_raw);
	_mav_put_float(buf, 36, encoder9_raw);
	_mav_put_uint8_t(buf, 40, port);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW, buf, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW, buf, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN);
#endif
#else
	mavlink_encoder_output_raw_t *packet = (mavlink_encoder_output_raw_t *)msgbuf;
	packet->time_usec = time_usec;
	packet->encoder1_raw = encoder1_raw;
	packet->encoder2_raw = encoder2_raw;
	packet->encoder3_raw = encoder3_raw;
	packet->encoder4_raw = encoder4_raw;
	packet->encoder5_raw = encoder5_raw;
	packet->encoder6_raw = encoder6_raw;
	packet->encoder7_raw = encoder7_raw;
	packet->encoder8_raw = encoder8_raw;
	packet->encoder9_raw = encoder9_raw;
	packet->port = port;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW, (const char *)packet, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW, (const char *)packet, MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE ENCODER_OUTPUT_RAW UNPACKING


/**
 * @brief Get field time_usec from encoder_output_raw message
 *
 * @return Timestamp (microseconds since system boot)
 */
static inline uint32_t mavlink_msg_encoder_output_raw_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field port from encoder_output_raw message
 *
 * @return Encoder output port (set of 9 outputs = 1 port). Most MAVs will just use one, but this allows to encode more than 9 encoders.
 */
static inline uint8_t mavlink_msg_encoder_output_raw_get_port(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  40);
}

/**
 * @brief Get field encoder1_raw from encoder_output_raw message
 *
 * @return Encoder output 1 value, in deg
 */
static inline float mavlink_msg_encoder_output_raw_get_encoder1_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field encoder2_raw from encoder_output_raw message
 *
 * @return Encoder output 2 value, in deg
 */
static inline float mavlink_msg_encoder_output_raw_get_encoder2_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field encoder3_raw from encoder_output_raw message
 *
 * @return Encoder output 3 value, in deg
 */
static inline float mavlink_msg_encoder_output_raw_get_encoder3_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field encoder4_raw from encoder_output_raw message
 *
 * @return Encoder output 4 value, in deg
 */
static inline float mavlink_msg_encoder_output_raw_get_encoder4_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field encoder5_raw from encoder_output_raw message
 *
 * @return Encoder output 5 value, in deg
 */
static inline float mavlink_msg_encoder_output_raw_get_encoder5_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field encoder6_raw from encoder_output_raw message
 *
 * @return Encoder output 6 value, in deg
 */
static inline float mavlink_msg_encoder_output_raw_get_encoder6_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field encoder7_raw from encoder_output_raw message
 *
 * @return Encoder output 7 value, in deg
 */
static inline float mavlink_msg_encoder_output_raw_get_encoder7_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field encoder8_raw from encoder_output_raw message
 *
 * @return Encoder output 8 value, in deg
 */
static inline float mavlink_msg_encoder_output_raw_get_encoder8_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field encoder9_raw from encoder_output_raw message
 *
 * @return Encoder output 9 value, in deg
 */
static inline float mavlink_msg_encoder_output_raw_get_encoder9_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Decode a encoder_output_raw message into a struct
 *
 * @param msg The message to decode
 * @param encoder_output_raw C-struct to decode the message contents into
 */
static inline void mavlink_msg_encoder_output_raw_decode(const mavlink_message_t* msg, mavlink_encoder_output_raw_t* encoder_output_raw)
{
#if MAVLINK_NEED_BYTE_SWAP
	encoder_output_raw->time_usec = mavlink_msg_encoder_output_raw_get_time_usec(msg);
	encoder_output_raw->encoder1_raw = mavlink_msg_encoder_output_raw_get_encoder1_raw(msg);
	encoder_output_raw->encoder2_raw = mavlink_msg_encoder_output_raw_get_encoder2_raw(msg);
	encoder_output_raw->encoder3_raw = mavlink_msg_encoder_output_raw_get_encoder3_raw(msg);
	encoder_output_raw->encoder4_raw = mavlink_msg_encoder_output_raw_get_encoder4_raw(msg);
	encoder_output_raw->encoder5_raw = mavlink_msg_encoder_output_raw_get_encoder5_raw(msg);
	encoder_output_raw->encoder6_raw = mavlink_msg_encoder_output_raw_get_encoder6_raw(msg);
	encoder_output_raw->encoder7_raw = mavlink_msg_encoder_output_raw_get_encoder7_raw(msg);
	encoder_output_raw->encoder8_raw = mavlink_msg_encoder_output_raw_get_encoder8_raw(msg);
	encoder_output_raw->encoder9_raw = mavlink_msg_encoder_output_raw_get_encoder9_raw(msg);
	encoder_output_raw->port = mavlink_msg_encoder_output_raw_get_port(msg);
#else
	memcpy(encoder_output_raw, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ENCODER_OUTPUT_RAW_LEN);
#endif
}
