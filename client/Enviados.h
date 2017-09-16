/*
 * Enviados.h
 *
 *  Created on: May 30, 2015
 *      Author: horacio
 */

#ifndef TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_ENVIADOS_H_
#define TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_ENVIADOS_H_

#include <gtkmm/button.h>
#include <gtkmm/iconview.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treemodelfilter.h>
#include <gtkmm/filechooserbutton.h>
#include <string>
#include <vector>
#include "Screen.h"
#include "VentanaOK.h"
#include "DescargarImagenes.h"


class Enviados : public Screen {
 public:
  Enviados(Glib::RefPtr<Gtk::Application> app, Procesador* procesador, Screen* home);
  virtual ~Enviados();
  void show();
  void hide();


 private:
  void agregarProducto(const std::string &s);
  void agregarImagen(const std::string &producto, Glib::RefPtr<Gdk::Pixbuf> img);
  void cargarValoresPrueba();
  void on_botonHome_clicked();
  void on_botonDescargar_clicked();
  void cargarProductos();
  void on_productos_row_activated(const Gtk::TreeModel::Path& path,Gtk::TreeViewColumn*c);
  bool on_filter_row_visible(const Gtk::TreeModel::const_iterator& iter);

  Screen* padre;
  VentanaOK* ventanaOK;
  DescargarImagenes* descargar;
  Procesador* procesador;
  Gtk::Window* window;
  Gtk::Button* botonHome;
  Gtk::Button* botonDescargar;
  Gtk::IconView* iconView;
  Gtk::TreeView* treeView;
  Glib::RefPtr<Gtk::ListStore> treeModelIcons;
  Glib::RefPtr<Gtk::ListStore> treeModelProductos;
  Glib::RefPtr<Gtk::TreeModelFilter> filtroImagenes;
  Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > columnaImagen;
  Gtk::TreeModelColumn<Glib::ustring> columnaNombreImagen;
  Gtk::TreeModelColumn<Glib::ustring> columnaProducto;
  std::string productoElegido;
  std::string aux;
  bool cargados;
};

#endif /* TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_ENVIADOS_H_ */
