#ifndef OPENGL_BASIC_DEMO_WINDOW_H
#define OPENGL_BASIC_DEMO_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace opengl_basic_demo
{

void framebufferSizeCallback(GLFWwindow* window, int width, int height);


class ApplicationWindow
{
    unsigned int m_width;
    unsigned int m_height;
    const char* m_title;
    GLFWwindow* m_window{};

  public:
    // Constructor
    ApplicationWindow(unsigned int width, unsigned int height, const char* title)
        : m_width(width), m_height(height), m_title(title) {}

    // Open the window and start its render loop
    void start();
  
  private:
    // glfw: initialize and configure - helper method
    void initialiseGlfw();

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react
    // accordingly
    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
    }
};

} // opengl_basic_demo

#endif
