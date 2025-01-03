#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    // Initialize the GLEW
    if (glewInit() != GLEW_OK)
    {

    std::cout << "error" << std::endl;
    }
    
    std::cout << glGetString(GL_VERSION) << std::endl;
    {

    float positions[] = {
        0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f

    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    //GLCall(glEnable(GL_BLEND));
    //GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

    Shader shader("res/shaders/basic.shader");
    shader.Bind();


    shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    
    Texture texture("res/textures/Balling.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    float r = 0.6f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        //GLCall(glUseProgram(shader));
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        renderer.Draw(va, ib, shader);
        
        //if (r > 1.0f)
        //    increment = -0.05f;
        //else if (r < 0.0f)
        //    increment = 0.05f;

        //r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //glDeleteProgram(shader);

    }

    glfwTerminate();
    return 0;
}