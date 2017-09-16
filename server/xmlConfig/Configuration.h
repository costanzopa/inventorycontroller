/*
 * Configuration.h
 *
 *  Created on: 28/06/2015
 *      Author: pablito
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_
#include "XmlElement.h"
#include "CatalogConfig.h"
#include "ServerConfig.h"
#include <iostream>

namespace config {

class Configuration {
public:
	Configuration();
	~Configuration();
	void add(xml::XmlElement* element);
	CatalogConfig* getCatalog();
	ServerConfig* getServerConfig();
	const std::string& getPort() const;
	const std::string& getHost() const;
	const unsigned int getQueue() const;

private:
	CatalogConfig* catalog;
	ServerConfig* server;
};

} /* namespace config */
#endif /* CONFIGURATION_H_ */
