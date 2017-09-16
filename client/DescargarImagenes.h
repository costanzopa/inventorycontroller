/*
 * DescargarImagenes.h
 *
 *  Created on: Jun 20, 2015
 *      Author: horacio
 */

#ifndef DESCARGARIMAGENES_H_
#define DESCARGARIMAGENES_H_

#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/filechooserdialog.h>

#include "Procesador.h"
#include "Screen.h"
#include "VentanaOK.h"

class DescargarImagenes: public Screen {
 public:
  DescargarImagenes(Glib::RefPtr<Gtk::Application> app, Procesador* procesador, Screen* padre);
  virtual ~DescargarImagenes();
  void setImagenes(std::vector<Glib::RefPtr<Gdk::Pixbuf> > &imagenes);
  void show();
  void hide();
 private:
  void on_botonAceptar_clicked();
  void on_botonCancelar_clicked();

  Screen* padre;
  Procesador* procesador;
  VentanaOK* ventanaOK;
  VentanaOK* ventanaDescargado;
  Gtk::Window* window;
  Gtk::FileChooserDialog* fileChooser;
  Gtk::Button* botonCancelar;
  Gtk::Button* botonAceptar;
  std::vector<Glib::RefPtr<Gdk::Pixbuf> > imagenes;
};

#endif
