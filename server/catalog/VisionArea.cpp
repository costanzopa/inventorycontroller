/*
 * VisionArea.cpp
 *
 *  Created on: 04/06/2015
 *      Author: pablito
 */

#include "VisionArea.h"

namespace catalog {

VisionArea::VisionArea(const std::string& className) {
	this->elementName = className;
	this->id="0000";
}

VisionArea::VisionArea(const std::string& id, const std::string& name,
		const std::string& type,const std::string& path,
		const std::string& pathProcess) {
	this->id = id;
	this->name = name;
	this->type = type;
	this->path = path;
	this->pathProcess = pathProcess;
}

VisionArea::VisionArea(const std::string& name,
		const std::string& type) {
	this->name =name;
	this->type = type;
}

VisionArea::~VisionArea() {
	// TODO Auto-generated destructor stub
}

void VisionArea::complete(const std::string& attributes) {
	utils::StringUtils util;
	std::vector<std::string> splitVector = util.split(attributes, utils::separator);
	if (!splitVector.empty()) {
		this->name = splitVector[0];
		this->type = splitVector[1];
		this->setPath(splitVector[2]);
		this->setPathProcess(splitVector[3]);
	}
}

const std::string& VisionArea::getClassName() {
	return (this->elementName);
}

const std::string& VisionArea::getId() const {
	return (this->id);
}
const std::string& VisionArea::getName() const {
	return (this->name);
}
const std::string& VisionArea::getType() const {
	return (this->type);
}

void VisionArea::setId(const std::string& id) {
	this->id = id;
}

void VisionArea::setName(const std::string& name) {
	this->name = name;
}

void VisionArea::setType(const std::string& type) {
	this->type = type;
}

void VisionArea::setPath(const std::string& path) {
	this->path = path;
}

void VisionArea::setPathProcess(const std::string& path) {
	this->pathProcess = path;
}

const std::string& VisionArea::getPath() const {
	return (this->path);
}


const std::string& VisionArea::getPathProcess() const {
	return (this->pathProcess);
}

} /* namespace config */
