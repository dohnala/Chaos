#pragma once

#include "Chaos.h"

struct Keybind
{
	enum Type
	{
		Key = 0,
		Mouse
	};

	Type Type;
	uint16_t Code;
};

struct InputComponent
{
	Keybind Up			= { Keybind::Type::Key, Chaos::Key::W };
	Keybind Left		= { Keybind::Type::Key, Chaos::Key::A };
	Keybind Down		= { Keybind::Type::Key, Chaos::Key::S };
	Keybind Right		= { Keybind::Type::Key, Chaos::Key::D };
	Keybind SkillSlot1	= { Keybind::Type::Mouse, Chaos::Mouse::ButtonLeft };

	InputComponent() = default;
	InputComponent(const InputComponent&) = default;
};