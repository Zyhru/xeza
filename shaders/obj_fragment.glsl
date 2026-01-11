#version 330 core

out vec4 FragColor;

uniform vec3 random_color;
uniform float time;


void main() {
    vec3 red = vec3(1.0, 0.0, 0.0);
    vec3 green = vec3(0.0, 1.0, 0.0);
    vec3 blue = vec3(0.0, 0.0, 1.0);
   
    vec3 rg = mix(red, green, time);
    vec3 rgb = mix(rg, blue, time);
   
    FragColor = vec4(rgb, 1.0f);
    //FragColor = vec4(0.4f, 0.3f, 0.2f, 1.0f);
    //FragColor = vec4(random_color, 1.0f);
}
