## Backlog 
- [x] Create an option to render obj files and non-obj files
- [ ] Report each commit and explain what was fix/changed
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
        - [ ] Move object around with mouse
        - [ ] Look Around (Mouse) 
    - [ ] Textures 
    - [ ] Logger 
    - [x] Window
    - [x] Shaders 
    - [x] Render submission 
    - [x] Utils 
- [x] Dynamic List appending (Keep reviewing this though)
- [x] Build system

## 10/18/2025

- [ ] Figure out why I'm getting 25 vertices instead of 24.
Make steps of inserting clean by cleaning up the print 

psuedo-code:
    When inserting a key make sure to print out the key that is being inserted
    Find the key, if not found report that.
    Otherwise say we found the key

## 10/16/2025
- [ ] Implement regrow

When I'm regrowing the hash table 
we need to move the entries to another array by grabbing
it's current index and setting the entry to the index 
in the new arra


## 10/12/2025 (For later)
- [ ] Write ht_find function
- [ ] Write ht_print function
- [ ] Finally use index buffer

## 10/11/2025 (For later)
- [ ] Work on creating an index buffer 
    - [ ] Implement a hashmap
        - [x] create func 
        - [x] add func 
        - [x] hashing func 
        - [ ] printing out hashmap (iterator) func
        - [ ] find func (read more on this)
        - [ ] regrow (internal) func (read more on this)
        - [ ] test 

## 10/10/2025 
- [ ] Design on how to implement rotating objects
with mouse.  (*Rotate and drag*)

- [ ] Work on creating an index buffer 
    - [ ] Implement a hashmap
        - [ ] create func 
        - [ ] add func 
        - [ ] find func 
        - [ ] regrow (internal) func
- [ ] Write a texture system
- [ ] Study on Normals/Lighting

## 10/09/2025 
- [x] Clean up obj code for creating vbo
- [ ] Rotate objects with mouse
- [ ] Use an index buffer

## 10/07/2025 
- [x] Create VBO based on faces without an index buffer
- [ ] Use an index buffer to optimize the rendering

* NOTE: tinyobj-loader-c will give me the faces in 
triangulated way

example:

f 1 2 3 4

will be: 

1 2 3 -> 0
1 3 4 -> 1

Another example:

f 1/1/1 2/2/2 3/3/3 4/4/4
1/1/1 2/2/2 3/3/3
1/1/1 3/3/3 4/4/4

1. Based on the vertex index, create a OBJVertex (custom data structure)
and place into VBO.

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


## Today

Fix the the hash table
