#pragma once

#include <Geode/Geode.hpp>
#include <iostream>
#include "../HackTemplate.hpp"
#include "../HackManager.hpp"

using namespace geode::prelude;

class Speedhack  public: Hack {
public:
	inline static std::string name = "Speedhack";
	inline static std::string description = "Changes The Game's Speed";
	inline static std::string hackKey;

	inline static void setEnabled(bool enabled) {
		Hacks::setEnabled(hackKey, enabled);
	}
	inline static void loadValue() {
		Hacks::setEnabled(hackKey, Mod::get()->getSavedValue<bool>(hackKey));
	}
};
