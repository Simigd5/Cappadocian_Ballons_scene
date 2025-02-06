#version 330 core

layout(location = 0) in vec3 position;

out vec2 texCoords;

void main() {
    texCoords = vec2((position.x + 1.0) / 2.0, (position.y + 1.0) / 2.0); // Map to [0, 1]
    gl_Position = vec4(position, 1.0);
}
