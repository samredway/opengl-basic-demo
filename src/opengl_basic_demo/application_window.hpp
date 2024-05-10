#ifndef OPENGL_BASIC_DEMO_WINDOW_H
#define OPENGL_BASIC_DEMO_WINDOW_H

namespace opengl_basic_demo {

void framebufferSizeCallback(GLFWwindow* window, int width, int height);


class ApplicationWindow {
public:
    // Constructor
    ApplicationWindow(unsigned int width, unsigned int height, const char* title)
        : m_width(width), m_height(height), m_title(title) {}

    // Open the window and start its render loop
    void start();
  
private:
    // members
    unsigned int m_width;
    unsigned int m_height;
    const char* m_title;
    GLFWwindow* m_window{};
  
    // glfw: initialize and configure - helper method
    void initialiseGlfw();

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react
    // accordingly
    void processInput(GLFWwindow* window);
};

} // opengl_basic_demo

#endif
