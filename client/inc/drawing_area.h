#ifndef DRAWING_H
#define DRAWING_H

#include "libmx.h"
#include "view_tools.h"
#include "resources.h"

typedef struct  s_point
{
	int x;
	int y;
	struct s_point *next;
}               t_point; 

static t_point *point, *s_point_start;

void draw_brush(GtkWidget *widget, gdouble x, gdouble y, GtkWidget *draw_area);

gboolean on_draw_button_press_event(GtkWidget *widget, GdkEventButton *event,  t_current_window_info* current_window_info);

gboolean on_draw_button_release_event(GtkWidget *widget, GdkEventButton *event,  t_current_window_info* current_window_info);

gboolean on_draw_draw(GtkWidget *widget, cairo_t *cr, gpointer data);

gboolean on_draw_motion_notify_event(GtkWidget *widget, GdkEventMotion *event, t_current_window_info* current_window_info);

void add_draw_area(t_current_window_info *current_window_info);

void set_rock_on_button(GtkWidget *button, t_current_window_info *current_window_info) ;

#endif