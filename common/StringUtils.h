/*
 * StringUtils.h
 *
 *  Created on: 06/06/2015
 *      Author:
 */

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_
#include <string>
#include <vector>
#include <sstream>
#include "Constants.h"

namespace utils {

class StringUtils {
public:
	StringUtils();
	~StringUtils();
	std::vector<std::string> split(const std::string& string,
								   const char delimiter);

	std::string toString(const unsigned int integer);
	std::string fillFront(std::string& fill,
			const std::string& cad,int tot);
	void removeLastChar(std::string& string);
	std::string concatenarMensaje(std::vector<std::string>& parametros);
	void tokenizarMensaje(std::string mensaje,
	                      std::vector<std::string> &vectorMensaje);
	std::string getExtension(const std::string& extension);
   unsigned int fileToString(const std::string &direccion,
                            std::string &stringResultado);
  void stringTofile(const std::string &bytesArchivo,
                    const std::string &direccionYNombreSalida);
  std::string setExtension(const std::string& extension);

  void tokenizarMensajeConChar(std::string mensaje, std::vector<std::string>& vectorResultado, char c);
  std::string getExtension2(const std::string& extension);
  int compareDate(std::string date1, std::string date2);
};

} /* namespace utils */
#endif /* STRINGUTILS_H_ */
