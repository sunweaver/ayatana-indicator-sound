/*
Copyright 2010 Canonical Ltd.

Authors:
    Conor Curran <conor.curran@canonical.com>
    Mirco Müller <mirco.mueller@canonical.com>

This program is free software: you can redistribute it and/or modify it 
under the terms of the GNU General Public License version 3, as published 
by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranties of 
MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR 
PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along 
with this program.  If not, see <http://www.gnu.org/licenses/>.

Uses code from ctk
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <math.h>
#include "play-button.h"

#define RECT_WIDTH 130.0f
#define Y 5.0f
#define X	37.0f
#define INNER_RADIUS 12.5
#define	MIDDLE_RADIUS 13.5f
#define OUTER_RADIUS  14.5f
#define CIRCLE_RADIUS 21.0f
#define PREV_WIDTH  25.0f
#define PREV_HEIGHT 17.0f
#define	NEXT_WIDTH  25.0f //PREV_WIDTH
#define NEXT_HEIGHT 17.0f //PREV_HEIGHT
#define TRI_WIDTH  11.0f
#define TRI_HEIGHT 13.0f
#define TRI_OFFSET  6.0f
#define PREV_X 35.0f
#define PREV_Y 11.0f
#define NEXT_X 113.0f
#define NEXT_Y 11.0f //prev_y
#define PAUSE_WIDTH 21.0f
#define PAUSE_HEIGHT 27.0f
#define BAR_WIDTH 4.5f
#define BAR_HEIGHT 24.0f
#define BAR_OFFSET 10.0f
#define PAUSE_X 78.0f
#define	PAUSE_Y 5.0f
#define PLAY_WIDTH 28.0f
#define PLAY_HEIGHT 29.0f
#define PLAY_PADDING 5.0f

typedef struct _PlayButtonPrivate PlayButtonPrivate;

struct _PlayButtonPrivate
{
	GdkColor 				background_colour_fg;
	GdkColor 				background_colour_bg_dark;
	GdkColor 				background_colour_bg_light;
	GdkColor 				foreground_colour_fg;
	GdkColor 				foreground_colour_bg;
	PlayButtonEvent current_command;
	PlayButtonState current_state;
	GHashTable* 		command_coordinates;	
};

#define PLAY_BUTTON_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), PLAY_BUTTON_TYPE, PlayButtonPrivate))

/* Gobject boiler plate */
static void play_button_class_init (PlayButtonClass *klass);
static void play_button_init       (PlayButton *self);
static void play_button_dispose    (GObject *object);
static void play_button_finalize   (GObject *object);

static gboolean play_button_expose (GtkWidget *button, GdkEventExpose *event);
static void draw (GtkWidget* button, cairo_t *cr);

G_DEFINE_TYPE (PlayButton, play_button, GTK_TYPE_DRAWING_AREA);

/// internal helper functions //////////////////////////////////////////////////


static inline void
_blurinner (guchar* pixel,
	    gint*   zR,
	    gint*   zG,
	    gint*   zB,
	    gint*   zA,
	    gint    alpha,
	    gint    aprec,
	    gint    zprec)
{
	gint R;
	gint G;
	gint B;
	guchar A;

	R = *pixel;
	G = *(pixel + 1);
	B = *(pixel + 2);
	A = *(pixel + 3);

	*zR += (alpha * ((R << zprec) - *zR)) >> aprec;
	*zG += (alpha * ((G << zprec) - *zG)) >> aprec;
	*zB += (alpha * ((B << zprec) - *zB)) >> aprec;
	*zA += (alpha * ((A << zprec) - *zA)) >> aprec;

	*pixel       = *zR >> zprec;
	*(pixel + 1) = *zG >> zprec;
	*(pixel + 2) = *zB >> zprec;
	*(pixel + 3) = *zA >> zprec;
}

static inline void
_blurrow (guchar* pixels,
	  gint    width,
	  gint    height,
	  gint    channels,
	  gint    line,
	  gint    alpha,
	  gint    aprec,
	  gint    zprec)
{
	gint    zR;
	gint    zG;
	gint    zB;
	gint    zA;
	gint    index;
	guchar* scanline;

	scanline = &(pixels[line * width * channels]);

	zR = *scanline << zprec;
	zG = *(scanline + 1) << zprec;
	zB = *(scanline + 2) << zprec;
	zA = *(scanline + 3) << zprec;

	for (index = 0; index < width; index ++)
		_blurinner (&scanline[index * channels],
			    &zR,
			    &zG,
			    &zB,
			    &zA,
			    alpha,
			    aprec,
			    zprec);

	for (index = width - 2; index >= 0; index--)
		_blurinner (&scanline[index * channels],
			    &zR,
			    &zG,
			    &zB,
			    &zA,
			    alpha,
			    aprec,
			    zprec);
}

static inline void
_blurcol (guchar* pixels,
	  gint    width,
	  gint    height,
	  gint    channels,
	  gint    x,
	  gint    alpha,
	  gint    aprec,
	  gint    zprec)
{
	gint zR;
	gint zG;
	gint zB;
	gint zA;
	gint index;
	guchar* ptr;

	ptr = pixels;

	ptr += x * channels;

	zR = *((guchar*) ptr    ) << zprec;
	zG = *((guchar*) ptr + 1) << zprec;
	zB = *((guchar*) ptr + 2) << zprec;
	zA = *((guchar*) ptr + 3) << zprec;

	for (index = width; index < (height - 1) * width; index += width)
		_blurinner ((guchar*) &ptr[index * channels],
			    &zR,
			    &zG,
			    &zB,
			    &zA,
			    alpha,
			    aprec,
			    zprec);

	for (index = (height - 2) * width; index >= 0; index -= width)
		_blurinner ((guchar*) &ptr[index * channels],
			    &zR,
			    &zG,
			    &zB,
			    &zA,
			    alpha,
			    aprec,
			    zprec);
}

void
_expblur (guchar* pixels,
	  gint    width,
	  gint    height,
	  gint    channels,
	  gint    radius,
	  gint    aprec,
	  gint    zprec)
{
	gint alpha;
	gint row = 0;
	gint col = 0;

	if (radius < 1)
		return;

	// calculate the alpha such that 90% of 
	// the kernel is within the radius.
	// (Kernel extends to infinity)
	alpha = (gint) ((1 << aprec) * (1.0f - expf (-2.3f / (radius + 1.f))));

	for (; row < height; row++)
		_blurrow (pixels,
			  width,
			  height,
			  channels,
			  row,
			  alpha,
			  aprec,
			  zprec);

	for(; col < width; col++)
		_blurcol (pixels,
			  width,
			  height,
			  channels,
			  col,
			  alpha,
			  aprec,
			  zprec);

	return;
}

void
_surface_blur (cairo_surface_t* surface,
               guint            radius)
{
	guchar*        pixels;
	guint          width;
	guint          height;
	cairo_format_t format;

	// before we mess with the surface execute any pending drawing
	cairo_surface_flush (surface);

	pixels = cairo_image_surface_get_data (surface);
	width  = cairo_image_surface_get_width (surface);
	height = cairo_image_surface_get_height (surface);
	format = cairo_image_surface_get_format (surface);

	switch (format)
	{
		case CAIRO_FORMAT_ARGB32:
			_expblur (pixels, width, height, 4, radius, 16, 7);
		break;

		case CAIRO_FORMAT_RGB24:
			_expblur (pixels, width, height, 3, radius, 16, 7);
		break;

		case CAIRO_FORMAT_A8:
			_expblur (pixels, width, height, 1, radius, 16, 7);
		break;

		default :
			// do nothing
		break;
	}

	// inform cairo we altered the surfaces contents
	cairo_surface_mark_dirty (surface);	
}

/// GObject functions //////////////////////////////////////////////////////////

static void
play_button_class_init (PlayButtonClass *klass)
{	
	GObjectClass	*gobject_class = G_OBJECT_CLASS (klass);
 	GtkWidgetClass* widget_class = GTK_WIDGET_CLASS (klass);

	g_type_class_add_private (klass, sizeof (PlayButtonPrivate));

 	widget_class->expose_event = play_button_expose;

	gobject_class->dispose = play_button_dispose;
	gobject_class->finalize = play_button_finalize;
}

static void
play_button_init (PlayButton *self)
{
	PlayButtonPrivate* priv = PLAY_BUTTON_GET_PRIVATE(self);	
	priv->current_command	= TRANSPORT_NADA;
	priv->current_state = PAUSE;
	priv->command_coordinates =  g_hash_table_new_full(g_direct_hash,
	                                             				g_direct_equal,
	                                             				NULL,
	                                             				(GDestroyNotify)g_list_free);
	GList* previous_list = NULL;
	previous_list = g_list_insert(previous_list, GINT_TO_POINTER(15), 0);
	previous_list = g_list_insert(previous_list, GINT_TO_POINTER(5), 1);
	previous_list = g_list_insert(previous_list, GINT_TO_POINTER(60), 2);
	previous_list = g_list_insert(previous_list, GINT_TO_POINTER(34), 3);
	
  g_hash_table_insert(priv->command_coordinates,
                      GINT_TO_POINTER(TRANSPORT_PREVIOUS),
                      previous_list);
                     
	GList* play_list = NULL;
	play_list = g_list_insert(play_list, GINT_TO_POINTER(58), 0);
	play_list = g_list_insert(play_list, GINT_TO_POINTER(0), 1);
	play_list = g_list_insert(play_list, GINT_TO_POINTER(50), 2);
	play_list = g_list_insert(play_list, GINT_TO_POINTER(43), 3);

	g_hash_table_insert(priv->command_coordinates,
                      GINT_TO_POINTER(TRANSPORT_PLAY_PAUSE),
                      play_list);

	GList* next_list = NULL;
	next_list = g_list_insert(next_list, GINT_TO_POINTER(100), 0);
	next_list = g_list_insert(next_list, GINT_TO_POINTER(5), 1);
	next_list = g_list_insert(next_list, GINT_TO_POINTER(60), 2);
	next_list = g_list_insert(next_list, GINT_TO_POINTER(34), 3);

	g_hash_table_insert(priv->command_coordinates,
                      GINT_TO_POINTER(TRANSPORT_NEXT),
                      next_list);
	
	gtk_widget_set_size_request(GTK_WIDGET(self), 200, 50); 
}

static void
play_button_dispose (GObject *object)
{
	G_OBJECT_CLASS (play_button_parent_class)->dispose (object);
}

static void
play_button_finalize (GObject *object)
{
	G_OBJECT_CLASS (play_button_parent_class)->finalize (object);
}

static gboolean
play_button_expose (GtkWidget *button, GdkEventExpose *event)
{
	cairo_t *cr;
	cr = gdk_cairo_create (button->window);

	cairo_rectangle (cr,
                   event->area.x, event->area.y,
                   event->area.width, event->area.height);

	cairo_clip(cr);
	draw (button, cr);
	cairo_destroy (cr);
	return FALSE;
}


PlayButtonEvent
determine_button_event(GtkWidget* button, GdkEventButton* event)
{
	g_debug("event x coordinate = %f", event->x);
	g_debug("event y coordinate = %f", event->y);
	PlayButtonEvent button_event = TRANSPORT_NADA;
	// For now very simple rectangular collision detection
	if(event->x > 55 && event->x < 95
	   && event->y > 12 && event->y < 40){
		button_event = TRANSPORT_PREVIOUS;
	}
	else if(event->x > 99 && event->x < 136
	   && event->y > 5 && event->y < 47){
		button_event = TRANSPORT_PLAY_PAUSE;	
	}
	else if(event->x > 137 && event->x < 179
	   && event->y > 12 && event->y < 40){
		button_event = TRANSPORT_NEXT;
	}	
	return button_event;
}

void 
play_button_react_to_button_press(GtkWidget* button, PlayButtonEvent command)
{
	g_return_if_fail(IS_PLAY_BUTTON(button));
	PlayButtonPrivate* priv = PLAY_BUTTON_GET_PRIVATE(button);
	priv->current_command = command;
	
	cairo_t *cr;
	cr = gdk_cairo_create (button->window);

	GList* list = g_hash_table_lookup(priv->command_coordinates, GINT_TO_POINTER(command));
	cairo_rectangle(cr,
	                GPOINTER_TO_INT(g_list_nth_data(list, 0)),
	                GPOINTER_TO_INT(g_list_nth_data(list, 1)),
									GPOINTER_TO_INT(g_list_nth_data(list, 2)),	               	
									GPOINTER_TO_INT(g_list_nth_data(list, 3)));
	cairo_clip(cr);
	draw (button, cr);
	cairo_destroy (cr);
}


void 
play_button_react_to_button_release(GtkWidget* button)
{
	g_return_if_fail(IS_PLAY_BUTTON(button));
	PlayButtonPrivate* priv = PLAY_BUTTON_GET_PRIVATE(button);	
	cairo_t *cr;
	
	cr = gdk_cairo_create (button->window);
	GList* list = g_hash_table_lookup(priv->command_coordinates,
	                                  GINT_TO_POINTER(priv->current_command));

	priv->current_command = TRANSPORT_NADA;

	cairo_rectangle(cr,
	                GPOINTER_TO_INT(g_list_nth_data(list, 0)),
	                GPOINTER_TO_INT(g_list_nth_data(list, 1)),
									GPOINTER_TO_INT(g_list_nth_data(list, 2)),	               	
									GPOINTER_TO_INT(g_list_nth_data(list, 3)));

	cairo_clip(cr);
	draw (button, cr);
	cairo_destroy (cr);
	
}    

void
play_button_toggle_play_pause(GtkWidget* button, PlayButtonState update)
{
	PlayButtonPrivate* priv = PLAY_BUTTON_GET_PRIVATE(button);
	priv->current_state = update;
	g_debug("PlayButton::toggle play state : %i", priv->current_state); 
}


void
play_button_set_style(GtkWidget* button, GtkStyle* style)
{
	PlayButtonPrivate* priv = PLAY_BUTTON_GET_PRIVATE(button);
	priv->background_colour_fg = style->fg[GTK_STATE_NORMAL];
	priv->background_colour_bg_dark = style->bg[GTK_STATE_NORMAL];
	priv->background_colour_bg_light = style->base[GTK_STATE_NORMAL];
	priv->foreground_colour_fg = style->fg[GTK_STATE_PRELIGHT];
	priv->foreground_colour_bg = style->bg[GTK_STATE_NORMAL];
}

static void
draw_gradient (cairo_t* cr,
               double   x,
               double   y,
               double   w,
               double   r,
               double*  rgba_start,
               double*  rgba_end)
{
	cairo_pattern_t* pattern = NULL;

	cairo_move_to (cr, x, y);
	cairo_line_to (cr, x + w - 2.0f * r, y);
	cairo_arc (cr,
		   x + w - 2.0f * r,
		   y + r,
		   r,
		   -90.0f * G_PI / 180.0f,
		   90.0f * G_PI / 180.0f);
	cairo_line_to (cr, x, y + 2.0f * r);
	cairo_arc (cr,
		   x,
		   y + r,
		   r,
		   90.0f * G_PI / 180.0f,
		   270.0f * G_PI / 180.0f);
	cairo_close_path (cr);

	pattern = cairo_pattern_create_linear (x, y, x, y + 2.0f * r);
	cairo_pattern_add_color_stop_rgba (pattern,
	                                   0.0f,
	                                   rgba_start[0],
	                                   rgba_start[1],
	                                   rgba_start[2],
	                                   rgba_start[3]);
	cairo_pattern_add_color_stop_rgba (pattern,
	                                   1.0f,
	                                   rgba_end[0],
	                                   rgba_end[1],
	                                   rgba_end[2],
	                                   rgba_end[3]);
	cairo_set_source (cr, pattern);
	cairo_fill (cr);
	cairo_pattern_destroy (pattern);
}

static void
draw_circle (cairo_t* cr,
	     double   x,
	     double   y,
	     double   r,
	     double*  rgba_start,
	     double*  rgba_end)
{
	cairo_pattern_t* pattern = NULL;

	cairo_move_to (cr, x, y);
	cairo_arc (cr,
		   x + r,
		   y + r,
		   r,
		   0.0f * G_PI / 180.0f,
		   360.0f * G_PI / 180.0f);

	pattern = cairo_pattern_create_linear (x, y, x, y + 2.0f * r);
	cairo_pattern_add_color_stop_rgba (pattern,
	                                   0.0f,
	                                   rgba_start[0],
	                                   rgba_start[1],
	                                   rgba_start[2],
	                                   rgba_start[3]);
	cairo_pattern_add_color_stop_rgba (pattern,
	                                   1.0f,
	                                   rgba_end[0],
	                                   rgba_end[1],
	                                   rgba_end[2],
	                                   rgba_end[3]);
	cairo_set_source (cr, pattern);
	cairo_fill (cr);
	cairo_pattern_destroy (pattern);
}

static void
_setup (cairo_t**         cr,
	cairo_surface_t** surf,
	gint              width,
	gint              height)
{
	if (!cr || !surf)
		return;

	*surf = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
	*cr = cairo_create (*surf);
	cairo_scale (*cr, 1.0f, 1.0f);
	cairo_set_operator (*cr, CAIRO_OPERATOR_CLEAR);
	cairo_paint (*cr);
	cairo_set_operator (*cr, CAIRO_OPERATOR_OVER);
}

static void
_mask_prev (cairo_t* cr,
	    double   x,
	    double   y,
	    double   tri_width,
	    double   tri_height,
	    double   tri_offset)
{
	if (!cr)
		return;

	cairo_move_to (cr, x,             y + tri_height / 2.0f);
	cairo_line_to (cr, x + tri_width, y);
	cairo_line_to (cr, x + tri_width, y + tri_height);
	x += tri_offset;
	cairo_move_to (cr, x,             y + tri_height / 2.0f);
	cairo_line_to (cr, x + tri_width, y);
	cairo_line_to (cr, x + tri_width, y + tri_height);
	x -= tri_offset;
	cairo_rectangle (cr, x, y, 2.5f, tri_height);
	cairo_close_path (cr);	
}

static void
_mask_next (cairo_t* cr,
	    double   x,
	    double   y,
	    double   tri_width,
	    double   tri_height,
	    double   tri_offset)
{
	if (!cr)
		return;

	cairo_move_to (cr, x,             y);
	cairo_line_to (cr, x + tri_width, y + tri_height / 2.0f);
	cairo_line_to (cr, x,             y + tri_height);
	x += tri_offset;
	cairo_move_to (cr, x,             y);
	cairo_line_to (cr, x + tri_width, y + tri_height / 2.0f);
	cairo_line_to (cr, x,             y + tri_height);
	x -= tri_offset;
	x += 2.0f * tri_width - tri_offset - 1.0f;
	cairo_rectangle (cr, x, y, 2.5f, tri_height);

	cairo_close_path (cr);	
}

static void
_mask_pause (cairo_t* cr,
	     double   x,
	     double   y,
	     double   bar_width,
	     double   bar_height,
	     double   bar_offset)
{
	if (!cr)
		return;

	cairo_set_line_width (cr, bar_width);
	cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);

	x += bar_width;
	y += bar_width;
	cairo_move_to (cr, x,              y);
	cairo_line_to (cr, x,              y + bar_height);
	cairo_move_to (cr, x + bar_offset, y);
	cairo_line_to (cr, x + bar_offset, y + bar_height);

}

static void
_mask_play (cairo_t* cr,
	     double   x,
	     double   y,
	     double   tri_width,
	     double   tri_height
	     /*double   tri_offset*/)
{
	if (!cr)
		return;

	cairo_move_to (cr, x,             y);
	cairo_line_to (cr, x + tri_width, y + tri_height / 2.0f);
	cairo_line_to (cr, x,             y + tri_height);
	cairo_close_path (cr);	
	
}

static void
_fill (cairo_t* cr,
       double   x_start,
       double   y_start,
       double   x_end,
       double   y_end,
       double*  rgba_start,
       double*  rgba_end,
       gboolean stroke)
{
	cairo_pattern_t* pattern = NULL;

	if (!cr || !rgba_start || !rgba_end)
		return;

	pattern = cairo_pattern_create_linear (x_start, y_start, x_end, y_end);
	cairo_pattern_add_color_stop_rgba (pattern,
					   0.0f,
					   rgba_start[0],
					   rgba_start[1],
					   rgba_start[2],
					   rgba_start[3]);
	cairo_pattern_add_color_stop_rgba (pattern,
					   1.0f,
					   rgba_end[0],
					   rgba_end[1],
					   rgba_end[2],
					   rgba_end[3]);
	cairo_set_source (cr, pattern);
	if (stroke)
		cairo_stroke (cr);
	else
		cairo_fill (cr);
	cairo_pattern_destroy (pattern);
}

static void
_finalize (cairo_t*          cr,
	   cairo_t**         cr_surf,
	   cairo_surface_t** surf,
	   double            x,
	   double            y)
{
	if (!cr || !cr_surf || !surf)
		return;

	cairo_set_source_surface (cr, *surf, x, y);
	cairo_paint (cr);
	cairo_surface_destroy (*surf);
	cairo_destroy (*cr_surf);
}

static void
draw (GtkWidget* button, cairo_t *cr)
{
	g_return_if_fail(IS_PLAY_BUTTON(button));
	PlayButtonPrivate* priv = PLAY_BUTTON_GET_PRIVATE(button);	

	cairo_surface_t*  surf = NULL;
	cairo_t*       cr_surf = NULL;

	double INNER_START[] =  {229.0f/255.0f, 223.0f/255.0f, 215.0f/255.0f, 1.0f};
	double INNER_END[] = {183.0f / 255.0f, 178.0f / 255.0f, 172.0f / 255.0f, 1.0f};
	double MIDDLE_START[] = {61.0f / 255.0f, 60.0f / 255.0f, 57.0f / 255.0f, 1.0f};
	double MIDDLE_END[] = {94.0f / 255.0f,93.0f / 255.0f, 90.0f / 255.0f,1.0f};
	double OUTER_START[] = {36.0f / 255.0f, 35.0f / 255.0f, 33.0f / 255.0f, 1.0f};
	double OUTER_END[] = {123.0f / 255.0f, 123.0f / 255.0f, 120.0f / 255.0f, 1.0f};
	double BUTTON_START[] = {252.0f / 255.0f, 251.0f / 255.0f, 251.0f / 255.0f,1.0f};
	double BUTTON_END[] = {186.0f / 255.0f,180.0f / 255.0f, 170.0f / 255.0f, 1.0f};
	double BUTTON_SHADOW[] = {0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 0.75f};
	double INNER_COMPRESSED_END[] = {61.0f / 255.0f, 60.0f / 255.0f, 57.0f / 255.0f, 1.0f};
	double INNER_COMPRESSED_START[] = {36.0f / 255.0f, 35.0f / 255.0f, 33.0f / 255.0f, 1.0f};
	
	// prev/next-background
  draw_gradient (cr,
                 X,
                 Y,
                 RECT_WIDTH,
                 OUTER_RADIUS,
                 OUTER_START,
                 OUTER_END);
  draw_gradient (cr,
                 X,
                 Y + 1,
                 RECT_WIDTH - 2,
                 MIDDLE_RADIUS,
                 MIDDLE_START,
                 MIDDLE_END);
	draw_gradient (cr,
               X,
               Y + 2,
               RECT_WIDTH - 4,
               INNER_RADIUS,
               INNER_START,
               INNER_END);

	if(priv->current_command == TRANSPORT_PREVIOUS){
		draw_gradient (cr,
		               X,
		               Y + 2,
		               RECT_WIDTH/2,
		               INNER_RADIUS,
		               INNER_COMPRESSED_START,
		               INNER_COMPRESSED_END);
	}	
	else if(priv->current_command == TRANSPORT_NEXT){
		draw_gradient (cr,
		               RECT_WIDTH / 2 + X,
		               Y + 2,
		               (RECT_WIDTH - 7)/2,
		               INNER_RADIUS,
		               INNER_COMPRESSED_START,
		               INNER_COMPRESSED_END);		
	}

	// play/pause-background
        draw_circle (cr,
		     X + RECT_WIDTH / 2.0f - 2.0f * OUTER_RADIUS - 5.5f,
		     Y - ((CIRCLE_RADIUS - OUTER_RADIUS)),
		     CIRCLE_RADIUS,
		     OUTER_START,
		     OUTER_END);
        draw_circle (cr,
                       X + RECT_WIDTH / 2.0f - 2.0f * OUTER_RADIUS - 5.5f + 0.5f,
                       Y - ((CIRCLE_RADIUS - OUTER_RADIUS)) + 0.5f,
                       CIRCLE_RADIUS - 0.75f,
                       MIDDLE_START,
                       MIDDLE_END);

				if(priv->current_command == TRANSPORT_PLAY_PAUSE){
		      draw_circle (cr,
		                   X + RECT_WIDTH / 2.0f - 2.0f * OUTER_RADIUS - 5.5f + 1.5f,
		                   Y - ((CIRCLE_RADIUS - OUTER_RADIUS)) + 1.5f,
		                   CIRCLE_RADIUS - 1.5f,
		               		 INNER_COMPRESSED_START,
		                   INNER_COMPRESSED_END);
				}
				else{        
					draw_circle (cr,
                     X + RECT_WIDTH / 2.0f - 2.0f * OUTER_RADIUS - 5.5f + 1.5f,
                     Y - ((CIRCLE_RADIUS - OUTER_RADIUS)) + 1.5f,
                     CIRCLE_RADIUS - 1.5f,
                     INNER_START,
		     						 INNER_END);
				}					
	// draw previous-button drop-shadow
	_setup (&cr_surf, &surf, PREV_WIDTH, PREV_HEIGHT);
	_mask_prev (cr_surf,
		    (PREV_WIDTH - (2.0f * TRI_WIDTH - TRI_OFFSET)) / 2.0f,
		    (PREV_HEIGHT - TRI_HEIGHT) / 2.0f,
		    TRI_WIDTH,
		    TRI_HEIGHT,
		    TRI_OFFSET);
	_fill (cr_surf,
               (PREV_WIDTH - (2.0f * TRI_WIDTH - TRI_OFFSET)) / 2.0f,
               (PREV_HEIGHT - TRI_HEIGHT) / 2.0f,
               (PREV_WIDTH - (2.0f * TRI_WIDTH - TRI_OFFSET)) / 2.0f,
	       (double) TRI_HEIGHT,
	       BUTTON_SHADOW,
	       BUTTON_SHADOW,
	       FALSE);
	_surface_blur (surf, 1);
	_finalize (cr, &cr_surf, &surf, PREV_X, PREV_Y + 1.0f);

	// draw previous-button
	_setup (&cr_surf, &surf, PREV_WIDTH, PREV_HEIGHT);
	_mask_prev (cr_surf,
		    (PREV_WIDTH - (2.0f * TRI_WIDTH - TRI_OFFSET)) / 2.0f,
		    (PREV_HEIGHT - TRI_HEIGHT) / 2.0f,
		    TRI_WIDTH,
		    TRI_HEIGHT,
		    TRI_OFFSET);
	_fill (cr_surf,
		     (PREV_WIDTH - (2.0f * TRI_WIDTH - TRI_OFFSET)) / 2.0f,
		     (PREV_HEIGHT - TRI_HEIGHT) / 2.0f,
		     (PREV_WIDTH - (2.0f * TRI_WIDTH - TRI_OFFSET)) / 2.0f,
		     (double) TRI_HEIGHT,
		     BUTTON_START,
		     BUTTON_END,
		     FALSE);		
	_finalize (cr, &cr_surf, &surf, PREV_X, PREV_Y);

	// draw next-button drop-shadow
	_setup (&cr_surf, &surf, NEXT_WIDTH, NEXT_HEIGHT);
	_mask_next (cr_surf,
		    (NEXT_WIDTH - (2.0f * TRI_WIDTH - TRI_OFFSET)) / 2.0f,
		    (NEXT_HEIGHT - TRI_HEIGHT) / 2.0f,
		    TRI_WIDTH,
		    TRI_HEIGHT,
		    TRI_OFFSET);
	_fill (cr_surf,
	       (NEXT_WIDTH - (2.0f * TRI_WIDTH - TRI_OFFSET)) / 2.0f,
	       (NEXT_HEIGHT - TRI_HEIGHT) / 2.0f,
	       (NEXT_WIDTH - (2.0f * TRI_WIDTH - TRI_OFFSET)) / 2.0f,
	       (double) TRI_HEIGHT,
	       BUTTON_SHADOW,
	       BUTTON_SHADOW,
	       FALSE);
	_surface_blur (surf, 1);
	_finalize (cr, &cr_surf, &surf, NEXT_X, NEXT_Y + 1.0f);

	// draw next-button
	_setup (&cr_surf, &surf, NEXT_WIDTH, NEXT_HEIGHT);
	_mask_next (cr_surf,
		    (NEXT_WIDTH - (2.0f * TRI_WIDTH - TRI_OFFSET)) / 2.0f,
		    (NEXT_HEIGHT - TRI_HEIGHT) / 2.0f,
		    TRI_WIDTH,
		    TRI_HEIGHT,
		    TRI_OFFSET);
	_fill (cr_surf,
	       (NEXT_WIDTH - (2.0f * TRI_WIDTH - TRI_OFFSET)) / 2.0f,
	       (NEXT_HEIGHT - TRI_HEIGHT) / 2.0f,
	       (NEXT_WIDTH - (2.0f * TRI_WIDTH - TRI_OFFSET)) / 2.0f,
	       (double) TRI_HEIGHT,
	       BUTTON_START,
	       BUTTON_END,
	       FALSE);
	_finalize (cr, &cr_surf, &surf, NEXT_X, NEXT_Y);

	// draw pause-button drop-shadow
	if(priv->current_state == PLAY){
		_setup (&cr_surf, &surf, PAUSE_WIDTH, PAUSE_HEIGHT);
		_mask_pause (cr_surf,
				   (PAUSE_WIDTH - (2.0f * BAR_WIDTH + BAR_OFFSET)) / 2.0f,
				   (PAUSE_HEIGHT - BAR_HEIGHT) / 2.0f,
				   BAR_WIDTH,
				   BAR_HEIGHT - 2.0f * BAR_WIDTH,
				   BAR_OFFSET);
		_fill (cr_surf,
			     (PAUSE_WIDTH - (2.0f * BAR_WIDTH + BAR_OFFSET)) / 2.0f,
			     (PAUSE_HEIGHT - BAR_HEIGHT) / 2.0f,
			     (PAUSE_WIDTH - (2.0f * BAR_WIDTH + BAR_OFFSET)) / 2.0f,
			     (double) BAR_HEIGHT,
			     BUTTON_SHADOW,
			     BUTTON_SHADOW,
			     TRUE);
		_surface_blur (surf, 1);
		_finalize (cr, &cr_surf, &surf, PAUSE_X, PAUSE_Y + 1.0f);

		// draw pause-button
		_setup (&cr_surf, &surf, PAUSE_WIDTH, PAUSE_HEIGHT);
		_mask_pause (cr_surf,
				   (PAUSE_WIDTH - (2.0f * BAR_WIDTH + BAR_OFFSET)) / 2.0f,
				   (PAUSE_HEIGHT - BAR_HEIGHT) / 2.0f,
				   BAR_WIDTH,
				   BAR_HEIGHT - 2.0f * BAR_WIDTH,
				   BAR_OFFSET);
		_fill (cr_surf,
			     (PAUSE_WIDTH - (2.0f * BAR_WIDTH + BAR_OFFSET)) / 2.0f,
			     (PAUSE_HEIGHT - BAR_HEIGHT) / 2.0f,
			     (PAUSE_WIDTH - (2.0f * BAR_WIDTH + BAR_OFFSET)) / 2.0f,
			     (double) BAR_HEIGHT,
			     BUTTON_START,
			     BUTTON_END,
			     TRUE);
		_finalize (cr, &cr_surf, &surf, PAUSE_X, PAUSE_Y);
	}
	else if(priv->current_state == PAUSE){
		_setup (&cr_surf, &surf, PLAY_WIDTH, PLAY_HEIGHT);
		_mask_play (cr_surf,
		            PLAY_PADDING,
		            PLAY_PADDING,
		            PLAY_WIDTH - (2*PLAY_PADDING),
		            PLAY_HEIGHT - (2*PLAY_PADDING));		            
		_fill (cr_surf,
		       PLAY_PADDING,
		       PLAY_PADDING,
		       PLAY_WIDTH - (2*PLAY_PADDING),
		       PLAY_HEIGHT - (2*PLAY_PADDING),
			     BUTTON_SHADOW,
			     BUTTON_SHADOW,
			     FALSE);
		_surface_blur (surf, 1);
		_finalize (cr, &cr_surf, &surf, PAUSE_X-0.75f, PAUSE_Y + 1.0f);
		// draw play-button
		_setup (&cr_surf, &surf, PLAY_WIDTH, PLAY_HEIGHT);
		cairo_set_line_width (cr, 10.5);
		cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
		cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
		_mask_play (cr_surf,
		            PLAY_PADDING,
		            PLAY_PADDING,
		            PLAY_WIDTH - (2*PLAY_PADDING),
		            PLAY_HEIGHT - (2*PLAY_PADDING));		            
		_fill (cr_surf,
		       PLAY_PADDING,
		       PLAY_PADDING,
		       PLAY_WIDTH - (2*PLAY_PADDING),
		       PLAY_HEIGHT - (2*PLAY_PADDING),
			     BUTTON_START,
			     BUTTON_END,
			     FALSE);
		_finalize (cr, &cr_surf, &surf, PAUSE_X-0.5f, PAUSE_Y);
	}
	
}


/**
* play_button_new:
* @returns: a new #PlayButton.
**/
GtkWidget* 
play_button_new()
{	
	GtkWidget* widget =	g_object_new(PLAY_BUTTON_TYPE, NULL);
	gtk_widget_set_app_paintable (widget, TRUE);	
	return widget;
}

