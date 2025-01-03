#pragma once

#include <Geode/Geode.hpp>
#include <iostream>
#include "../HackTemplate.hpp"
#include "../HackManager.hpp"

using namespace geode::prelude;

class Hack {
public:
	inline static std::string name = "Show Hitboxes";
	inline static std::string description = "Shows The Level's Hitboxes";
	inline static std::string hackKey = "hitboxes-hack";

	inline static void setEnabled(bool enabled) {
		Hacks::setEnabled(hackKey, enabled);
	}
	inline static void loadValue() {
		Hacks::setEnabled(hackKey, Mod::get()->getSavedValue<bool>(hackKey));
	}
};
