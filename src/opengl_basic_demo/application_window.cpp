#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "application_window.hpp"
#include "exceptions.hpp"

#ifdef __APPLE__
    bool is_apple {true};
#endif


namespace opengl_basic_demo {

void ApplicationWindow::start() {
    // initial GLFW and create window instance
    initialiseGlfw();

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw ApplicationWindowException(std::string("Unable to load glad function pointers"));
    }

    // do render loop
    while (!glfwWindowShouldClose(m_window)) {
        // input
        // -----
        processInput(m_window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    // after exit based on user input close down GLFW gracefully
    glfwTerminate();
}

void ApplicationWindow::initialiseGlfw() {
    // initialise GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (is_apple) {
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    // create GLFW window instance
    m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
    if (m_window == NULL) {
        glfwTerminate();
        throw ApplicationWindowException(std::string("Failed to create GLFW window"));
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback); 
}

void ApplicationWindow::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

}  // opengl_basic_demo