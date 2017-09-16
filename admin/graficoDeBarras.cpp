#include "graficoDeBarras.h"
#include <cairomm/context.h>
#include <cairomm/enums.h>
#include <gtkmm.h>
#include <iostream>

#define MARGEN_INF 30
#define MARGEN_SUP 10

GraficoDeBarras::GraficoDeBarras(Gtk::DrawingArea* dibujo,int tipo){
	this -> dibujo = dibujo;
	dibujo->signal_draw().connect(sigc::mem_fun(this,&GraficoDeBarras::dibu));
	this -> tipo = tipo;
}
bool GraficoDeBarras::setDatos(std::vector<std::string> labels, std::vector<int> datos){
	if (datos.size() == 0) return false;
	if(tipo == GBARRAS_COMPARACION){
		if (labels.size()!=datos.size())return false;
	}
	else if(tipo == GBARRAS_HISTORICO){
		if(labels.size()!=datos.size()+1)return false;
	}
	this->labels = labels;
	this->datos = datos;
	return true;
}
void GraficoDeBarras::vaciar(){
	this->labels.clear();
	this->datos.clear();
}
bool GraficoDeBarras::dibu(const Cairo::RefPtr<Cairo::Context>& contexto){
	Pango::FontDescription font;
	font.set_family("Monospace");
	font.set_size(8*PANGO_SCALE);
	contexto->set_source_rgb(1.0,1.0,1.0);
	contexto->paint();	
	if(datos.size()==0)return false;
	Gdk::Rectangle rect = dibujo->get_allocation();
	int step = 70;
	int max = 0;
	for(int i = 0; i < datos.size(); i++){
		if(datos[i] > max) max = datos[i];
	}
	int total = 0;
	float altoStep = (float)(rect.get_height()-MARGEN_INF-MARGEN_SUP)/max;
	
	dibujo->set_size_request(step*labels.size()+40,300);
	std::stringstream s;
	Glib::RefPtr<Pango::Layout> layout;
	layout = dibujo->create_pango_layout(labels[0]);
	int a,b;
	layout->get_pixel_size(a,b);
	int c,d;
	layout = dibujo->create_pango_layout(labels[labels.size()-1]);
	layout->get_pixel_size(c,d);
	int extra;
	if(tipo == GBARRAS_HISTORICO)extra = ( a + c )/2;
	else if (tipo == GBARRAS_COMPARACION)extra = (a-step)/2+(b-step)/2;
	if(extra<0)extra=0;
	dibujo->set_size_request(step*datos.size()+extra,300);
	int alto = 0;
	int x = 0;
	int y = 0;
	for(int i = 0; i < datos.size(); i++){


		//Dibujo rectangulo

		x = total*step+extra/2;
		alto = datos[i]*altoStep;
		y = rect.get_height() - MARGEN_INF  - alto;
		int t_width,t_height;
		dibujarRectangulo(contexto,x,y,step,alto);

		//Dibujo la cantidad encima de la barra

		s.str("");
		s << datos[i];
		layout = dibujo->create_pango_layout(s.str());
		layout -> set_font_description(font);
		layout -> get_pixel_size(t_width,t_height);
		contexto->set_source_rgb(0,0,0);
		contexto->move_to(x+(step-t_width)/2,y+alto/2);
		layout->show_in_cairo_context(contexto);

		//Dibujo el/los labels para esta barra			

		if(tipo == GBARRAS_COMPARACION){
			s.str("");
			s << labels[i];
			layout = dibujo -> create_pango_layout(s.str());
			layout -> set_font_description(font);
			contexto->set_source_rgb(0,0,0);
			layout -> get_pixel_size(t_width,t_height);
			contexto->move_to(x+(step-t_width)/2,y+alto);
			layout -> show_in_cairo_context(contexto);
		}else if(tipo == GBARRAS_HISTORICO){
			s.str("");
			s << labels[i];
			layout = dibujo -> create_pango_layout(s.str());
			layout -> set_font_description(font);
			contexto->set_source_rgb(0,0,0);
			layout -> get_pixel_size(t_width,t_height);
			contexto->move_to(x-t_width/2,y+alto);
			layout -> show_in_cairo_context(contexto);	
		}
		total ++;
	}
	if(tipo == GBARRAS_HISTORICO){
		int t_width,t_height;
		s.str("");
		s << labels[labels.size()-1];	
		layout = dibujo -> create_pango_layout(s.str());
		layout -> set_font_description(font);
		contexto->set_source_rgb(0,0,0);
		layout -> get_pixel_size(t_width,t_height);
		contexto->move_to(x+step-t_width/2,y+alto);
		layout -> show_in_cairo_context(contexto);	
	}
	return true;
}
void GraficoDeBarras::dibujarRectangulo(const Cairo::RefPtr<Cairo::Context>& c,int x, int y, int ancho,int alto){
	c->set_source_rgb(1.0,0.0,0.0);
	c->rectangle(x,y,ancho,alto);
	c->fill_preserve();
	c->set_source_rgb(0,0,0);
	c->stroke();
}

void GraficoDeBarras::dibujar(){
	Gdk::Rectangle r(0,0,dibujo->get_allocation().get_width(),dibujo->get_allocation().get_height());
	win = dibujo -> get_window();
	win->invalidate_rect(r,false);
}

