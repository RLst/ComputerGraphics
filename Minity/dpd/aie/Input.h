#pragma once

#include <vector>
#include <functional>
#include <map>

struct GLFWwindow;

namespace pkr {

// a giant list of input codes for keyboard and mouse
enum KeyCode : int {	//This gets too tricky if I try to make this a enum class and enforce having to write KeyCode::A etc
	//Keyboard
	Unknown				= -1,
	Space				= 32,
	Apostrophe			= 39,
	Comma				= 44,
	Minus				= 45,
	Period				= 46,
	Slash				= 47,
	Alpha0				= 48,
	Alpha1				= 49,
	Alpha2				= 50,
	Alpha3				= 51,
	Alpha4				= 52,
	Alpha5				= 53,
	Alpha6				= 54,
	Alpha7				= 55,
	Alpha8				= 56,
	Alpha9				= 57,
	Semicolon			= 59,
	Equals				= 61,
	A					= 65,
	B					= 66,
	C					= 67,
	D					= 68,
	E					= 69,
	F					= 70,
	G					= 71,
	H					= 72,
	I					= 73,
	J					= 74,
	K					= 75,
	L					= 76,
	M					= 77,
	N					= 78,
	O					= 79,
	P					= 80,
	Q					= 81,
	R					= 82,
	S					= 83,
	T					= 84,
	U					= 85,
	V					= 86,
	W					= 87,
	X					= 88,
	Y					= 89,
	Z					= 90,
	LeftBracket			= 91,
	BackSlash			= 92,
	RightBracket		= 93,
	GraveAccent			= 96,
	Escape				= 256,
	Enter				= 257,
	Tab					= 258,
	BackSpace			= 259,
	Insert				= 260,
	Delete				= 261,
	RightArrow			= 262,
	LeftArrow			= 263,
	DownArrow			= 264,
	UpArrow				= 265,
	PageUp				= 266,
	PageDown			= 267,
	Home				= 268,
	End					= 269,
	CapsLock			= 280,
	ScrollLock			= 281,
	NumLock				= 282,
	PrintScreen			= 283,
	Pause				= 284,
	F1					= 290,
	F2					= 291,
	F3					= 292,
	F4					= 293,
	F5					= 294,
	F6					= 295,
	F7					= 296,
	F8					= 297,
	F9					= 298,
	F10					= 299,
	F11					= 300,
	F12					= 301,
	F13					= 302,
	F14					= 303,
	F15					= 304,
	F16					= 305,
	F17					= 306,
	F18					= 307,
	F19					= 308,
	F20					= 309,
	F21					= 310,
	F22					= 311,
	F23					= 312,
	F24					= 313,
	F25					= 314,
	Keypad0				= 320,
	Keypad1				= 321,
	Keypad2				= 322,
	Keypad3				= 323,
	Keypad4				= 324,
	Keypad5				= 325,
	Keypad6				= 326,
	Keypad7				= 327,
	Keypad8				= 328,
	Keypad9				= 329,
	KeypadPeriod		= 330,
	KeypadDivide		= 331,
	KeypadMultiply		= 332,
	KeypadMinus			= 333,
	KeypadPlus			= 334,
	KeypadEnter			= 335,
	KeypadEquals		= 336,
	LeftShift			= 340,
	LeftControl			= 341,
	LeftAlt				= 342,
	RightShift			= 344,
	RightControl		= 345,
	RightAlt			= 346,

	//Mouse
	Mouse0				= 0,
	Mouse1				= 1,
	Mouse2				= 2,
	Mouse3				= 3,
	Mouse4				= 4,
	Mouse5				= 5,
	Mouse6				= 6,
	Mouse7				= 7,

	//Joystick
	JoystickButton0		= 0,
	JoystickButton1		= 1,
	JoystickButton2		= 2,
	JoystickButton3		= 3,
	JoystickButton4		= 4,
	JoystickButton5		= 5,
	JoystickButton6		= 6,
	JoystickButton7		= 7,
	JoystickButton8		= 8,
	JoystickButton9		= 9,
	JoystickButton10	= 10,
	JoystickButton11	= 11,
	JoystickButton12	= 12,
	JoystickButton13	= 13,
	JoystickButton14	= 14,
	JoystickButton15	= 15,
	JoystickButton16	= 16,
};

// a singleton class that manages Input from the keyboard and mouse
class Input 
{
	// just giving the Application class access to the Input singleton
	friend class App;
	friend class Core;
public:

	// returns access to the singleton instance
	static Input* getInstance() { return m_instance;  }

	//Like Unity
	bool GetKeyDown(int inputKeyID);
	bool GetKeyUp(int binputKeyID);

	// query the keyboard state
	bool isKeyDown(int inputKeyID);
	bool isKeyUp(int inputKeyID);

	// returns true if the key was pressed / released this frame
	bool wasKeyPressed(int inputKeyID);
	bool wasKeyReleased(int inputKeyID);

	// returns access to all keys that are currently pressed
	const std::vector<int>& getPressedKeys() const;
	const std::vector<unsigned int>& getPressedCharacters() const;

	// query the mouse button state
	bool isMouseButtonDown(int inputMouseID);
	bool isMouseButtonUp(int inputMouseID);

	// returns true if the button was pressed / released this frame
	bool wasMouseButtonPressed(int inputMouseID);
	bool wasMouseButtonReleased(int inputMouseID);

	// query the mouse position
	int getMouseX();
	int getMouseY();
	void getMouseXY(int* x, int* y);

	// query mouse movement
	int getMouseDeltaX();
	int getMouseDeltaY();
	void getMouseDelta(int* x, int* y);

	// query how far the mouse wheel has been moved 
	double getMouseScroll();

	// delgates for attaching input observers to the Input class
	typedef std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)> KeyCallback;
	typedef std::function<void(GLFWwindow* window, unsigned int character)> CharCallback;
	typedef std::function<void(GLFWwindow* window, int button, int action, int mods)> MouseButtonCallback;
	typedef std::function<void(GLFWwindow* window, double xoffset, double yoffset)> MouseScrollCallback;
	typedef std::function<void(GLFWwindow* window, double x, double y)> MouseMoveCallback;

	// functions for attaching input observers
	void attachKeyObserver(const KeyCallback& callback) { m_keyCallbacks.push_back(callback); }
	void attachCharObserver(const CharCallback& callback) { m_charCallbacks.push_back(callback); }
	void attachMouseButtonObserver(const MouseButtonCallback& callback) { m_mouseButtonCallbacks.push_back(callback); }
	void attachMouseMoveObserver(const MouseMoveCallback& callback) { m_mouseMoveCallbacks.push_back(callback); }
	void attachMouseScrollObserver(const MouseScrollCallback& callback) { m_mouseScrollCallbacks.push_back(callback); }

protected:

	// singleton pointer
	static Input* m_instance;

	// only want the Application class to be able to create / destroy
	static void create()			{ m_instance = new Input(); }
	static void destroy()			{ delete m_instance; }

	// should be called once by the application each frame after the current update
	// or before glfwPollEvents
	void clearStatus();

private:

	// constructor private for singleton
	Input();
	~Input();

	std::vector<int>			m_pressedKeys;
	std::vector<unsigned int>	m_pressedCharacters;
		
	int		m_mouseX;
	int		m_mouseY;
	int		m_oldMouseX;
	int		m_oldMouseY;
	double	m_mouseScroll;

	bool	m_firstMouseMove;	// flag for first mouse input after start or mouse entering window

	void onMouseMove(int newXPos, int newYPos);
	
	std::vector<KeyCallback>			m_keyCallbacks;
	std::vector<CharCallback>			m_charCallbacks;
	std::vector<MouseMoveCallback>		m_mouseMoveCallbacks;
	std::vector<MouseButtonCallback>	m_mouseButtonCallbacks;
	std::vector<MouseScrollCallback>	m_mouseScrollCallbacks;

	// used to track down/up/released/pressed
	int* m_lastKeys, *m_currentKeys;
	int m_lastButtons[8], m_currentButtons[8];
};

} // namespace aie