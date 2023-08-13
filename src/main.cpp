#include <framework.h>

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Window", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }
    else
    {
        Logger::getInstance().log_i("Hello World!");
    }

    Monitor::Monitor();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
