/*
 * Directory.h
 *
 *  Created on: 14/06/2015
 *      Author: pablito
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include "../common/Exception.h"
#include "Constants.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

namespace utils {

class Directory {
public:
	Directory();
	explicit Directory(const std::string& directory);
	virtual ~Directory();
	std::vector<std::string> getFileNames() const;
	void make(const std::string& path);
	void remove();

private:
	std::vector<std::string> fileNames;
	bool open;
	DIR *dir;
	struct dirent *ent;
	std::string path;
};

} /* namespace utils */
#endif /* DIRECTORY_H_ */
