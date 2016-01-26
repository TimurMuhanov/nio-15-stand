// MESSAGE SETTINGS_ITEM PACKING

#define MAVLINK_MSG_ID_SETTINGS_ITEM 152

typedef struct __mavlink_settings_item_t
{
 char name[50]; ///< Settings item name.
 char value[50]; ///< Settings item value.
} mavlink_settings_item_t;

#define MAVLINK_MSG_ID_SETTINGS_ITEM_LEN 100
#define MAVLINK_MSG_ID_152_LEN 100

#define MAVLINK_MSG_ID_SETTINGS_ITEM_CRC 105
#define MAVLINK_MSG_ID_152_CRC 105

#define MAVLINK_MSG_SETTINGS_ITEM_FIELD_NAME_LEN 50
#define MAVLINK_MSG_SETTINGS_ITEM_FIELD_VALUE_LEN 50

#define MAVLINK_MESSAGE_INFO_SETTINGS_ITEM { \
	"SETTINGS_ITEM", \
	2, \
	{  { "name", NULL, MAVLINK_TYPE_CHAR, 50, 0, offsetof(mavlink_settings_item_t, name) }, \
         { "value", NULL, MAVLINK_TYPE_CHAR, 50, 50, offsetof(mavlink_settings_item_t, value) }, \
         } \
}


/**
 * @brief Pack a settings_item message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param name Settings item name.
 * @param value Settings item value.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_settings_item_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       const char *name, const char *value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SETTINGS_ITEM_LEN];

	_mav_put_char_array(buf, 0, name, 50);
	_mav_put_char_array(buf, 50, value, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN);
#else
	mavlink_settings_item_t packet;

	mav_array_memcpy(packet.name, name, sizeof(char)*50);
	mav_array_memcpy(packet.value, value, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SETTINGS_ITEM;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN, MAVLINK_MSG_ID_SETTINGS_ITEM_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN);
#endif
}

/**
 * @brief Pack a settings_item message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param name Settings item name.
 * @param value Settings item value.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_settings_item_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           const char *name,const char *value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SETTINGS_ITEM_LEN];

	_mav_put_char_array(buf, 0, name, 50);
	_mav_put_char_array(buf, 50, value, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN);
#else
	mavlink_settings_item_t packet;

	mav_array_memcpy(packet.name, name, sizeof(char)*50);
	mav_array_memcpy(packet.value, value, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SETTINGS_ITEM;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN, MAVLINK_MSG_ID_SETTINGS_ITEM_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN);
#endif
}

/**
 * @brief Encode a settings_item struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param settings_item C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_settings_item_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_settings_item_t* settings_item)
{
	return mavlink_msg_settings_item_pack(system_id, component_id, msg, settings_item->name, settings_item->value);
}

/**
 * @brief Encode a settings_item struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param settings_item C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_settings_item_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_settings_item_t* settings_item)
{
	return mavlink_msg_settings_item_pack_chan(system_id, component_id, chan, msg, settings_item->name, settings_item->value);
}

/**
 * @brief Send a settings_item message
 * @param chan MAVLink channel to send the message
 *
 * @param name Settings item name.
 * @param value Settings item value.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_settings_item_send(mavlink_channel_t chan, const char *name, const char *value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SETTINGS_ITEM_LEN];

	_mav_put_char_array(buf, 0, name, 50);
	_mav_put_char_array(buf, 50, value, 50);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_ITEM, buf, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN, MAVLINK_MSG_ID_SETTINGS_ITEM_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_ITEM, buf, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN);
#endif
#else
	mavlink_settings_item_t packet;

	mav_array_memcpy(packet.name, name, sizeof(char)*50);
	mav_array_memcpy(packet.value, value, sizeof(char)*50);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_ITEM, (const char *)&packet, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN, MAVLINK_MSG_ID_SETTINGS_ITEM_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_ITEM, (const char *)&packet, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_SETTINGS_ITEM_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_settings_item_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const char *name, const char *value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;

	_mav_put_char_array(buf, 0, name, 50);
	_mav_put_char_array(buf, 50, value, 50);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_ITEM, buf, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN, MAVLINK_MSG_ID_SETTINGS_ITEM_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_ITEM, buf, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN);
#endif
#else
	mavlink_settings_item_t *packet = (mavlink_settings_item_t *)msgbuf;

	mav_array_memcpy(packet->name, name, sizeof(char)*50);
	mav_array_memcpy(packet->value, value, sizeof(char)*50);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_ITEM, (const char *)packet, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN, MAVLINK_MSG_ID_SETTINGS_ITEM_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SETTINGS_ITEM, (const char *)packet, MAVLINK_MSG_ID_SETTINGS_ITEM_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE SETTINGS_ITEM UNPACKING


/**
 * @brief Get field name from settings_item message
 *
 * @return Settings item name.
 */
static inline uint16_t mavlink_msg_settings_item_get_name(const mavlink_message_t* msg, char *name)
{
	return _MAV_RETURN_char_array(msg, name, 50,  0);
}

/**
 * @brief Get field value from settings_item message
 *
 * @return Settings item value.
 */
static inline uint16_t mavlink_msg_settings_item_get_value(const mavlink_message_t* msg, char *value)
{
	return _MAV_RETURN_char_array(msg, value, 50,  50);
}

/**
 * @brief Decode a settings_item message into a struct
 *
 * @param msg The message to decode
 * @param settings_item C-struct to decode the message contents into
 */
static inline void mavlink_msg_settings_item_decode(const mavlink_message_t* msg, mavlink_settings_item_t* settings_item)
{
#if MAVLINK_NEED_BYTE_SWAP
	mavlink_msg_settings_item_get_name(msg, settings_item->name);
	mavlink_msg_settings_item_get_value(msg, settings_item->value);
#else
	memcpy(settings_item, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_SETTINGS_ITEM_LEN);
#endif
}
