/*
 * GenerarVideo.h
 *
 *  Created on: May 30, 2015
 *      Author: horacio
 */

#ifndef TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_GENERARVIDEO_H_
#define TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_GENERARVIDEO_H_

#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/liststore.h>
#include "Screen.h"
#include "Procesador.h"
#include "ControladorOpenCV.h"
#include "VentanaOK.h"
#include "CrearVideo.h"

class GenerarVideo : public Screen {
 public:
  GenerarVideo(Glib::RefPtr<Gtk::Application> app,Procesador* procesador, Screen* home);
  virtual ~GenerarVideo();
  void show();
  void hide();

 private:
  void on_botonAgregar_clicked();
  void on_botonGenerar_clicked();
  void on_botonHome_clicked();
  void on_botonBorrar_clicked();
  void on_botonDireccion_file_set();
  void on_row_activated(const Gtk::TreeModel::Path& path,Gtk::TreeViewColumn*c);
  Screen* padre;
  VentanaOK* ventanaOK;
  CrearVideo* crearVideo;
  Procesador* procesador;
  Gtk::Window* window;
  Gtk::Button* botonHome;
  Gtk::Button* botonBorrar;
  Gtk::Button* botonGenerar;
  Gtk::Button* botonAgregar;
  Gtk::FileChooserButton* botonDireccionArchivo;
  Gtk::Image* imagen;
  Gtk::TreeView* treeView;
  Glib::RefPtr<Gtk::ListStore> treeModel;
  Gtk::TreeModelColumn<Glib::ustring> columnaNombre;
  Gtk::TreeModelColumn<Glib::ustring> columnaDir;

  std::string direccionImagenElegida;
};

#endif /* UI_SCREENS_ENVIAR_H_ */
