#version 330 core

in vec3 final_color;
out vec4 FragColor;

void main() {
    FragColor = vec4(final_color, 1.0f);
}
