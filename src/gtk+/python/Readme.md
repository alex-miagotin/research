To create a simple window with a rectangle in the middle using **GTK+** in Python, you can use the **PyGObject** library, which provides Python bindings for GTK+ and other libraries. Here is an example of how to do this:

### Requirements:
- Python 3
- PyGObject library (which includes bindings for GTK+)

To install PyGObject, you can run the following command (if it's not installed already):

```bash
pip install PyGObject
```

### Code Example in Python:

```python
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gdk

class SimpleWindow(Gtk.Window):
    def __init__(self):
        super().__init__(title="Simple GTK Window with Rectangle")

        # Set the window size
        self.set_default_size(400, 400)

        # Connect the "destroy" signal to close the window
        self.connect("destroy", Gtk.main_quit)

        # Create a drawing area widget
        self.drawing_area = Gtk.DrawingArea()
        self.add(self.drawing_area)

        # Connect the drawing signal to the drawing function
        self.drawing_area.connect("draw", self.on_draw)

    def on_draw(self, widget, cr):
        # Get the window size
        width, height = self.get_size()

        # Define the rectangle's width and height
        rect_width = 200
        rect_height = 100

        # Calculate the rectangle's position to center it
        rect_x = (width - rect_width) / 2
        rect_y = (height - rect_height) / 2

        # Set the color to red (RGB values: red, green, blue)
        cr.set_source_rgb(1.0, 0.0, 0.0)

        # Draw the rectangle
        cr.rectangle(rect_x, rect_y, rect_width, rect_height)
        cr.fill()

# Create and run the window
window = SimpleWindow()
window.show_all()
Gtk.main()
```

### Explanation:
1. **GTK Window**: A simple GTK window is created by subclassing `Gtk.Window`.
2. **Drawing Area**: The `Gtk.DrawingArea` widget is used as the area where we will perform custom drawing. The drawing area is added to the window.
3. **Drawing Function**: The `on_draw` method is connected to the "draw" signal of the drawing area. Inside this function:
   - We get the current window size.
   - Define the size of the rectangle (200x100 pixels).
   - Calculate the position of the rectangle to center it in the window.
   - Set the color to red (`cr.set_source_rgb(1.0, 0.0, 0.0)`), and then draw and fill the rectangle using Cairo graphics context (`cr`).
4. **Main Loop**: The `Gtk.main()` function starts the GTK main event loop, which waits for events like user interactions (e.g., closing the window).

### How to Run:
1. Save the code in a Python file, e.g., `gtk_rectangle.py`.
2. Run the file from the terminal:

```bash
python3 gtk_rectangle.py
```

This will open a window with a red rectangle centered in the middle of the window.