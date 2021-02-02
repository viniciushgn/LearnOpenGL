#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <cmath> //sin function for BlueLevel

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

//VERTEX SHADER CODE------------------------------------------------------------------
const char *vertexShaderSource1 = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"

"out vec3 ourColor;\n"
"void main(){\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "ourColor = aColor;\n"
"}\0";

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"

"void main(){\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//usei layout (location = 0) pra falar de onde eu estou recebendo e onde vou colocar (no vetor vec3 aPos) 

//------------------------------------------------------------------------------------
//FRAGMENT SHADER CODE----------------------------------------------------------------
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main(){\n"
"FragColor = vec4(ourColor,1.0f);\n"
"}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main(){\n"
"FragColor = ourColor;\n"
"}\0";
//------------------------------------------------------------------------------------
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
//MODEL---------------------------------------------------------------------------------



//SHADERS-------------------------------------------------------------------------------
//Shader Vertex 1
unsigned int vertexShader1;
vertexShader1 = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader1, 1, &vertexShaderSource1, NULL);
glCompileShader(vertexShader1);
//Errors Compiling?
int  success;
char infoLog[512];
glGetShaderiv(vertexShader1, GL_COMPILE_STATUS, &success);
if(!success)
{
    glGetShaderInfoLog(vertexShader1, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
//Shader Vertex
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
//Errors Compiling?
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if(!success)
{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
//Shader Fragment 1
unsigned int fragmentShader;
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);
//Errors Compiling?
glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
if(!success){

    glGetShaderInfoLog(fragmentShader,512,NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

}
//Shader Fragment 2
unsigned int fragmentShader2;
fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
glCompileShader(fragmentShader2);
//Errors Compiling?
glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
if(!success){

    glGetShaderInfoLog(fragmentShader2,512,NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

}

//Shader Program 1
unsigned int shaderProgram;
shaderProgram = glCreateProgram();

glAttachShader(shaderProgram, vertexShader1);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);

glDeleteShader(fragmentShader);
glDeleteShader(vertexShader1);

glUseProgram(shaderProgram);

//Shader Program 2
unsigned int shaderProgram2;
shaderProgram2 = glCreateProgram();

glAttachShader(shaderProgram2, vertexShader);
glAttachShader(shaderProgram2, fragmentShader2);
glLinkProgram(shaderProgram2);

glDeleteShader(vertexShader);
glDeleteShader(fragmentShader2);

glUseProgram(shaderProgram2);

//--------------------------------------------------------------------------------------

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
int uniformColorLocation = glGetUniformLocation(shaderProgram2, "ourColor");
//--------------------------------------------------------------------------------------
//LOOP----------------------------------------------------------------------------------
while(!glfwWindowShouldClose(janela)){
    processaImput(janela);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0,3);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    glUseProgram(shaderProgram2);                                                                                                                                                
    glBindVertexArray(VAO2);

    timeNow = glfwGetTime();
    glUniform4f(uniformColorLocation, 1.0f, 1.0f, blueLevel, 1.0f);
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



