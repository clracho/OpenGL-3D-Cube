#include <Cube3D/Input/InputSystem.h>
#include <Windows.h>
InputSystem* InputSystem::m_system=nullptr;


InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
    InputSystem::m_system = nullptr;
}

void InputSystem::update()
{
    POINT current_mouse_pos = {};
    ::GetCursorPos(&current_mouse_pos);
    
    if (m_first_time)
    {
        m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
        m_first_time = false;
    }

    // check if mouse position changed:
    if (current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y)
    {
        // mouse move event
        // notify all listeners

        std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.begin();

        while (it != m_map_listeners.end())
        {
            it->second->onMouseMove(Point(current_mouse_pos.x, current_mouse_pos.y));
            ++it;
        }
    }
    m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

    if (::GetKeyboardState(m_keys_state))
    {
        for (unsigned int i = 0; i < 256; i++)
        {
            // KEY IS DOWN
            if (m_keys_state[i] & 0x80)
            {
                std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.begin();
          
                while (it != m_map_listeners.end())
                {
                    if (i == VK_LBUTTON)
                    {
                        // check if previous state different than current one
                        if (m_keys_state[i] != m_old_keys_state[i])
                            it->second->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
                    }
                    else if (i == VK_RBUTTON)
                    {
                        // check if previous state different than current one
                        if (m_keys_state[i] != m_old_keys_state[i])
                            it->second->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
                    }
                    else
                        it->second->onKeyDown(i);

                    ++it;
                }

            }
            else // KEY IS UP
            {
                if (m_keys_state[i] != m_old_keys_state[i])
                {
                    std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.begin();

                    while (it != m_map_listeners.end())
                    {
                        if (i == VK_LBUTTON)
                            it->second->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
                        else if (i == VK_RBUTTON)
                            it->second->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
                        else
                            it->second->onKeyUp(i);
                        ++it;
                    }

                }
            }
        }
        // store current keys state to old keys state buffer
        ::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
    }
}

void InputSystem::addListener(InputListener* listener)
{
    // add listener to our map
    m_map_listeners.insert(std::make_pair< InputListener*, InputListener*>
        (std::forward< InputListener*>(listener), std::forward< InputListener*>(listener)));
}

void InputSystem::removeListener(InputListener* listener)
{
    std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.find(listener);

    if (it != m_map_listeners.end())
    {
        m_map_listeners.erase(it);
    }
}

void InputSystem::setCursorPosition(const Point& pos)
{
    ::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::showCursor(bool show)
{
    ::ShowCursor(show);
}

InputSystem* InputSystem::get()
{
    static InputSystem system;
    return &system;
}

void InputSystem::create()
{
    if (InputSystem::m_system) throw std::exception("Input System already created");
    InputSystem::m_system = new InputSystem();
}

void InputSystem::release()
{
    if (!InputSystem::m_system) return;
    delete InputSystem::m_system;
}
