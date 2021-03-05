#include "Engine/Engine.h"
#include "Engine/Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "RaytracingShader.h"
#include <vector>

class Game : public Engine::PixelEngine
{
private:
	Engine::FloatingCamera camera = Engine::FloatingCamera(90.0f);
	std::vector<GameObject> vObjects;
	std::vector<PointLight> vLights;
	std::vector<Circle> vCircles;
	RaytracingShader *shader;
	Engine::VertexBufferColor *m_vertBuffer;

public:
	Game()
	{
		m_sAppName = "Test";
	}

public:
	bool OnUserCreate() noexcept override
	{
		vObjects.push_back(GameObject({    1.0f,   0.0f,    0.0f }, {   0.1f,  0.1f,   0.1f }, { 1.0f, 1.0f, 1.0f }, 0.5f));
		vObjects.push_back(GameObject({    0.0f,   0.0f,    0.0f }, {   0.1f,  0.1f,   0.1f }, { 1.0f, 1.0f, 1.0f }, 0.5f));
		vObjects.push_back(GameObject({ -100.0f, -0.01f, -100.0f }, { 200.0f, 0.01f, 200.0f }, { 1.0f, 1.0f, 1.0f }, 0.0f));
		
		vLights.push_back(PointLight({ 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f }, 5.0f));
		vLights.push_back(PointLight({ 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 1.0f }, 5.0f));
		
		//vCircles.push_back(Circle({ 0.0f, 0.1f, 0.2f }, { 1.0f, 0.843f, 0.0f }, 0.075f, 0.75f));
		for (int i = 0; i < 50; i++)
		{
			vCircles.push_back(Circle({ randomf(-1.0f, 1.0f), randomf(0.0f, 2.0f), randomf(-1.0f, 1.0f) }, { 1.0f, 0.843f, 0.0f }, randomf(0.025f, 0.1f), 1.0f));
		}
		
		camera.setPosition(glm::vec3(0.0f, 0.2f, 0.0f));

		shader = new RaytracingShader("Raytracing", m_vScreenSize);

		Engine::Vertex2DC vertices[] =
		{
			{ -1.0f, -1.0f, },
			{ -1.0f,  1.0f, },
			{  1.0f, -1.0f, },
			{ -1.0f,  1.0f, },
			{  1.0f, -1.0f, },
			{  1.0f,  1.0f, }
		};
		m_vertBuffer = new Engine::VertexBufferColor(vertices, 6);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) noexcept override
	{
		Clear(Engine::BLACK);

		if (GetHideMouseStatus())
			camera.onMouseMoved(-GetRelativeMouseX(), GetRelativeMouseY());

		if (GetKey(Engine::Key::W).bHeld)
			camera.moveFront(fElapsedTime);
		if (GetKey(Engine::Key::S).bHeld)
			camera.moveFront(-fElapsedTime);
		if (GetKey(Engine::Key::A).bHeld)
			camera.moveSideways(fElapsedTime);
		if (GetKey(Engine::Key::D).bHeld)
			camera.moveSideways(-fElapsedTime);
		if (GetKey(Engine::Key::SPACE).bHeld)
			camera.moveUp(fElapsedTime);
		if (GetKey(Engine::Key::LSHIFT).bHeld)
			camera.moveUp(-fElapsedTime);

		if (GetKey(Engine::Key::MOUSE_LEFT).bPressed)
			HideMouse(true);
		if (GetKey(Engine::Key::ESCAPE).bPressed)
			HideMouse(false);

		Engine::vf3d lookAt = camera.getLookAt();
		Engine::vf3d up = Engine::vf3d(0.0f, 1.0f, 0.0f);
		Engine::vf3d sideWays = lookAt.cross(up).norm();
		Engine::vf3d lookAtUp = sideWays.cross(lookAt).norm();

		shader->bind();
		shader->update(camera.getPosition(), camera.getLookAt(), camera.getFieldOfView(), vObjects, vLights, vCircles);
		m_vertBuffer->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		return true;
	}

	bool OnUserDestroy() noexcept override
	{
		return true;
	}
};

int main()
{
	Game game;
	if (game.Construct(Engine::vu2d(1280, 720), Engine::FullscreenMode::WINDOWED, Engine::RefreshRate::REFRESH_RATE_UNLIMITED))
		game.Start();
}
