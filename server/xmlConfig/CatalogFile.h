/*
 * CatalogFile.h
 *
 *  Created on: 28/06/2015
 *      Author: pablito
 */

#ifndef CATALOGFILE_H_
#define CATALOGFILE_H_

#include "XmlFile.h"
#include "XmlElement.h"
#include "../catalog/Catalog.h"

namespace catalog {

class CatalogFile: public xml::XmlFile {
public:
	CatalogFile();
	CatalogFile(const std::string& filename);
	~CatalogFile();
	void add(xml::XmlElement* element);
	//Plasma los cambios en la configuracion en un
	// archivo xml
	void update(Catalog* config);
	Catalog* getCatalog() const;

private:
	Catalog* catalog;
};

} /* namespace config */
#endif /* CATALOGFILE_H_ */
