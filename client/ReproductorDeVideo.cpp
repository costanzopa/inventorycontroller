/*
 * ReproductorDeVideo.cpp
 *
 *  Created on: Jun 18, 2015
 *      Author: horacio
 */

#include "ReproductorDeVideo.h"

#include <gdkmm/pixbuf.h>
#include <glibconfig.h>
#include <glibmm/refptr.h>
#include <opencv2/core/mat.hpp>
#include <string>
#include <vector>

ReproductorDeVideo::ReproductorDeVideo(Gtk::Image* imagen) {
  this->imagen = imagen;
  playing = false;
  frameIndex = 0;
  fps = 0;
}

void ReproductorDeVideo::update() {

  if (frameIndex >= frames.size())
    playing = false;

  if (playing) {
    cv::Mat& imagenMat = this->frames[frameIndex];
    Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data(
        (guint8*) imagenMat.data, Gdk::COLORSPACE_RGB, false, 8, imagenMat.cols,
        imagenMat.rows, imagenMat.step);
    imagen->set(pixbuf);
    frameIndex++;
  }
}

void ReproductorDeVideo::setVideo(const std::string &dir) {
  frames.clear();
  fps = openCV.getFrames(frames, dir);
}

void ReproductorDeVideo::play() {
  if (frameIndex >= frames.size())
    frameIndex = 0;
  playing = true;
}

void ReproductorDeVideo::stop() {
  frameIndex = 0;
  this->update();
  frameIndex = 0;
  playing = false;
}

void ReproductorDeVideo::pause() {
  playing = false;
}

int ReproductorDeVideo::getFps() const {
  return fps;
}

float ReproductorDeVideo::getFraccionProgreso() {
  return ((float) frameIndex / (float) frames.size());
}
