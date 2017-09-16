/*
 * Configuration.cpp
 *
 *  Created on: 05/06/2015
 *      Author: pablito
 */

#include "Catalog.h"
#include <iostream>
#include <cstdio>

namespace catalog {

Catalog::Catalog() {
	this->idAreas=utils::ZERO;
	this->idProducts=utils::ZERO;
}

Catalog::~Catalog() {
	std::vector<Product*>::iterator itProduct = products.begin();
	std::vector<VisionArea*>::iterator itArea = areas.begin();
	while(itProduct != products.end()) {
		delete (*itProduct);
		itProduct++;
	}
	while(itArea != areas.end()) {
		delete (*itArea);
		itArea++;
	}
}

void Catalog::add(xml::XmlElement* element) {
	try {
	if(element->getClassName()=="product") {
		Product* product =  dynamic_cast<Product *> (element);
		std::string id = this->nextProductId();
		product->setId(id);
		products.push_back(product);
	} else if(element->getClassName()=="visionArea") {
		VisionArea* area =  dynamic_cast<VisionArea *> (element);
		std::string id = this->nextAreaId();
		area->setId(id);
		areas.push_back(area);
	}
	} catch (std::exception& e) {
		std::cerr<<e.what()<<std::endl;
	}
}

std::vector<Product*> Catalog::getProducts() const {
	return (this->products);
}
std::vector<VisionArea*> Catalog::getAreas() const {
	return (this->areas);
}

void Catalog::addProduct(const std::string& attributes) {
	threads::Lock lock(this->mutex);
	utils::StringUtils stringutils;
	std::vector<std::string> msj;
	stringutils.tokenizarMensaje(attributes,msj);
	Product* product = new Product("product");
	std::string path = this->pathProducts+utils::DIR_SEPARATOR+msj[0];
	std::string pathImages = path + utils::DIR_SEPARATOR+"Images";
	std::string pathIconos = "data/Icons/"+msj[0];
	std::string pathStock = this->pathProducts+ utils::DIR_SEPARATOR+msj[0]+"/Stock";
	utils::Directory dir;
	dir.make(path);
	dir.make(pathImages);
	dir.make(pathIconos);
	std::string s = attributes + "|" + pathImages + "|" + pathIconos +"|" + pathStock;
	product->complete(s);
	std::string id = this->nextProductId();
	product->setId(id);
	dir.make(pathStock);
	this->products.push_back(product);
}
std::string Catalog::addArea(const std::string& name, const std::string& type) {
	threads::Lock lock(this->mutex);
	VisionArea* area = new VisionArea("visionArea");
	area->setName(name);
	std::string path = this->pathVisionAreas +utils::DIR_SEPARATOR+ name;
	area->setPath(path);
	std::string pathProcess = path + utils::DIR_SEPARATOR + "Process";
	std::string id = this->nextAreaId();
	area->setId(id);
	area->setType(type);
	area->setPathProcess(pathProcess);
	this->areas.push_back(area);
	utils::Directory dir;
	dir.make(path);
	dir.make(pathProcess);
	return (id);
}

bool Catalog::removeProduct(const std::string& id) {
	threads::Lock lock(this->mutex);
	bool toReturn = false;
	Product* toRemove= utils::null;
	std::vector<Product*> temp;
	std::vector<Product*>::iterator it = this->products.begin();
	while (it != this->products.end()) {
		toRemove = (*it);
		if ((*it)->getId() == id) {
				toReturn = true;
				utils::Directory dirStock(toRemove->getPathStock());
				dirStock.remove();
				utils::Directory dirImg(toRemove->getPath());
				dirImg.remove();
				utils::Directory dirIconos(toRemove->getPathIcon());
				dirIconos.remove();
				std::string path = this->pathProducts+"/"+toRemove->getName();
				rmdir(path.c_str());
				delete toRemove;
			} else {
				temp.push_back(toRemove);
			}
			it++;
		}
		this->products.swap(temp);
		return  toReturn;
}

bool Catalog::removeArea(const std::string& id) {
	threads::Lock lock(this->mutex);
	bool toReturn = false;
	VisionArea* toRemove=utils::null;
	std::vector<VisionArea*> temp;
	std::vector<VisionArea*>::iterator it = this->areas.begin();
	while (it != this->areas.end()) {
		toRemove = (*it);
		if ((*it)->getId() == id) {
				toReturn = true;
				utils::Directory dirProcess(toRemove->getPathProcess());
				dirProcess.remove();
				rmdir(toRemove->getPath().c_str());
				delete toRemove;
			} else {
				temp.push_back(toRemove);
			}
			it++;
		}
		this->areas.swap(temp);
	return  toReturn;
}

bool Catalog::updateArea(const std::string& id,
							   std::string nombre, std::string tipo) {
	threads::Lock lock(this->mutex);
	bool toReturn = false;
	std::vector<VisionArea*>::iterator it = this->areas.begin();
	while (it != this->areas.end()) {
		if ((*it)->getId() == id) {
				toReturn = true;
				(*it)->setName(nombre);
				utils::StringUtils c;
				c.removeLastChar(tipo);
				(*it)->setType(tipo);
				std::string oldPath = (*it)->getPath();
				std::string nuevoDir = nombre;
				std::string mensaje = oldPath;
				std::vector<std::string> vectorResultado;
				if (!mensaje.empty() && mensaje[mensaje.length() - 1] == '\n'
					&& mensaje.size() > 1) {
				  mensaje.erase(mensaje.length() - 1);
				}
				std::stringstream stream(mensaje);
				std::string token;
				while (std::getline(stream, token, '/')) {
				  vectorResultado.push_back(token);
				}
				vectorResultado.back()=nuevoDir;
				nuevoDir = "";
				for(int i = 0; i < vectorResultado.size(); i++){
					nuevoDir += vectorResultado[i] + "/";
				}
				utils::StringUtils util;
				util.removeLastChar(nuevoDir);
				(*it)->setPathProcess(nuevoDir + "/Process");
				std::rename(oldPath.c_str(),nuevoDir.c_str());
				(*it)->setPath(nuevoDir);
		}
		it++;
	}
	return  toReturn;
}

bool Catalog::updateProduct(const std::string& id,
								 std::string nombre, std::string descripcion) {
	threads::Lock lock(this->mutex);
	bool toReturn = false;
	std::vector<Product*>::iterator it = this->products.begin();
	while (it != this->products.end()) {
		if ((*it)->getId() == id) {
				toReturn = true;
				(*it)->setName(nombre);
				(*it)->setDescription(descripcion);
				std::string oldPath = (*it)->getPath();
				utils::StringUtils util;
				std::vector<std::string> v;
				util.tokenizarMensajeConChar(oldPath,v,'/');
				v.back()=nombre;
				std::string newPath = "";
				for(int i = 0; i < v.size(); i++){
					newPath += v[i] + "/";
				}
				util.removeLastChar(newPath);
				utils::Directory dir1(oldPath);
				dir1.remove();
				dir1.make(newPath);
				(*it)->setPath(newPath);

				oldPath = (*it)->getPathIcon();
				v.clear();
				util.tokenizarMensajeConChar(oldPath,v,'/');
				v.back()=nombre;
				newPath = "";
				for(int i = 0; i <v.size(); i++){
					newPath += v[i] + "/";
				}
				util.removeLastChar(newPath);
				utils::Directory dir2(oldPath);
				dir2.remove();
				dir2.make(newPath);
				(*it)->setPathIcon(newPath);
				/*Directorios renombrados*/
		}
		it++;
	}
	return  toReturn;
}

std::string Catalog::listAreas() {
	threads::Lock lock(this->mutex);
	std::string toReturn;
	std::vector<std::string> areasNames;
	utils::StringUtils  utils;
	std::vector<VisionArea*>::iterator it = this->areas.begin();
	while (it != this->areas.end()) {
		areasNames.push_back((*it)->getName());
		it++;
	}
	toReturn = utils.concatenarMensaje(areasNames);
	return toReturn;
}

std::string Catalog::listProducts() {
	threads::Lock lock(this->mutex);
	std::string toReturn;
	std::vector<std::string> productsNames;
	utils::StringUtils  utils;
	std::vector<Product*>::iterator it = this->products.begin();
	while (it != this->products.end()) {
		productsNames.push_back((*it)->getName());
		it++;
	}
	toReturn = utils.concatenarMensaje(productsNames);
	return toReturn;
}

std::string Catalog::getPathProductImages(const std::string& name) {
	threads::Lock lock(this->mutex);
	std::string toReturn = "";
	std::vector<Product*>::iterator it = this->products.begin();
	while (it != this->products.end()) {
		if(name== (*it)->getName()) {
			toReturn = (*it)->getPath();
			break;
		}
		it++;
	}
	return toReturn;
}

std::string Catalog::getPathProductIcons(const std::string& nombre) {
	threads::Lock lock(this->mutex);
	std::string toReturn = "";
	std::vector<Product*>::iterator it = this->products.begin();
	while (it != this->products.end()) {
		if(nombre== (*it)->getName()) {
			toReturn = (*it)->getPathIcon();
			break;
		}
		it++;
	}
	return toReturn;
}

std::string Catalog::getProductDescripcion(const std::string& name) {
	threads::Lock lock(this->mutex);
	std::string toReturn = "";
	std::vector<Product*>::iterator it = this->products.begin();
	while (it != this->products.end()) {
		if(name == (*it)->getName()) {
			toReturn = (*it)->getDescription();
			break;
		}
		it++;
	}
	return toReturn;
}

std::string Catalog::getPathAreasProcess(const std::string& id) {
	threads::Lock lock(this->mutex);
	std::string toReturn = "";
	std::vector<VisionArea*>::iterator it = this->areas.begin();
	while (it != this->areas.end()) {
		if(id== (*it)->getName()) {
			toReturn = (*it)->getPathProcess();
			break;
		}
		it++;
	}
	return toReturn;
}

const std::string Catalog::nextProductId() {
	this->idProducts++;
	utils::StringUtils util;
	std::string idString = util.toString(this->idProducts);
	std::string fill("0");
	idString = util.fillFront(fill,idString,4);
	return (idString);
}

const std::string Catalog::nextAreaId() {
	this->idAreas++;
	utils::StringUtils util;
	std::string idString = util.toString(this->idAreas);
	std::string fill("0");
	idString = util.fillFront(fill,idString,4);
	return (idString);
}

void Catalog::setProductsPath(const std::string& path) {
	this->pathProducts = path;
}
void Catalog::setVisionAreasPath(const std::string& path) {
	this->pathVisionAreas = path;
}

std::vector<Product> Catalog::getProducts() {
	threads::Lock lock(this->mutex);

	std::vector<Product*>::iterator it = this->products.begin();
	std::vector<Product> aux;
	while (it != this->products.end()) {
		Product product((*it)->getId(), (*it)->getName(),
				(*it)->getDescription(),(*it)->getPath(),
				(*it)->getPathIcon(),(*it)->getPathStock());
		aux.push_back(product);
		it++;
	}
	return aux;
}

std::vector<VisionArea> Catalog::getAreas() {
	threads::Lock lock(this->mutex);

	std::vector<VisionArea*>::iterator it = this->areas.begin();
	std::vector<VisionArea> aux;
	while (it != this->areas.end()) {
		VisionArea area((*it)->getId(), (*it)->getName(),(*it)->getType(),
				(*it)->getPath(),(*it)->getPathProcess());
		aux.push_back(area);
		it++;
	}
	return aux;
}


} /* namespace catalog */
