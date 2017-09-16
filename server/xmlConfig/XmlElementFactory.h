/*
 * XmlElementFactory.h
 *
 *  Created on: 06/06/2015
 *      Author:
 */

#ifndef XMLELEMENTFACTORY_H_
#define XMLELEMENTFACTORY_H_
#include "XmlElement.h"
#include "../../common/Exception.h"
#include "../catalog/Product.h"
#include "../catalog/VisionArea.h"
#include "ServerConfig.h"
#include "CatalogConfig.h"

namespace xml {

class XmlElementFactory {
public:
	XmlElementFactory();
	~XmlElementFactory();
	XmlElement* create(const std::string& classname);
};

} /* namespace config */
#endif /* XMLELEMENTFACTORY_H_ */
