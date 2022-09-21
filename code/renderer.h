/* date = September 4th 2022 1:39 pm */

#ifndef RENDERER_H
#define RENDERER_H

#include "common.h"

struct Shader;

#ifdef SIMPLE_RENDERER_IMPLEMENTATION

struct Shader {
    uint32_t program_handle;
    
    inline void
        create_program(char* vertex_file_path, char* fragment_file_path, char* geometry_file_path = 0)
    {
        assert(vertex_file_path && fragment_file_path, (char*)"Shaders file path is invalid");
        
        FILE* fp;
        fopen_s(&fp, vertex_file_path, "rb");
        fseek(fp, 0, SEEK_END);
        size_t size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char* vertsrc = (char*) _malloca((size + 1));
        fread(vertsrc, 1, size, fp);
        vertsrc[size] = '\0';
        fclose(fp);
        
        fopen_s(&fp, fragment_file_path, "rb");
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char* fragsrc = (char*) _malloca((size + 1));
        fread(fragsrc, 1, size, fp);
        fragsrc[size] = '\0';
        fclose(fp);
        
        uint vert, frag, geo;
        int  success;
        char infoLog[512];
        
        vert = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vert, 1, &vertsrc, 0);
        glCompileShader(vert);
        glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vert, 512, NULL, infoLog);
            fprintf(stderr, "[ERROR][VERTEX SHADER COMPILATION ERROR]\n%s\n", infoLog);
        }
        
        frag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag, 1, &fragsrc, 0);
        glCompileShader(frag);
        glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(frag, 512, NULL, infoLog);
            fprintf(stderr, "[ERROR][FRAGMENT SHADER COMPILATION ERROR]\n%s\n", infoLog);
        }
        
        this->program_handle = glCreateProgram();
        glAttachShader(this->program_handle, vert);
        glAttachShader(this->program_handle, frag);
        
        char* geosrc;
        if(geometry_file_path) {
            fopen_s(&fp, geometry_file_path, "rb");
            fseek(fp, 0, SEEK_END);
            size = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            geosrc = (char*) _malloca((size + 1));
            fread(geosrc, 1, size, fp);
            geosrc[size] = '\0';
            fclose(fp);
            geo = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geo, 1, &geosrc, 0);
            glCompileShader(geo);
            glGetShaderiv(geo, GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(geo, 512, NULL, infoLog);
                fprintf(stderr, "[ERROR][GEOMETRY SHADER COMPILATION ERROR]\n%s\n", infoLog);
            }
            glAttachShader(this->program_handle, geo);
        }
        
        glLinkProgram(this->program_handle);
        glGetProgramiv(this->program_handle, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(this->program_handle, 512, NULL, infoLog);
            fprintf(stderr, "[ERROR][PROGRAM SHADER LINKING ERROR]\n%s\n", infoLog);
        }
        glDeleteShader(vert);
        glDeleteShader(frag);
        _freea(vertsrc);
        _freea(fragsrc);
        
        if(geometry_filepath) {
            glDeleteShader(geo);
            _freea(geosrc);
        }
    }
    
    inline void use() { glUseProgram(program_handle); }
    
    inline void
        set_uniform(char* name, glm::mat4 value)
    {
        glUniformMatrix4fv(glGetUniformLocation(program_handle, name),
                           1,
                           GL_FALSE,
                           glm::value_ptr(value));
    }
    
    inline void
        set_uniform(char* name, glm::mat3 value)
    {
        glUniformMatrix3fv(glGetUniformLocation(program_handle, name),
                           1,
                           GL_FALSE,
                           glm::value_ptr(value));
    }
    
    inline void
        set_uniform(char* name, glm::vec4 value)
    {
        glUniform4fv(glGetUniformLocation(program_handle, name),
                     1,
                     glm::value_ptr(value));
    }
    
    inline void
        set_uniform(char* name, glm::vec3 value)
    {
        glUniform3fv(glGetUniformLocation(program_handle, name),
                     1,
                     glm::value_ptr(value));
    }
    
    inline void
        set_uniform(char* name, glm::vec2 value)
    {
        glUniform2fv(glGetUniformLocation(program_handle, name),
                     1,
                     glm::value_ptr(value));
    }
    
    inline void
        set_uniform(char* name, int value)
    {
        glUniform1i(glGetUniformLocation(program_handle, name),
                    value);
    }
    
    inline void
        set_uniform(char* name, float value)
    {
        glUniform1f(glGetUniformLocation(program_handle, name),
                    value);
    }
    
    inline void
        set_uniform(char* name, bool value)
    {
        glUniform1i(glGetUniformLocation(program_handle, name),
                    value);
    }
    
    inline void
        set_uniform(char* name, uint value)
    {
        glUniform1ui(glGetUniformLocation(program_handle, name),
                     value);
    }
    
};

#endif //SIMPLE_RENDERER_IMPLEMENTATION

#endif //RENDERER_H
