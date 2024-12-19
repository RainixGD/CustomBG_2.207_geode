#pragma once
#include "./includes.h"

class CustomBGManager {

	enum DataLoadingResult {
		OK,
		FileNotFound,
		ParsingError
	};

	std::unordered_map<std::string, std::string> bgs;
	DataLoadingResult loadingStatus;
	static CustomBGManager* instance;
	bool noGroundInLSL = false;

	void init();

	DataLoadingResult loadData();
	void createErrorLabel(CCLayer* layer);

	CustomBGManager() {};
public:

	void createBGNode(CCLayer* layer, std::string layerName);
	static CustomBGManager* getInstance();

};