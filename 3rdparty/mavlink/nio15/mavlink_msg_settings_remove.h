// MESSAGE SETTINGS_REMOVE PACKING

#define MAVLINK_MSG_ID_SETTINGS_REMOVE 153

typedef struct __mavlink_settings_remove_t
{
 char name[50]; ///< Settings item name.
} mavlink_settings_remove_t;

#define MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN 50
#define MAVLINK_MSG_ID_153_LEN 50

#define MAVLINK_MSG_ID_SETTINGS_REMOVE_CRC 44
#define MAVLINK_MSG_ID_153_CRC 44

#define MAVLINK_MSG_SETTINGS_REMOVE_FIELD_NAME_LEN 50

#define MAVLINK_MESSAGE_INFO_SETTINGS_REMOVE { \
	"SETTINGS_REMOVE", \
	1, \
	{  { "name", NULL, MAVLINK_TYPE_CHAR, 50, 0, offsetof(mavlink_settings_remove_t, name) }, \
         } \
}


/**
 * @brief Pack a settings_remove message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param name Settings item name.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_settings_remove_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN];

	_mav_put_char_array(buf, 0, name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN);
#else
	mavlink_settings_remove_t packet;

	mav_array_memcpy(packet.name, name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SETTINGS_REMOVE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN, MAVLINK_MSG_ID_SETTINGS_REMOVE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN);
#endif
}

/**
 * @brief Pack a settings_remove message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param name Settings item name.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_settings_remove_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN];

	_mav_put_char_array(buf, 0, name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN);
#else
	mavlink_settings_remove_t packet;

	mav_array_memcpy(packet.name, name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SETTINGS_REMOVE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN, MAVLINK_MSG_ID_SETTINGS_REMOVE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN);
#endif
}

/**
 * @brief Encode a settings_remove struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param settings_remove C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_settings_remove_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_settings_remove_t* settings_remove)
{
	return mavlink_msg_settings_remove_pack(system_id, component_id, msg, settings_remove->name);
}

/**
 * @brief Encode a settings_remove struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param settings_remove C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_settings_remove_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_settings_remove_t* settings_remove)
{
	return mavlink_msg_settings_remove_pack_chan(system_id, component_id, chan, msg, settings_remove->name);
}

/**
 * @brief Send a settings_remove message
 * @param chan MAVLink channel to send the message
 *
 * @param name Settings item name.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_settings_remove_send(mavlink_channel_t chan, const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN];

	_mav_put_char_array(buf, 0, name, 50);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_REMOVE, buf, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN, MAVLINK_MSG_ID_SETTINGS_REMOVE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_REMOVE, buf, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN);
#endif
#else
	mavlink_settings_remove_t packet;

	mav_array_memcpy(packet.name, name, sizeof(char)*50);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_REMOVE, (const char *)&packet, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN, MAVLINK_MSG_ID_SETTINGS_REMOVE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_REMOVE, (const char *)&packet, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_settings_remove_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;

	_mav_put_char_array(buf, 0, name, 50);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_REMOVE, buf, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN, MAVLINK_MSG_ID_SETTINGS_REMOVE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_REMOVE, buf, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN);
#endif
#else
	mavlink_settings_remove_t *packet = (mavlink_settings_remove_t *)msgbuf;

	mav_array_memcpy(packet->name, name, sizeof(char)*50);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_REMOVE, (const char *)packet, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN, MAVLINK_MSG_ID_SETTINGS_REMOVE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_REMOVE, (const char *)packet, MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE SETTINGS_REMOVE UNPACKING


/**
 * @brief Get field name from settings_remove message
 *
 * @return Settings item name.
 */
static inline uint16_t mavlink_msg_settings_remove_get_name(const mavlink_message_t* msg, char *name)
{
	return _MAV_RETURN_char_array(msg, name, 50,  0);
}

/**
 * @brief Decode a settings_remove message into a struct
 *
 * @param msg The message to decode
 * @param settings_remove C-struct to decode the message contents into
 */
static inline void mavlink_msg_settings_remove_decode(const mavlink_message_t* msg, mavlink_settings_remove_t* settings_remove)
{
#if MAVLINK_NEED_BYTE_SWAP
	mavlink_msg_settings_remove_get_name(msg, settings_remove->name);
#else
	memcpy(settings_remove, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_SETTINGS_REMOVE_LEN);
#endif
}
