/*
 * Procesador.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: horacio
 */

#include "Procesador.h"

#include <fstream>
#include <iostream>
#include <sstream>

Procesador::Procesador() {
  comunicacion = new net::Communication("localhost", "12345");  // TEMPORAL
  protocolo = new Protocolo(comunicacion);
}

Procesador::~Procesador() {
  delete comunicacion;
  delete protocolo;
}

void Procesador::actualizar() {
  delete comunicacion;
  comunicacion = new net::Communication("localhost", "12345");  // TEMPORAL
}

void Procesador::getAreasDeVision(std::vector<std::string> &areasDeVision) {
  protocolo->getAreasDeVision(areasDeVision);
}

// devuelve tamaño del archivo y almacena el archivo como string en stringResultado
unsigned int Procesador::fileToString(const std::string &direccion,
                                      std::string &stringResultado) {

  std::ifstream fin(direccion.c_str(), std::ios::binary);
  std::ostringstream aux;
  aux << fin.rdbuf();
  stringResultado = aux.str();
  fin.close();
  return stringResultado.size();
}

void Procesador::stringTofile(const std::string &bytesArchivo,
                              const std::string &direccionYNombreSalida) {
  std::ofstream fout(direccionYNombreSalida.c_str());
  fout << bytesArchivo;
  fout.close();
}

bool Procesador::enviarImagen(std::vector<std::string> &respuesta,
                              const std::string &areaDeVision,
                              bool featureMatching,
                              const std::string &fechaYHora,
                              const std::string &direccion) {
  std::string mensajeImagen;
  std::string aux;
  std::cout << fileToString(direccion, mensajeImagen) << std::endl;
  bool png = false;
  if (getFileExtension(direccion) == "png")
    png = true;
  try {
    protocolo->enviarImagen(png, featureMatching, areaDeVision, fechaYHora,
                            mensajeImagen);
    comunicacion->receive(aux);
  } catch (...) {
    return false;
  }
  protocolo->tokenizarMensaje(aux, respuesta);
  return true;
}

bool Procesador::enviarVideo(std::vector<std::string> &respuesta,
                             const std::string &areaDeVision,
                             bool featureMatching,
                             const std::string &fechaYHora,
                             const std::string &direccion) {
  std::string mensajeImagen;
  std::string aux;
  std::cout << fileToString(direccion, mensajeImagen) << std::endl;
  try {
    protocolo->enviarVideo(featureMatching, areaDeVision, fechaYHora,
                           mensajeImagen);
    comunicacion->receive(aux);
  } catch (...) {
    return false;
  }
  protocolo->tokenizarMensaje(aux, respuesta);
  return true;
}

bool Procesador::getProductos(std::vector<std::string> &productos) {
  try {
    protocolo->getProductos(productos);
  } catch (...) {
    return false;
  }
  return true;
}

bool Procesador::getImagenesDeProducto(const std::string &producto,
                                       std::vector<std::string> &imagenes,
                                       std::vector<std::string> &extensiones) {
  try {
    protocolo->getImagenesDeProducto(producto, imagenes, extensiones);
  } catch (...) {
    return false;
  }
  return true;
}

std::string Procesador::getFileExtension(const std::string &direccionArchivo) {
  return direccionArchivo.substr(direccionArchivo.find_last_of(".") + 1);
}

std::string Procesador::getFileName(const std::string &direccionArchivo) {
  return direccionArchivo.substr(direccionArchivo.find_last_of("/") + 1);
}

std::string Procesador::getFilePath(const std::string &direccionArchivo) {
  return direccionArchivo.substr(0, direccionArchivo.find_last_of("/") + 1);
}

