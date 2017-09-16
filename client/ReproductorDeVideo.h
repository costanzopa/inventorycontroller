/*
 * ReproductorDeVideo.h
 *
 *  Created on: Jun 18, 2015
 *      Author: horacio
 */

#ifndef REPRODUCTORDEVIDEO_H_
#define REPRODUCTORDEVIDEO_H_

#include "ControladorOpenCV.h"
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class ReproductorDeVideo{
 public:
  ReproductorDeVideo(Gtk::Image* imagen);
  void setVideo(const std::string &dir);
  void update();
  void play();
  void stop();
  void pause();
  int getFps() const;
  float getFraccionProgreso();

 private:
  int fps;
  bool playing;
  unsigned int frameIndex;
  ControladorOpenCV openCV;
  Gtk::Image* imagen;
  std::string dir;
  std::vector<cv::Mat> frames;
};

#endif /* REPRODUCTORDEVIDEO_H_ */
