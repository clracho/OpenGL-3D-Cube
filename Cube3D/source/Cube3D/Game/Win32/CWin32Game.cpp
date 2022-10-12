#include <Cube3D/Window/Window.h>
#include <Cube3D/Graphics/RenderSystem/GraphicsEngine.h>
#include <Cube3D/Game/Game.h>
#include <Windows.h>


void Game::run()
{
	onCreate();

	MSG msg;
	// runs while is_Running true and window <<not>> closed
	while (m_isRunning)
	{
		msg = {};
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				m_isRunning = false;
				continue;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		onUpdateInternal();
	}

	onQuit();
}
