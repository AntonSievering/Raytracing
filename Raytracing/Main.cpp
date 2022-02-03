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
	
		for (int i = 0; i < 25; i++)
		{
			Engine::vf3d vec, colour;
			vec.x = 10.0f * randomf();
			vec.y = 10.0f * randomf() + 1.0f;
			vec.z = 10.0f * randomf();
			colour.x = 1.0f;
			colour.y = 0.8431f;
			colour.z = 0.0f;
			float radius = randomf();

			vCircles.push_back(Circle({ vec, colour, radius, 0.8f }));
		}

		vLights.push_back(PointLight({ 0.0f, 1.0f, 1.0f }, { 1.0f, 0.25f, 0.0f }, 5.0f));
		vLights.push_back(PointLight({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.25f, 1.0f }, 5.0f));
		
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

		shader->update(camera.getPosition(), camera.getLookAt(), camera.getFieldOfView(), vObjects, vLights, vCircles);
		m_vertBuffer->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glFlush();

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
