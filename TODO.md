## Backlog 
- [x] Build system
- [ ] Parse OBJ models 
    - [ ] Support parsing one object
    - [ ] Support parsing multiple objects
    - [ ] Test parsing mechanism with a simple obj file
    - [ ] Test parsing mechanism with a more complex obj file
- [x] Add option to close the window with the ESC key
- [x] Add check to see if .obj file exists 
- [ ] Core system 
    - [x] NDC Coordinates 
        - [x] Install cglm 
        - [x] Model Matrix
        - [x] View Matrix
        - [x] Projection Matrix
        - [x] Render Cube 
    - [ ] Camera 
        - [x] Move Around (WASD) 
        - [ ] Look Around (Mouse) 
    - [ ] Textures 
    - [ ] Logger 
    - [x] Window
    - [x] Shaders 
    - [x] Render submission 
    - [x] Utils 
- [x] Dynamic List appending (Keep reviewing this though)

## 9/29/2025 
- [x] Fix malloc issues (buffer.c)

## FIX:
- [x] Fix input system 

## Bugs 
- [ ] Investigate and fix free() and memory issues when closing the application

(double free or corruption (fasttop)
9101 IOT instruction (core dumped)  ./xeza obj_models/cube.obj)

- [x] Fix list_append logic

## Tools
CMake
Make
GLFW opengl ctx / window
Glad opengl function pointers
cimgui gui / telemetry
tiny-obj-loader loading obj files
stb_image textures
cglm math

## Links

This section provides all the third-party information that I read and used to apply onto this project.
learnopengl.com 

## Books To Read

learnopengl.com 

* Will need to find reccomendations on possible graphics books
* ECS?

NOTE: I want to get a basic system down first, and see from there what will need to be refactored
and if I need to change/add components.
