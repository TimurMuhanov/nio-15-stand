// MESSAGE MCU_JUMP_TO PACKING

#define MAVLINK_MSG_ID_MCU_JUMP_TO 151

typedef struct __mavlink_mcu_jump_to_t
{
 uint8_t address; /*< Jump address. Indices defined by ENUM MCU_JUMP_TO_ADDRESS*/
} mavlink_mcu_jump_to_t;

#define MAVLINK_MSG_ID_MCU_JUMP_TO_LEN 1
#define MAVLINK_MSG_ID_151_LEN 1

#define MAVLINK_MSG_ID_MCU_JUMP_TO_CRC 181
#define MAVLINK_MSG_ID_151_CRC 181



#define MAVLINK_MESSAGE_INFO_MCU_JUMP_TO { \
	"MCU_JUMP_TO", \
	1, \
	{  { "address", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mcu_jump_to_t, address) }, \
         } \
}


/**
 * @brief Pack a mcu_jump_to message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param address Jump address. Indices defined by ENUM MCU_JUMP_TO_ADDRESS
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mcu_jump_to_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t address)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MCU_JUMP_TO_LEN];
	_mav_put_uint8_t(buf, 0, address);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN);
#else
	mavlink_mcu_jump_to_t packet;
	packet.address = address;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MCU_JUMP_TO;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN, MAVLINK_MSG_ID_MCU_JUMP_TO_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN);
#endif
}

/**
 * @brief Pack a mcu_jump_to message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param address Jump address. Indices defined by ENUM MCU_JUMP_TO_ADDRESS
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mcu_jump_to_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t address)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MCU_JUMP_TO_LEN];
	_mav_put_uint8_t(buf, 0, address);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN);
#else
	mavlink_mcu_jump_to_t packet;
	packet.address = address;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MCU_JUMP_TO;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN, MAVLINK_MSG_ID_MCU_JUMP_TO_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN);
#endif
}

/**
 * @brief Encode a mcu_jump_to struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mcu_jump_to C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mcu_jump_to_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mcu_jump_to_t* mcu_jump_to)
{
	return mavlink_msg_mcu_jump_to_pack(system_id, component_id, msg, mcu_jump_to->address);
}

/**
 * @brief Encode a mcu_jump_to struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mcu_jump_to C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mcu_jump_to_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mcu_jump_to_t* mcu_jump_to)
{
	return mavlink_msg_mcu_jump_to_pack_chan(system_id, component_id, chan, msg, mcu_jump_to->address);
}

/**
 * @brief Send a mcu_jump_to message
 * @param chan MAVLink channel to send the message
 *
 * @param address Jump address. Indices defined by ENUM MCU_JUMP_TO_ADDRESS
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mcu_jump_to_send(mavlink_channel_t chan, uint8_t address)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MCU_JUMP_TO_LEN];
	_mav_put_uint8_t(buf, 0, address);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MCU_JUMP_TO, buf, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN, MAVLINK_MSG_ID_MCU_JUMP_TO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MCU_JUMP_TO, buf, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN);
#endif
#else
	mavlink_mcu_jump_to_t packet;
	packet.address = address;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MCU_JUMP_TO, (const char *)&packet, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN, MAVLINK_MSG_ID_MCU_JUMP_TO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MCU_JUMP_TO, (const char *)&packet, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_MCU_JUMP_TO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mcu_jump_to_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t address)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, address);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MCU_JUMP_TO, buf, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN, MAVLINK_MSG_ID_MCU_JUMP_TO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MCU_JUMP_TO, buf, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN);
#endif
#else
	mavlink_mcu_jump_to_t *packet = (mavlink_mcu_jump_to_t *)msgbuf;
	packet->address = address;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MCU_JUMP_TO, (const char *)packet, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN, MAVLINK_MSG_ID_MCU_JUMP_TO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MCU_JUMP_TO, (const char *)packet, MAVLINK_MSG_ID_MCU_JUMP_TO_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE MCU_JUMP_TO UNPACKING


/**
 * @brief Get field address from mcu_jump_to message
 *
 * @return Jump address. Indices defined by ENUM MCU_JUMP_TO_ADDRESS
 */
static inline uint8_t mavlink_msg_mcu_jump_to_get_address(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a mcu_jump_to message into a struct
 *
 * @param msg The message to decode
 * @param mcu_jump_to C-struct to decode the message contents into
 */
static inline void mavlink_msg_mcu_jump_to_decode(const mavlink_message_t* msg, mavlink_mcu_jump_to_t* mcu_jump_to)
{
#if MAVLINK_NEED_BYTE_SWAP
	mcu_jump_to->address = mavlink_msg_mcu_jump_to_get_address(msg);
#else
	memcpy(mcu_jump_to, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_MCU_JUMP_TO_LEN);
#endif
}
