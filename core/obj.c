#include <stdint.h>
#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "../vendor/tinyobj_loader_c.h" 
#include "obj.h"

//TODO: Find the fixed size for VBO
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#define TRI_VERTEX_COUNT 3

// Processing 1/1/1 instead of the whole vertex
typedef struct {
   int v;
   int vt;
   int vn;
} face_t;

static bool vertex_exists(list_t* list) {
    return true;
}

//tinyobj_vertex_index_t idx1 = attributes.faces[face_offset + 3 * 0 + 1];
static void _print_face_index(tinyobj_vertex_index_t* self) {
    if(self->v_idx >= 0)  printf("%d", self->v_idx);
    if(self->vt_idx >= 0) printf("%d", self->vt_idx); if(self->vn_idx >= 0) printf("%d", self->vn_idx); printf("\n");
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

static void print_vertex(tinyobj_attrib_t* attrib) {
    printf("Position Vertices\n");        
    for(int i = 0; i < attrib->num_vertices * 3; ++i) {
        printf("%f\n", attrib->vertices[i]);
    }
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
// @zai
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
        return 1;
    }
    
    ht_t* table = ht_create();
    if(table == NULL) return 1;

    printf("No. of shapes =  %d\n", (int)num_shapes);
    printf("No. of materials  = %d\n", (int)num_materials);
    printf("No. of vertices  = %d\n", attributes.num_vertices);
    printf("No. of texture coords  = %d\n", attributes.num_texcoords);
    printf("No. of normals  = %d\n", attributes.num_normals);
    printf("No. of faces: %d\n", attributes.num_faces);
    printf("No. of triangles: %d\n", attributes.num_face_num_verts);

    //print_vertex(&attributes);
      
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
    uint32_t value = 0;
    uint32_t count  = 0;
    list_t* vb = list_create(OBJ_VERTEX_BUFFER);
    list_t* ib = list_create(INDEX_BUFFER);
    
    for(int i = 0; i < attributes.num_face_num_verts; ++i) {
        /*
         * NOTE: The above idx will return the index - 1 since the tinyobj 
         * library makes our face indices 0 based to work easier with C.
         * */
        tinyobj_vertex_index_t idx0 = attributes.faces[face_offset + 3 * 0 + 0]; // t1
        tinyobj_vertex_index_t idx1 = attributes.faces[face_offset + 3 * 0 + 1]; // t2
        tinyobj_vertex_index_t idx2 = attributes.faces[face_offset + 3 * 0 + 2]; // t3

        //TEST: Print the vertices using the v_idx.
        #if 0
        printf("Triangle #%d\n", i);
        _print_face_index(&idx0);
        _print_face_index(&idx1);
        _print_face_index(&idx2);
        #endif

        // ======================================================= //
        obj_vertex_t vertex[3] = {0};
        // x y z = 0
        // x y z = 1
        // x y z = 2
        face_t face_indices[3] = {0};
        unsigned int pos_vertices[3] = {idx0.v_idx, idx1.v_idx, idx2.v_idx};
        for(int i = 0; i < 3; ++i) {
            unsigned int face = pos_vertices[i];
            float x = attributes.vertices[face * 3 + 0];
            float y = attributes.vertices[face * 3 + 1];
            float z = attributes.vertices[face * 3 + 2];
            vertex[i].v = (vec3_t){x,y,z};
            face_indices[i].v = face;
        }

        if(attributes.num_normals > 0) {
            unsigned int normal_vertices[3] = {idx0.vn_idx, idx1.vn_idx, idx2.vn_idx};
            for(int i = 0; i < 3; ++i) {
                unsigned int face = normal_vertices[i];
                float x = attributes.normals[face * 3 + 0];
                float y = attributes.normals[face * 3 + 1];
                float z = attributes.normals[face * 3 + 2];
                vertex[i].vn = (vec3_t){x,y,z};
                face_indices[i].vn = face;
            }
        }

        if(attributes.num_texcoords > 0) {
            unsigned int texcoords_vertices[3] = {idx0.vt_idx, idx1.vt_idx, idx2.vt_idx};
            for(int i = 0; i < 3; ++i) {
                unsigned int face = texcoords_vertices[i];
                float x = attributes.texcoords[face * 2 + 0];
                float y = attributes.texcoords[face * 2 + 1];
                vertex[i].vt = (vec2_t){x,y};
                face_indices[i].vt = face;
            }
        }
    
        // INFO:
        // Hash table is created (kind of scuffed tho)
        // Let's insert items into our ht only if the item isn't found
        // once the hash table is finished being populated,
        // then we create our vbo and index buffer
        // Must append unique vertices

        for(int i = 0; i < TRI_VERTEX_COUNT; ++i) {
            face_t face = face_indices[i];
            Key key;
            key.v = face.v;
            key.vt = face.vt;
            key.vn = face.vn;
            printf("Face being processed: {%u/%u/%u}\n", key.v, key.vt, key.vn);
            if(!ht_find(table, key)) {
                ht_insert(table, (entry_t){key,value});
                value += 1;
            }

            count++;
            //obj_vertex_t v = vertex[i];
        }
       
        face_offset += 3;
    }

    ht_print(table);
    //printf("Hash Table Size: %zu\n", table->size);
    
    //object->vertex_buff = vb;
    //list_print(object->vertex_buff);
    //object->index_buff = ib;
    //list_print(object->index_buff);
    ht_free(table);
    tinyobj_attrib_free(&attributes);
    tinyobj_shapes_free(shapes, num_shapes);
    tinyobj_materials_free(materials, num_materials);
    return TINYOBJ_SUCCESS;
}



//TODO: Add an index buffer when parsing obj file for better optimization.
//
// Use a hashmap to store unique vertices when creating my vbo

// Can I create my index buffer as Im making my VBO since it'll only store
// unique vertices, therfore storing the current index?
