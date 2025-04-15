#include <glad/glad.h>
#include <GLFW/glfw3.h>

//download this and go back to beginning of textures to find cpp code for this header
#include "../include/stb_image.h"

#include "../include/shader.h"

#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
    
int main() {
    //glfw: initliaze and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfw window creation
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout <<"Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    std::cout << "Making colorInput shader program." << std::endl;
    Shader colorInput("../shaders/colorInput.vs", "../shaders/colorInput.fs");
    std::cout << "Making colorUpdate shader program" << std::endl;
    Shader colorUpdate("../shaders/colorUpdate.vs", "../shaders/colorUpdate.fs");

    // set up vertex data and buffers and configure vertex attributes
    float triangle1[] = {
        -1.0f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.0f, -0.5f, 0.0f
    };
    float triangle2[] = {
         0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    float rectangle[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, //bottom left
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, //bottom right
        -0.7f, -0.3f, 0.0f, 0.0f, 1.0f, //top left
        -0.2f,  0.7f, 0.0f, 1.0f, 1.0f  //top right
    };
    unsigned int indices[] = {  // note that we start from 0!
       0, 1, 3,   // first triangle
       0, 2, 3    // second triangle
    };

    float texCoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f
    };

    int width, height, nrChannels;
    unsigned char *data = stbi_load("../textures/wall.jpg", &width, &height, &nrChannels, 0);

    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }

    //unsigned int VAO, VBO, EBO;
    unsigned int VAO[3];
    unsigned int VBO[3];
    unsigned int EBO[1];

    glGenVertexArrays(3, VAO);
    glGenBuffers(3, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float alphaValue = std::abs(std::sin(timeValue));
        float oppAlphaValue = std::abs(std::sin(1 - timeValue));
        int vertexColorLocation = glGetUniformLocation(colorUpdate.ID, "inputColor");
        int texOrNotLocation = glGetUniformLocation(colorUpdate.ID, "texOrNot");
        colorUpdate.use();
        glUniform1f(vertexColorLocation, alphaValue);
        glUniform1i(texOrNotLocation, 0);
        colorUpdate.setFloat("xOffset", .5); 

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        colorInput.use();
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        colorUpdate.use();
        glUniform1f(vertexColorLocation, oppAlphaValue);
        glUniform1i(texOrNotLocation, 1);
        colorUpdate.setFloat("xOffset", 0.0f);
        glBindVertexArray(VAO[2]);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(1, EBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}