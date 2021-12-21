#include <glad/glad.h>
#include "challenges.h"

#include <stdlib.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include "defines.h"

#ifndef MCLONE_NO_CHALLENGES
namespace Challenges {
    
    //~ Episode 2
    
    // Shader Strings....
    const char* v_ep2_src = "#version 330 core\n"
        "layout (location = 0) in vec2  a_pos;\n"
        "\n"
        "void main() {\n"
        "    gl_Position = vec4(a_pos, 0.0, 1.0);\n"
        "}\n";
    
    const char* f_ep2_src = "#version 330 core\n"
        "\n"
        "layout (location = 0) out vec4 f_color;\n"
        "\n"
        "void main() {\n"
        "    f_color = vec4(1.0);\n"
        "}\n";
    
    
    struct Episode2_ChallengeState {
        GLuint vertex_array;
        GLuint vertex_buffer;
        GLuint element_buffer;
        
        // If you're following the series and are on episode 2, dw about this
        GLuint program;
    };
    
    Episode2_ChallengeState state;
    
    // If you're following the series and are on episode 2, dw about this
    static void Ep2_CreateShader() {
        int ret;
        unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &v_ep2_src, nullptr);
        glCompileShader(vs);
        glGetShaderiv(vs, GL_COMPILE_STATUS, &ret);
        if (ret == GL_FALSE) {
            int length;
            glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
            GLchar *info = (GLchar *)calloc(length, sizeof(GLchar));
            glGetShaderInfoLog(vs, length, nullptr, info);
            fprintf(stderr, "glCompileShader(vertex) failed:\n%s\n", info);
            free(info);
            exit(-20);
        }
        
        unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &f_ep2_src, nullptr);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &ret);
        if (ret == GL_FALSE) {
            int length;
            glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);
            GLchar *info = (GLchar *)calloc(length, sizeof(GLchar));
            glGetShaderInfoLog(fs, length, nullptr, info);
            fprintf(stderr, "glCompileShader(fragment) failed:\n%s\n", info);
            free(info);
            exit(-21);
        }
        
        state.program = glCreateProgram();
        glAttachShader(state.program, vs);
        glAttachShader(state.program, fs);
        glLinkProgram(state.program);
        glGetProgramiv(state.program, GL_LINK_STATUS, &ret);
        if (ret == GL_FALSE) {
            int length;
            glGetProgramiv(state.program, GL_INFO_LOG_LENGTH, &length);
            GLchar *info = (GLchar *)calloc(length, sizeof(GLchar));
            glGetProgramInfoLog(state.program, length, NULL, info);
            fprintf(stderr, "glLinkProgram failed:\n%s\n", info);
            free(info);
            exit(-22);
        }
        glValidateProgram(state.program);
        glGetProgramiv(state.program, GL_VALIDATE_STATUS, &ret);
        if (ret == GL_FALSE) {
            int length;
            glGetProgramiv(state.program, GL_INFO_LOG_LENGTH, &length);
            GLchar *info = (GLchar *)calloc(length, sizeof(GLchar));
            glGetProgramInfoLog(state.program, length, nullptr, info);
            fprintf(stderr, "glValidateProgram failed:\n%s\n", info);
            free(info);
            exit(-23);
        }
        glDetachShader(state.program, vs);
        glDetachShader(state.program, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);
    }
    
    static void Ep2_FreeShader() {
        glDeleteProgram(state.program);
    }
    
    //- Challenge 1 
    void Ep2_1_Init() {
        Ep2_CreateShader();
        
        glGenVertexArrays(1, &state.vertex_array);
        glBindVertexArray(state.vertex_array);
        
        float data[] = {
            -.5f, -.5f, // Bottom left
            +.5f, -.5f, // Bottom right
            +.5f, +.5f, // Top right
            
            -.5f, -.5f, // Bottom left
            +.5f, +.5f, // Top right
            -.5f, +.5f, // Top left
        };
        
        glGenBuffers(1, &state.vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, state.vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
    }
    
    void Ep2_1_Draw() {
        glBindVertexArray(state.vertex_array);
        glUseProgram(state.program);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    
    void Ep2_1_Free() {
        glDeleteBuffers(1, &state.vertex_buffer);
        glDeleteVertexArrays(1, &state.vertex_array);
        Ep2_FreeShader();
    }
    
    
    //- Challenge 2 
    void Ep2_2_Init() {
        Ep2_CreateShader();
        
        glGenVertexArrays(1, &state.vertex_array);
        glBindVertexArray(state.vertex_array);
        
        float data[] = {
            -.5f, -.5f, // Bottom left
            +.5f, -.5f, // Bottom right
            +.5f, +.5f, // Top right
            -.5f, +.5f, // Top left
        };
        
        glGenBuffers(1, &state.vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, state.vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
        
        u32 indices[] = {
            0, 1, 2,
            0, 2, 3
        };
        
        glGenBuffers(1, &state.element_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state.element_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }
    
    void Ep2_2_Draw() {
        glBindVertexArray(state.vertex_array);
        glUseProgram(state.program);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    void Ep2_2_Free() {
        glDeleteBuffers(1, &state.vertex_buffer);
        glDeleteBuffers(1, &state.element_buffer);
        glDeleteVertexArrays(1, &state.vertex_array);
        Ep2_FreeShader();
    }
    
    //- Challenge 3 
    void Ep2_3_Init() {
        Ep2_CreateShader();
        
        glGenVertexArrays(1, &state.vertex_array);
        glBindVertexArray(state.vertex_array);
        
        // Radius of inner circle
        float inner = 0.20f;
        // Theta offset of inner circle
        float inner_theta = glm::radians(130.f);
        // Radius of outer circle
        float outer = 0.50f;
        // Theta offset of outer circle
        float outer_theta = glm::radians(90.f);
        
        // Calculated using multiple Polar Coordinate to Cartesian Coordinate conversions
        float data[] = {
            // Origin
            0.f, 0.f,
            
            // Inner circle
            inner * glm::cos(inner_theta + glm::radians(72 * 0.f)), inner * glm::sin(inner_theta + glm::radians(72 * 0.f)),
            inner * glm::cos(inner_theta + glm::radians(72 * 1.f)), inner * glm::sin(inner_theta + glm::radians(72 * 1.f)),
            inner * glm::cos(inner_theta + glm::radians(72 * 2.f)), inner * glm::sin(inner_theta + glm::radians(72 * 2.f)),
            inner * glm::cos(inner_theta + glm::radians(72 * 3.f)), inner * glm::sin(inner_theta + glm::radians(72 * 3.f)),
            inner * glm::cos(inner_theta + glm::radians(72 * 4.f)), inner * glm::sin(inner_theta + glm::radians(72 * 4.f)),
            
            // Outer circle
            outer * glm::cos(outer_theta + glm::radians(72 * 0.f)), outer * glm::sin(outer_theta + glm::radians(72 * 0.f)),
            outer * glm::cos(outer_theta + glm::radians(72 * 1.f)), outer * glm::sin(outer_theta + glm::radians(72 * 1.f)),
            outer * glm::cos(outer_theta + glm::radians(72 * 2.f)), outer * glm::sin(outer_theta + glm::radians(72 * 2.f)),
            outer * glm::cos(outer_theta + glm::radians(72 * 3.f)), outer * glm::sin(outer_theta + glm::radians(72 * 3.f)),
            outer * glm::cos(outer_theta + glm::radians(72 * 4.f)), outer * glm::sin(outer_theta + glm::radians(72 * 4.f)),
        };
        
        glGenBuffers(1, &state.vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, state.vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
        
        u32 indices[] = {
            6,  1, 0, 1, 7,  0,
            7,  2, 0, 2, 8,  0,
            8,  3, 0, 3, 9,  0,
            9,  4, 0, 4, 10, 0,
            10, 5, 0, 5, 6,  0
        };
        
        glGenBuffers(1, &state.element_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state.element_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }
    
    void Ep2_3_Draw() {
        glBindVertexArray(state.vertex_array);
        glUseProgram(state.program);
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
    }
    
    void Ep2_3_Free() {
        glDeleteBuffers(1, &state.vertex_buffer);
        glDeleteBuffers(1, &state.element_buffer);
        glDeleteVertexArrays(1, &state.vertex_array);
        Ep2_FreeShader();
    }
    
    //- Challenge 4 
    void Ep2_4_Init() {
        Ep2_CreateShader();
        
        glGenVertexArrays(1, &state.vertex_array);
        glBindVertexArray(state.vertex_array);
        
        float data[] = {
            -.5f, -.5f, // Bottom left
            +.5f, -.5f, // Bottom right
            +.5f, +.5f, // Top right
            -.5f, +.5f, // Top left
        };
        
        glGenBuffers(1, &state.vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, state.vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
        
        u32 indices[] = {
            0, 1,
            1, 2,
            2, 3,
            3, 0
        };
        
        glGenBuffers(1, &state.element_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state.element_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }
    
    void Ep2_4_Draw() {
        glBindVertexArray(state.vertex_array);
        glUseProgram(state.program);
        glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
    }
    
    void Ep2_4_Free() {
        glDeleteBuffers(1, &state.vertex_buffer);
        glDeleteBuffers(1, &state.element_buffer);
        glDeleteVertexArrays(1, &state.vertex_array);
        Ep2_FreeShader();
    }
    
    //- Challenge 5 
    void Ep2_5_Init() {
        Ep2_CreateShader();
        
        glGenVertexArrays(1, &state.vertex_array);
        glBindVertexArray(state.vertex_array);
        
        // Radius of inner circle
        float inner = 0.20f;
        // Theta offset of inner circle
        float inner_theta = glm::radians(130.f);
        // Radius of outer circle
        float outer = 0.50f;
        // Theta offset of outer circle
        float outer_theta = glm::radians(90.f);
        
        // Calculated using multiple Polar Coordinate to Cartesian Coordinate conversions
        float data[] = {
            // Origin
            0.f, 0.f,
            
            // Inner circle
            inner * glm::cos(inner_theta + glm::radians(72 * 0.f)), inner * glm::sin(inner_theta + glm::radians(72 * 0.f)),
            inner * glm::cos(inner_theta + glm::radians(72 * 1.f)), inner * glm::sin(inner_theta + glm::radians(72 * 1.f)),
            inner * glm::cos(inner_theta + glm::radians(72 * 2.f)), inner * glm::sin(inner_theta + glm::radians(72 * 2.f)),
            inner * glm::cos(inner_theta + glm::radians(72 * 3.f)), inner * glm::sin(inner_theta + glm::radians(72 * 3.f)),
            inner * glm::cos(inner_theta + glm::radians(72 * 4.f)), inner * glm::sin(inner_theta + glm::radians(72 * 4.f)),
            
            // Outer circle
            outer * glm::cos(outer_theta + glm::radians(72 * 0.f)), outer * glm::sin(outer_theta + glm::radians(72 * 0.f)),
            outer * glm::cos(outer_theta + glm::radians(72 * 1.f)), outer * glm::sin(outer_theta + glm::radians(72 * 1.f)),
            outer * glm::cos(outer_theta + glm::radians(72 * 2.f)), outer * glm::sin(outer_theta + glm::radians(72 * 2.f)),
            outer * glm::cos(outer_theta + glm::radians(72 * 3.f)), outer * glm::sin(outer_theta + glm::radians(72 * 3.f)),
            outer * glm::cos(outer_theta + glm::radians(72 * 4.f)), outer * glm::sin(outer_theta + glm::radians(72 * 4.f)),
        };
        
        glCreateBuffers(1, &state.vertex_buffer);
        glNamedBufferData(state.vertex_buffer, sizeof(data), data, GL_STATIC_DRAW);
        // Adds the vertex buffer to the vao
        glVertexArrayVertexBuffer(state.vertex_array, 0, state.vertex_buffer, 0, 2 * sizeof(float));
        glVertexArrayAttribFormat(state.vertex_array, 0, 2, GL_FLOAT, GL_FALSE, 0);
        glEnableVertexArrayAttrib(state.vertex_array, 0);
        
        u32 indices[] = {
            6,  1, 0, 1, 7,  0,
            7,  2, 0, 2, 8,  0,
            8,  3, 0, 3, 9,  0,
            9,  4, 0, 4, 10, 0,
            10, 5, 0, 5, 6,  0
        };
        
        glCreateBuffers(1, &state.element_buffer);
        glNamedBufferData(state.element_buffer, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexArrayElementBuffer(state.vertex_array, state.element_buffer);
    }
    
    void Ep2_5_Draw() {
        glBindVertexArray(state.vertex_array);
        glUseProgram(state.program);
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
    }
    
    void Ep2_5_Free() {
        glDeleteBuffers(1, &state.vertex_buffer);
        glDeleteBuffers(1, &state.element_buffer);
        glDeleteVertexArrays(1, &state.vertex_array);
        Ep2_FreeShader();
    }
}
#endif //MCLONE_NO_CHALLENGES