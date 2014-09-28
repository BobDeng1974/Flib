#include <FRONTIER/Window/Event.hpp>
#include <windows.h>

namespace fw
{
	/////////////////////////////////////////////////////////////
	unsigned int VKfromButton(Mouse::Button button)
	{
		if (button == Mouse::Left)   return VK_LBUTTON;
		if (button == Mouse::Right)  return VK_RBUTTON;
		if (button == Mouse::Middle) return VK_MBUTTON;
		
		return 0;
	}

	/////////////////////////////////////////////////////////////
	unsigned int VKfromKey(Keyboard::Key key)
	{
		if (key == Keyboard::Left)         return VK_LEFT;
		if (key == Keyboard::Right)        return VK_RIGHT;
		if (key == Keyboard::Down)         return VK_DOWN;
		if (key == Keyboard::Up)           return VK_UP;
		if (key == Keyboard::Escape)       return VK_ESCAPE;
		if (key == Keyboard::Enter)        return VK_RETURN;
		if (key == Keyboard::PrintScreen)  return VK_SNAPSHOT;
		if (key == Keyboard::ScrollLock)   return VK_SCROLL;
		if (key == Keyboard::PauseBreak)   return VK_PAUSE;
		if (key == Keyboard::Backspace)    return VK_BACK;
		if (key == Keyboard::Insert)       return VK_INSERT;
		if (key == Keyboard::Delete)       return VK_DELETE;
		if (key == Keyboard::Home)         return VK_HOME;
		if (key == Keyboard::End)          return VK_END;
		if (key == Keyboard::PageUp)       return VK_PRIOR;
		if (key == Keyboard::PageDown)     return VK_NEXT;
		if (key == Keyboard::Divide)       return VK_DIVIDE;
		if (key == Keyboard::Multiply)     return VK_MULTIPLY;
		if (key == Keyboard::Minus)        return VK_OEM_MINUS;
		if (key == Keyboard::Plus)         return VK_OEM_PLUS;
		if (key == Keyboard::Comma)        return VK_OEM_COMMA;
		if (key == Keyboard::Tab)          return VK_TAB;
		if (key == Keyboard::CapsLock)     return VK_CAPITAL;
		if (key == Keyboard::LShift)       return VK_LSHIFT;
		if (key == Keyboard::RShift)       return VK_RSHIFT;
		if (key == Keyboard::LCtrl)        return VK_LCONTROL;
		if (key == Keyboard::RCtrl)        return VK_RCONTROL;
		if (key == Keyboard::LWindows)     return VK_LWIN;
		if (key == Keyboard::RWindows)     return VK_RWIN;
		if (key == Keyboard::Print)        return VK_PRINT;
		if (key == Keyboard::LAlt)         return VK_LMENU;
		if (key == Keyboard::RAlt)         return VK_RMENU;
		if (key == Keyboard::Space)        return VK_SPACE;
		
		if (key>=Keyboard::Num0 && key<=Keyboard::Num9)
			return 0x30+(key-Keyboard::Num0);
			
		if (key>=Keyboard::Numpad0 && key<=Keyboard::Numpad9)
			return VK_NUMPAD0+(key-Keyboard::Numpad0);
			
		if (key>=Keyboard::F1 && key<=Keyboard::F12)
			return VK_F1+(key-Keyboard::F1);
			
		if (key>=Keyboard::A && key<=Keyboard::Z)
			return 0x41+(key-Keyboard::A);
		
		return 0;
	}
	
	/////////////////////////////////////////////////////////////
	bool Keyboard::isKeyHeld(Keyboard::Key code)
	{
		int VKcode = VKfromKey(code);
		if (!VKcode)
			return false;
		return GetAsyncKeyState(VKcode);
	}

	/////////////////////////////////////////////////////////////
	bool Mouse::isButtonHeld(Mouse::Button button)
	{
		int VKcode = VKfromButton(button);
		if (!VKcode)
			return false;
		return GetAsyncKeyState(VKcode);
	}
}