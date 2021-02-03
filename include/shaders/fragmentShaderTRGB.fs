#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 ourTexPos;

uniform sampler2D ourTexture;
uniform sampler2D mixTexture;

uniform float mixParameter;


void main(){


FragColor = mix((vec4(ourColor,1.0f) + texture(ourTexture, ourTexPos)), texture(mixTexture, ourTexPos), mixParameter);
}
