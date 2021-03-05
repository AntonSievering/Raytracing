#pragma once
#include <string>
#include "Engine/Shader.h"
#include "Texture1D.h"

class RaytracingShader
{
public:
	static constexpr const int nMaxEntities = 100;

private:
	Engine::Shader *shader;
	int m_nPositionLocation, m_nLookAtLocation, m_nSideWaysLocation, m_nLookAtUpLocation;
	int m_nObjectsLocation, m_nLightsLocation, m_nFovLocation, m_nCirclesLocation;

	Texture1D *pAABBPosTexture, *pAABBSizeTexture, *pAABBMaterial1Texture, *pAABBMaterial2Texture;
	Texture1D *pCircleBoundsTexture, *pCircleMaterial1Texture, *pCircleMaterial2Texture;
	Texture1D *pPointLightPos, *pPointLightColor;

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

		float emptyData[4 * nMaxEntities]{};
		
		// AABB
		glActiveTexture(GL_TEXTURE0);
		pAABBPosTexture = new Texture1D(nMaxEntities, emptyData);
		glUniform1i(shader->getUniformLocation("u_AABBPos"), 0);
		glActiveTexture(GL_TEXTURE1);
		pAABBSizeTexture = new Texture1D(nMaxEntities, emptyData);
		glUniform1i(shader->getUniformLocation("u_AABBSize"), 1);
		glActiveTexture(GL_TEXTURE2);
		pAABBMaterial1Texture = new Texture1D(nMaxEntities, emptyData);
		glUniform1i(shader->getUniformLocation("u_AABBMaterial1"), 2);
		glActiveTexture(GL_TEXTURE3);
		pAABBMaterial2Texture = new Texture1D(nMaxEntities, emptyData);
		glUniform1i(shader->getUniformLocation("u_AABBMaterial2"), 3);

		// Circle
		glActiveTexture(GL_TEXTURE4);
		pCircleBoundsTexture = new Texture1D(nMaxEntities, emptyData);
		glUniform1i(shader->getUniformLocation("u_CircleBounds"), 4);
		glActiveTexture(GL_TEXTURE5);
		pCircleMaterial1Texture = new Texture1D(nMaxEntities, emptyData);
		glUniform1i(shader->getUniformLocation("u_CircleMaterial1"), 5);
		glActiveTexture(GL_TEXTURE6);
		pCircleMaterial2Texture = new Texture1D(nMaxEntities, emptyData);
		glUniform1i(shader->getUniformLocation("u_CircleMaterial2"), 6);

		// PointLight
		glActiveTexture(GL_TEXTURE7);
		pPointLightPos = new Texture1D(nMaxEntities, emptyData);
		glUniform1i(shader->getUniformLocation("u_lightPos"), 7);
		glActiveTexture(GL_TEXTURE8);
		pPointLightColor = new Texture1D(nMaxEntities, emptyData);
		glUniform1i(shader->getUniformLocation("u_lightColor"), 8);
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
		int nLights = std::min((int)lights.size(), nMaxEntities);
		glUniform1i(m_nLightsLocation, nLights);
		int nCircles = std::min((int)circles.size(), nMaxEntities);
		glUniform1i(m_nCirclesLocation, nCircles);

		float buffer[4 * nMaxEntities]{};
		
		for (int i = 0; i < nObjects; i++)
		{
			buffer[4 * i + 0] = gameObjects.at(i).pos.x;
			buffer[4 * i + 1] = gameObjects.at(i).pos.y;
			buffer[4 * i + 2] = gameObjects.at(i).pos.z;
		}
		glActiveTexture(GL_TEXTURE0);
		pAABBPosTexture->reupload(buffer);

		memset(buffer, 0, sizeof(buffer));
		for (int i = 0; i < nObjects; i++)
		{
			buffer[4 * i + 0] = gameObjects.at(i).size.x;
			buffer[4 * i + 1] = gameObjects.at(i).size.y;
			buffer[4 * i + 2] = gameObjects.at(i).size.z;
		}
		glActiveTexture(GL_TEXTURE1);
		pAABBSizeTexture->reupload(buffer);

		memset(buffer, 0, sizeof(buffer));
		for (int i = 0; i < nObjects; i++)
		{
			buffer[4 * i + 0] = gameObjects.at(i).color.x;
			buffer[4 * i + 1] = gameObjects.at(i).color.y;
			buffer[4 * i + 2] = gameObjects.at(i).color.z;
		}

		glActiveTexture(GL_TEXTURE2);
		pAABBMaterial1Texture->reupload(buffer);

		memset(buffer, 0, sizeof(buffer));
		for (int i = 0; i < nObjects; i++)
		{
			buffer[4 * i + 3] = gameObjects.at(i).fReflectiveIndex;
		}
		glActiveTexture(GL_TEXTURE3);
		pAABBMaterial2Texture->reupload(buffer);



		memset(buffer, 0, sizeof(buffer));
		for (int i = 0; i < nCircles; i++)
		{
			buffer[4 * i + 0] = circles.at(i).pos.x;
			buffer[4 * i + 1] = circles.at(i).pos.y;
			buffer[4 * i + 2] = circles.at(i).pos.z;
			buffer[4 * i + 3] = circles.at(i).fRadius;
		}
		glActiveTexture(GL_TEXTURE4);
		pCircleBoundsTexture->reupload(buffer);

		memset(buffer, 0, sizeof(buffer));
		for (int i = 0; i < nCircles; i++)
		{
			buffer[4 * i + 0] = circles.at(i).color.x;
			buffer[4 * i + 1] = circles.at(i).color.y;
			buffer[4 * i + 2] = circles.at(i).color.z;
		}
		glActiveTexture(GL_TEXTURE5);
		pCircleMaterial1Texture->reupload(buffer);

		memset(buffer, 0, sizeof(buffer));
		for (int i = 0; i < nCircles; i++)
		{
			buffer[4 * i + 3] = circles.at(i).fReflectiveIndex;
		}
		glActiveTexture(GL_TEXTURE6);
		pCircleMaterial2Texture->reupload(buffer);



		memset(buffer, 0, sizeof(buffer));
		for (int i = 0; i < nLights; i++)
		{
			buffer[4 * i + 0] = lights.at(i).pos.x;
			buffer[4 * i + 1] = lights.at(i).pos.y;
			buffer[4 * i + 2] = lights.at(i).pos.z;
		}
		glActiveTexture(GL_TEXTURE7);
		pPointLightPos->reupload(buffer);

		memset(buffer, 0, sizeof(buffer));
		for (int i = 0; i < nLights; i++)
		{
			buffer[4 * i + 0] = lights.at(i).color.x;
			buffer[4 * i + 1] = lights.at(i).color.y;
			buffer[4 * i + 2] = lights.at(i).color.z;
			buffer[4 * i + 3] = lights.at(i).fStrength;
		}
		glActiveTexture(GL_TEXTURE8);
		pPointLightColor->reupload(buffer);
	}
};
