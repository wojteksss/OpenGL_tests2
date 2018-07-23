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
const float fWIDTH = WIDTH, fHEIGHT = 600;



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
    
    
    
    GLfloat positions[] =
    {
        //position
         100.0f,  100.0f,    0.0f, 0.0f,
         200.0f,  100.0f,    1.0f, 0.0f,
         200.0f,  200.0f,    1.0f, 1.0f,
         100.0f,  200.0f,    0.0f, 1.0f
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
    
    glm::mat4 proj = glm::ortho(0.0f, fWIDTH, 0.0f, fHEIGHT, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
    
    glm::mat4 mvp = proj * view * model;

    Shader shader("resources/shaders/basic.shader");
    shader.Bind();
    shader.setUniform4f("u_Color", 0.9f, 0.2f, 0.2f, 0.9f);
    shader.setUniformMat4f("u_MVP", mvp);
    
    Texture texture("resources/textures/examplePicture.png");
    texture.Bind();
    shader.setUniform1i("u_Texture", 0);
    
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
    
    Renderer renderer;
    
//    ImGui::CreateContext();
//    ImGui_ImplGlfwGL3_Init(window, true);
//    ImGui::StyleColorsDark();

    
//    bool show_demo_window = true;
//    bool show_another_window = false;
//    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    while (!glfwWindowShouldClose(window))
    {
        GLCall(glfwPollEvents());
        
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        

        renderer.Clear();
        
//        ImGui_ImplGlfwGL3_NewFrame();
        
        shader.Bind();
        
        renderer.Draw(va, ib, shader);
        
        
//        {
//            static float f = 0.0f;
//            static int counter = 0;
//            ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
//            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
//            
//            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
//            ImGui::Checkbox("Another Window", &show_another_window);
//            
//            if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
//                counter++;
//            ImGui::SameLine();
//            ImGui::Text("counter = %d", counter);
//            
//            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//        }
        
        
//        ImGui::Render();
//        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
    }
    
//    ImGui_ImplGlfwGL3_Shutdown();
//    ImGui::DestroyContext();
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
