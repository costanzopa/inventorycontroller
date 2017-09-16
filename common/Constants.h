/*
 * Constants.h
 *
 *  Created on: 07/06/2015
 *      Author:
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <sys/stat.h>

namespace utils {
	const char separator = '|';
	const unsigned int ZERO = 0;
	const unsigned int null = 0;

	//Server-Client
	const unsigned int SERVER_ARGUMENTS = 3;
	const unsigned int SUCCESFUL_RETURN = 0;
	const unsigned int FAILURE_RETURN = -1;
	const std::string CONFIG_FILE_PATH = "config/config.xml";

	//Request
	const std::string NEW_VISION_AREA = "AA";
	const std::string MODIFY_VISION_AREA = "AM";
	const std::string DELETE_VISION_AREA = "AB";
	const std::string DETAILS_AREA = "DA\n";

	const std::string NEW_PRODUCT = "PA";
	const std::string MODIFY_PRODUCT = "PM";
	const std::string DELETE_PRODUCT = "PB";
	const std::string PRODUCT_IMAGE = "PI";
	const std::string DETAILS_PRODUCT = "DP\n";
	const std::string IMAGES = "II";

	const std::string LIST_PRODUCT = "PL\n";
	const std::string LIST_AREA = "AL\n";

	const std::string STOCK_GENERAL = "SG\n";
	const std::string STOCK_AREA = "SA";
	const std::string STOCK_HISTORIC = "SH";

	const std::string PROCESS_FILE = "PF";
	const std::string PROCESS_VIDEO = "PV";

	//Areas
	const unsigned int CREATE_AREA_ARGU = 3;
	const unsigned int MODIFY_AREA_ARGU = 3;
	const unsigned int DELETE_AREA_ARGU = 2;
	const unsigned int ID_AREA = 1;
	const std::string INVALID_AREA_ID = "0000";


	//Send and Receive
	const std::string ERROR_MESSAGE = "error\n";
	const std::string OK_MESSAGE = "ok\n";
	const char sepList = 0x03;
	const std::string endline = "\n";
	const std::string QUIT = "Q\n";

	//Directorio
	const mode_t MODE_PERMISSIONS = 0777;
	const std::string DIR_SEPARATOR = "/";

	//Matcher
	const double THRESHOLD = 0.9;
	const std::string TM = "TM";
	const std::string FM = "FM";

	//Formatos
	const std::string PNG = "EIP";
	const std::string JPG = "EIJ";
	const std::string MPG = "EV";
	const std::string MP4 = "MP4";
	const std::string AVI = "AVI";
}

#endif /* CONSTANTS_H_ */
