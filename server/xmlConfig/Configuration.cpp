/*
 * Configuration.cpp
 *
 *  Created on: 28/06/2015
 *      Author: pablito
 */

#include "Configuration.h"

namespace config {

Configuration::Configuration() {
	this->catalog = utils::null;
	this->server = utils::null;
}

Configuration::~Configuration() {
	if (this->catalog != utils::null)
		delete catalog;
	if (this->server != utils::null)
		delete server;
}

void Configuration::add(xml::XmlElement* element) {
	try {
	if(element->getClassName()=="server") {
		this->server =  dynamic_cast<ServerConfig*> (element);
	} else if(element->getClassName()=="catalog") {
		this->catalog =  dynamic_cast<CatalogConfig*> (element);
	}
	} catch (std::exception& e) {
		std::cerr<<e.what()<<std::endl;
	}
}

CatalogConfig* Configuration::getCatalog() {
	return (this->catalog);
}
ServerConfig* Configuration::getServerConfig() {
	return (this->server);
}
const std::string& Configuration::getPort() const {
	return (this->server->getPort());
}
const std::string& Configuration::getHost() const {
	return (this->server->getHost());
}
const unsigned int Configuration::getQueue() const {
	return (this->server->getQueue());
}

} /* namespace config */
