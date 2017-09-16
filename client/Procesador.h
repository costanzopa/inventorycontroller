/*
 * Procesador.h
 *
 *  Created on: Jun 9, 2015
 *      Author: horacio
 */

#ifndef PROCESADOR_H_
#define PROCESADOR_H_

#include "../common/Protocolo.h"
#include "../common/Communication.h"
#include "../common/StringUtils.h"
#include <string>
#include <vector>

class Procesador {
 public:
  Procesador();
  virtual ~Procesador();
  void actualizar();
  void getAreasDeVision(std::vector<std::string> &areasDeVision);
  bool enviarImagen(std::string areaDeVision, bool templateMatching,
                    std::string fechaYHora, const std::string &direccion);
  std::string getFileExtension(const std::string &direccionArchivo);
  std::string getFileName(const std::string &direccionArchivo);
  std::string getFilePath(const std::string &direccionArchivo);
  bool enviarImagen(std::vector<std::string> &respuesta,
                    const std::string &areaDeVision, bool featureMatching,
                    const std::string &fechaYHora,
                    const std::string &direccion);
  bool enviarVideo(std::vector<std::string> &respuesta,
                               const std::string &areaDeVision,
                               bool featureMatching,
                               const std::string &fechaYHora,
                               const std::string &direccion);
  bool getProductos(std::vector<std::string> &productos);
  bool getImagenesDeProducto(const std::string &producto,
                             std::vector<std::string> &imagenes,
                             std::vector<std::string> &extensiones);
  unsigned int fileToString(const std::string &direccion,
                            std::string &stringResultado);
  void stringTofile(const std::string &bytesArchivo,
                    const std::string &direccionYNombreSalida);
 private:
  Protocolo* protocolo;
  net::Communication *comunicacion;
  utils::StringUtils stringUtils;
};

#endif /* PROCESADOR_H_ */
