/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

#include <bitset>
#include <format>
#include <iostream>
#include <string>
#include <string_view>

#include <windows.h>

using namespace std::literals;

enum class event
{
	key,
	mouse,
	size,
	menu,
	focus,

	unknown
};

static constexpr wchar_t const* EventNames[]
{
	L"key",
	L"mouse",
	L"size",
	L"menu",
	L"focus",

	L"unknown",
};

static_assert(std::size(EventNames) == std::to_underlying(event::unknown) + 1);

static constexpr std::wstring_view VKeyNames[]
{
	L"NULL"sv,
	L"VK_LBUTTON"sv,
	L"VK_RBUTTON"sv,
	L"VK_CANCEL"sv,
	L"VK_MBUTTON"sv,
	L"VK_XBUTTON1"sv,
	L"VK_XBUTTON2"sv,
	L"reserved"sv,
	L"VK_BACK"sv,
	L"VK_TAB"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"VK_CLEAR"sv,
	L"VK_RETURN"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"VK_SHIFT"sv,
	L"VK_CONTROL"sv,
	L"VK_MENU"sv,
	L"VK_PAUSE"sv,
	L"VK_CAPITAL"sv,
	L"VK_KANA/VK_HANGUL"sv,
	L"VK_IME_ON"sv,
	L"VK_JUNJA"sv,
	L"VK_FINAL"sv,
	L"VK_HANJA/VK_KANJI"sv,
	L"VK_IME_OFF"sv,
	L"VK_ESCAPE"sv,
	L"VK_CONVERT"sv,
	L"VK_NONCONVERT"sv,
	L"VK_ACCEPT"sv,
	L"VK_MODECHANGE"sv,
	L"VK_SPACE"sv,
	L"VK_PRIOR"sv,
	L"VK_NEXT"sv,
	L"VK_END"sv,
	L"VK_HOME"sv,
	L"VK_LEFT"sv,
	L"VK_UP"sv,
	L"VK_RIGHT"sv,
	L"VK_DOWN"sv,
	L"VK_SELECT"sv,
	L"VK_PRINT"sv,
	L"VK_EXECUTE"sv,
	L"VK_SNAPSHOT"sv,
	L"VK_INSERT"sv,
	L"VK_DELETE"sv,
	L"VK_HELP"sv,
	L"0"sv,
	L"1"sv,
	L"2"sv,
	L"3"sv,
	L"4"sv,
	L"5"sv,
	L"6"sv,
	L"7"sv,
	L"8"sv,
	L"9"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"A"sv,
	L"B"sv,
	L"C"sv,
	L"D"sv,
	L"E"sv,
	L"F"sv,
	L"G"sv,
	L"H"sv,
	L"I"sv,
	L"J"sv,
	L"K"sv,
	L"L"sv,
	L"M"sv,
	L"N"sv,
	L"O"sv,
	L"P"sv,
	L"Q"sv,
	L"R"sv,
	L"S"sv,
	L"T"sv,
	L"U"sv,
	L"V"sv,
	L"W"sv,
	L"X"sv,
	L"Y"sv,
	L"Z"sv,
	L"VK_LWIN"sv,
	L"VK_RWIN"sv,
	L"VK_APPS"sv,
	L"reserved"sv,
	L"VK_SLEEP"sv,
	L"VK_NUMPAD0"sv,
	L"VK_NUMPAD1"sv,
	L"VK_NUMPAD2"sv,
	L"VK_NUMPAD3"sv,
	L"VK_NUMPAD4"sv,
	L"VK_NUMPAD5"sv,
	L"VK_NUMPAD6"sv,
	L"VK_NUMPAD7"sv,
	L"VK_NUMPAD8"sv,
	L"VK_NUMPAD9"sv,
	L"VK_MULTIPLY"sv,
	L"VK_ADD"sv,
	L"VK_SEPARATOR"sv,
	L"VK_SUBTRACT"sv,
	L"VK_DECIMAL"sv,
	L"VK_DIVIDE"sv,
	L"VK_F1"sv,
	L"VK_F2"sv,
	L"VK_F3"sv,
	L"VK_F4"sv,
	L"VK_F5"sv,
	L"VK_F6"sv,
	L"VK_F7"sv,
	L"VK_F8"sv,
	L"VK_F9"sv,
	L"VK_F10"sv,
	L"VK_F11"sv,
	L"VK_F12"sv,
	L"VK_F13"sv,
	L"VK_F14"sv,
	L"VK_F15"sv,
	L"VK_F16"sv,
	L"VK_F17"sv,
	L"VK_F18"sv,
	L"VK_F19"sv,
	L"VK_F20"sv,
	L"VK_F21"sv,
	L"VK_F22"sv,
	L"VK_F23"sv,
	L"VK_F24"sv,
	L"VK_NAVIGATION_VIEW"sv,
	L"VK_NAVIGATION_MENU"sv,
	L"VK_NAVIGATION_UP"sv,
	L"VK_NAVIGATION_DOWN"sv,
	L"VK_NAVIGATION_LEFT"sv,
	L"VK_NAVIGATION_RIGHT"sv,
	L"VK_NAVIGATION_ACCEPT"sv,
	L"VK_NAVIGATION_CANCEL"sv,
	L"VK_NUMLOCK"sv,
	L"VK_SCROLL"sv,
	L"VK_OEM_FJ_JISHO/VK_OEM_NEC_EQUAL"sv,
	L"VK_OEM_FJ_MASSHOU"sv,
	L"VK_OEM_FJ_TOUROKU"sv,
	L"VK_OEM_FJ_LOYA"sv,
	L"VK_OEM_FJ_ROYA"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"VK_LSHIFT"sv,
	L"VK_RSHIFT"sv,
	L"VK_LCONTROL"sv,
	L"VK_RCONTROL"sv,
	L"VK_LMENU"sv,
	L"VK_RMENU"sv,
	L"VK_BROWSER_BACK"sv,
	L"VK_BROWSER_FORWARD"sv,
	L"VK_BROWSER_REFRESH"sv,
	L"VK_BROWSER_STOP"sv,
	L"VK_BROWSER_SEARCH"sv,
	L"VK_BROWSER_FAVORITES"sv,
	L"VK_BROWSER_HOME"sv,
	L"VK_VOLUME_MUTE"sv,
	L"VK_VOLUME_DOWN"sv,
	L"VK_VOLUME_UP"sv,
	L"VK_MEDIA_NEXT_TRACK"sv,
	L"VK_MEDIA_PREV_TRACK"sv,
	L"VK_MEDIA_STOP"sv,
	L"VK_MEDIA_PLAY_PAUSE"sv,
	L"VK_LAUNCH_MAIL"sv,
	L"VK_LAUNCH_MEDIA_SELECT"sv,
	L"VK_LAUNCH_APP1"sv,
	L"VK_LAUNCH_APP2"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"VK_OEM_1"sv,
	L"VK_OEM_PLUS"sv,
	L"VK_OEM_COMMA"sv,
	L"VK_OEM_MINUS"sv,
	L"VK_OEM_PERIOD"sv,
	L"VK_OEM_2"sv,
	L"VK_OEM_3"sv,
	L"reserved"sv,
	L"reserved"sv,
	L"VK_GAMEPAD_A"sv,
	L"VK_GAMEPAD_B"sv,
	L"VK_GAMEPAD_X"sv,
	L"VK_GAMEPAD_Y"sv,
	L"VK_GAMEPAD_RIGHT_SHOULDER"sv,
	L"VK_GAMEPAD_LEFT_SHOULDER"sv,
	L"VK_GAMEPAD_LEFT_TRIGGER"sv,
	L"VK_GAMEPAD_RIGHT_TRIGGER"sv,
	L"VK_GAMEPAD_DPAD_UP"sv,
	L"VK_GAMEPAD_DPAD_DOWN"sv,
	L"VK_GAMEPAD_DPAD_LEFT"sv,
	L"VK_GAMEPAD_DPAD_RIGHT"sv,
	L"VK_GAMEPAD_MENU"sv,
	L"VK_GAMEPAD_VIEW"sv,
	L"VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON"sv,
	L"VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON"sv,
	L"VK_GAMEPAD_LEFT_THUMBSTICK_UP"sv,
	L"VK_GAMEPAD_LEFT_THUMBSTICK_DOWN"sv,
	L"VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT"sv,
	L"VK_GAMEPAD_LEFT_THUMBSTICK_LEFT"sv,
	L"VK_GAMEPAD_RIGHT_THUMBSTICK_UP"sv,
	L"VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN"sv,
	L"VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT"sv,
	L"VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT"sv,
	L"VK_OEM_4"sv,
	L"VK_OEM_5"sv,
	L"VK_OEM_6"sv,
	L"VK_OEM_7"sv,
	L"VK_OEM_8"sv,
	L"reserved"sv,
	L"VK_OEM_AX"sv,
	L"VK_OEM_102"sv,
	L"VK_ICO_HELP"sv,
	L"VK_ICO_00"sv,
	L"VK_PROCESSKEY"sv,
	L"VK_ICO_CLEAR"sv,
	L"VK_PACKET"sv,
	L"reserved"sv,
	L"VK_OEM_RESET"sv,
	L"VK_OEM_JUMP"sv,
	L"VK_OEM_PA1"sv,
	L"VK_OEM_PA2"sv,
	L"VK_OEM_PA3"sv,
	L"VK_OEM_WSCTRL"sv,
	L"VK_OEM_CUSEL"sv,
	L"VK_OEM_ATTN"sv,
	L"VK_OEM_FINISH"sv,
	L"VK_OEM_COPY"sv,
	L"VK_OEM_AUTO"sv,
	L"VK_OEM_ENLW"sv,
	L"VK_OEM_BACKTAB"sv,
	L"VK_ATTN"sv,
	L"VK_CRSEL"sv,
	L"VK_EXSEL"sv,
	L"VK_EREOF"sv,
	L"VK_PLAY"sv,
	L"VK_ZOOM"sv,
	L"VK_NONAME"sv,
	L"VK_PA1"sv,
	L"VK_OEM_CLEAR"sv,
	L"reserved"sv,
};

static auto replace_control_character(wchar_t const Char)
{
	switch (Char)
	{
	// C0
	case L'\u0000': return L' '; // space
	case L'\u0001': return L'☺'; // white smiling face
	case L'\u0002': return L'☻'; // black smiling face
	case L'\u0003': return L'♥'; // black heart suit
	case L'\u0004': return L'♦'; // black diamond suit
	case L'\u0005': return L'♣'; // black club suit
	case L'\u0006': return L'♠'; // black spade suit
	case L'\u0007': return L'•'; // bullet
	case L'\u0008': return L'◘'; // inverse bullet
	case L'\u0009': return L'○'; // white circle
	case L'\u000A': return L'◙'; // inverse white circle
	case L'\u000B': return L'♂'; // male sign
	case L'\u000C': return L'♀'; // female sign
	case L'\u000D': return L'♪'; // eighth note
	case L'\u000E': return L'♫'; // beamed eighth notes
	case L'\u000F': return L'☼'; // white sun with rays
	case L'\u0010': return L'►'; // black right - pointing pointer
	case L'\u0011': return L'◄'; // black left - pointing pointer
	case L'\u0012': return L'↕'; // up down arrow
	case L'\u0013': return L'‼'; // double exclamation mark
	case L'\u0014': return L'¶'; // pilcrow sign
	case L'\u0015': return L'§'; // section sign
	case L'\u0016': return L'▬'; // black rectangle
	case L'\u0017': return L'↨'; // up down arrow with base
	case L'\u0018': return L'↑'; // upwards arrow
	case L'\u0019': return L'↓'; // downwards arrow
	case L'\u001A': return L'→'; // rightwards arrow
	case L'\u001B': return L'←'; // leftwards arrow
	case L'\u001C': return L'∟'; // right angle
	case L'\u001D': return L'↔'; // left right arrow
	case L'\u001E': return L'▲'; // black up - pointing triangle
	case L'\u001F': return L'▼'; // black down - pointing triangle
	case L'\u007F': return L'⌂'; // house

	// C1
	// These are considered control characters too now.
	// Unlike C0, it is unclear what glyphs to use, so just replace with FFFD for now.
	case L'\u0080':
	case L'\u0081':
	case L'\u0082':
	case L'\u0083':
	case L'\u0084':
	case L'\u0085':
	case L'\u0086':
	case L'\u0087':
	case L'\u0088':
	case L'\u0089':
	case L'\u008A':
	case L'\u008B':
	case L'\u008C':
	case L'\u008D':
	case L'\u008E':
	case L'\u008F':
	case L'\u0090':
	case L'\u0091':
	case L'\u0092':
	case L'\u0093':
	case L'\u0094':
	case L'\u0095':
	case L'\u0096':
	case L'\u0097':
	case L'\u0098':
	case L'\u0099':
	case L'\u009A':
	case L'\u009B':
	case L'\u009C':
	case L'\u009D':
	case L'\u009E':
	case L'\u009F': return L'�';

	default:        return Char;
	}
}

static auto decode_control_key_state(DWORD const ControlKeyState)
{
	return std::format(
		L"control=0x{:08X} [{}{}{}{}{}|{}|{}{}{}]"sv,
		ControlKeyState,
		ControlKeyState & LEFT_CTRL_PRESSED?  L'C':L'c',
		ControlKeyState & LEFT_ALT_PRESSED?   L'A':L'a',
		ControlKeyState & SHIFT_PRESSED?      L'S':L's',
		ControlKeyState & RIGHT_ALT_PRESSED?  L'A':L'a',
		ControlKeyState & RIGHT_CTRL_PRESSED? L'C':L'c',
		ControlKeyState & ENHANCED_KEY?       L'E':L'e',
		ControlKeyState & CAPSLOCK_ON?        L'C':L'c',
		ControlKeyState & NUMLOCK_ON?         L'N':L'n',
		ControlKeyState & SCROLLLOCK_ON?      L'S':L's'
	);
}

static void decode_key_event(INPUT_RECORD const& ir, std::wstring& Str)
{
	const auto& Event = ir.Event.KeyEvent;

	std::format_to(
		std::back_inserter(Str),
		L"{0}, count={1}, vk={2}/0x{3:02X}/{3}, scan=0x{4:02X}/{4}, char='{5}'/U+{6:04X}/{6}, {7}"sv,
		Event.bKeyDown? L'↓' : L'↑',
		Event.wRepeatCount,
		HIBYTE(Event.wVirtualKeyCode)? L"Unknown"sv : VKeyNames[LOBYTE(Event.wVirtualKeyCode)],
		Event.wVirtualKeyCode,
		Event.wVirtualScanCode,
		replace_control_character(Event.uChar.UnicodeChar),
		static_cast<unsigned short>(Event.uChar.UnicodeChar),
		decode_control_key_state(Event.dwControlKeyState)
	);
}

static auto wheel_direction(DWORD const ButtonState, DWORD const EventFlags)
{
	const auto Direction = static_cast<short>(HIWORD(ButtonState));

	if (EventFlags == MOUSE_WHEELED)
		return Direction > 0? L" ↑ "sv : L" ↓ "sv;

	if (EventFlags == MOUSE_HWHEELED)
		return Direction > 0? L" ← "sv : L" → "sv;

	return L""sv;
}

static auto mouse_event_type(DWORD const EventFlags)
{
	switch (EventFlags)
	{
	case 0:              return L"Button"sv;
	case MOUSE_MOVED:    return L"Move"sv;
	case DOUBLE_CLICK:   return L"DblClick"sv;
	case MOUSE_WHEELED:
	case MOUSE_HWHEELED: return L"Wheel"sv;
	default:             return L""sv;
	}
}

static auto is_wheel_event(DWORD const EventFlags)
{
	return
		EventFlags == MOUSE_WHEELED ||
		EventFlags == MOUSE_HWHEELED;
}

static auto decode_coord(COORD const Coord)
{
	return std::format(
		L"{{X={}; Y={}}}"sv,
		Coord.X,
		Coord.Y
	);
}

static void decode_mouse_event(INPUT_RECORD const& ir, std::wstring& Str)
{
	const auto& Event = ir.Event.MouseEvent;
	const auto& ButtonState = Event.dwButtonState;
	const auto& EventFlags = Event.dwEventFlags;

	const auto ScrollDistance = [&]
	{
		if (!is_wheel_event(EventFlags))
			return L""s;

		const auto AbsValue = std::abs(static_cast<short>(HIWORD(ButtonState)));
		const auto Delta = std::div(AbsValue, WHEEL_DELTA);

		return std::format(
			L"{}/{}{}Δ"sv,
			AbsValue,
			Delta.quot,
			Delta.rem? std::format(L"{:.2f}"sv, static_cast<double>(Delta.rem) / WHEEL_DELTA).substr(1, 3) : L""sv
		);
	}();

	const auto EventType = mouse_event_type(EventFlags);

	std::format_to(
		std::back_inserter(Str),
		L"pos={}, button=0x{:08X} [{}{}{}{}{}], {}, flags=0x{:08X} [{}{}{}]"sv,
		decode_coord(Event.dwMousePosition),
		ButtonState,
		ButtonState & FROM_LEFT_1ST_BUTTON_PRESSED? L'L' : L'l',
		ButtonState & FROM_LEFT_2ND_BUTTON_PRESSED? L'L' : L'l',
		ButtonState & FROM_LEFT_3RD_BUTTON_PRESSED? L'L' : L'l',
		ButtonState & FROM_LEFT_4TH_BUTTON_PRESSED? L'L' : L'l',
		ButtonState & RIGHTMOST_BUTTON_PRESSED?     L'R' : L'r',
		decode_control_key_state(Event.dwControlKeyState),
		EventFlags,
		!EventType.empty()? EventType : std::format(L"Unknown ({:08X})"sv, EventFlags),
		wheel_direction(ButtonState, EventFlags),
		is_wheel_event(EventFlags)? ScrollDistance : L""sv
	);
}

static void decode_size_event(INPUT_RECORD const& ir, std::wstring& Str)
{
	const auto& Event = ir.Event.WindowBufferSizeEvent;

	std::format_to(
		std::back_inserter(Str),
		L"size={}"sv,
		decode_coord(Event.dwSize)
	);
}

static auto menu_command(DWORD const Command)
{
	switch (Command)
	{
#define TO_STR(x) case x: return L"" #x;
		TO_STR(WM_INITMENU)
			TO_STR(WM_MENUSELECT)
#undef TO_STR
	default: return L"Unknown";
	}
}

static void decode_menu_event(INPUT_RECORD const& ir, std::wstring& Str)
{
	const auto& Event = ir.Event.MenuEvent;

	std::format_to(
		std::back_inserter(Str),
		L"command={}/{}"sv,
		menu_command(Event.dwCommandId),
		Event.dwCommandId
	);
}

static void decode_focus_event(INPUT_RECORD const& ir, std::wstring& Str)
{
	const auto& Event = ir.Event.FocusEvent;

	std::format_to(
		std::back_inserter(Str),
		L"set={}"sv,
		Event.bSetFocus? L"true"sv : L"false"sv
	);
}

static void decode_unknown_event(INPUT_RECORD const& ir, std::wstring& Str)
{
	std::format_to(
		std::back_inserter(Str),
		L"{0}/0x{0:08X}"sv,
		ir.EventType
	);
}

class os_exception: public std::runtime_error
{
public:
	explicit os_exception(char const* const Message):
		std::runtime_error(std::format("{}: {}"sv, Message, GetLastError()))
	{
	}
};

static auto read_config()
{
	wchar_t ModuleName[MAX_PATH];
	if (!GetModuleFileName({}, ModuleName, static_cast<DWORD>(std::size(ModuleName))))
		throw os_exception("GetModuleFileName");

	const auto CfgName = ModuleName + L".cfg"s;

	std::bitset<std::size(EventNames)> Result;

	for (size_t i = 0; i != std::size(EventNames); ++i)
	{
		Result[i] = GetPrivateProfileInt(L"events", EventNames[i], 1, CfgName.c_str());
	}

	return Result;
}

static BOOL WINAPI handler_routine(DWORD const CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
		return TRUE;

	default:
		return FALSE;
	}
}

static void update_console_mode(HANDLE const Con, DWORD const FlagsToClear, DWORD const FlagsToSet)
{
	DWORD Mode;
	if (!GetConsoleMode(Con, &Mode))
		throw os_exception("GetConsoleMode");

	const auto NewMode = (Mode & ~FlagsToClear) | FlagsToSet;

	if (NewMode == Mode)
		return;

	if (!SetConsoleMode(Con, NewMode))
		throw os_exception("SetConsoleMode");
}

static void setup_in(HANDLE const ConIn)
{
	update_console_mode(ConIn, ENABLE_PROCESSED_INPUT, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS);

	if (!SetConsoleCtrlHandler(&handler_routine, true))
		throw os_exception("SetConsoleCtrlHandler");
}

static void setup_out(HANDLE const ConOut)
{
	update_console_mode(ConOut, 0, ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
}

static auto get_event(DWORD const EventType)
{
	switch (EventType)
	{
	case KEY_EVENT:                return event::key;
	case MOUSE_EVENT:              return event::mouse;
	case WINDOW_BUFFER_SIZE_EVENT: return event::size;
	case MENU_EVENT:               return event::menu;
	case FOCUS_EVENT:              return event::focus;

	default:                       return event::unknown;
	}
}

static void program()
{
	const auto ActiveEvents = read_config();
	if (!ActiveEvents.any())
		throw std::runtime_error("Duh!"s);

	const auto
		ConIn = GetStdHandle(STD_INPUT_HANDLE),
		ConOut = GetStdHandle(STD_OUTPUT_HANDLE);

	setup_in(ConIn);
	setup_out(ConOut);

	using handler = void(*)(INPUT_RECORD const&, std::wstring&);

	static constexpr handler Handlers[]
	{
		&decode_key_event,
		&decode_mouse_event,
		&decode_size_event,
		&decode_menu_event,
		&decode_focus_event,

		&decode_unknown_event
	};

	static_assert(std::size(Handlers) == std::to_underlying(event::unknown) + 1);

	std::wstring Message;

	for (;;)
	{
		INPUT_RECORD ir;
		if (DWORD n; !ReadConsoleInput(ConIn, &ir, 1, &n) || !n)
			throw os_exception("ReadConsoleInput");

		const auto Event = get_event(ir.EventType);

		const auto Index = std::to_underlying(Event);

		if (!ActiveEvents[Index])
			continue;

		Message.clear();
		std::format_to(std::back_inserter(Message), L"{}: "sv, EventNames[Index]);

		Handlers[Index](ir, Message);

		Message += L"\n"sv;

		if (DWORD n; !WriteConsole(ConOut, Message.data(), static_cast<DWORD>(Message.size()), &n, {}) || !n)
			throw os_exception("WriteConsole");
	}
}

int main()
{
	try
	{
		program();
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what();
		return EXIT_FAILURE;
	}
}
