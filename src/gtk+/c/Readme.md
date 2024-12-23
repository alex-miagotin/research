To create a simple GTK+ window with a rectangle in the middle using GTK 3, you can write a C program. Below is an example of how to achieve this:

### Requirements:
- GTK+ 3 development libraries installed on your system.

### Code Example:

```c
#include <gtk/gtk.h>

static void do_drawing(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    // Get the allocation of the window
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);

    // Set the rectangle size and position
    int rect_width = 200;
    int rect_height = 100;
    int rect_x = (allocation.width - rect_width) / 2;
    int rect_y = (allocation.height - rect_height) / 2;

    // Set the drawing color (RGB for red)
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);

    // Draw the rectangle
    cairo_rectangle(cr, rect_x, rect_y, rect_width, rect_height);
    cairo_fill(cr);
}

static gboolean on_configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer user_data) {
    gtk_widget_queue_draw(widget);
    return FALSE;
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *drawing_area;

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new top-level window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK+ Rectangle Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Connect the "destroy" signal to gtk_main_quit
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a drawing area widget
    drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    // Connect the draw signal to our drawing function
    g_signal_connect(drawing_area, "draw", G_CALLBACK(do_drawing), NULL);

    // Connect the configure event to refresh the drawing area
    g_signal_connect(drawing_area, "configure-event", G_CALLBACK(on_configure_event), NULL);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Start the GTK main event loop
    gtk_main();

    return 0;
}
```

### Explanation:
- **GTK+ Initialization**: The program initializes GTK with `gtk_init`.
- **Window Creation**: A simple window is created with `gtk_window_new()`. We set the window's size and position.
- **Drawing Area**: The `gtk_drawing_area_new()` creates a drawing area widget, which is where we can draw our custom graphics.
- **Rectangle Drawing**: The function `do_drawing` uses Cairo to draw a rectangle. The rectangle is positioned in the center of the window, with a width of 200 and a height of 100 pixels. The color is set to red (`cairo_set_source_rgb(cr, 1.0, 0.0, 0.0)`).
- **Signals**: The `draw` signal triggers the drawing function, and the `configure-event` ensures the window is redrawn if resized.
- **Event Loop**: The `gtk_main()` function runs the GTK main event loop, waiting for user actions like window events.

### How to Compile:
To compile the program, you can use `gcc` with the GTK+ 3 flags. For example:

```bash
gcc `pkg-config --cflags --libs gtk+-3.0` -o gtk_rectangle gtk_rectangle.c
```

This will compile the program into an executable named `gtk_rectangle`.

### How to Run:
After compiling, run the program like so:

```bash
./gtk_rectangle
```

You should see a window with a red rectangle in the middle.