/*
 * XmlElementFactory.cpp
 *
 *  Created on: 06/06/2015
 *      Author: pablito
 */

#include "XmlElementFactory.h"

namespace xml {

XmlElementFactory::XmlElementFactory() {
}

XmlElementFactory::~XmlElementFactory() {
}

XmlElement* XmlElementFactory::create(const std::string& classname) {
	XmlElement* element = NULL;
	if (classname=="product") {
		 element = new catalog::Product(classname);
	} else if (classname=="visionArea") {
		element = new catalog::VisionArea(classname);
	} else if (classname=="server") {
		element = new config::ServerConfig(classname);
	} else if (classname=="catalog") {
		element = new config::CatalogConfig(classname);
	} else {
		throw (exceptions::XmlException("Error elemento invalido."));
	}
	return element;
}

} /* namespace config */
