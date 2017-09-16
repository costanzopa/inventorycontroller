/*
 * File.cpp
 *
 *  Created on: 30/05/2015
 *      Author: pablito
 */

#include "Stock.h"
#include <cstdlib>
#include <map>
#include <iterator>

namespace utils {

Stock::Stock(){
}

Stock::~Stock() {
}

void Stock::update(const std::string& idProduct,const std::string& path, const std::string& idArea,unsigned int counter, const std::string& date) {
	utils::StringUtils util;
	updateProductStock(idProduct,path,idArea,counter,date);
	updateHistoricStock(idProduct,idArea,counter,date);
	std::cout << "Actual de producto " << idProduct << ":" << getActual(idProduct);
	std::string desde = "01/01/10/00/30";
	std::string hasta = "01/01/10/01/30";
	obtenerHistorico(idProduct,desde,hasta);
}

std::string Stock::calcularIntervalo(const std::string& date){
	std::string hh;
	std::string mm;
	std::vector<std::string> tok;
	utils::StringUtils util;
	util.tokenizarMensajeConChar(date, tok, '/');
	hh = tok[3];
	mm = tok[4];
	if(atoi(mm.c_str())<30){
		return hh+"30";
	}
	std::string s = "0";
	return util.fillFront(s,util.toString(atoi(hh.c_str())+1),2)+"00";
}

void Stock::updateHistoricStock(const std::string& idProduct,const std::string& idArea, unsigned int counter, const std::string& date){
	//Los archivos historicos están en /Historic
	//Creo un archivo por día
	//Antes que nada me fijo si exite ya el archivo para ese día
	//Obtengo la fecha, dia, mes, año, del date
	std::string intervalo = calcularIntervalo(date);
	std::string dia;
	std::string mes;
	std::string anio;
	std::vector<std::string> tok;
	utils::StringUtils util;
	util.tokenizarMensajeConChar(date, tok, '/');
	dia = tok[0];
	mes = tok[1];
	anio = tok[2];
	std::string hh = tok[3];
	std::string mm = tok[4];
	std::ifstream stock;
	std::string f = "data/Historic";
	f += "/" + dia + "_" + mes + "_" + anio + ".csv";
	stock.open(f.c_str());
	bool found = false;
	std::ofstream aux;
	std::string a = "data/Historic/aux.csv";
	aux.open(a.c_str());
	int interEntry, interDato;
	int timeEntry, timeDato;
	timeDato = std::atoi((hh+mm).c_str());
	interDato = std::atoi(intervalo.c_str());
	std::string newEntry = intervalo + "," + hh + mm + "," + idArea + "," + idProduct + "," + util.toString(counter) + "\n";
	if(stock.is_open()){
		std::string stockEntry;
		while(std::getline(stock,stockEntry)){
			std::vector<std::string> toka;
			util.tokenizarMensajeConChar(stockEntry,toka,',');
			std::string entryInterv = toka[0];
			std::string entryTime = toka[1];
			std::string entryArea = toka[2];

			timeEntry = std::atoi(entryTime.c_str());
			interEntry = std::atoi(entryInterv.c_str());

			if(interEntry < interDato){
				/*Todos los que están en un intervalo anterior, los copio tal cual.*/
				aux << stockEntry << "\n";
			} else if(idArea == entryArea && interEntry == interDato){
				/*Si encuentro uno que es de la misma área en el mismo intervalo, lo remplazo*/
				aux << newEntry;
				found = true;
			}else if(idArea != entryArea && interEntry == interDato){
				aux << stockEntry << "\n";
			}else if(interEntry > interDato){
				if(!found){
					/*Si el intervalo es mayor, pero todavía no lo encontré, lo pongo en el medio.*/
					found = true;
					aux << newEntry;
					aux << stockEntry << std::endl;
				} else {
					/*Si ya lo había agregado, sigo con la copia.*/
					aux << stockEntry << std::endl;
				}
			}
		}
		stock.close();
	}

	if(!found)aux << newEntry; /*Si el archivo estaba vacio, lo agrego*/
	aux.close();
	::remove(f.c_str());
	::rename(a.c_str(),f.c_str());

}

void Stock::updateProductStock(const std::string& idProduct, const std::string& path,const std::string& idArea, unsigned int counter, const std::string& date ){
	//Abrir el archivo de stock del producto
	std::ifstream gral;
	std::string g = "data/gral.csv";
	gral.open(g.c_str());
	std::ifstream stock;
	std::string f = path+"/"+"stock.csv";
	stock.open(f.c_str());

	std::string stockEntry;

	std::string entryIdArea;
	std::string entryCant;
	std::string entryDate;

	std::ofstream aux;
	std::string a = path+"/"+"aux.csv";
	aux.open(a.c_str());
	int diff = 0;
	bool found = false;
	bool nuevo = false;
	utils::StringUtils util;
	if(stock.is_open()){
		while(std::getline(stock,stockEntry)){
			//stockEntry tiene el formato: idArea,cantidad,fecha y hora
			std::vector<std::string> v;

			util.tokenizarMensajeConChar(stockEntry,v,',');
			entryIdArea = v[0];
			if(entryIdArea != idArea){
				aux << stockEntry + "\n";
			}
			else {
				found = true;
				//Ya hay una entrada de esa área de visión, hay que actualizarla si date es más nueva que entryDate;
				//if(date > entryDate)
				entryDate = v[2];
				if(util.compareDate(date,entryDate)==1){
					aux << idArea + "," + util.toString(counter) + "," + date + "\n";
					entryCant = v[1];
					int act = std::atoi(entryCant.c_str());
					diff = counter - act;
					nuevo = true;
				}else{
					aux << stockEntry << "\n";
				}
			}
		}
		stock.close();
	}
	if(!found){
		diff = counter;
		aux << idArea + "," + util.toString(counter) + "," + date + "\n";
		nuevo = true;
	}
	aux.close();
	::remove(f.c_str());
	::rename(a.c_str(),f.c_str());
	std::string entryIdProduct;
	std::ofstream auxGral;
	auxGral.open("data/auxGral.csv");
	found = false;
	if(nuevo){
		if(gral.is_open()){
			while(std::getline(gral,stockEntry)){
				std::vector<std::string> v;
				util.tokenizarMensajeConChar(stockEntry,v,',');
				entryIdProduct = v[0];
				if(entryIdProduct == idProduct){
					entryCant = v[1];
					found = true;
					int a = std::atoi(entryCant.c_str());
					a += diff;
					auxGral << entryIdProduct << "," << a << "\n";
				} else {
					auxGral << stockEntry << "\n";
				}

			}
			gral.close();

			auxGral.close();
			::remove(g.c_str());

		}
		if(!found) auxGral << idProduct << "," << counter << "\n";
		::rename("data/auxGral.csv",g.c_str());
	}


	/*También se podría guardar un archivo en la carpeta del área de visión con el id del producto y la cantidad actualizada.
	 * (Podría ser EN LUGAR del archivo que se guarda en la carpeta del producto, o LOS DOS)
	 *  Así, en el obtenerStockAreaVision, no hay que abrir un archivo por cada producto y recorrerlos, abrimos un sólo
	 * del área de visión y listo.
	*/
}

unsigned int Stock::getActual(const std::string& idProduct) {
	//Voy al archivo de stock general, busco el id del producto y devuelvo la cantidad.
	std::ifstream gral;
	gral.open("data/gral.csv");
	if(gral.is_open()){
		std::string stockEntry;
		utils::StringUtils util;
		while(std::getline(gral,stockEntry)){
			std::vector<std::string> v;
			util.tokenizarMensajeConChar(stockEntry,v,',');
			std::string entryIdProduct = v[0];
			if(entryIdProduct == idProduct){
				std::string entryIdCant = v[1];
				return std::atoi(entryIdCant.c_str()) ;
			}
		}
		gral.close();
	}
	return 0;
}


std::vector<int> Stock::obtenerHistorico(const std::string& idProduct, const std::string& desde, const std::string& hasta){
	//Supongo que desde y hasta estan <<<EN EL MISMO DIA Y SON DISTINTOS >>>
	//Busco el archivo correspondiente a ese día
	std::vector<std::string> tok;
	utils::StringUtils util;
	util.tokenizarMensajeConChar(desde, tok, '/');
	std::string dia = tok[0];
	std::string mes = tok[1];
	std::string anio = tok[2];
	std::string hh = tok[3];
	std::string mm = tok[4];
	tok.clear();
	util.tokenizarMensajeConChar(hasta, tok,'/');
	std::string hh2 = tok[3];
	std::string mm2 = tok[4];
	int total = (std::atoi(tok[3].c_str()) - std::atoi(hh.c_str()))*2 + (std::atoi(tok[4].c_str()) - std::atoi(mm.c_str()))/30;

	std::ifstream stock;
	std::string f = "data/Historic";
	f += "/" + dia + "_" + mes + "_" + anio + ".csv";
	stock.open(f.c_str());
	//Supongo que el archivo existe. Si no existe relleno con 0s
	//Busco el intervalo "desde" en el archivo.
	std::string interDesde = calcularIntervalo(desde);
	/*No incluye a la hora final*/
		if(mm2 == "30")mm2 = "29";
		else {
			hh2 = util.toString(std::atoi(hh2.c_str()) - 1);
			mm2 = "59";
		}

	std::string interHasta = calcularIntervalo(tok[0]+"/"+tok[1]+"/"+tok[2] + "/" + hh2 + "/" + mm2);
	std::vector<int> hist(total,0);
	std::map<std::string, std::vector<int> > areas;
	if(stock.is_open()){
		std::string stockEntry;
		/*Este vector tiene el stock histórico.*/
		while(std::getline(stock,stockEntry)){
			std::vector<std::string> toka;
			util.tokenizarMensajeConChar(stockEntry,toka,',');
			std::string entryInterv = toka[0];
			std::string entryTime = toka[1];
			std::string entryArea = toka[2];
			std::string entryProduct = toka[3];
			std::string entryCant = toka[4];

			/*Busco el vector de esta área de visión*/
			if(entryProduct == idProduct){
				if(areas.count(entryArea) == 0){
					std::vector<int> actual (total,0);
					areas[entryArea] = actual;
				}

				std::vector<int>& actual = areas[entryArea];

				/*indice es la posicion donde va el dato del intervalo actual*/
				int indice;
				if(std::atoi(entryInterv.c_str()) > std::atoi(interHasta.c_str()))break;
				if(std::atoi(entryInterv.c_str()) <= std::atoi(interDesde.c_str())){
					indice = 0;
				}else {
					std::string hh3;
					hh3.push_back(entryInterv[0]);
					hh3.push_back(entryInterv[1]);
					std::string mm3;
					mm3.push_back(entryInterv[2]);
					mm3.push_back(entryInterv[3]);
					indice = (std::atoi(hh3.c_str()) - std::atoi(hh.c_str()))*2 + (std::atoi(mm3.c_str()) - std::atoi(mm.c_str()))/30 - 1;
				}
				for(int i = indice; i < total; i++){
					actual[i] = std::atoi(entryCant.c_str());
				}
			}
		}
	}
	for(std::map<std::string, std::vector<int> >::iterator iter = areas.begin(); iter != areas.end(); ++iter){
		for(int i = 0; i < total;i++){
			hist[i] += iter->second[i];
		}
	}
	for(int i = 0; i < hist.size(); i++){
		std::cout << "hist: " << hist[i] << std::endl;
	}
	return hist;
}

void Stock::obtenerStockAreaVision(const std::string& idArea,std::vector<std::string>& idProducts,std::vector<int>& cant){
	/*Ir al archivo de stock de cada producto*/
	utils::StringUtils util;
	//hacer .clear() de los vectores acá, o antes de llamar a esta función.

	//Por cada producto:
	//	std::string id = el id del producto;
	//	std::string f = path del archivo de stock del producto;
	/*	std::ifstream stock;
	 *	stock.open(f.c_str());
	 *	if(stock.is_open()){
	 *		while(std::getline(stock,stockEntry){
	 *			std:vector<std::string> v;
	 *			util.tokenizarMensajeConChar(stockEntry,v,',');
	 *			std::string idAreaEntry = v[0];
	 *			if(idAreaEntry == idArea){
	 *				std::string num = v[1];
	 *				idProducts.push_back(id);
	 *				cant.push_back(std::atoi(num.c_str());
	 *			}
	 *		}
	 *	}
	 *
	 *
	*/
}

} /* namespace utils */
