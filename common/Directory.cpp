/*
 * Directory.cpp
 *
 *  Created on: 14/06/2015
 *      Author: pablito
 */

#include "Directory.h"

namespace utils {

Directory::Directory() {
	open=false;
}

Directory::Directory(const std::string& directory) {
	try {
		open =  false;
		dir = opendir (directory.c_str());
		this->path = directory;
		if (dir == NULL)
		   throw(exceptions::DirectoryException("No se pudo abrir el directorio"));
		open=true;
		std::string filename;
		 while ((ent = readdir (dir)) != NULL)  {
			 std::string filepath;
			 filename+=this->ent->d_name;
			 if(filename != "." && filename != "..") {
				 filepath=directory+"/"+filename;
				 this->fileNames.push_back(filepath);
			 }
			 filepath.clear();
			 filename.clear();
		 }
	} catch (std::exception& e) {
		std::cerr<<e.what()<<std::endl;
	}
}

Directory::~Directory() {
	if (open) {
		closedir(this->dir);
	}
}

std::vector<std::string> Directory::getFileNames() const {
	return (this->fileNames);
}

void Directory::make(const std::string& path) {
	int value = 0;
	if (!path.empty()) {
		value = mkdir(path.c_str(),utils::MODE_PERMISSIONS);
		if (value != 0) {
			throw (exceptions::DirectoryException("No se pudo crear el directorio"));
		}
	} else {
		throw (exceptions::DirectoryException("Directorio invalido."));
	}
}

void Directory::remove() {
	std::vector<std::string> files = this->getFileNames();
	std::vector<std::string>::iterator it = files.begin();

	while (it != files.end()) {
		::remove((*it).c_str());
		it++;
	}
	rmdir(path.c_str());

}


} /* namespace utils */
