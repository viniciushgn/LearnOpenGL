#version 330 core

out vec4 FragColor;
in vec2 ourTexPos;

uniform sampler2D ourTexture;
uniform sampler2D mixTexture;

uniform float mixParameter;


void main(){


FragColor = mix(( texture(ourTexture, ourTexPos)), texture(mixTexture, ourTexPos), mixParameter);
}
