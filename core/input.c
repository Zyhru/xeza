#include "input.h"

void input_check(input_t* input, GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        input->forward = true;
    } else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
        input->forward = false;
    }
   
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        input->left = true;
    } else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
        input->left = false;
    }
    
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        input->backward = true;
    } else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
        input->backward = false;
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        input->right = true;
    } else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
        input->right = false;
    }
}
