/*
 * CrearVideo.h
 *
 *  Created on: Jun 15, 2015
 *      Author: horacio
 */

#ifndef CREARVIDEO_H_
#define CREARVIDEO_H_

#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/liststore.h>

#include "Procesador.h"
#include "Screen.h"
#include "ControladorOpenCV.h"
#include "VentanaOK.h"

class CrearVideo : public Screen {
 public:
  CrearVideo(Glib::RefPtr<Gtk::Application> app,Procesador* procesador, Screen* padre);
  virtual ~CrearVideo();
  void show();
  void hide();
  void setDirImagenes(const std::vector<std::string>& dirImagenes) {
    this->dirImagenes = dirImagenes;
  }

 private:
  void on_botonAceptar_clicked();
  void on_botonCancelar_clicked();
  void on_botonCrear_clicked();
  Procesador* procesador;
  ControladorOpenCV openCV;
  Gtk::Window* window;
  Gtk::Button* botonCrear;
  Gtk::FileChooserDialog* fileChooser;
  Gtk::Button* botonCancelar;
  Gtk::Button* botonAceptar;
  Gtk::SpinButton* spinFPS;
  Gtk::SpinButton* spinAncho;
  Gtk::SpinButton* spinAlto;
  Screen* padre;
  VentanaOK* ventanaOK;
  VentanaOK* ventanaCreado;
  std::vector<std::string> dirImagenes;
};

#endif /* CREARVIDEO_H_ */
