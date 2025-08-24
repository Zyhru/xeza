#ifndef COLOR_H 
#define COLOR_H

// TODO:: Create a simple color system to easily pass in predefined 
// custom colors that I like

// Soft pastel purple
float bg1[4] = {0.4f, 0.3f, 0.6f, 1.0f};

// Muted teal / cyan
float bg2[4] = {0.2f, 0.5f, 0.6f, 1.0f};

// Warm pinkish tone
float bg3[4] = {0.8f, 0.5f, 0.6f, 1.0f};

// Classic grayish PSX background
float bg4[4] = {0.25f, 0.25f, 0.25f, 1.0f};

// Faded blue / nostalgic Y2K color
float bg5[4] = {0.35f, 0.45f, 0.6f, 1.0f};

typedef struct {
    float r;
    float g;
    float b;
} color_t;

void color_create(color_t *color);

#endif
