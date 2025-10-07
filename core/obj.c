#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "../vendor/tinyobj_loader_c.h"

#include "obj.h"
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

//tinyobj_vertex_index_t idx1 = attributes.faces[face_offset + 3 * 0 + 1];
static void _print_face_index(tinyobj_vertex_index_t* self) {
    if(self->v_idx >= 0)  printf("%d", self->v_idx);
    if(self->vt_idx >= 0) printf("%d", self->vt_idx);
    if(self->vn_idx >= 0) printf("%d", self->vn_idx);
    printf("\n");
}

static void _print_vertices(tinyobj_attrib_t* attrib) {
    int total = attrib->num_vertices * 3;
    int c = 0;
    for(int i = 0; i < total; i += 3) {
        printf("Vertex %d : {%f, %f, %f}\n", c, attrib->vertices[i], attrib->vertices[i+1], attrib->vertices[i+2]);
        c++;
    }
    
    printf("\n");
}

static void _print_texcoords(tinyobj_attrib_t* attrib) {
    int total = attrib->num_texcoords * 2;
    int c = 0;
    for(int i = 0; i < total; i += 2) {
        printf("TexCoords %d : {%f, %f}\n", c, attrib->texcoords[i], attrib->texcoords[i+1]);
        c++;
    }
    
    printf("\n");
}

static void _print_normals(tinyobj_attrib_t* attrib) {
    int total = attrib->num_normals * 3;
    int c = 0;
    for(int i = 0; i < total; i += 3) {
        printf("Normal %d : {%f, %f, %f}\n", c, attrib->normals[i], attrib->normals[i+1], attrib->normals[i+2]);
        c++;
    }
    
    printf("\n");
}

static char* _mmap_file(size_t* len, const char* filename) {
  struct stat sb;
  char* p;
  int fd;

  fd = open(filename, O_RDONLY);
  if (fd == -1) {
    perror("open");
    return NULL;
  }

  if (fstat(fd, &sb) == -1) {
    perror("fstat");
    return NULL;
  }

  if (!S_ISREG(sb.st_mode)) {
    fprintf(stderr, "%s is not a file\n", filename);
    return NULL;
  }

  p = (char*)mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

  if (p == MAP_FAILED) {
    perror("mmap");
    return NULL;
  }

  if (close(fd) == -1) {
    perror("close");
    return NULL;
  }

  (*len) = sb.st_size;

  return p;
}

static void get_file_data(void* ctx, const char* filename, const int is_mtl,
                          const char* obj_filename, char** data, size_t* len) {
    (void)ctx;
    (void)obj_filename;
    (void)is_mtl;

    if (!filename) {
        fprintf(stderr, "null filename\n");
        (*data) = NULL;
        (*len) = 0;
        return;
    }

    size_t data_len = 0;

    *data = _mmap_file(&data_len, filename);
    (*len) = data_len;
}

//TODO: Parse OBJ
// Think of extracting raw obj data for each shape within the object file
// e.g if theres an obj model with multiple 'o' then create the model based on the amount of meshes
// INFO: Still use tinyobj-loader-c and make two seperate functions to parse for triangualting and 
// non-trianuglation
int obj_load(gl_t* object, const char* obj_file) {
    tinyobj_attrib_t attributes;
    tinyobj_material_t* materials = NULL;
    tinyobj_shape_t* shapes = NULL;
    size_t num_shapes;
    size_t num_materials;
    unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;

    int ret = tinyobj_parse_obj(&attributes, &shapes, &num_shapes, &materials, &num_materials, obj_file, get_file_data, NULL, flags);
    if(ret != TINYOBJ_SUCCESS) {
        fprintf(stderr, "Failed to parse obj file: %s\n", obj_file);
    }

    printf("No. of shapes =  %d\n", (int)num_shapes);
    printf("No. of materials  = %d\n", (int)num_materials);
    printf("No. of vertices  = %d\n", attributes.num_vertices);
    printf("No. of texture coords  = %d\n", attributes.num_texcoords);
    printf("No. of normals  = %d\n", attributes.num_normals);
    printf("No. of faces: %d\n", attributes.num_faces);
    printf("No. of triangles: %d\n", attributes.num_face_num_verts);
      
    #if 0
    _print_vertices(&attributes);
    _print_texcoords(&attributes);
    _print_normals(&attributes);
    for(int i = 0; i < attributes.num_face_num_verts; ++i) {
        {0 -> {v_idx, vt_idx, vn_idx}};
    }
    if(num_shapes > 0) {
        for(size_t i = 0; i < shapes->length; ++i) {
            printf("%d : Shape Name: %s\n", (int)i, shapes[i].name);
        }
    }
    #endif
    

    size_t face_offset = 0;
    list_t* vb = list_create(OBJ_VERTEX_BUFFER);
    //list_t* ib = list_create(INDEX_BUFFER);

    for(int i = 0; i < attributes.num_face_num_verts; ++i) {
        
        // of each triangle
        // example:
        // 1 2 3 4
        // triangle 1 = 1 2 3
        // triangle 2 = 1 3 4

        /* Represents the index of each face. e.g f 1 2 3 4
         *
         * The two trianglest that are made are now:
         * idx0 idx1  idx2
         * 1     2     3   
         * idx0 idx1  idx2
         * 1     3      4
         *
         *
         * NOTE: The above idx will return the index - 1 since the tinyobj 
         * library makes our face indices 0 based to work easier with C.
         * */
        tinyobj_vertex_index_t idx0 = attributes.faces[face_offset + 3 * 0 + 0]; // t1
        tinyobj_vertex_index_t idx1 = attributes.faces[face_offset + 3 * 0 + 1]; // t2
        tinyobj_vertex_index_t idx2 = attributes.faces[face_offset + 3 * 0 + 2]; // t3

        //TEST: Print the vertices using the v_idx.
        #if 1
        printf("Triangle #%d\n", i);
        _print_face_index(&idx0);
        _print_face_index(&idx1);
        _print_face_index(&idx2);
        #endif

        // ======================================================= //
        /* Triangle */
        // v0
        float x0 = attributes.vertices[idx0.v_idx * 3 + 0]; // x
        float y0 = attributes.vertices[idx0.v_idx * 3 + 1]; // y 
        float z0 = attributes.vertices[idx0.v_idx * 3 + 2]; // z

        // v1
        float x1 = attributes.vertices[idx1.v_idx * 3 + 0]; // x 
        float y1 = attributes.vertices[idx1.v_idx * 3 + 1]; // y
        float z1 = attributes.vertices[idx1.v_idx * 3 + 2]; // z
      
        // v2
        float x2 = attributes.vertices[idx2.v_idx * 3 + 0]; // x
        float y2 = attributes.vertices[idx2.v_idx * 3 + 1]; // y
        float z2 = attributes.vertices[idx2.v_idx * 3 + 2]; // z
        // ======================================================= //
      
        obj_vertex_t vertex[3] = {0};
        
        // v
        vertex[0].v = (vec3_t){x0, y0, z0}; // 0 {x,y,z}
        vertex[1].v = (vec3_t){x1, y1, z1}; // 0 {x,y,z}
        vertex[2].v = (vec3_t){x2, y2, z2}; // 0 {x,y,z}
        
        for(int i = 0; i < 3; ++i) {
            list_append(vb, (obj_vertex_t *)&vertex[i]);
        }

        //TODO: Parse vt
        

        //TODO: Parse vn
       
        //TODO: Construct Index Buffer
        #if 0
        list_append(ib, (unsigned int *)&idx0.v_idx);
        list_append(ib, (unsigned int *)&idx1.v_idx);
        list_append(ib, (unsigned int *)&idx2.v_idx);
        #endif

        // v0 v1 v2
        // 1  2 3 ->
       
        // v0 v1 v2
        // 1  3  4
    
        //TODO: Create vb by using the the face index to grab the actual v, vt, vn
        // tinyobj-loader-c already made the indices 0-based.
        /*
        0 1 2 0
        x x x
        3 4 5 1
        x x x
        6 7 8 2
        x x x
        9 10 11 3
        x x  x 
       
        0 * 3 + 0 = 0
        0 * 3 + 1 = 1
        0 * 3 + 2 = 2
        
        1 * 3 + 0 = 3
        1 * 3 + 1 = 4
        1 * 3 + 2 = 5

        [v_idx * 3 + 0];
        [v_idx * 3 + 1];
        [v_idx * 3 + 2];
        */
        face_offset += 3;
    }
    
    object->vertex_buff = vb;
    list_print(object->vertex_buff);
    //object->index_buff = ib;
    //list_print(object->index_buff);

    tinyobj_attrib_free(&attributes);
    tinyobj_shapes_free(shapes, num_shapes);
    tinyobj_materials_free(materials, num_materials);
    return TINYOBJ_SUCCESS;
}

//TODO: Add an index buffer when parsing obj file for better optimization.
