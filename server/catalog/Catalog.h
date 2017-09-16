/*
 * Configuration.h
 *
 *  Created on: 05/06/2015
 *      Author:
 */

#ifndef CATALOG_H_
#define CATALOG_H_
#include "../xmlConfig/XmlElement.h"
#include "Product.h"
#include "VisionArea.h"
#include "../threads/Mutex.h"
#include "../../common/Directory.h"
#include "../threads/Lock.h"
#include <iostream>
#include <unistd.h>

namespace catalog {

class Catalog {
public:
	Catalog();
	~Catalog();
	std::vector<Product*> getProducts() const;
	std::vector<VisionArea*> getAreas() const;
	void add(xml::XmlElement* element);
	void setProductsPath(const std::string& path);
	void setVisionAreasPath(const std::string& path);

	void addProduct(const std::string& attributes);
	std::string addArea(const std::string& name, const std::string& type);
	bool removeProduct(const std::string& id);
	bool removeArea(const std::string& id);
	bool updateArea(const std::string& id, std::string nombre, std::string tipo);
	bool updateProduct(const std::string& id,std::string nombre, std::string descripcion);
	std::string listAreas();
	std::string listProducts();
	std::string getPathProductImages(const std::string& path);
	std::string getPathProductIcons(const std::string& nombre);
	std::string getPathAreasProcess(const std::string& id);


	std::vector<Product> getProducts();
	std::vector<VisionArea> getAreas();

	std::string getProductDescripcion(const std::string& name);
	private:
	//Metodos privados
	const std::string nextAreaId();
	const std::string nextProductId();
	//Miembros de clase privados
	std::vector<Product*> products;
	std::vector<VisionArea*> areas;
	unsigned int idProducts;
	unsigned int idAreas;
	std::string pathVisionAreas;
	std::string pathProducts;
	threads::Mutex mutex;
};

} /* namespace config */
#endif /* CONFIGURATION_H_ */
