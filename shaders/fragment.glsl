#version 330 core

uniform float time;

in vec3 final_color;
out vec4 FragColor;

void main() {
    //FragColor = vec4(0.5f, 0.3f, 0.2f, 1.0f);
    vec3 red = (1.0f, 0.0f, 0.0f);
    vec3 green = (0.0f, 1.0f, 0.0f);
    vec3 blue = (0.0f, 0.0f, 1.0f);
    vec3 rg = mix(red, green, time);
    vec3 rgb = mix(rg, blue, time);
    FragColor = vec4(rgb, 1.0f);
}
