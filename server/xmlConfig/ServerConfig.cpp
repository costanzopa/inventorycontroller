/*
 * ServerConfig.cpp
 *
 *  Created on: 28/06/2015
 *      Author: pablito
 */

#include "ServerConfig.h"

namespace config {

ServerConfig::ServerConfig() {
	// TODO Auto-generated constructor stub

}

ServerConfig::ServerConfig(const std::string& className) {
	this->elementName = className;
}

ServerConfig::~ServerConfig() {
	// TODO Auto-generated destructor stub
}


void ServerConfig::complete(const std::string& attributes) {
	utils::StringUtils util;
	std::vector<std::string> splitVector = util.split(attributes,utils::separator);
	if (!splitVector.empty()) {
		this->port = splitVector[0];
		this->host = splitVector[1];
		this->queue = atoi(splitVector[2].c_str());
	}
}
const std::string& ServerConfig::getClassName() {
	return (this->elementName);
}

unsigned int ServerConfig::getQueue() const {
	return (this->queue);
}
const std::string& ServerConfig::getHost() const {
	return (this->host);
}
const std::string& ServerConfig::getPort() const {
	return (this->port);
}

} /* namespace config */
