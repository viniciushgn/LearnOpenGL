#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <cmath> //sin function for BlueLevel

#include <shaders/ShaderClass.h> //

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
Shader shader2("./include/shaders/vertexShaderGrad.vs", "./include/shaders/fragmentShaderGrad.fs");

shader2.use();
//--------------------------------------------------------------------------------------

//VAO-----------------------------------------------------------------------------------

float vertices[] = {           //color
     0.5f,  0.5f, 0.0f, 1.0f,0.0f,0.0f,  // top right
     0.5f, -0.5f, 0.0f, 0.0f,1.0f,0.0f,  // bottom right
//    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f, 0.0f,0.0f,1.0f   // top left 
};

float vertices2[] = {
    -0.6f,  0.5f, 0.0f,   
    -0.6f, -0.5f, 0.0f,
    0.4f, -0.5f, 0.0f
};

unsigned int indices[] = {
    0,1,3,3,2,1
};

//1

unsigned int VAO;
glGenVertexArrays(1, &VAO);
unsigned int VBO;
glGenBuffers(1,&VBO);
//unsigned int EBO;
//glGenBuffers(1,&EBO);


glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 6*sizeof(float),(void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 6*sizeof(float),(void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);

//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//2

unsigned int VAO2;
glGenVertexArrays(1, &VAO2);
unsigned int VBO2;
glGenBuffers(1,&VBO2);
//unsigned int EBO;
//glGenBuffers(1,&EBO);


glBindVertexArray(VAO2);

glBindBuffer(GL_ARRAY_BUFFER, VBO2);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices2),vertices2,GL_STATIC_DRAW);
glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3*sizeof(float),(void*)0);
glEnableVertexAttribArray(0);

//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//--------------------------------------------------------------------------------------
//CHANGE COLOR--------------------------------------------------------------------------
float timeNow = glfwGetTime();
float blueLevel = (sin(timeNow)/ 2.0f) + 0.5f;
shader2.setFloat("ourColor", blueLevel);

//--------------------------------------------------------------------------------------
//LOOP----------------------------------------------------------------------------------
while(!glfwWindowShouldClose(janela)){
    processaImput(janela);
    glClear(GL_COLOR_BUFFER_BIT);
    shader1.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0,3);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    shader2.use();                                                                                                                                              
    glBindVertexArray(VAO2);

    timeNow = glfwGetTime();
    shader2.setFloat("ourColor", blueLevel);
    blueLevel = (sin(timeNow)/ 4.0f) + 0.75f;

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(janela);
    glfwPollEvents();
}
//--------------------------------------------------------------------------------------
//TERMINATE-----------------------------------------------------------------------------
glfwTerminate();
return 0;
//--------------------------------------------------------------------------------------
}



