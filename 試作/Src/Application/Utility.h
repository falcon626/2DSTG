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
}