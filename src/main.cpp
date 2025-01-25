#include "./includes.h"

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/GauntletLayer.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>
#include <Geode/modify/EditLevelLayer.hpp>

#include "./CustomBGManager.h"

#include "./ErrorsManager/ErrorsManager.h"

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		CustomBGManager::getInstance()->createBGNode(this, "MenuLayer");
		ErrorsManager::onMenuLayer(this);
		return true;
	}
};

class $modify(CreatorLayer) {
	bool init() {
		if (!CreatorLayer::init()) return false;
		CustomBGManager::getInstance()->createBGNode(this, "CreatorLayer");
		return true;
	}
};

class $modify(GJGarageLayer) {
	bool init() {
		if (!GJGarageLayer::init()) return false;
		CustomBGManager::getInstance()->createBGNode(this, "GarageLayer");
		return true;
	}
};

class $modify(LevelSearchLayer) {
	bool init(int p0) {
		if (!LevelSearchLayer::init(p0)) return false;
		CustomBGManager::getInstance()->createBGNode(this, "LevelSearchLayer");
		return true;
	}
};

class $modify(LevelBrowserLayer) {
	bool init(GJSearchObject * p0) {
		if (!LevelBrowserLayer::init(p0)) return false;
		CustomBGManager::getInstance()->createBGNode(this, "LevelBrowserLayer");
		return true;
	}
};

class $modify(LevelSelectLayer) {
	bool init(int page) {
		if (!LevelSelectLayer::init(page)) return false;
		CustomBGManager::getInstance()->createBGNode(this, "LevelSelectLayer");
		return true;
	}
};

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel * level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;
		CustomBGManager::getInstance()->createBGNode(this, "LevelInfoLayer");
		return true;
	}
};

class $modify(LeaderboardsLayer) {
	bool init(LeaderboardState p0) {
		if (!LeaderboardsLayer::init(p0)) return false;
		CustomBGManager::getInstance()->createBGNode(this, "LeaderLayer");
		return true;
	}
};

class $modify(GauntletLayer) {
	bool init(GauntletType p0) {
		if (!GauntletLayer::init(p0)) return false;
		CustomBGManager::getInstance()->createBGNode(this, "GauntletLayer");
		return true;
	}
};

class $modify(GauntletSelectLayer) {
	bool init(int p0) {
		if (!GauntletSelectLayer::init(p0)) return false;
		CustomBGManager::getInstance()->createBGNode(this, "GauntletSelectLayer");
		return true;
	}
};

class $modify(EditLevelLayer) {
	bool init(GJGameLevel * p0) {
		if (!EditLevelLayer::init(p0)) return false;
		CustomBGManager::getInstance()->createBGNode(this, "EditLevelLayer");
		return true;
	}
};