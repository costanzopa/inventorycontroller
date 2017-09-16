//============================================================================
// Name        : Server.cpp
// Author      : 
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : TP4: Inventario por Imagenes
//============================================================================

#include <iostream>
#include "Server.h"
#include "../common/Constants.h"
#include "xmlConfig/ConfigFile.h"
#include "xmlConfig/Configuration.h"

int main() {
	int returnValue = utils::SUCCESFUL_RETURN;
	config::Configuration* config;
	try {
		config::ConfigFile configFile(utils::CONFIG_FILE_PATH);
		config = configFile.getConfig();
		inventory::Server server(config->getPort(),config->getQueue(),config->getCatalog());
		server.start();
		std::cout<<"Se ha iniciado el servidor."<<std::endl;
		char input;
		do {
			std::cin >> input;
		} while ((input != 'q') && (input != 'Q'));
			delete config;
			server.stop();
			std::cout<<"Se ha parado el servidor"<<std::endl;
	} catch (const std::exception &e) {
		std::cerr<<e.what()<<std::endl;

		if (config!= utils::null)
			delete config;

		returnValue = utils::SUCCESFUL_RETURN;
		return returnValue;
	}
	return returnValue;
}
