/****************************************************************************
 *
 *   Copyright (c) 2020 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef ECAN_INVERTER_REQUEST_SPEED_RPMMAX_HPP
#define ECAN_INVERTER_REQUEST_SPEED_RPMMAX_HPP

#include <uORB/topics/ecan_inverter_request.h>

class MavlinkStreamEcanInverterRequestSpeedRpmMax : public MavlinkStream
{
public:
	static MavlinkStream *new_instance(Mavlink *mavlink) { return new MavlinkStreamEcanInverterRequestSpeedRpmMax(mavlink); }

	static constexpr const char *get_name_static() { return "ECAN_INVERTER_REQUEST_SPEED_RPMMAX"; }
	static constexpr uint16_t get_id_static() { return MAVLINK_MSG_ID_ECAN_INVERTER_REQUEST_SPEED_RPMMAX; }

	const char *get_name() const override { return get_name_static(); }
	uint16_t get_id() override { return get_id_static(); }

	unsigned get_size() override
	{
		return _uorb_sub.advertised() ? (MAVLINK_MSG_ID_ECAN_INVERTER_REQUEST_SPEED_RPMMAX_LEN + MAVLINK_NUM_NON_PAYLOAD_BYTES) : 0;
	}

private:
	explicit MavlinkStreamEcanInverterRequestSpeedRpmMax(Mavlink *mavlink) : MavlinkStream(mavlink) {}

	uORB::Subscription _uorb_sub{ORB_ID(ecan_inverter_request_speed_rpmmax)};

	bool send() override
	{
		// Only send MAVLink message if uORB message is updated
		ecan_inverter_request_s uorbMsg;
		if (_uorb_sub.update(&uorbMsg)) {
			// Assign message elemenets
			mavlink_ecan_inverter_request_speed_rpmmax_t mavlinkMsg{};
			mavlinkMsg.target_system = uorbMsg.target_system;
			mavlinkMsg.target_component = uorbMsg.target_system;
			mavlinkMsg.timestamp = uorbMsg.timestamp;
			mavlinkMsg.packet_number = uorbMsg.packet_number;
			mavlinkMsg.frame_info = uorbMsg.frame_info;
			mavlinkMsg.frame_id = uorbMsg.frame_id;
			mavlinkMsg.regid_type = uorbMsg.regid_type;
			mavlinkMsg.regid = uorbMsg.regid;
			mavlinkMsg.rate = uorbMsg.rate;
			mavlinkMsg.padding1 = uorbMsg.padding1;
			mavlinkMsg.padding1 = uorbMsg.padding1;
			// Send
			mavlink_msg_ecan_inverter_request_speed_rpmmax_send_struct(_mavlink->get_channel(), &mavlinkMsg);

			return true;
		}

		return false;
	}
};

#endif // ECAN_INVERTER_REQUEST_SPEED_RPMMAX_HPP
