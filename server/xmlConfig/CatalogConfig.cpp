/*
 * CatalogElement.cpp
 *
 *  Created on: 28/06/2015
 *      Author: pablito
 */

#include "CatalogConfig.h"

namespace config {

CatalogConfig::CatalogConfig() {
	// TODO Auto-generated constructor stub

}

CatalogConfig::CatalogConfig(const std::string& className) {
	this->elementName = className;
}

CatalogConfig::~CatalogConfig() {
	// TODO Auto-generated destructor stub
}

void CatalogConfig::complete(const std::string& attributes) {
	utils::StringUtils util;
	std::vector<std::string> splitVector = util.split(attributes,utils::separator);
	if (!splitVector.empty()) {
		this->pathCatalog = splitVector[0];
		this->pathProducts = splitVector[1];
		this->pathVisionAreas = splitVector[2];
	}
}
const std::string& CatalogConfig::getClassName() {
	return (this->elementName);
}

const std::string& CatalogConfig::getCatalogPath() const {
	return (this->pathCatalog);
}
const std::string& CatalogConfig::getProductsPath() const {
	return (this->pathProducts);
}
const std::string& CatalogConfig::getVisionAreasPath() const {
	return (this->pathVisionAreas);
}

} /* namespace config */
