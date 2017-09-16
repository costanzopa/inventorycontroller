/*
 * ConfigFile.cpp
 *
 *  Created on: 28/06/2015
 *      Author: pablito
 */

#include "ConfigFile.h"

namespace config {

ConfigFile::ConfigFile() {
	// TODO Auto-generated constructor stub
}


ConfigFile::ConfigFile(const std::string& filename) {
	try {
		this->config = utils::null;
		this->filepath = filename;
		this->config = new Configuration();
		this->parse_file(filename);
		this->complete();
	} catch(std::exception& e) {
		std::cerr<<e.what()<<std::endl;
		throw(e);
	}
}


ConfigFile::~ConfigFile() {
	// TODO Auto-generated destructor stub
}

void ConfigFile::add(xml::XmlElement* element) {
	this->config->add(element);
}

Configuration* ConfigFile::getConfig() const {
	return (this->config);
}
} /* namespace config */
