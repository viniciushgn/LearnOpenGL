#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <cmath> //sin function for BlueLevel

#include <shaders/ShaderClass.h> //loading and setting up shader programs

#include <glm/glm.hpp> //GLM matrizes e vetores
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <imageLoader/stb_image.h> //loading images

float mixFloatValue = 0.0f;

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
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        mixFloatValue = mixFloatValue + 0.0005f;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        mixFloatValue = mixFloatValue - 0.0005f;
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
float vertices[] = {    
    //vertex positions              //color                texture coordinate
     0.5f,  0.5f, 0.0f,          1.0f,0.0f,0.0f,               1.0f,  1.0f,                // top right
     0.5f, -0.5f, 0.0f,          0.0f,1.0f,0.0f,               1.0f,0.0f,                 // bottom right
    -0.5f, -0.5f, 0.0f,          1.0f,0.0f,0.0f,               0.0f,0.0f,                // bottom left
    -0.5f,  0.5f, 0.0f,          0.0f,0.0f,1.0f,               0.0f,1.0f,               // top left 
};


unsigned int indices[] = {
    0,1,3,1,2,3
};
//1
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
//2
stbi_set_flip_vertically_on_load(true);
unsigned char *faceTexData = stbi_load("./assets/texture/awesomeface.png", &largura, &altura, &nrChannels, 0);
stbi_set_flip_vertically_on_load(false);

unsigned int awesomeFaceTexture;
glGenTextures(1, &awesomeFaceTexture);

glBindTexture(GL_TEXTURE_2D, awesomeFaceTexture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, faceTexData);
glGenerateMipmap(GL_TEXTURE_2D);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

if(!faceTexData)
{
    std::cout << "Failed to load texture" << std::endl;
}

stbi_image_free(faceTexData);
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

glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 8*sizeof(float),(void*)0);
glEnableVertexAttribArray(0);

glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 8*sizeof(float),(void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);

glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, containerTexture); 

glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, awesomeFaceTexture);

shader1.use();
shader1.setInt("ourTexture", 0);
shader1.setInt("mixTexture", 1);
shader1.setFloat("mixParameter", 0.2);

//--------------------------------------------------------------------------------------
//CHANGE COLOR--------------------------------------------------------------------------

//testando vetores
glm::mat4 trans = glm::mat4(1.0f);

trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
trans = glm::scale(trans, glm::vec3(2.0f,2.0f,2.0f));

//fim


unsigned int transformLocal = glGetUniformLocation(shader1.ID, "transform");
glUniformMatrix4fv(transformLocal, 1,GL_FALSE, glm::value_ptr(trans));

//--------------------------------------------------------------------------------------
//LOOP----------------------------------------------------------------------------------
while(!glfwWindowShouldClose(janela)){
    processaImput(janela);
    shader1.setFloat("mixParameter", mixFloatValue);
    glClear(GL_COLOR_BUFFER_BIT);
    shader1.use();
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0,3);

    glm::mat4 trans = glm::mat4(1.0f);


    trans = glm::translate(trans, glm::vec3(1.0f,0.0f,0.0f));
    
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f,0.0f,1.0f));
    trans = glm::scale(trans, glm::vec3(0.5f,0.5f,0.5f));



    glUniformMatrix4fv(transformLocal, 1,GL_FALSE, glm::value_ptr(trans));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    trans = glm::mat4(1.0f);

    trans = glm::translate(trans, glm::vec3(-1.0f,0.0f,0.0f));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f,0.0f,1.0f));

    trans = glm::scale(trans, glm::vec3(2.0f,2.0f,2.0f));


    glUniformMatrix4fv(transformLocal, 1,GL_FALSE, glm::value_ptr(trans));

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



