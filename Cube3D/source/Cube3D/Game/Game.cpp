
#include <Cube3D/Window/Window.h>
#include <Cube3D/Graphics/RenderSystem/GraphicsEngine.h>
#include <Cube3D/Game/Game.h>
#include <Cube3D/Graphics/RenderSystem/VertexArrayObject.h>
#include <Cube3D/Graphics/RenderSystem/ShaderProgram.h>
#include <Cube3D/Graphics/RenderSystem/UniformBuffer.h>
#include <Cube3D/Graphics/RenderSystem/GraphicsEngine.h>
#include <Cube3D/Graphics/RenderSystem/TexturingProgram.h>
#include <Cube3D/Math/OMat4.h>
#include <Cube3D/Math/OVec3.h>
#include <Cube3D/Math/OVec2.h>
#include <Cube3D/Input/InputSystem.h>

#include <stdio.h>

struct UniformData
{
	OMat4 world;
	OMat4 projection;
	int useColors;
};

struct Vertex
{
	OVec3 position;
	OVec2 color;
	OVec3 texcoord;
};


//constructor:
Game::Game()
{
	//executes when ogame object constructed
	
	m_graphicsEngine = std::make_unique<GraphicsEngine>();
	m_display = std::make_unique<Window>();

	m_display->makeCurrentContext();

	m_graphicsEngine->setViewport(m_display->getInnerSize());
}

//destructor:
Game::~Game()
{
}

//.onCreate() function
void Game::onCreate()
{
	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	m_world_cam.setTranslation(OVec3(0, 0, -1.0f));

	OVec3 positionsList[] =
	{
		//front face
		OVec3(-0.5f,-0.5f,-0.5f),
		OVec3(-0.5f,0.5f,-0.5f),
		OVec3(0.5f,0.5f,-0.5f),
		OVec3(0.5f,-0.5f,-0.5f),

		//back face
		OVec3(0.5f,-0.5f,0.5f),
		OVec3(0.5f,0.5f,0.5f),
		OVec3(-0.5f,0.5f,0.5f),
		OVec3(-0.5f,-0.5f,0.5f)

	};

	OVec3 colorsList[] =
	{
		OVec3(1.0f,0.0f,0.0f),
		OVec3(0.0f,1.0f,0.0f),
		OVec3(0.0f,0.0f,1.0f),
		OVec3(1.0f,1.0f,0.0f)
	};

	OVec2 texcoordsList[] =
	{
		OVec2(0.0f,0.0f),
		OVec2(0.0f,1.0f),
		OVec2(1.0f,0.0f),
		OVec2(1.0f,1.0f)
	};

	Vertex verticesList[] =
	{
		// for each vertex element, we define a face of the cube
		//front face
		{positionsList[0],texcoordsList[1],colorsList[1]},
		{positionsList[1],texcoordsList[0],colorsList[0]},
		{positionsList[2],texcoordsList[2],colorsList[2]},
		{positionsList[3],texcoordsList[3],colorsList[3]},
		//back face
		{positionsList[4],texcoordsList[1],colorsList[1]},
		{positionsList[5],texcoordsList[0],colorsList[0]},
		{positionsList[6],texcoordsList[2],colorsList[2]},
		{positionsList[7],texcoordsList[3],colorsList[3]},
		//top face
		{positionsList[1],texcoordsList[1],colorsList[1]},
		{positionsList[6],texcoordsList[0],colorsList[0]},
		{positionsList[5],texcoordsList[2],colorsList[2]},
		{positionsList[2],texcoordsList[3],colorsList[3]},
		//bottom face
		{positionsList[7],texcoordsList[1],colorsList[1]},
		{positionsList[0],texcoordsList[0],colorsList[0]},
		{positionsList[3],texcoordsList[2],colorsList[2]},
		{positionsList[4],texcoordsList[3],colorsList[3]},
		//right face
		{positionsList[3],texcoordsList[1],colorsList[1]},
		{positionsList[2],texcoordsList[0],colorsList[0]},
		{positionsList[5],texcoordsList[2],colorsList[2]},
		{positionsList[4],texcoordsList[3],colorsList[3]},
		//left face
		{positionsList[7],texcoordsList[1],colorsList[1]},
		{positionsList[6],texcoordsList[0],colorsList[0]},
		{positionsList[1],texcoordsList[2],colorsList[2]},
		{positionsList[0],texcoordsList[3],colorsList[3]}
	};

	ui32 indicesList[] =
	{
		//front
		0,1,2,
		2,3,0,

		//back
		4,5,6,
		6,7,4,

		//top
		8,9,10,
		10,11,8,

		//bottom
		12,13,14,
		14,15,12,

		//right
		16,17,18,
		18,19,16,

		//left
		20,21,22,
		22,23,20
	};

	VertexAttribute attribsList[] = {
		sizeof(OVec3)/sizeof(f32),  //position
		sizeof(OVec2)/sizeof(f32), //texcoord
		sizeof(OVec3)/sizeof(f32) //color
	};

	// inputs to createVertexArrayObject become OVertexBufferData struct
	m_polygonVAO = m_graphicsEngine->createVertexArrayObject({ 
		(void*)verticesList,
		sizeof(Vertex),
		sizeof(verticesList)/sizeof(Vertex),
		attribsList,
		sizeof(attribsList)/sizeof(VertexAttribute)
		},
		// also pass various element buffer's data through the createVertexArrayObject method
		{
			(void *) indicesList,
			sizeof(indicesList)
		}
	);

	m_uniform = m_graphicsEngine->createUniformBuffer({
		sizeof(UniformData)
		});

	m_shader = m_graphicsEngine->createShaderProgram(
		{ L"Assets/Shaders/Shaderfile.vert",
		L"Assets/Shaders/Shaderfile.frag"
		});

	m_texturing = m_graphicsEngine->createTexturingProgram({ "Assets/asset.jpg" });

	m_shader->setUniformBufferSlot("UniformData", 0); // "UniformData" defined in shader vert code | slot 0
}

void Game::onUpdateInternal()

{
	// update focus
	if (currentFocus != m_display->inFocus)
	{
		if (m_display->inFocus) {
			InputSystem::get()->addListener(this);
		}
		else {
			InputSystem::get()->removeListener(this);
		}
		currentFocus = m_display->inFocus;
	}
	
	// update inputs
	InputSystem::get()->update();

	//computing delta time
	auto currentTime = std::chrono::system_clock::now();
	auto elapsedSeconds = std::chrono::duration<double>();

	if (m_previousTime.time_since_epoch().count())
	elapsedSeconds = currentTime - m_previousTime;
	
	m_previousTime = currentTime;
	
	deltaTime = (f32)elapsedSeconds.count();

	onUpdate(deltaTime); // onUpdate for MyGame class


	m_scale += deltaTime;
	//auto currentScale = 1.5*abs(sin(m_scale*.66));
	//auto currentScale = m_scale;
	
	OMat4 world, projection, temp;

	//// rotational matrices

	temp.setIdentity();
	temp.setRotationZ(1.5 * sin(m_scale) * autoRotateCube);
	world *= temp; // multiply as defined in Mat4

	temp.setIdentity();
	temp.setRotationY(1.5 * sin(1 + m_scale) * autoRotateCube + m_rot_y);
	world *= temp; // multiply as defined in Mat4

	temp.setIdentity();
	temp.setRotationX(1.5 * sin(2 + m_scale) * autoRotateCube + m_rot_x);
	world *= temp; // multiply as defined in Mat4

	//// translation matrix

	temp.setIdentity();
	temp.setTranslation(OVec3(0, 0, 2));
	world *= temp; // multiply as defined in Mat4

	//// projection matrix
	//// 0.004f allows for zooming
	//// multiplied in Shader file

	auto displaySize = m_display->getInnerSize();
	//projection.setOrthoLH(displaySize.width * 0.004f, displaySize.height * 0.004f, 0.01f, 100.0f);
	projection.setPerspectiveFovLH(1.57f, ((f32) displaySize.width / (f32) displaySize.height), 0.1f, 100.0f);

	//world.setIdentity();

	OMat4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	// scaling matrix

	temp.setIdentity();
	temp.setScale(OVec3(m_scale_cube, m_scale_cube, m_scale_cube));
	world_cam *= temp; // multiply as defined in Mat4

	temp.setIdentity();
	temp.setScale(OVec3(3 * m_scale_cube, 3 * m_scale_cube, 3 * m_scale_cube));
	world *= temp; // multiply as defined in Mat4

	// first calculate new position in z axis
	OVec3 new_pos = m_world_cam.getTranslation() + (world_cam.getZDirection() * deltaTime * 10.0f * m_forward * movingCamera);
	// second calculate new position in x axis, add to last calculation
	new_pos = new_pos + (world_cam.getXDirection() * deltaTime * 10.0f * m_rightward * movingCamera);
	// apply new position
	world_cam.setTranslation(new_pos);
	m_world_cam = world_cam;

	world_cam.inverse();
	
	

	// depending on control, allow movements with WASD
	UniformData data = { world, projection, useColors };
	if (movingCamera == 1) {
		data = { world_cam, projection, useColors };
	}
	else {
		data = { world, projection, useColors };
	}
	
	m_uniform->setData(&data);
	
	
	m_graphicsEngine->clear(OVec4(0, 0, 0, 1));

	m_graphicsEngine->setFaceCulling(CullType::BackFace);
	m_graphicsEngine->setWindingOrder(WindingOrder::ClockWise);

	// bind VAO of triangle to graphics pipeline:
	m_graphicsEngine->setVertexArrayObject(m_polygonVAO);

	m_graphicsEngine->setUniformBuffer(m_uniform, 0);

	m_graphicsEngine->setShaderProgram(m_shader);

	// draw triangles with 3 as vertices and 0 as offset.
	m_graphicsEngine->drawIndexedTriangles(TriangleType::TriangleList, 36);

	m_display->present(false);
}

void Game::onKeyDown(int key)
{
	if (key == 'W'|| key == 38)
	{
		//m_rot_x += 6.0f * deltaTime;
		m_forward = 1.0f;
	}
	else if (key == 'S' || key == 40)
	{
		//m_rot_x -= 6.0f * deltaTime;
		m_forward = -1.0f;
	}
	else if (key == 'A' || key == 37)
	{
		//m_rot_y += 6.0f * deltaTime;;
		m_rightward = -1.0f;
	}
	else if (key == 'D' || key == 39)
	{
		//m_rot_y -= 6.0f * deltaTime;
		m_rightward = 1.0f;
	}
	else if (key == 16)
	{
		if (movingCamera == 0)
		{
			movingCamera = 1;
			m_rot_x = 0;
			m_rot_y = 0;
		}
	}
	else if (key == 27)
	{
		quit();
	}
}

void Game::onKeyUp(int key)
{
	if (key == 'W' || key == 38 || key == 'S' || key == 40 || key == 'A' || key == 37 || key == 'D' || key == 39)
	{
		m_forward = 0.0f;
		m_rightward = 0.0f;
	}
	else if (key == 32)
	{
		if (autoRotateCube == 1) autoRotateCube = 0;
		else if (autoRotateCube == 0) autoRotateCube = 1;
	}
	else if (key == 16)
	{
		movingCamera = 0;
		m_rot_x = 0;
		m_rot_y = 0;
	}
	else if (key == 'C')
	{
		if (useColors == 1) useColors = 0;
		else if (useColors == 0) useColors = 1;
		std::cout << "COLOR SHIFT" << std::endl;
	}
}

void Game::onMouseMove(const Point& mouse_pos)
{
	auto displaySize = m_display->getInnerSize();
	
	m_rot_x += (mouse_pos.m_y - (displaySize.height / 2.0f))* 0.005f;
	m_rot_y += (mouse_pos.m_x - (displaySize.width / 2.0f)) * 0.005f;

	InputSystem::get()->setCursorPosition(Point((displaySize.width / 2.0f), (displaySize.height / 2.0f)));
}

void Game::onLeftMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 5.0f;
}

void Game::onLeftMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}

void Game::onRightMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 0.20f;
}

void Game::onRightMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}

void Game::onQuit()
{
}

void Game::quit()
{
	m_display->~Window();
	m_isRunning = false;
}

