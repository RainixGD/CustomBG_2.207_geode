#include "./CustomBGManager.h"
#include "./ErrorsManager/ErrorsManager.h"

void CustomBGManager::init() {
	isOk = loadData();
}

bool CustomBGManager::hasFileExtension(const std::string& fileName, const std::string& extension) {
    std::string pattern = ".*\\." + extension + "$";
    std::regex regexPattern(pattern, std::regex::icase);

    return std::regex_match(fileName, regexPattern);
}

bool CustomBGManager::loadData() {
    std::ifstream file("Resources/customBG.json");
    if (!file) {
        ErrorsManager::addError("Custom BG: File 'Resources/customBG.json' not found or unable to open.", ErrorsManager::Error);
        return false;
    }

    std::ostringstream buffer;
    try {
        buffer << file.rdbuf();
    }
    catch (const std::ios_base::failure& e) {
        ErrorsManager::addError("Custom BG: Failed to read from file 'Resources/customBG.json'. IOError: " + std::string(e.what()), ErrorsManager::Error);
        file.close();
        return false;
    }

    std::string fileContent = buffer.str();
    file.close();

    if (fileContent.empty()) {
        ErrorsManager::addError("Custom BG: File 'Resources/customBG.json' is empty.", ErrorsManager::Error);
        return false;
    }

    try {
        auto root = nlohmann::json::parse(fileContent);

        if (!root.contains("settings") || !root["settings"].is_object() ||
            !root.contains("backgrounds") || !root["backgrounds"].is_object()) {
            ErrorsManager::addError("Custom BG: JSON missing required properties: 'settings' or 'backgrounds'.", ErrorsManager::Error);
            return false;
        }

        if (root["settings"].contains("NoGroundInLevelSearchLayer") && root["settings"]["NoGroundInLevelSearchLayer"].is_boolean() &&
            root["settings"]["NoGroundInLevelSearchLayer"].get<bool>()) {
            noGroundInLSL = true;
        }

        for (const auto& [key, value] : root["backgrounds"].items()) {
            if (!value.is_string()) {
                ErrorsManager::addError("Custom BG: Invalid value for background key '" + key + "'. It should be a string.", ErrorsManager::Error);
                return false;
            }

            auto bg = value.get<std::string>();
            if (bg.empty()) continue;

            if (!hasFileExtension(bg, "png")) {
                ErrorsManager::addError("Custom BG: Background file '" + bg + "' should have a .png extension.", ErrorsManager::Error);
                return false;
            }

            bgs[key] = std::move(bg);
        }
    }
    catch (const nlohmann::json::parse_error& e) {
        ErrorsManager::addError("Custom BG: JSON parse error. Exception: " + std::string(e.what()), ErrorsManager::Error);
        return false;
    }
    catch (const nlohmann::json::type_error& e) {
        ErrorsManager::addError("Custom BG: JSON type error. Exception: " + std::string(e.what()), ErrorsManager::Error);
        return false;
    }
    catch (const std::bad_alloc& e) {
        ErrorsManager::addError("Custom BG: Memory allocation error. Exception: " + std::string(e.what()), ErrorsManager::Error);
        return false;
    }
    catch (const std::ios_base::failure& e) {
        ErrorsManager::addError("Custom BG: I/O operation failure. Exception: " + std::string(e.what()), ErrorsManager::Error);
        return false;
    }
    catch (const std::exception& e) {
        ErrorsManager::addError("Custom BG: Unknown error occurred. Exception: " + std::string(e.what()), ErrorsManager::Error);
        return false;
    }

    return true;
}

void CustomBGManager::createBGNode(CCLayer* layer, std::string layerName) {
	if (!isOk || bgs.find(layerName) == bgs.end()) return;

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