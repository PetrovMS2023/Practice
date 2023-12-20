#pragma once
#include <gtkmm.h>
#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H

#include <gtkmm/drawingarea.h>

class MyArea : public Gtk::DrawingArea
{
public:
  MyArea();
  virtual ~MyArea();
  void setParam(double a, double b, double c);
  gfloat f(gfloat x);
  void setT(double t);
  protected:
  //Перекрытие стандартного обработчика сигналов:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
private:
  double a,b,c,t;
};

#endif
