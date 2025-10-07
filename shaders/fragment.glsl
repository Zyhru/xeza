#version 330 core

in vec3 final_color;
out vec4 FragColor;

void main() {
    //FragColor = vec4(0.5f, 0.3f, 0.2f, 1.0f);
    FragColor = vec4(final_color, 1.0f);
}
