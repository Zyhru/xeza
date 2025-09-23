## TODO

- [x] Build system
- [ ] Parse OBJ models 
- [ ] Core system 
    - [x] NDC Coordinates 
        - [x] Install cglm 
        - [x] Model Matrix
        - [x] View Matrix
        - [x] Projection Matrix
        - [x] Render Cube 
    - [ ] Camera 
    - [ ] Textures 
    - [ ] Logger 
    - [x] Window
    - [x] Shaders 
    - [x] Render submission 
    - [x] Utils 
- [x] Dynamic List appending (Keep reviewing this though)
- [x] Test by rendering a triangle 
- [ ] Have some a GUI window that will have a menu to select some settings before starting the renderer

## Bugs
- Whenever I kill the process with an alt c (killactive) I get segfaults, but
whenever I kill the process with an ctrl-c, its all good... make sure to check into this

NOTE: I want to get a basic system down first, and see from there what will need to be refactored
and if I need to change/add components.

The basic system should have an efficient way in setting up a program that will allow me to setup an object and let the renderer handle everything else 
behind the scenes with a simple call:

## Working On Now

- Understanding MVP and implementing it to test render a cube
- Implementing camera 
- Understanding the coordinate system and the different spaces such as local space, world space, view space , clip space, and screen space

## Recap 8/24/2025
 - I was initializing the renderer first instead of the window context, which was running OpenGL functions before initializing and loading OGL's function
pointers

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

## Books To Read

learnopengl.com 

* Will need to find reccomendations on possible graphics books
* ECS?

## Thoughts

what's a better way to check for error status codes?

I don't want to populate my codebase with a bunch of 

int status;
if(( status = some_func() ) == STATUS_ERROR)
    return ERROR?

Or I can have an enum of errors that will return a error message code depending
on the type of error

For example, if glfw doesn't initialize, then INIT_GLFW_ERR will be returned
and internally, grab the message that is related to this error and print this
to the screen?

enum status_error_e {
    INIT_GLFW_ERR
    INIT_XEZA_CTX
};



TODO Today:

- Understand the basics of vector math and matrices
for converting 2D to 3D
- Implement a small math.h to apply what I just learned

