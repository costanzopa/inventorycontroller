/*
 * ControladorOpenCV.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: horacio
 */

#include "ControladorOpenCV.h"

#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/operations.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <cstdio>
#include <string>

#define FPS_MINIMOS 20

int ControladorOpenCV::getFrames(std::vector<cv::Mat> &frames,
                                 const std::string &dir) {
  cv::VideoCapture capture(dir);
  int fps = (int) capture.get(CV_CAP_PROP_FPS);
  int frame_count = (int) capture.get(CV_CAP_PROP_FRAME_COUNT);
  for (int i = 0; i < frame_count; i++) {
    cv::Mat frame;
    capture >> frame;
    cv::cvtColor(frame, frame, CV_BGR2RGB);
    frames.push_back(frame);
  }

  return fps;
}

void ControladorOpenCV::crearVideo(const std::vector<std::string> &dirImagenes,
                                   const std::string &dirSalida,
                                   const std::string &nombre, int fps,
                                   int ancho, int alto) {

  // si pongo extension mpg el codec tira error (a pesar de estar usando el que dice ser para MPEG-1 )
    // asi que lo creo en .avi y luego lo renombro con .mpg
  std::string direccionAux = dirSalida + "/" + nombre + ".avi";
  std::string direccionFinal = dirSalida + "/" + nombre + ".mpg";

  cv::Mat img;
  cv::Mat imgFinal;

  int j = 0;
  // Si los fps son menores a 20 el codec tira error, entonces copio las imagenes X cantidad
  // de veces para que se vea como si fuesen de esa cantidad de fps.
  if (fps < FPS_MINIMOS) {
    j = FPS_MINIMOS - fps;
    fps = FPS_MINIMOS;
  }

  cv::VideoWriter videoSalida(direccionAux,
                              CV_FOURCC('M','P','E','G'), fps,
                              cv::Size(ancho, alto));

  for (unsigned int i = 0; i < dirImagenes.size(); i++) {
    img = cv::imread(dirImagenes[i], CV_LOAD_IMAGE_COLOR);
    cv::resize(img, imgFinal, cv::Size(ancho, alto));
    for (int k = 0; k < j + 1; k++) {
      videoSalida.write(imgFinal);
    }
  }
  rename(direccionAux.c_str(), direccionFinal.c_str());
}
