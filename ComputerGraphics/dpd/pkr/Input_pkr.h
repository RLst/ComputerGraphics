//Tony Le
//21 Mar 2019

#pragma once

namespace Minity {

	enum KeyCode : int {	//This gets too tricky if I try to make this a enum class and enforce having to write KeyCode::A etc
		//Keyboard
		Unknown = -1,
		Space = 32,
		Apostrophe = 39,
		Comma = 44,
		Minus = 45,
		Period = 46,
		Slash = 47,
		Alpha0 = 48,
		Alpha1 = 49,
		Alpha2 = 50,
		Alpha3 = 51,
		Alpha4 = 52,
		Alpha5 = 53,
		Alpha6 = 54,
		Alpha7 = 55,
		Alpha8 = 56,
		Alpha9 = 57,
		Semicolon = 59,
		Equals = 61,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		LeftBracket = 91,
		BackSlash = 92,
		RightBracket = 93,
		GraveAccent = 96,
		Escape = 256,
		Enter = 257,
		Tab = 258,
		BackSpace = 259,
		Insert = 260,
		Delete = 261,
		RightArrow = 262,
		LeftArrow = 263,
		DownArrow = 264,
		UpArrow = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		Keypad0 = 320,
		Keypad1 = 321,
		Keypad2 = 322,
		Keypad3 = 323,
		Keypad4 = 324,
		Keypad5 = 325,
		Keypad6 = 326,
		Keypad7 = 327,
		Keypad8 = 328,
		Keypad9 = 329,
		KeypadPeriod = 330,
		KeypadDivide = 331,
		KeypadMultiply = 332,
		KeypadMinus = 333,
		KeypadPlus = 334,
		KeypadEnter = 335,
		KeypadEquals = 336,
		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,

		//Mouse
		Mouse0 = 0,
		Mouse1 = 1,
		Mouse2 = 2,
		Mouse3 = 3,
		Mouse4 = 4,
		Mouse5 = 5,
		Mouse6 = 6,
		Mouse7 = 7,

		//Joystick
		JoystickButton0 = 0,
		JoystickButton1 = 1,
		JoystickButton2 = 2,
		JoystickButton3 = 3,
		JoystickButton4 = 4,
		JoystickButton5 = 5,
		JoystickButton6 = 6,
		JoystickButton7 = 7,
		JoystickButton8 = 8,
		JoystickButton9 = 9,
		JoystickButton10 = 10,
		JoystickButton11 = 11,
		JoystickButton12 = 12,
		JoystickButton13 = 13,
		JoystickButton14 = 14,
		JoystickButton15 = 15,
		JoystickButton16 = 16,
	};

	class Input
	{
		friend class Core;	//App has full access
	private:
		//Static class only, cannot create an instance
		Input() = delete;
		~Input() = delete;

		static std::vector<int>				m_pressedKeys;
		static std::vector<unsigned int>	m_pressedCharacters;

		static int				m_mouseX;
		static int				m_mouseY;
		static int				m_oldMouseX;
		static int				m_oldMouseY;
		static double			m_mouseScroll;

		static bool				m_firstMouseMove;		//Flag for the first mouse input after start or mouse entering window

		static void				onMouseMove(int newXpos, int newYPos);

		static std::vector<KeyCallback>				m_keyCallbacks;
		static std::vector<CharCallback>			m_charCallbacks;
		static std::vector<MouseMoveCallback>		m_mouseMoveCallbacks;
		static std::vector<MouseButtonCallback>		m_mouseButtonCallbacks;
		static std::vector<MouseScrollCallback>		m_mouseScrollCallbacks;

	protected:

	public:


	};

}
