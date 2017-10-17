// MESSAGE VECTOR_VALUE PACKING

#define MAVLINK_MSG_ID_VECTOR_VALUE 157

typedef struct __mavlink_vector_value_t
{
 uint32_t time_usec; ///< Timestamp (microseconds since system boot)
 float x; ///< Value X
 float y; ///< Value Y
 float z; ///< Value Z
 char key[15]; ///< Key
} mavlink_vector_value_t;

#define MAVLINK_MSG_ID_VECTOR_VALUE_LEN 31
#define MAVLINK_MSG_ID_157_LEN 31

#define MAVLINK_MSG_ID_VECTOR_VALUE_CRC 94
#define MAVLINK_MSG_ID_157_CRC 94

#define MAVLINK_MSG_VECTOR_VALUE_FIELD_KEY_LEN 15

#define MAVLINK_MESSAGE_INFO_VECTOR_VALUE { \
	"VECTOR_VALUE", \
	5, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_vector_value_t, time_usec) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_vector_value_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_vector_value_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_vector_value_t, z) }, \
         { "key", NULL, MAVLINK_TYPE_CHAR, 15, 16, offsetof(mavlink_vector_value_t, key) }, \
         } \
}


/**
 * @brief Pack a vector_value message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (microseconds since system boot)
 * @param key Key
 * @param x Value X
 * @param y Value Y
 * @param z Value Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_vector_value_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_usec, const char *key, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_VECTOR_VALUE_LEN];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_float(buf, 4, x);
	_mav_put_float(buf, 8, y);
	_mav_put_float(buf, 12, z);
	_mav_put_char_array(buf, 16, key, 15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VECTOR_VALUE_LEN);
#else
	mavlink_vector_value_t packet;
	packet.time_usec = time_usec;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	mav_array_memcpy(packet.key, key, sizeof(char)*15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VECTOR_VALUE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_VECTOR_VALUE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_VECTOR_VALUE_LEN, MAVLINK_MSG_ID_VECTOR_VALUE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_VECTOR_VALUE_LEN);
#endif
}

/**
 * @brief Pack a vector_value message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (microseconds since system boot)
 * @param key Key
 * @param x Value X
 * @param y Value Y
 * @param z Value Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_vector_value_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_usec,const char *key,float x,float y,float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_VECTOR_VALUE_LEN];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_float(buf, 4, x);
	_mav_put_float(buf, 8, y);
	_mav_put_float(buf, 12, z);
	_mav_put_char_array(buf, 16, key, 15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VECTOR_VALUE_LEN);
#else
	mavlink_vector_value_t packet;
	packet.time_usec = time_usec;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	mav_array_memcpy(packet.key, key, sizeof(char)*15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VECTOR_VALUE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_VECTOR_VALUE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_VECTOR_VALUE_LEN, MAVLINK_MSG_ID_VECTOR_VALUE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_VECTOR_VALUE_LEN);
#endif
}

/**
 * @brief Encode a vector_value struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param vector_value C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_vector_value_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_vector_value_t* vector_value)
{
	return mavlink_msg_vector_value_pack(system_id, component_id, msg, vector_value->time_usec, vector_value->key, vector_value->x, vector_value->y, vector_value->z);
}

/**
 * @brief Encode a vector_value struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param vector_value C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_vector_value_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_vector_value_t* vector_value)
{
	return mavlink_msg_vector_value_pack_chan(system_id, component_id, chan, msg, vector_value->time_usec, vector_value->key, vector_value->x, vector_value->y, vector_value->z);
}

/**
 * @brief Send a vector_value message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (microseconds since system boot)
 * @param key Key
 * @param x Value X
 * @param y Value Y
 * @param z Value Z
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_vector_value_send(mavlink_channel_t chan, uint32_t time_usec, const char *key, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_VECTOR_VALUE_LEN];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_float(buf, 4, x);
	_mav_put_float(buf, 8, y);
	_mav_put_float(buf, 12, z);
	_mav_put_char_array(buf, 16, key, 15);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VECTOR_VALUE, buf, MAVLINK_MSG_ID_VECTOR_VALUE_LEN, MAVLINK_MSG_ID_VECTOR_VALUE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VECTOR_VALUE, buf, MAVLINK_MSG_ID_VECTOR_VALUE_LEN);
#endif
#else
	mavlink_vector_value_t packet;
	packet.time_usec = time_usec;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	mav_array_memcpy(packet.key, key, sizeof(char)*15);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VECTOR_VALUE, (const char *)&packet, MAVLINK_MSG_ID_VECTOR_VALUE_LEN, MAVLINK_MSG_ID_VECTOR_VALUE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VECTOR_VALUE, (const char *)&packet, MAVLINK_MSG_ID_VECTOR_VALUE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_VECTOR_VALUE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_vector_value_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_usec, const char *key, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_float(buf, 4, x);
	_mav_put_float(buf, 8, y);
	_mav_put_float(buf, 12, z);
	_mav_put_char_array(buf, 16, key, 15);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VECTOR_VALUE, buf, MAVLINK_MSG_ID_VECTOR_VALUE_LEN, MAVLINK_MSG_ID_VECTOR_VALUE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VECTOR_VALUE, buf, MAVLINK_MSG_ID_VECTOR_VALUE_LEN);
#endif
#else
	mavlink_vector_value_t *packet = (mavlink_vector_value_t *)msgbuf;
	packet->time_usec = time_usec;
	packet->x = x;
	packet->y = y;
	packet->z = z;
	mav_array_memcpy(packet->key, key, sizeof(char)*15);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VECTOR_VALUE, (const char *)packet, MAVLINK_MSG_ID_VECTOR_VALUE_LEN, MAVLINK_MSG_ID_VECTOR_VALUE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VECTOR_VALUE, (const char *)packet, MAVLINK_MSG_ID_VECTOR_VALUE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE VECTOR_VALUE UNPACKING


/**
 * @brief Get field time_usec from vector_value message
 *
 * @return Timestamp (microseconds since system boot)
 */
static inline uint32_t mavlink_msg_vector_value_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field key from vector_value message
 *
 * @return Key
 */
static inline uint16_t mavlink_msg_vector_value_get_key(const mavlink_message_t* msg, char *key)
{
	return _MAV_RETURN_char_array(msg, key, 15,  16);
}

/**
 * @brief Get field x from vector_value message
 *
 * @return Value X
 */
static inline float mavlink_msg_vector_value_get_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field y from vector_value message
 *
 * @return Value Y
 */
static inline float mavlink_msg_vector_value_get_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field z from vector_value message
 *
 * @return Value Z
 */
static inline float mavlink_msg_vector_value_get_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a vector_value message into a struct
 *
 * @param msg The message to decode
 * @param vector_value C-struct to decode the message contents into
 */
static inline void mavlink_msg_vector_value_decode(const mavlink_message_t* msg, mavlink_vector_value_t* vector_value)
{
#if MAVLINK_NEED_BYTE_SWAP
	vector_value->time_usec = mavlink_msg_vector_value_get_time_usec(msg);
	vector_value->x = mavlink_msg_vector_value_get_x(msg);
	vector_value->y = mavlink_msg_vector_value_get_y(msg);
	vector_value->z = mavlink_msg_vector_value_get_z(msg);
	mavlink_msg_vector_value_get_key(msg, vector_value->key);
#else
	memcpy(vector_value, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_VECTOR_VALUE_LEN);
#endif
}
