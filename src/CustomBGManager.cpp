#include "./CustomBGManager.h"

void CustomBGManager::init() {
	loadingStatus = loadData();
}

CustomBGManager::DataLoadingResult CustomBGManager::loadData() {
	std::ifstream file("Resources/customBG.json");
	if (!file) return FileNotFound;
	std::ostringstream buffer;
	buffer << file.rdbuf();
	std::string fileContent = buffer.str();

	file.close();
	try {
		auto root = nlohmann::json::parse(fileContent);
		if (!root.contains("settings") || !root["settings"].is_object()
			|| !root.contains("backgrounds") || !root["backgrounds"].is_object()) return ParsingError;

		if (root["settings"].contains("NoGroundInLevelSearchLayer") && root["settings"]["NoGroundInLevelSearchLayer"].is_boolean() && root["settings"]["NoGroundInLevelSearchLayer"].get<bool>())
			noGroundInLSL = true;
		for (const auto& [key, value] : root["backgrounds"].items()) {
			if (!value.is_string()) return ParsingError;

			auto bg = value.get<std::string>();
			if (bg.empty()) continue;

			bgs[key] = std::move(bg);
		}
	}
	catch (...) {
		return ParsingError;
	}
	return OK;
}

void CustomBGManager::createErrorLabel(CCLayer* layer) {
	std::string errorText;
	switch (loadingStatus) {
	case CustomBGManager::FileNotFound:
		errorText = "Can't find 'customBG.json' in ./Resources";
		break;
	case CustomBGManager::ParsingError:
		errorText = "Can't parse 'customBG.json'";
		break;
	}

	auto size = CCDirector::sharedDirector()->getWinSize();

	auto errorLabel = CCLabelBMFont::create(errorText.c_str(), "bigFont.fnt");
	errorLabel->setColor({ 255, 0, 0 });
	errorLabel->setScale(0.6);
	errorLabel->setPosition({ size.width / 2, size.height - 10 });
	layer->addChild(errorLabel);
}

void CustomBGManager::createBGNode(CCLayer* layer, std::string layerName) {
	if (loadingStatus != OK) {
		createErrorLabel(layer);
		return;
	}

	if (bgs.find(layerName) == bgs.end()) return;

	layer->sortAllChildren();
	auto oldBG = dynamic_cast<CCNode*>(layer->getChildren()->objectAtIndex(0));
	oldBG->setVisible(0);

	if (noGroundInLSL && layerName == "LevelSelectLayer") {
		auto ground = dynamic_cast<CCNode*>(layer->getChildren()->objectAtIndex(1));
		ground->setVisible(0);
	}

	CCSprite* newBG = CCSprite::create(bgs[layerName].c_str());
	if (newBG != NULL) {
		auto size = CCDirector::sharedDirector()->getWinSize();
		newBG->setAnchorPoint({ 0, 0 });
		newBG->setScaleX(size.width / newBG->getContentSize().width);
		newBG->setScaleY(size.height / newBG->getContentSize().height);
		layer->addChild(newBG, -10);
	}
}

CustomBGManager* CustomBGManager::getInstance() {
	if (!instance) {
		instance = new CustomBGManager();
		instance->init();
	}
	return instance;
}

CustomBGManager* CustomBGManager::instance = nullptr;