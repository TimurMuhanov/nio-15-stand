// MESSAGE SYSTEM_INFO PACKING

#define MAVLINK_MSG_ID_SYSTEM_INFO 155

typedef struct __mavlink_system_info_t
{
 float cpu_usage; ///< CPU usage in rage in 0..1
 uint32_t time; ///< Time from system start in ms
 uint32_t thread_count; ///< Number of running threads
} mavlink_system_info_t;

#define MAVLINK_MSG_ID_SYSTEM_INFO_LEN 12
#define MAVLINK_MSG_ID_155_LEN 12

#define MAVLINK_MSG_ID_SYSTEM_INFO_CRC 25
#define MAVLINK_MSG_ID_155_CRC 25



#define MAVLINK_MESSAGE_INFO_SYSTEM_INFO { \
	"SYSTEM_INFO", \
	3, \
	{  { "cpu_usage", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_system_info_t, cpu_usage) }, \
         { "time", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_system_info_t, time) }, \
         { "thread_count", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_system_info_t, thread_count) }, \
         } \
}


/**
 * @brief Pack a system_info message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param cpu_usage CPU usage in rage in 0..1
 * @param time Time from system start in ms
 * @param thread_count Number of running threads
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_system_info_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float cpu_usage, uint32_t time, uint32_t thread_count)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SYSTEM_INFO_LEN];
	_mav_put_float(buf, 0, cpu_usage);
	_mav_put_uint32_t(buf, 4, time);
	_mav_put_uint32_t(buf, 8, thread_count);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SYSTEM_INFO_LEN);
#else
	mavlink_system_info_t packet;
	packet.cpu_usage = cpu_usage;
	packet.time = time;
	packet.thread_count = thread_count;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SYSTEM_INFO_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SYSTEM_INFO;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SYSTEM_INFO_LEN, MAVLINK_MSG_ID_SYSTEM_INFO_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SYSTEM_INFO_LEN);
#endif
}

/**
 * @brief Pack a system_info message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cpu_usage CPU usage in rage in 0..1
 * @param time Time from system start in ms
 * @param thread_count Number of running threads
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_system_info_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float cpu_usage,uint32_t time,uint32_t thread_count)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SYSTEM_INFO_LEN];
	_mav_put_float(buf, 0, cpu_usage);
	_mav_put_uint32_t(buf, 4, time);
	_mav_put_uint32_t(buf, 8, thread_count);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SYSTEM_INFO_LEN);
#else
	mavlink_system_info_t packet;
	packet.cpu_usage = cpu_usage;
	packet.time = time;
	packet.thread_count = thread_count;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SYSTEM_INFO_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SYSTEM_INFO;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SYSTEM_INFO_LEN, MAVLINK_MSG_ID_SYSTEM_INFO_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SYSTEM_INFO_LEN);
#endif
}

/**
 * @brief Encode a system_info struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param system_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_system_info_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_system_info_t* system_info)
{
	return mavlink_msg_system_info_pack(system_id, component_id, msg, system_info->cpu_usage, system_info->time, system_info->thread_count);
}

/**
 * @brief Encode a system_info struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param system_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_system_info_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_system_info_t* system_info)
{
	return mavlink_msg_system_info_pack_chan(system_id, component_id, chan, msg, system_info->cpu_usage, system_info->time, system_info->thread_count);
}

/**
 * @brief Send a system_info message
 * @param chan MAVLink channel to send the message
 *
 * @param cpu_usage CPU usage in rage in 0..1
 * @param time Time from system start in ms
 * @param thread_count Number of running threads
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_system_info_send(mavlink_channel_t chan, float cpu_usage, uint32_t time, uint32_t thread_count)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SYSTEM_INFO_LEN];
	_mav_put_float(buf, 0, cpu_usage);
	_mav_put_uint32_t(buf, 4, time);
	_mav_put_uint32_t(buf, 8, thread_count);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_INFO, buf, MAVLINK_MSG_ID_SYSTEM_INFO_LEN, MAVLINK_MSG_ID_SYSTEM_INFO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_INFO, buf, MAVLINK_MSG_ID_SYSTEM_INFO_LEN);
#endif
#else
	mavlink_system_info_t packet;
	packet.cpu_usage = cpu_usage;
	packet.time = time;
	packet.thread_count = thread_count;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_INFO, (const char *)&packet, MAVLINK_MSG_ID_SYSTEM_INFO_LEN, MAVLINK_MSG_ID_SYSTEM_INFO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_INFO, (const char *)&packet, MAVLINK_MSG_ID_SYSTEM_INFO_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_SYSTEM_INFO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_system_info_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float cpu_usage, uint32_t time, uint32_t thread_count)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, cpu_usage);
	_mav_put_uint32_t(buf, 4, time);
	_mav_put_uint32_t(buf, 8, thread_count);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_INFO, buf, MAVLINK_MSG_ID_SYSTEM_INFO_LEN, MAVLINK_MSG_ID_SYSTEM_INFO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_INFO, buf, MAVLINK_MSG_ID_SYSTEM_INFO_LEN);
#endif
#else
	mavlink_system_info_t *packet = (mavlink_system_info_t *)msgbuf;
	packet->cpu_usage = cpu_usage;
	packet->time = time;
	packet->thread_count = thread_count;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_INFO, (const char *)packet, MAVLINK_MSG_ID_SYSTEM_INFO_LEN, MAVLINK_MSG_ID_SYSTEM_INFO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_INFO, (const char *)packet, MAVLINK_MSG_ID_SYSTEM_INFO_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE SYSTEM_INFO UNPACKING


/**
 * @brief Get field cpu_usage from system_info message
 *
 * @return CPU usage in rage in 0..1
 */
static inline float mavlink_msg_system_info_get_cpu_usage(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field time from system_info message
 *
 * @return Time from system start in ms
 */
static inline uint32_t mavlink_msg_system_info_get_time(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field thread_count from system_info message
 *
 * @return Number of running threads
 */
static inline uint32_t mavlink_msg_system_info_get_thread_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Decode a system_info message into a struct
 *
 * @param msg The message to decode
 * @param system_info C-struct to decode the message contents into
 */
static inline void mavlink_msg_system_info_decode(const mavlink_message_t* msg, mavlink_system_info_t* system_info)
{
#if MAVLINK_NEED_BYTE_SWAP
	system_info->cpu_usage = mavlink_msg_system_info_get_cpu_usage(msg);
	system_info->time = mavlink_msg_system_info_get_time(msg);
	system_info->thread_count = mavlink_msg_system_info_get_thread_count(msg);
#else
	memcpy(system_info, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_SYSTEM_INFO_LEN);
#endif
}
