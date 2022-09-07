=== SIMPLE GL ===
This is a template library for OpenGL projects.
To use it properly you should do something in 1 file like this:

...
#define SIMPLE_WINDOW_IMPLEMENTATION
#define SIMPLE_CAMERA_IMPLEMENTATION
#define SIMPLE_RENDERER_IMPLEMENTATION
#include "renderer.h"
#include "camera.h"
#include "window.h"
...