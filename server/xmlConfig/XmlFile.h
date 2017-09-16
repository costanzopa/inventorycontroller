/*
 * xmlFile.h
 *
 *  Created on: 28/06/2015
 *      Author: pablito
 */

#ifndef XMLFILE_H_
#define XMLFILE_H_

#include <libxml++/libxml++.h>
#include "XmlElementFactory.h"
#include "XmlElement.h"
#include "../../common/Constants.h"

namespace xml {

class XmlFile: public xmlpp::DomParser  {
public:
	XmlFile();
	virtual ~XmlFile();
	virtual void add(XmlElement* element) = 0;
	void setFilename(const std::string& filename);

protected:
	//Metodos privados
	void complete(const xmlpp::Node* node);
	void complete();
	//Miembros de Clase
	std::string filepath;

private:

};

} /* namespace configuration */
#endif /* XMLFILE_H_ */
