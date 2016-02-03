/** @file
 *	@brief MAVLink comm protocol testsuite generated from nio15.xml
 *	@see http://qgroundcontrol.org/mavlink/
 */
#ifndef NIO15_TESTSUITE_H
#define NIO15_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_nio15(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_common(system_id, component_id, last_msg);
	mavlink_test_nio15(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_encoder_output_raw(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_encoder_output_raw_t packet_in = {
		963497464,45.0,73.0,101.0,129.0,157.0,185.0,213.0,241.0,269.0,125
    };
	mavlink_encoder_output_raw_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.time_usec = packet_in.time_usec;
        	packet1.encoder1_raw = packet_in.encoder1_raw;
        	packet1.encoder2_raw = packet_in.encoder2_raw;
        	packet1.encoder3_raw = packet_in.encoder3_raw;
        	packet1.encoder4_raw = packet_in.encoder4_raw;
        	packet1.encoder5_raw = packet_in.encoder5_raw;
        	packet1.encoder6_raw = packet_in.encoder6_raw;
        	packet1.encoder7_raw = packet_in.encoder7_raw;
        	packet1.encoder8_raw = packet_in.encoder8_raw;
        	packet1.encoder9_raw = packet_in.encoder9_raw;
        	packet1.port = packet_in.port;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_encoder_output_raw_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_encoder_output_raw_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_encoder_output_raw_pack(system_id, component_id, &msg , packet1.time_usec , packet1.port , packet1.encoder1_raw , packet1.encoder2_raw , packet1.encoder3_raw , packet1.encoder4_raw , packet1.encoder5_raw , packet1.encoder6_raw , packet1.encoder7_raw , packet1.encoder8_raw , packet1.encoder9_raw );
	mavlink_msg_encoder_output_raw_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_encoder_output_raw_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.port , packet1.encoder1_raw , packet1.encoder2_raw , packet1.encoder3_raw , packet1.encoder4_raw , packet1.encoder5_raw , packet1.encoder6_raw , packet1.encoder7_raw , packet1.encoder8_raw , packet1.encoder9_raw );
	mavlink_msg_encoder_output_raw_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_encoder_output_raw_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_encoder_output_raw_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.port , packet1.encoder1_raw , packet1.encoder2_raw , packet1.encoder3_raw , packet1.encoder4_raw , packet1.encoder5_raw , packet1.encoder6_raw , packet1.encoder7_raw , packet1.encoder8_raw , packet1.encoder9_raw );
	mavlink_msg_encoder_output_raw_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mcu_jump_to(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_mcu_jump_to_t packet_in = {
		5
    };
	mavlink_mcu_jump_to_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.address = packet_in.address;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mcu_jump_to_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_mcu_jump_to_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mcu_jump_to_pack(system_id, component_id, &msg , packet1.address );
	mavlink_msg_mcu_jump_to_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mcu_jump_to_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.address );
	mavlink_msg_mcu_jump_to_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_mcu_jump_to_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mcu_jump_to_send(MAVLINK_COMM_1 , packet1.address );
	mavlink_msg_mcu_jump_to_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_settings_item(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_settings_item_t packet_in = {
		"ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVW","YZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTU"
    };
	mavlink_settings_item_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        	mav_array_memcpy(packet1.name, packet_in.name, sizeof(char)*50);
        	mav_array_memcpy(packet1.value, packet_in.value, sizeof(char)*50);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_settings_item_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_settings_item_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_settings_item_pack(system_id, component_id, &msg , packet1.name , packet1.value );
	mavlink_msg_settings_item_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_settings_item_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.name , packet1.value );
	mavlink_msg_settings_item_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_settings_item_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_settings_item_send(MAVLINK_COMM_1 , packet1.name , packet1.value );
	mavlink_msg_settings_item_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_settings_remove(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_settings_remove_t packet_in = {
		"ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVW"
    };
	mavlink_settings_remove_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        	mav_array_memcpy(packet1.name, packet_in.name, sizeof(char)*50);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_settings_remove_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_settings_remove_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_settings_remove_pack(system_id, component_id, &msg , packet1.name );
	mavlink_msg_settings_remove_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_settings_remove_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.name );
	mavlink_msg_settings_remove_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_settings_remove_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_settings_remove_send(MAVLINK_COMM_1 , packet1.name );
	mavlink_msg_settings_remove_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_settings_request(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_settings_request_t packet_in = {
		5,72
    };
	mavlink_settings_request_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_settings_request_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_settings_request_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_settings_request_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component );
	mavlink_msg_settings_request_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_settings_request_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component );
	mavlink_msg_settings_request_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_settings_request_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_settings_request_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component );
	mavlink_msg_settings_request_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_system_info(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_system_info_t packet_in = {
		17.0,963497672,963497880,963498088
    };
	mavlink_system_info_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.cpu_usage = packet_in.cpu_usage;
        	packet1.usage_time = packet_in.usage_time;
        	packet1.system_time = packet_in.system_time;
        	packet1.thread_count = packet_in.thread_count;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_system_info_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_system_info_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_system_info_pack(system_id, component_id, &msg , packet1.cpu_usage , packet1.usage_time , packet1.system_time , packet1.thread_count );
	mavlink_msg_system_info_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_system_info_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.cpu_usage , packet1.usage_time , packet1.system_time , packet1.thread_count );
	mavlink_msg_system_info_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_system_info_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_system_info_send(MAVLINK_COMM_1 , packet1.cpu_usage , packet1.usage_time , packet1.system_time , packet1.thread_count );
	mavlink_msg_system_info_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_nio15(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_encoder_output_raw(system_id, component_id, last_msg);
	mavlink_test_mcu_jump_to(system_id, component_id, last_msg);
	mavlink_test_settings_item(system_id, component_id, last_msg);
	mavlink_test_settings_remove(system_id, component_id, last_msg);
	mavlink_test_settings_request(system_id, component_id, last_msg);
	mavlink_test_system_info(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // NIO15_TESTSUITE_H
