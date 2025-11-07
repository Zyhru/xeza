#ifndef OBJ_H
#define OBJ_H

#include "buffer.h"
#include "gl_core.h"

int obj_load(model_t* object, const char* obj_file);
int obj_load_test(model_t* object, const char* obj_file);

#endif // OBJ_H
//
//

/*
//TODO:
- [ ] Extract v, vt, and vns to a list
- [ ] Grab the count of each vertex
- [ ] Triangulate no matter how many indices we have for the faces
- [ ] Parse .mtl files
- [ ] Read each mesh within the file

*/
