#pragma once
#include <string>
#include "Engine/Shader.h"

class RaytracingShader
{
public:
	static constexpr const int nMaxEntities = 100;

private:
	Engine::Shader *shader;
	int m_nPositionLocation, m_nLookAtLocation, m_nSideWaysLocation, m_nLookAtUpLocation;
	int m_nObjectsLocation, m_nLightsLocation, m_nFovLocation, m_nCirclesLocation;

public:
	RaytracingShader(const std::string &sFilename, const Engine::vf2d &screenSize) noexcept
	{
		shader = new Engine::Shader(sFilename + ".vert", sFilename + ".frag");
		shader->bind();

		m_nFovLocation      = shader->getUniformLocation("u_fFovHalf");
		m_nPositionLocation = shader->getUniformLocation("u_pos");
		m_nLookAtLocation   = shader->getUniformLocation("u_lookAt");
		m_nSideWaysLocation = shader->getUniformLocation("u_sideWays");
		m_nLookAtUpLocation = shader->getUniformLocation("u_lookAtUp");
		m_nObjectsLocation  = shader->getUniformLocation("u_nObjects");
		m_nLightsLocation   = shader->getUniformLocation("u_nLights");
		m_nCirclesLocation  = shader->getUniformLocation("u_nCircles");

		glUniform2f(shader->getUniformLocation("u_screenSize"), screenSize.x, screenSize.y);
	}

public:
	void bind() const noexcept
	{
		shader->bind();
	}

	void unbind() const noexcept
	{
		shader->unbind();
	}

	void update(const Engine::vf3d &cameraPosition, const Engine::vf3d &cameraLookAt, const float &fov, const std::vector<GameObject> &gameObjects, const std::vector<PointLight> &lights, const std::vector<Circle> &circles) const noexcept
	{
		Engine::vf3d up = Engine::vf3d(0.0f, 1.0f, 0.0f);
		Engine::vf3d sideWays = cameraLookAt.cross(up).norm();
		Engine::vf3d lookAtUp = sideWays.cross(cameraLookAt).norm();

		shader->bind();

		glUniform1f(m_nFovLocation, glm::radians(0.5f * fov));
		glUniform3f(m_nPositionLocation, cameraPosition.x, cameraPosition.y, cameraPosition.z);
		glUniform3f(m_nLookAtLocation,   cameraLookAt.x,   cameraLookAt.y,   cameraLookAt.z);
		glUniform3f(m_nSideWaysLocation, sideWays.x,       sideWays.y,       sideWays.z);
		glUniform3f(m_nLookAtUpLocation, lookAtUp.x,       lookAtUp.y,       lookAtUp.z);

		int nObjects = std::min((int)gameObjects.size(), nMaxEntities);
		glUniform1i(m_nObjectsLocation, nObjects);

		for (std::size_t i = 0; i < nObjects; i++)
		{
			const GameObject &object = gameObjects.at(i);
			std::string sUniformNameBase = "u_objects[" + std::to_string(i) + "].";

			glUniform3f(shader->getUniformLocation(sUniformNameBase + "pos"),   object.pos.x,   object.pos.y,   object.pos.z);
			glUniform3f(shader->getUniformLocation(sUniformNameBase + "size"),  object.size.x,  object.size.y,  object.size.z);
			glUniform3f(shader->getUniformLocation(sUniformNameBase + "color"), object.color.x, object.color.y, object.color.z);
			glUniform1f(shader->getUniformLocation(sUniformNameBase + "fReflectiveIndex"), object.fReflectiveIndex);
		}
		
		int nLights = std::min((int)lights.size(), nMaxEntities);
		glUniform1i(m_nLightsLocation, nLights);
		
		for (std::size_t i = 0; i < nLights; i++)
		{
			const PointLight &light = lights.at(i);
			std::string sUniformNameBase = "u_lights[" + std::to_string(i) + "].";

			glUniform3f(shader->getUniformLocation(sUniformNameBase + "pos"),   light.pos.x,   light.pos.y,   light.pos.z);
			glUniform3f(shader->getUniformLocation(sUniformNameBase + "color"), light.color.x, light.color.y, light.color.z);
			glUniform1f(shader->getUniformLocation(sUniformNameBase + "fStrength"), light.fStrength);
		}

		int nCircles = std::min((int)circles.size(), nMaxEntities);
		glUniform1i(m_nCirclesLocation, nCircles);

		for (std::size_t i = 0; i < nCircles; i++)
		{
			const Circle &circle = circles.at(i);
			std::string sUniformNameBase = "u_circles[" + std::to_string(i) + "].";

			glUniform3f(shader->getUniformLocation(sUniformNameBase + "middle"),  circle.pos.x,   circle.pos.y,   circle.pos.z);
			glUniform3f(shader->getUniformLocation(sUniformNameBase + "color"),   circle.color.x, circle.color.y, circle.color.z);
			glUniform1f(shader->getUniformLocation(sUniformNameBase + "fRadius"), circle.fRadius);
			glUniform1f(shader->getUniformLocation(sUniformNameBase + "fReflectiveIndex"), circle.fReflectiveIndex);
		}
	}
};
