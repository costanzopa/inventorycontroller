/*
 * File.h
 *
 *  Created on: 30/05/2015
 *      Author: pablito
 */

#ifndef STOCK_H_
#define STOCK_H_
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "StringUtils.h"

namespace utils {

class Stock {
public:
	Stock();
	~Stock();
	void update(const std::string& idProduct, const std::string& path, const std::string& idArea, unsigned int counter, const std::string& date);


	void updateHistoricStock(const std::string& idProduct,const std::string& idArea, unsigned int counter, const std::string& date);
	unsigned int getActual(const std::string& path);
	std::string calcularIntervalo(const std::string& date);
	std::vector<int> obtenerHistorico(const std::string& idProduct, const std::string& desde, const std::string& hasta);
	void obtenerStockAreaVision(const std::string& idArea, std::vector<std::string>& idProducts, std::vector<int>& cant);
	private:
	/*Constructor por copia declarado privado pero no definido
	 * no se deben copiar las instancias de "Archivo").
	*/
	Stock(const Stock &file);
	/*
	 * Operador asignacion de copia declarado privado pero no definido
	 * (no se deben copiar las instancias de "Archivo").
	*/
	Stock& operator=(const Stock &File);

	std::fstream file;
	void updateProductStock(const std::string& idProduct, const std::string& path,const std::string& idArea, unsigned int counter, const std::string& date );
};

} /* namespace utils */
#endif /* STOCK_H_ */
