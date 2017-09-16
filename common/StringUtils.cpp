/*
 * StringUtils.cpp
 *
 *  Created on: 06/06/2015
 *      Author: pablito
 */

#include "StringUtils.h"

#include <fstream>
#include <iterator>
#include <iostream>
#include <cstdlib>
namespace utils {

StringUtils::StringUtils() {
	// TODO Auto-generated constructor stub

}

StringUtils::~StringUtils() {
	// TODO Auto-generated destructor stub
}

int StringUtils::compareDate(std::string date1, std::string date2){
	//Recibe las fechas en formato DD/MM/AA/hh/mm y devuelve 1 si date1 > date2, 0 en otro caso.

	std::vector<std::string> d1;
	this->tokenizarMensajeConChar(date1,d1,'/');
	std::vector<std::string> d2;
	this->tokenizarMensajeConChar(date2,d2,'/');
	date1 = d1[2]+d1[1]+d1[0]+d1[3]+d1[4];
	date2 = d2[2]+d2[1]+d2[0]+d2[3]+d2[4];
	int fecha1;
	int fecha2;
	fecha1 = std::atoi(date1.c_str());
	fecha2 = std::atoi(date2.c_str());

	if (fecha1 > fecha2)return 1;
	else if(fecha1 == fecha2) return 0;
	return -1;
}

std::vector<std::string> StringUtils::split(
		const std::string& string, const char del) {
	std::vector<std::string> splitVector;
	unsigned int i = 0;
	std::string subString;
	while (i < string.length()) {
		if (string[i]!= del) {
	       subString+=string[i];
		} else {
			if (!subString.empty()) {
			   splitVector.push_back(subString);
			   subString.clear();
			}
		}
		i++;
	}
	splitVector.push_back(subString);
	return splitVector;
}

std::string StringUtils::toString(const unsigned int integer) {
	std::string string;
	std::ostringstream oss;
	oss << integer;
	string += oss.str();
	return string;
}

std::string StringUtils::fillFront(std::string& fill,
		const std::string& cad,int tot) {
	std::string string;
	for(unsigned int i=tot-1; i>=cad.length(); i--) {
		string+=fill;
	}
	string+=cad;
	return string;
}

void StringUtils::removeLastChar(std::string& string) {
	if (!string.empty()) {
		string.erase(string.length()-1);
	}
}

unsigned int StringUtils::fileToString(const std::string &direccion,
                                      std::string &stringResultado) {

  std::ifstream fin(direccion.c_str(), std::ios::binary);
  std::ostringstream aux;
  aux << fin.rdbuf();
  stringResultado = aux.str();
  fin.close();
  return stringResultado.size();
}

void StringUtils::stringTofile(const std::string &bytesArchivo,
                              const std::string &direccionYNombreSalida) {
  std::ofstream fout(direccionYNombreSalida.c_str());
  fout << bytesArchivo;
  fout.close();
}


// Pasar parametros sin fin de linea, genera un string concatenado de la forma
// parametro1|parametro2|...|ultimoparametro\n
std::string StringUtils::concatenarMensaje(std::vector<std::string>& parametros) {
  std::stringstream buffer;
  std::string mensajeConcatenado;
  std::vector<std::string>::iterator it;
  std::vector<std::string>::iterator final_iter = parametros.end();
  --final_iter;
  for (it = parametros.begin(); it != parametros.end(); ++it) {
    if (it != final_iter)
      buffer << *it << "|";
    else
      buffer << *it;
  }
  buffer << '\n';
  return buffer.str();
}

// Guarda en un vector los parametros de un string concatenado como con la funcion de arriba
void StringUtils::tokenizarMensaje(std::string mensaje,
                                 std::vector<std::string> &vectorResultado) {
  // remover '\n' del final del mensaje si es que lo tiene
  // y no es el unico caracter:
  if (!mensaje.empty() && mensaje[mensaje.length() - 1] == '\n'
      && mensaje.size() > 1) {
    mensaje.erase(mensaje.length() - 1);
  }
  std::stringstream stream(mensaje);
  std::string token;
  while (std::getline(stream, token, '|')) {
    vectorResultado.push_back(token);
  }
}

// Guarda en un vector los parametros de un string concatenado como con la funcion de arriba
void StringUtils::tokenizarMensajeConChar(std::string mensaje,
								 std::vector<std::string> &vectorResultado, char c) {
  // remover '\n' del final del mensaje si es que lo tiene
  // y no es el unico caracter:
  if (!mensaje.empty() && mensaje[mensaje.length() - 1] == '\n'
	  && mensaje.size() > 1) {
	mensaje.erase(mensaje.length() - 1);
  }
  std::stringstream stream(mensaje);
  std::string token;
  while (std::getline(stream, token, c)) {
	vectorResultado.push_back(token);
  }
}

std::string StringUtils::getExtension(const std::string& extension) {
	std::string result;
	if(extension=="png") {
		result = utils::PNG;
	} else if (extension == "jpg") {
		result = utils::JPG;
	} else {
		result = utils::PNG;
	}
	return result;
}
std::string StringUtils::getExtension2(const std::string& extension) {
	std::string result;
	if(extension=="png" || extension=="jpg") result = "EI";
	return result;
}

std::string StringUtils::setExtension(const std::string& extension) {
	std::string result;
	if(extension==utils::PNG) {
		result = ".png";
	} else if (extension == utils::JPG) {
		result = utils::JPG;
	} else if (extension == utils::MPG){
		result = ".mpg";
	} else if (extension == utils::MP4){
		result = ".mp4";
	} else if (extension == utils::AVI){
		result = ".avi";
	}
	return result;
}

} /* namespace utils */
