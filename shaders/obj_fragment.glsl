#version 330 core

out vec4 FragColor;

uniform vec3 random_color;

void main() {
   FragColor = vec4(0.1f, 0.3f, 0.2f, 1.0f);
    //FragColor = vec4(random_color, 1.0f);
}
