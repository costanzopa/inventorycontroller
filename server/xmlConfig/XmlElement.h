/*
 * XmlElement.h
 *
 *  Created on: 06/06/2015
 *      Author: pablito
 */

#ifndef XMLELEMENT_H_
#define XMLELEMENT_H_
#include <string>

namespace xml {

class XmlElement {
public:
	XmlElement();
	virtual ~XmlElement();
	virtual void complete(const std::string& attributes)=0;
	virtual const std::string& getClassName() = 0;

protected:
	std::string elementName;
};

} /* namespace config */
#endif /* XMLELEMENT_H_ */
