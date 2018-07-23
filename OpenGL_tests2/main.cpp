#include <iostream>
#include <chrono>
#include <thread>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

const GLint WIDTH = 800, HEIGHT = 600;
void printGL_Version();





int main(void)
{
    glfwInit();
    
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", nullptr, nullptr);
    
    int screenWidth, screenHeight;
    GLCall(glfwGetFramebufferSize(window, &screenWidth, &screenHeight));
    
    if (nullptr == window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    GLCall(glfwMakeContextCurrent(window));
    glfwSwapInterval(1);
    
    glewExperimental = GL_TRUE;
    
    if(glewInit() != GLEW_OK) {
        std::cout << "Hej! to jest error" << std::endl;
        return EXIT_FAILURE;
    }
    
    printGL_Version();
    
    GLCall(glViewport(0, 0, screenWidth, screenHeight));
    
//    xShader ourShader( "resources/shaders/basic.shader" );
    
    
    GLfloat positions[] =
    {
        //position
        -0.5f, -0.5f,    0.0f, 0.0f,
         0.5f, -0.5f,    1.0f, 0.0f,
         0.5f,  0.5f,    1.0f, 1.0f,
        -0.5f,  0.5f,    0.0f, 1.0f
    };
    
    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };
    
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    VertexArray va;
    VertexBuffer vb(positions, 4*4*sizeof(float));
    
    VertexBufferLayout layout;
    layout.Push(2, GL_FLOAT);
    layout.Push(2, GL_FLOAT);
    va.AddBuffer(vb, layout);
    
    IndexBuffer ib(indices, 6);

    Shader shader("resources/shaders/basic.shader");
    shader.Bind();
    shader.setUniform4f("u_Color", 0.9f, 0.2f, 0.2f, 0.9f);
    
    Texture texture("resources/textures/examplePicture.png");
    texture.Bind();
    shader.setUniform1i("u_Texture", 0);
    
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
    
    Renderer renderer;

    float red = 0.0f;
    float increment = 0.03f;
    
    while (!glfwWindowShouldClose(window))
    {
        GLCall(glfwPollEvents());
        
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        

        renderer.Clear();
        shader.Bind();
        
        shader.setUniform4f("u_Color", red, 0.2f, 0.2f, 0.9f);
        renderer.Draw(va, ib, shader);

        if(red > 1.0f)
            increment = -0.03f;
        else if(red < 0.0f)
            increment = 0.03f;
        
        red += increment;
        
        
        glfwSwapBuffers(window);
        
        
        // DELAY
//        float ggg = (float)(zzz%10) * 1.0f/10.0f;
//        GLCall(glUniform4f(location, ggg, 0.2f, 0.2f, 0.9f));
//        std::this_thread::sleep_for(0.02s);
//        zzz++;
////        std::cout << positions[3] << std::endl;
//        if(zzz>100) zzz=0;
    }
    
    glfwTerminate();
    return 0;
}

void printGL_Version()
{
    std::cout << std::endl << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << "======== OpenGL - version: " << glGetString(GL_VERSION) << " =========" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << "GL_TYPE: " << GL_FLOAT << std::endl;
}
