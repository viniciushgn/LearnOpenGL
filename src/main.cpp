#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int largura, int altura)
{
    glViewport(0,0,largura,altura);
}

void processaImput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

}

//VERTEX SHADER CODE------------------------------------------------------------------
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"

"void main(){\n"
    "GL_POSITION = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//------------------------------------------------------------------------------------
//FRAGMENT SHADER CODE----------------------------------------------------------------
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor\n"
"void main(){\n"
"FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
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
float vertices[] = {
    -0.5f,-0.5,0.0f,
    0.5f,-0.5f,0.0f,
    0.0f,0.5f,0.0f
};

unsigned int VBO;
glGenBuffers(1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

//Shader Vertex
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
//Errors Compiling?
int  success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if(!success)
{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
//Shader Fragment
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

//--------------------------------------------------------------------------------------
//LOOP----------------------------------------------------------------------------------
while(!glfwWindowShouldClose(janela)){
    processaImput(janela);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(janela);
    glfwPollEvents();
}
//--------------------------------------------------------------------------------------
//TERMINATE-----------------------------------------------------------------------------
glfwTerminate();
return 0;
//--------------------------------------------------------------------------------------
}



