#pragma once

namespace Screen
{
	const int Width = 1280;
	const int Height = 720;
	const int HalfWidth = Width / 2;
	const int HalfHeight = Height / 2;

	enum Scene
	{
		INITIAL,
		GAME,
		PAUSE,
		RESULT
	};
}

namespace Def
{
	const Math::Color Color = { 1.f,1.f,1.f,1.f };
	const Math::Vector3 Vec = Math::Vector3::Zero;
	const float AnNull = 1.f;
}

namespace Key
{
	enum Code
	{
		Constant=0x8000,
		Cero='0',
		Uno,Dos,Tres,Cuatro,Cinco,Seis,Siete,Ocho,Nueve,Diez,
		A='A',
		B,C,D,E,F,G,H,I,J,K,L,N,M,O,P,Q,R,S,T,U,V,W,X,Y,Z,
		L_Click=VK_LBUTTON,R_Click=VK_RBUTTON,Wheel_Click=VK_MBUTTON,
		Space=VK_SPACE,BackSpace=VK_BACK,Enter=VK_RETURN,
		L_Ctrl=VK_LCONTROL,R_Ctrl=VK_RCONTROL,
		L_Shift=VK_LSHIFT,R_Shift=VK_RSHIFT,
		Up=VK_UP,Down=VK_DOWN,Left=VK_LEFT,Right=VK_RIGHT,
		UnderScore=VK_OEM_102,Slash=VK_OEM_2,
	};
	static auto IsPushing(Code a_keyCode) noexcept { return (GetAsyncKeyState(a_keyCode) & Code::Constant) != NULL; }
}