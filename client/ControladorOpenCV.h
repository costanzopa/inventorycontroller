/*
 * ControladorOpenCV.h
 *
 *  Created on: Jun 11, 2015
 *      Author: horacio
 */

#ifndef CONTROLADOROPENCV_H_
#define CONTROLADOROPENCV_H_

#include <cv.h>
#include <vector>

class ControladorOpenCV {
 public:
  int getFrames(std::vector<cv::Mat> &frames, const std::string &dir);
  void crearVideo(const std::vector<std::string> &dirImagenes,
                  const std::string &nombre, const std::string &dirSalida,
                  int fps, int ancho, int alto);
};

#endif /* CONTROLADOROPENCV_H_ */
