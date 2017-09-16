#include "graficoDeTorta.h"
#include <algorithm>
#include <cairomm/context.h>
#include <cairomm/enums.h>
#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
bool comparador(std::pair<std::string,int> a, std::pair<std::string,int> b){
	return a.second<b.second;
}
GraficoDeTorta::GraficoDeTorta(Gtk::DrawingArea* dibujo){
	srand(time(NULL));
	this -> dibujo = dibujo;
	dibujo->signal_draw().connect(sigc::mem_fun(this,&GraficoDeTorta::dibujar));
}

void GraficoDeTorta::mezclarColores(){
	red.clear();
	green.clear();
	blue.clear();
	for(int i=0; i < stock.size();i++){
		red.push_back((float)(rand()%1000)/1000);
		green.push_back((float)(rand()%1000)/1000);
		blue.push_back((float)(rand()%1000)/1000);
	}
}
bool GraficoDeTorta::dibujar(const Cairo::RefPtr<Cairo::Context>& contexto){
	Gdk::Rectangle rect = dibujo->get_allocation();
	Pango::FontDescription font;
	font.set_family("Monospace");
	font.set_weight(Pango::WEIGHT_BOLD);

	if(stock.size() == 0) return false;
	contexto->set_source_rgb(1.0,1.0,1.0);
	contexto->paint();	
	
	int total = 0;
	for(int i = 0; i < stock.size(); i++){
		total +=  stock[i].second;
	}
	float step = 2*M_PI/total;
	total = 0;
	

	float angulo0=0;
	for(int i = 0; i < stock.size(); i++){
		float angulo1 = step*stock[i].second + angulo0;
		dibujarArco(contexto,rect.get_width()/2-rect.get_width()/4,rect.get_height()/2,rect.get_width()<rect.get_height()?rect.get_width()/4:rect.get_height()/4,angulo0,angulo1,red[i],green[i],blue[i]);
		angulo0 = angulo1;
	}
	
	Glib::RefPtr<Pango::Layout> layout;
	std::stringstream s;
	for(int i = 0; i < stock.size(); i++){
		s.str("");
		s << stock[i].first << "\t" << stock[i].second;
		layout = dibujo->create_pango_layout(s.str());
		layout -> set_font_description(font);
		int t_width, t_height;
		layout->get_pixel_size(t_width,t_height);
		contexto->set_source_rgb(0,0,0);	
		contexto -> move_to((rect.get_width())/2,15*(i+1)+5);
		layout -> show_in_cairo_context(contexto);
		contexto -> set_source_rgb(red[i],green[i],blue[i]);
		contexto -> rectangle(rect.get_width()/2+80,15*(i+1)+5,30,15);
		contexto -> fill();
	}
	return true;
}

void GraficoDeTorta::dibujarArco(const Cairo::RefPtr<Cairo::Context>& c,int x, int y, int radio, float angulo0, float angulo1,float r, float g, float b){
	c->set_source_rgb(1,1,1);
	c->set_line_width(2);
	c->arc(x,y,radio, angulo0, angulo1);
	c->line_to(x,y);
	c->close_path();
	c->stroke_preserve();
	c->set_source_rgb(r,g,b);
	c->fill();
}

void GraficoDeTorta::setearDatos(std::vector<std::pair<std::string,int> > stock){
	this->stock = stock;
	std::sort(this->stock.begin(),this->stock.end(),comparador);
	mezclarColores();
}

void GraficoDeTorta::dibujarStock(){
	Gdk::Rectangle r(0,0,dibujo->get_allocation().get_width(),dibujo->get_allocation().get_height());
	win = dibujo -> get_window();
	win->invalidate_rect(r,false);
}


