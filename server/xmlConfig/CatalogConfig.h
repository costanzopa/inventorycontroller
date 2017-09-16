/*
 * CatalogElement.h
 *
 *  Created on: 28/06/2015
 *      Author: pablito
 */

#ifndef CATALOGCONFIG_H_
#define CATALOGCONFIG_H_

#include "XmlElement.h"
#include "../../common/StringUtils.h"

namespace config {

class CatalogConfig: public xml::XmlElement {
public:
	CatalogConfig();
	explicit CatalogConfig(const std::string& className);
	virtual ~CatalogConfig();
	void complete(const std::string& attributes);
	const std::string& getClassName();
	const std::string& getCatalogPath() const;
	const std::string& getProductsPath() const;
	const std::string& getVisionAreasPath() const;

private:
	std::string pathCatalog;
	std::string pathProducts;
	std::string pathVisionAreas;
};

} /* namespace config */
#endif /* CATALOGELEMENT_H_ */
