#include "chase_camera.h"

namespace AllCamera
{
	void chase_camera::update(float delta_time) 
	{
		//calculate the combined roation as a quaternion 
		glm::quat rotation(target_rotaion + camera_rot);

		//calculate new posistion
		glm::vec3 new_pos = target_pos + (rotation * pos_offset);

	    posistion = glm::mix(posistion, new_pos, springiness);

		// Calculate new target offset based on rotation
		target_offset = rotation * target_offset;
		// Target is then the target position plus this offset
		target = target_pos + target_offset;

		// Calculate up vector based on rotation
		up = rotation * glm::vec3(0.0f, 1.0f, 0.0f);

		// Calculate view matrix
		view = glm::lookAt(posistion, target, up);

	}

	void chase_camera::move(const glm::vec3 &new_target_pos, const glm::vec3 &new_target_rotation)
	{
		target_pos = new_target_pos;
		//target_rotaion = new_target_rotation;
	}

	void chase_camera::rotate(const glm::vec3 &delta_rotation)
	{
		camera_rot += delta_rotation;
	}

	void chase_camera::pitch_it(float rot, const glm::vec3 &target_location, const glm::vec3 &cam_location, float y_)
	{
		if (6.0 >= cam_location.y - target_location.y)
		{
			target_rotaion += glm::vec3(rot, 0, 0);
		}
	}

	void chase_camera::neg_pitch_it(float rot, const glm::vec3 &target_location, const glm::vec3 &cam_location , float y_)
	{
		if (1.1 <= cam_location.y - target_location.y)
		{
			target_rotaion += glm::vec3(-rot, 0, 0);
		}
	}

	void chase_camera::yaw_it(float rot)
	{
		target_rotaion += glm::vec3(0, rot, 0);
	}

	void chase_camera::neg_yaw_it(float rot)
	{
		target_rotaion += glm::vec3(0, -rot, 0);
	}
	void chase_camera::zoom_out(float rot)
	{
		if (chase_camera::get_pos_offset().z >= -10.0 /*&& 1.1 <= cam_location.y - target_location.y*/)
		{
			chase_camera::set_pos_offset(glm::vec3(chase_camera::get_pos_offset().x, chase_camera::get_pos_offset().y - 0.01f, chase_camera::get_pos_offset().z - rot));
		}

	}
	void chase_camera::zoom_in(float rot)
	{
		if (chase_camera::get_pos_offset().z <= -2.5)
		{
			chase_camera::set_pos_offset(glm::vec3(chase_camera::get_pos_offset().x, chase_camera::get_pos_offset().y + 0.01f, chase_camera::get_pos_offset().z + rot));
		}
	}
}