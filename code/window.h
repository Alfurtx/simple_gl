/* date = August 31st 2022 11:31 am */

#if !defined(WINDOW_H)
#define WINDOW_H

#include "common.h"

typedef void (*window_func_callback)(GLFWwindow* window);

inline void window_create(const u32 window_width, const u32 window_height, const char* window_title, window_func_callback window_creation_cb, window_func_callback window_loop_cb, window_func_callback window_destroy_cb); 
inline void _default_loop_callback(GLFWwindow* window);

#if defined(SIMPLE_WINDOW_IMPLEMENTATION)

global GLFWwindow* _window;

internal void test(void) {  }

inline void
window_create(const u32 window_width,
              const u32 window_height,
              const char* window_title,
              window_func_callback window_creation_cb,
              window_func_callback window_loop_cb,
              window_func_callback window_destroy_cb)
{
    //~ WINDOW INITIALIZATION
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    
    GLFWwindow* _window = glfwCreateWindow(window_width, window_height, window_title, 0, 0);
    
    glfwMakeContextCurrent(_window);
    
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        assert(0, (char *)"Failed to load GLAD");
    }
    
    //~ WINDOW CREATION CALLBACK
    if(window_creation_cb) {
        window_creation_cb(_window);
    }
    
    //~ WINDOW LOOP
    while(!glfwWindowShouldClose(_window)) {
	    if(window_loop_cb) {
		    window_loop_cb(_window);
	    } else {
		    _default_loop_callback(_window);
	    }
    }
    
    //~ WINDOW DESTROY CALLBACK
    if(window_destroy_cb) {
    	window_destroy_cb(_window);
    }

    glfwTerminate();
}

inline void
_default_loop_callback(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2f, 0.5f, 0.5f, 1.0f);

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);

	glfwPollEvents();
	glfwSwapBuffers(window);
}

#endif // SIMPLE_WINDOW_IMPLEMENTATION

#endif // WINDOW_H
