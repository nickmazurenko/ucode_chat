#include "drawing_area.h"


void draw_brush(GtkWidget *widget, gdouble x, gdouble y, GtkWidget *draw_area)
{
	point = malloc(sizeof(struct s_point));
	if (point == NULL)
	{
		printf("out of memory\n");
		abort();
	}

	point->x = x;
	point->y = y;
	point->next = s_point_start;
	s_point_start = point;

	//check for better effectivness
	// gtk_widget_queue_draw(draw_area);

	gtk_widget_queue_draw_area(draw_area, 0, 0, 600, 600);
	
}

gboolean on_draw_button_press_event(GtkWidget *widget, GdkEventButton *event,  t_current_window_info* current_window_info)
{
	GtkWidget *draw_area = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "draw"));
    draw_brush(widget, event->x, event->y, draw_area);
	return TRUE;
}

gboolean on_draw_button_release_event(GtkWidget *widget, GdkEventButton *event,  t_current_window_info* current_window_info)
{

	GdkWindow *window = gtk_widget_get_window(widget);
	
	GdkPixbuf *pixbuf = gdk_pixbuf_get_from_window(window, 0, 0, 1366, 768);
	
	gdk_pixbuf_save(pixbuf, "new.png", "png", NULL, NULL, NULL); // TODO: change path

    return TRUE;
}

gboolean on_draw_draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{

    cairo_surface_t *cairo_image_surface = cairo_image_surface_create_from_png(get_path_to_image("surface.png"));

	guint width, height;
	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);

	cairo_set_line_width(cr, 4.0);

	if (s_point_start == NULL) {
    	return FALSE;
    }

        int old_x = s_point_start->x;
        int old_y = s_point_start->y;

        point = s_point_start->next;
        
	while (point != NULL)
	{
		// to lay texture
        cairo_set_source_surface(cr, cairo_image_surface, 0, 0);
        // cairo_set_source_rgb(cr, 0.2, 0.3, 0.2);
        
		cairo_move_to(cr, (double)old_x, (double)old_y);
        // if(ABS((point->x - old_x)) < cairo_get_line_width(cr) * 5 && ABS((point->y - old_y)) < cairo_get_line_width(cr) * 5) {
		    cairo_line_to(cr, (double)point->x, (double)point->y);

			// weird line version
	        // cairo_curve_to(cr, point->x, point->y, point->x + 3, point->y + 3, point->x + 5, point->y + 5);
        // }

        cairo_stroke(cr);

		// pixel version !!!!

		// cairo_rectangle(cr, old_x, old_y, 4, 4);
        // cairo_fill(cr);
		old_x = point->x;
        old_y = point->y;

        point = point->next;
	}
	
	return TRUE;
}



gboolean on_draw_motion_notify_event(GtkWidget *widget, GdkEventMotion *event, t_current_window_info* current_window_info)
{
	GtkWidget *draw_area = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "draw"));
	if (event->state & GDK_BUTTON1_MASK) {
		draw_brush(widget, event->x, event->y, draw_area);
    }
    return TRUE;
}

void add_draw_area(t_current_window_info *current_window_info) {

	GtkBuilder* drawing_window_builder = gtk_builder_new_from_file(get_path_to_glade("drawing_area.glade"));
    
    GtkWidget *drawing_window = GTK_WIDGET(gtk_builder_get_object(drawing_window_builder, "drawing_window"));
    g_signal_connect(drawing_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    
    t_current_window_info *drawing_window_info = NULL;
    
    drawing_window_info = create_current_window_info();
    drawing_window_info->main_window = drawing_window;
    drawing_window_info->builder = drawing_window_builder;
    
	GtkWidget *draw_area = GTK_WIDGET(gtk_builder_get_object(drawing_window_info->builder, "draw"));
	
    g_signal_connect(draw_area, "button-press-event", G_CALLBACK(on_draw_button_press_event), drawing_window_info);
    g_signal_connect(draw_area, "button-release-event", G_CALLBACK(on_draw_button_release_event), drawing_window_info);
    g_signal_connect(draw_area, "draw", G_CALLBACK(on_draw_draw), drawing_window_info);
    g_signal_connect(draw_area, "motion-notify-event", G_CALLBACK(on_draw_motion_notify_event), drawing_window_info);
    gtk_widget_set_events(draw_area, GDK_BUTTON_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);

    gtk_widget_show(drawing_window);

    gtk_main();

}


