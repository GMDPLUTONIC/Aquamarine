#pragma once

#include <Geode/Geode.hpp>

namespace aquamarine::hooks {
    bool registerHook(geode::Hook *hook, std::string id);
    bool toggleHook(geode::Hook *hook);
}