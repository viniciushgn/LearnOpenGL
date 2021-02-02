#version 330 core

out vec4 FragColor;

uniform float ourColor;

vec4 color = vec4(1.0f,1.0f, ourColor, 1.0f);

void main(){
FragColor = color;
}