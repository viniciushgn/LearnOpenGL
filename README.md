# LearnOpenGL
Code created by following the https://learnopengl.com guide. 

IDE: Visual Studio Code

include: GLFW, GCC compilers, GLAD (OS specific function pointers to OpenGL)

VSCode compilando usando o arquivo task.json, não consegui gerar o projeto GLFW pelo CMake por que, aparentemente, o CMake não tem um generator para projetos no VSCode (criar o task.json.) Compilação feita usando ctrl-shift-b (build) baseada (com algumas mudanças) no código do guia encontrado em  "https://medium.com/@vivekjha92/setup-opengl-with-vs-code-82852c653c43", acessado dia 31/01/2021. include: GLFW, GCC compilers.

Código default do launch.json modificado para executar o executável gerado pelo build na pasta win_build.

Documentação relevante para entender os arquivos .json usados para build (task.json) e run (launch.json).

(Dúvida Resolvida) Como o EBO (element buffer object) sabe dos dados do vértice? 
O EBO quando binded ao VAO controla quais valores recebidos pelo vetor de atributos será usado. Ou seja, TODOS os atributos, incluindo cor, normal, textura, o que for. Para usar o EBO, potanto, precisamos decidir não só os valores de posição (no caso colocamos ele como atributo de index 0) mas também todos os outros possíveis. Por isso uma declaração mais explícita dos vértices não é necessária, tratamos de todos os atributos com os valores dos índices do EBO. Usamos só um EBO por VAO. 
