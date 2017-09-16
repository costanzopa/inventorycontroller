/*
 * Product.cpp
 *
 *  Created on: 04/06/2015
 *      Author:
 */

#include "Product.h"

namespace catalog {

Product::Product(const std::string& className) {
	this->elementName = className;
}

Product::Product(const std::string& id, const std::string& name,
		const std::string& des,const std::string& path,
		const std::string& pathIcon,const std::string& pathStock) {
	this->id = id;
	this->name = name;
	this->description = des;
	this->path = path;
	this->pathIcon = pathIcon;
	this->pathStock = pathStock;
}

Product::~Product() {
	// TODO Auto-generated destructor stub
}

void Product::complete(const std::string& attributes) {
	utils::StringUtils util;
	std::vector<std::string> splitVector = util.split(attributes,utils::separator);
	if (!splitVector.empty()) {
		this->name = splitVector[0];
		this->description = splitVector[1];
		this->setPath(splitVector[2]);
		this->setPathIcon(splitVector[3]);
		this->setPathStock(splitVector[4]);
	}
}
const std::string& Product::getClassName() {
	return (this->elementName);
}

const std::string& Product::getId() const {
	return (this->id);
}

const std::string& Product::getName() const {
	return (this->name);
}

const std::string& Product::getDescription() const {
	return (this->description);
}
const std::string& Product::getPath() const {
	return (this->path);
}
const std::string& Product::getPathIcon() const {
	return (this->pathIcon);
}

void Product::setId(const std::string& id) {
	this->id = id;
}
void Product::setName(const std::string& s) {
	this->name = s;
}
void Product::setDescription(const std::string& s) {
	this->description = s;
}

void Product::setPath(const std::string& path) {
	this->path = path;
}
void Product::setPathIcon(const std::string& path) {
	this->pathIcon = path;
}

const std::string& Product::getPathStock() const {
	return (this->pathStock);
}

void Product::setPathStock(const std::string& pathStock) {
	this->pathStock = pathStock;
}

} /* namespace config */
