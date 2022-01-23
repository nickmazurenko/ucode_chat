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

	gtk_widget_queue_draw_area(draw_area, 0, 0, 440, 300);
	
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

	cairo_set_line_width(cr, 2.0);

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
        if(ABS((point->x - old_x)) < cairo_get_line_width(cr) * 5 && ABS((point->y - old_y)) < cairo_get_line_width(cr) * 5) {
		    cairo_line_to(cr, (double)point->x, (double)point->y);

			// weird line version
	        // cairo_curve_to(cr, point->x, point->y, point->x + 3, point->y + 3, point->x + 5, point->y + 5);
        }

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

	gtk_widget_hide(current_window_info->main_window);

	// create layout form glade
	// add layout to current window
    gtk_builder_add_from_file(current_window_info->builder, get_path_to_glade("drawing_area.glade"), NULL);


    GtkLayout *drawing_area_layout = GTK_LAYOUT(gtk_builder_get_object(current_window_info->builder, "draw_layout"));

    GtkLayout *current_layout = GTK_LAYOUT(gtk_builder_get_object(current_window_info->builder, "sign_in_layout")); //TODO: replace layout

    // gtk_widget_destroy(current_layout);
    // gtk_container_add(GTK_CONTAINER(current_window_info->main_window), GTK_WIDGET(drawing_area_layout));
	// current_layout = GTK_LAYOUT(gtk_builder_get_object(current_window_info->builder, "sign_in_layout"));
	// gtk_container_add(GTK_CONTAINER(drawing_area_layout), GTK_WIDGET(current_layout));
    gtk_container_add(GTK_CONTAINER(current_layout), GTK_WIDGET(drawing_area_layout));


	GtkWidget *draw_area = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "draw"));
	
    g_signal_connect(draw_area, "button-press-event", G_CALLBACK(on_draw_button_press_event), current_window_info);
    g_signal_connect(draw_area, "button-release-event", G_CALLBACK(on_draw_button_release_event), current_window_info);
    g_signal_connect(draw_area, "draw", G_CALLBACK(on_draw_draw), current_window_info);
    g_signal_connect(draw_area, "motion-notify-event", G_CALLBACK(on_draw_motion_notify_event), current_window_info);
    gtk_widget_set_events(draw_area, GDK_BUTTON_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
    gtk_widget_show_all(current_window_info->main_window);
}


