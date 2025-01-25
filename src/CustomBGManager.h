#pragma once
#include "./includes.h"

class CustomBGManager {
	bool isOk = false;
	std::unordered_map<std::string, std::string> bgs;
	static CustomBGManager* instance;
	bool noGroundInLSL = false;

	void init();

	bool hasFileExtension(const std::string& fileName, const std::string& extension);
	bool loadData();

	CustomBGManager() {};
public:

	void createBGNode(CCLayer* layer, std::string layerName);
	static CustomBGManager* getInstance();

};