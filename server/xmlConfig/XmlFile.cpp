/*
 * xmlFile.cpp
 *
 *  Created on: 28/06/2015
 *      Author: pablito
 */

#include "XmlFile.h"

namespace xml {

XmlFile::XmlFile() {
	// TODO Auto-generated constructor stub

}

XmlFile::~XmlFile() {
	// TODO Auto-generated destructor stub
}

void XmlFile::complete() {
	if(this->get_document()) {
       const xmlpp::Node* pNode = this->get_document()->get_root_node(); //deleted by DomParser.
       complete(pNode);
	}
}

void XmlFile::complete(const xmlpp::Node* node) {
	const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(node);
	std::string nodeName = node->get_name();
	if(const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(node)) {
	    const xmlpp::Element::AttributeList& attributes = nodeElement->get_attributes();
	    if (!attributes.empty()) {
	    	std::string elementAttributes;
	    	XmlElementFactory factory;
	    	XmlElement* element = factory.create(nodeName);
	    	for(xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter) {
	    		const xmlpp::Attribute* attribute = *iter;
	    		elementAttributes+=attribute->get_value();
	    		elementAttributes+= utils::separator;
	    	}
	    	 element->complete(elementAttributes);
	    	 this->add(element);
	    }
	}
	if(!nodeContent) {
	   //Recurse through child nodes:
	   xmlpp::Node::NodeList list = node->get_children();
	   for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter) {
	     complete(*iter); //recursive
	   }
	}
}


void XmlFile::setFilename(const std::string& filename) {
	this->filepath = filename;
}

} /* namespace configuration */
