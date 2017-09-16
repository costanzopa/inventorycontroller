/*
 * CatalogFile.cpp
 *
 *  Created on: 28/06/2015
 *      Author: pablito
 */

#include "CatalogFile.h"

namespace catalog {

CatalogFile::CatalogFile() {

}
CatalogFile::CatalogFile(const std::string& filename) {
	try {
		this->filepath = filename;
		this->catalog = utils::null;
		this->catalog = new Catalog();
		this->parse_file(filename);
		this->complete();
	} catch(exceptions::XmlException& e) {
		std::cerr<<e.what()<<std::endl;
	}
}

CatalogFile::~CatalogFile() {
	// TODO Auto-generated destructor stub
}

void CatalogFile::add(xml::XmlElement* element) {
	this->catalog->add(element);
}

void CatalogFile::update(Catalog* config) {
	try
	  {
	    xmlpp::Document document;
	    document.set_internal_subset("CATALOG", "", "");
	    document.set_entity_declaration("xml", xmlpp::XML_INTERNAL_GENERAL_ENTITY,
	      "", "", "Extensible Markup Language");

	    xmlpp::Element* nodeRoot = document.create_root_node("catalog");
	    nodeRoot->add_child_text("\n");
	    xmlpp::Element* products = nodeRoot->add_child("products");
	    std::vector<Product> productsVector = config->getProducts();
	    std::vector<Product>::iterator it = productsVector.begin();
	    while(it != productsVector.end()) {
	    	products->add_child_text("\n");
	    	xmlpp::Element* product = products->add_child("product");
	    	Product prod = (*it);
	    	product->set_attribute("name",prod.getName());
	    	product->set_attribute("description",prod.getDescription());
	    	product->set_attribute("path",prod.getPath());
	    	product->set_attribute("icon",prod.getPathIcon());
	    	product->set_attribute("pathStock",prod.getPathStock());
	    	product->add_child_text("\n");
	    	it++;
	    }
	    products->add_child_text("\n");
	    nodeRoot->add_child_text("\n");
	    xmlpp::Element* areas = nodeRoot->add_child("visionAreas");
	    std::vector<VisionArea> areasVector = config->getAreas();
	    std::vector<VisionArea>::iterator itAreas = areasVector.begin();
	    while(itAreas != areasVector.end()) {
	    	areas->add_child_text("\n");
	        xmlpp::Element* areaVision = areas->add_child("visionArea");
	        VisionArea area = (*itAreas);
	        areaVision->set_attribute("name",area.getName());
	        areaVision->set_attribute("type",area.getType());
	        areaVision->set_attribute("path",area.getPath());
	        areaVision->set_attribute("pathProcess",area.getPathProcess());
	        areaVision->add_child_text("\n");
	    	itAreas++;
	    }
	    areas->add_child_text("\n");
	    nodeRoot->add_child_text("\n");

	    Glib::ustring whole = document.write_to_string();
		//std::cout << "XML built at runtime: " << std::endl << whole << std::endl;
	    document.write_to_file(this->filepath);
	  }
	  catch(const std::exception& ex)
	  {
	    std::cout << "Exception caught: " << ex.what() << std::endl;
	  }
}

Catalog* CatalogFile::getCatalog() const {
	return (this->catalog);
}


} /* namespace config */
