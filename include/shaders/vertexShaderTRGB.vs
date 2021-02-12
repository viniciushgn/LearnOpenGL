#version 330 core

layout (location = 0) in vec3 aPos;


layout (location = 1) in vec2 aTexPos;


out vec2 ourTexPos;

uniform mat4 transform;

//projections in order
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){

    gl_Position =          projection*view*model                * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);


    ourTexPos = aTexPos;

}
