#pragma once
#include "InputListener.h"
#include <map>
#include <Windows.h>
#include <unordered_set>
#include <Cube3D/Math/Point.h>

class InputSystem
{
private:
	InputSystem();
	~InputSystem();
public:
	void update();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void setCursorPosition(const Point& pos);
	void showCursor(bool show);

public:
	static InputSystem* get();
	static void create();
	static void release();
private:
	// map object (container for listeners)
	// name: m_map_listeners
	// key and value type: InputListener*
	std::map<InputListener*, InputListener*> m_map_listeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	Point m_old_mouse_pos;
	bool m_first_time = true;
	static InputSystem* m_system;
};

