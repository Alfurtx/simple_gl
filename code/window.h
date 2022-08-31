/* date = August 31st 2022 11:31 am */

#ifndef WINDOW_H
#define WINDOW_H

#include "common.h"

typedef void (*window_func_callback)(GLFWwindow* window);

inline void
window_create(const u32 window_width, const u32 window_height, const char* window_title, window_func_callback window_creation_cb, window_func_callback window_loop_cb, window_func_callback window_destroy_cb); 

#if defined(SIMPLE_WINDOW_IMPLEMENTATION)

global_file GLFWwindow* _window;

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
        window_loop_cb(_window);
    }
    
    //~ WINDOW DESTROY CALLBACK
    window_destroy_cb(_window);
    glfwTerminate();
}

#endif // SIMPLE_WINDOW_IMPLEMENTATION

#endif // WINDOW_H
