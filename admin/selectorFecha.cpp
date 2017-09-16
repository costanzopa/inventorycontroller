#include "selectorFecha.h"
#include <iostream>
#include "../common/StringUtils.h"
/****** CONSTRUCTOR ******/

SelectorFecha::SelectorFecha(BaseObjectType* cobject, Glib::RefPtr<Gtk::Builder>& builder):Gtk::Box(cobject){
	builder -> get_widget("fechaDesdeCalendar",fechaDesdeCalendar);
	builder -> get_widget("fechaHastaCalendar",fechaHastaCalendar);
	builder -> get_widget("horaDesdeCombo",horaDesdeCombo);
	builder -> get_widget("horaHastaCombo",horaHastaCombo);
	builder -> get_widget("minDesdeCombo",minDesdeCombo);
	builder -> get_widget("minHastaCombo",minHastaCombo);
	builder -> get_widget("principioCheck",principioCheck);
	builder -> get_widget("finCheck",finCheck);
	principioCheck->signal_toggled().connect(sigc::mem_fun(this,&SelectorFecha::toggleDesdeActivo));
	finCheck->signal_toggled().connect(sigc::mem_fun(this,&SelectorFecha::toggleHastaActivo));
}

/****** ACTIVAR O DESACTIVAR LOS CALENDARIOS ******/

void SelectorFecha::toggleDesdeActivo(){
	fechaDesdeCalendar->set_sensitive(!principioCheck->get_active());
	horaDesdeCombo->set_sensitive(!principioCheck->get_active());
	minDesdeCombo->set_sensitive(!principioCheck->get_active());
}
void SelectorFecha::toggleHastaActivo(){
	fechaHastaCalendar->set_sensitive(!finCheck->get_active());
	horaHastaCombo->set_sensitive(!finCheck->get_active());
	minHastaCombo->set_sensitive(!finCheck->get_active());
}

/****** OBTENER LAS FECHAS ******/

std::string SelectorFecha::obtenerDesde(){
	if(principioCheck->get_active()) return "";
	guint dia;
	guint mes;
	guint anio;
	fechaDesdeCalendar->get_date(anio,mes,dia);
	utils::StringUtils util;
	std::string s_dia = util.toString(dia);
	std::string cero = "0";
	s_dia = util.fillFront(cero,s_dia,2);
	std::string s_mes = util.toString(mes+1);
	s_mes = util.fillFront(cero,s_mes,2);
	std::string s_anio = util.toString(anio);
	std::string ss_anio;
	ss_anio.push_back(s_anio[2]);
	ss_anio.push_back(s_anio[3]);
	std::string s_fecha = s_dia + "/" + s_mes + "/" + ss_anio;
	std::string s_hora = horaDesdeCombo->get_active_text();
	std::string s_min = minDesdeCombo->get_active_text();
	return s_fecha + "/" + s_hora + "/" + s_min;
}
std::string SelectorFecha::obtenerHasta(){
	if(finCheck->get_active()) return "";
	guint dia;
	guint mes;
	guint anio;
	fechaHastaCalendar->get_date(anio,mes,dia);
	utils::StringUtils util;
	std::string cero = "0";
	std::string s_dia = util.toString(dia);
	s_dia = util.fillFront(cero,s_dia,2);
	std::string s_mes = util.toString(mes+1);
	s_mes = util.fillFront(cero,s_mes,2);
	std::string s_anio = util.toString(anio);
	std::string ss_anio;
	ss_anio.push_back(s_anio[2]);
	ss_anio.push_back(s_anio[3]);
	std::string s_fecha = s_dia + "/" + s_mes + "/" + ss_anio;
	std::string s_hora = horaHastaCombo->get_active_text();
	std::string s_min = minHastaCombo->get_active_text();

	return s_fecha + "/" + s_hora + "/" + s_min;
}
