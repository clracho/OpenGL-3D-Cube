#pragma once
#include <Cube3D/Prerequisites.h>
#include <Cube3D/Input/InputListener.h>
#include <Cube3D/Window/Window.h>
#include <Cube3D/Math/OMat4.h>
#include <memory>
#include <chrono>

class GraphicsEngine;
//class OWindow;
class Game: public InputListener//, public OWindow
{
public:
	Game();
	virtual ~Game();

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

	void run();
	void quit();

protected:
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime) {}
	virtual void onQuit();
private:
	void onUpdateInternal();
protected:
	bool m_isRunning = true;
	std::unique_ptr<GraphicsEngine> m_graphicsEngine;

	// smart pointer
	std::unique_ptr<Window> m_display;

	// create triangle VAO (vertex array objects)
	VertexArrayObjectPtr m_polygonVAO;

	// attribute for ouniformbuffer
	UniformBufferPtr m_uniform;

	// attribute for shader program
	ShaderProgramPtr m_shader;

	// attribute for texturing program
	TexturingProgramPtr m_texturing;

	std::chrono::system_clock::time_point m_previousTime;
	f32 m_scale = 0;
private:
	bool currentFocus = true;

	ui32 movingCamera = 0;
	ui32 autoRotateCube = 0;
	int useColors = 1;

	f32 deltaTime = 0.0001f;

	f32 m_rot_x=0.0f;
	f32 m_rot_y = 0.0f;

	f32 m_scale_cube = 1;

	f32 m_forward = 0.0f;
	f32 m_rightward = 0.0f;
	OMat4 m_world_cam;
};

