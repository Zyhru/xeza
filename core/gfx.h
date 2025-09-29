#ifndef GFX_H
#define GFX_H

#include "api.h"
#include "renderer.h"
#include "window.h"
#include "camera.h"
#include "obj.h"

void init(char* obj_file);
void update();
void render();
void destroy();

#endif
