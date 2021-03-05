#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Engine
{
	class Camera
	{
	protected:
		glm::vec3 position;
		float fov;
		
	public:
		Camera() noexcept
		{
			position = glm::vec3(0.0f);
			fov = 0.0f;
		}

		Camera(const float &fov) noexcept
		{
			position = glm::vec3(0.0f);
			this->fov = fov;
		}

	public:
		glm::vec3 getPosition() const noexcept
		{
			return position;
		}
		void setPosition(const glm::vec3 &pos) noexcept
		{
			position = pos;
		}

		virtual void translate(const glm::vec3 &v) noexcept
		{
			position += v;
		}

		float getFieldOfView() const noexcept
		{
			return fov;
		}
	};


	class FPSCamera : public Camera
	{
	private:
		constexpr static const float mouseSensitivity = 0.2f;

	protected:
		float yaw;
		float pitch;
		glm::vec3 lookAt;
		glm::vec3 up;

	public:
		FPSCamera(const float &fov) noexcept
			: Camera(fov)
		{
			up = glm::vec3(0.0f, 1.0f, 0.0f);
			yaw = 0.0f;
			pitch = 0.0f;
			onMouseMoved(0.0f, 0.0f);
		}

	public:
		void onMouseMoved(const float &xRel, const float &yRel) noexcept
		{
			yaw   += xRel * mouseSensitivity;
			pitch -= yRel * mouseSensitivity;
			if (pitch > 89.9f)
				pitch = 89.9f;
			if (pitch < -89.9f)
				pitch = -89.9f;

			glm::vec3 front{};
			front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
			front.y = sin(glm::radians(pitch));
			front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
			lookAt = glm::normalize(front);
		}

		void moveFront(const float &amount) noexcept
		{
			translate(glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f) * lookAt) * amount);
		}

		glm::vec3 getMoveFrontVector(const float &amount) const noexcept
		{
			return glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f) * lookAt) * amount;
		}

		void moveSideways(const float &amount) noexcept
		{
			translate(glm::normalize(glm::cross(lookAt, up)) * amount);
		}

		glm::vec3 getMoveSidewaysVector() const noexcept
		{
			return glm::normalize(glm::cross(lookAt, up));
		}

		glm::vec3 getLookAt() const noexcept
		{
			return lookAt;
		}
	};

	class FloatingCamera : public FPSCamera
	{
	public:
		FloatingCamera(const float &fov) noexcept
			: FPSCamera(fov)
		{
		}

		void moveUp(const float &fAmount) noexcept
		{
			translate(up * fAmount);
		}

		glm::vec3 getMoveUpVector(const float &fAmount) noexcept
		{
			return up * fAmount;
		}
	};
}