/*
 * Enviar.h
 *
 *  Created on: May 30, 2015
 *      Author: horacio
 */

#ifndef TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_ENVIAR_H_
#define TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_ENVIAR_H_

#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>
#include <gtkmm/viewport.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/filechooserbutton.h>
#include "Screen.h"
#include "ReproductorDeVideo.h"
#include "Procesador.h"
#include "ControladorOpenCV.h"
#include "VentanaOK.h"

class Enviar : public Screen {
 public:
  Enviar(Glib::RefPtr<Gtk::Application> app,Procesador* procesador, Screen* home);
  virtual ~Enviar();
  void show();
  void hide();
  void clear();

 private:
  void cargarAreasDeVision();
  void setVideo(const std::string &dir);
  void desactivarVideo();
  void on_botonHome_clicked();
  void on_botonPlay_clicked();
  void on_botonPause_clicked();
  void on_botonStop_clicked();
  void on_botonDireccion_file_set();
  void on_comboMetodo_changed();
  void on_comboAreaVision_changed();
  void on_botonEnviar_clicked();
  bool on_video_timeout();

  std::string getFechaHora();
  Screen* padre;
  Procesador* procesador;
  ReproductorDeVideo* rep;
  VentanaOK* ventanaOK;
  bool videoActivo;
  Gtk::Window* window;
  Gtk::Button* botonHome;
  Gtk::Button* botonEnviar;
  Gtk::Button* botonPlay;
  Gtk::Button* botonPause;
  Gtk::Button* botonStop;
  Gtk::Box* boxVideo;
  Gtk::ProgressBar* progressbar;
  Gtk::FileChooserButton* botonDireccion;
  Gtk::ComboBoxText* comboMetodo;
  Gtk::ComboBoxText* comboAreaVision;
  Gtk::ComboBoxText* comboDia;
  Gtk::ComboBoxText* comboMes;
  Gtk::ComboBoxText* comboAnio;
  Gtk::ComboBoxText* comboHora;
  Gtk::ComboBoxText* comboMinutos;
  Gtk::Image* imagen;
  std::string direccionArchivo;
  std::string areaDeVisionElegida;
  bool templateMatching;
  sigc::slot<bool> slot;
};

#endif /* TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_ENVIAR_H_ */
