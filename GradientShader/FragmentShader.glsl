#version 330 core

in vec2 texCoords;
out vec4 FragColor;

void main() {
    vec3 orange = vec3(1.0, 0.65, 0.0);
   vec3 lightBlue = vec3(0.68, 0.85, 0.9); // Albastru deschis (173, 216, 230)
    FragColor = vec4(mix(orange, lightBlue, texCoords.y), 1.0); // Gradient based on Y coordinate
}
