#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <cmath> //sin function for BlueLevel

#include <shaders/ShaderClass.h> //loading and setting up shader programs

#define STB_IMAGE_IMPLEMENTATION
#include <imageLoader/stb_image.h> //loading images


void framebuffer_size_callback(GLFWwindow* window, int largura, int altura)
{
    glViewport(0,0,largura,altura);
}

void processaImput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
        
}

int main()
{
//GLFW INICIALIZANDO------------------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); OSX
    
    GLFWwindow* janela = glfwCreateWindow(800,600,"Learning", NULL, NULL);

    if(janela == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(janela);
    glfwSetFramebufferSizeCallback(janela, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0,800,600);
    glClearColor(0.2f,0.3f,0.3f,1.0f);

//--------------------------------------------------------------------------------------

//SHADERS-------------------------------------------------------------------------------

Shader shader1("./include/shaders/vertexShaderTRGB.vs", "./include/shaders/fragmentShaderTRGB.fs");
shader1.use();


//--------------------------------------------------------------------------------------

//VAO-----------------------------------------------------------------------------------


//MODELS------------------------------------------------
float vertices[] = {               //color                texture coordinate
     0.5f,  0.5f, 0.0f,          1.0f,0.0f,0.0f,              // top right
     0.5f, -0.5f, 0.0f,          0.0f,1.0f,0.0f,              // bottom right
    -0.5f, -0.5f, 0.0f,          1.0f,0.0f,0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,          0.0f,0.0f,1.0f,               // top left 
};


unsigned int indices[] = {
    0,1,3,1,2,3
};

int largura, altura, nrChannels;
unsigned char *containerTexData = stbi_load("./assets/texture/container.jpg", &largura, &altura, &nrChannels, 0);

unsigned int containerTexture;
glGenTextures(1, &containerTexture);

glBindTexture(GL_TEXTURE_2D, containerTexture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, containerTexData);
glGenerateMipmap(GL_TEXTURE_2D);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

if(!containerTexData)
{
    std::cout << "Failed to load texture" << std::endl;
}

stbi_image_free(containerTexData);
//------------------------------------------------------
//1

unsigned int VAO;
glGenVertexArrays(1, &VAO);
unsigned int VBO;
glGenBuffers(1,&VBO);
unsigned int EBO;
glGenBuffers(1,&EBO);


glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 6*sizeof(float),(void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 6*sizeof(float),(void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


//--------------------------------------------------------------------------------------
//CHANGE COLOR--------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
//LOOP----------------------------------------------------------------------------------
while(!glfwWindowShouldClose(janela)){
    processaImput(janela);
    glClear(GL_COLOR_BUFFER_BIT);
    shader1.use();
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0,3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(janela);
    glfwPollEvents();
}
//--------------------------------------------------------------------------------------
//TERMINATE-----------------------------------------------------------------------------
glfwTerminate();
return 0;
//--------------------------------------------------------------------------------------
}



