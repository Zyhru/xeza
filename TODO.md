## TODO

- [ ] Build system
- [ ] Core system 
    - [ ] Window
    - [x] Shaders 
    - [x] Render submission 
    - [ ] Textures 
    - [ ] Camera 
    - [ ] Logger 
    - [x] Utils 
- [ ] Dynamic List appending 
- [ ] Test by rendering a triangle 
- [ ] Parse OBJ models 

NOTE: I want to get a basic system down first, and see from there what will need to be refactored
and if I need to change/add components.

The basic system should have an efficient way in setting up a program that will allow me to setup an object and let the renderer handle everything else 
behind the scenes with a simple call:

pseudo code:

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
