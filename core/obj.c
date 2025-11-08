#include "buffer.h"
#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "../vendor/tinyobj_loader_c.h" 
#include "obj.h"

#include <stdint.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "hash_table.h"

#define TRI_VERTEX_COUNT 3

// Processing 1/1/1 instead of the whole vertex
typedef struct {
   int v;
   int vt;
   int vn;
} face_t;
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

    if (filename == NULL) {
        fprintf(stderr, "null filename\n");
        (*data) = NULL;
        (*len) = 0;
        return;
    }

    size_t data_len = 0;

    *data = _mmap_file(&data_len, filename);
    (*len) = data_len;
}

int obj_load(model_t* model, const char* obj_file) {
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

    // TODO: Parse each mesh to create a model
    if(num_shapes > 0) {
        ht_t* table = ht_create();
        if(table == NULL) {
            fprintf(stderr, "Failed to create Hash Table\n");
            return 1;
        }
        model->num_of_meshes = num_shapes;
        model->meshes = malloc(sizeof(mesh_t) * model->num_of_meshes);
        if(model->meshes == NULL) {
            fprintf(stderr, "Failed to allocate memory for model\n");
            return 1;
        }
        
        printf("No. of meshes {%zu}\n", model->num_of_meshes);

        for(size_t s = 0; s < num_shapes; ++s) {
            tinyobj_shape_t shape = shapes[s];
            size_t start = shape.face_offset;
            size_t end = shape.face_offset + shape.length;
           
            //strcpy(model->meshes[s].name, shape.name);
            printf("Mesh Name = %s\n", shape.name);
            printf("Mesh Face Offset = %zu\n", start);
            printf("Mesh Length = %zu\n", end);

            list_t* vb = list_create(OBJ_VERTEX_BUFFER);
            if(vb == NULL) {
                fprintf(stderr, "Failed to create Vertex Buffer\n");
                return 1;
            }
           
            list_t* ib = list_create(INDEX_BUFFER);
            if(ib == NULL) {
                fprintf(stderr, "Failed to create Index Buffer\n");
                return 1;
            }

            unsigned int value = 0;
            
            for(size_t i = start; i < end; ++i) {
                tinyobj_vertex_index_t idx0 = attributes.faces[i * 3 + 0]; // f0
                tinyobj_vertex_index_t idx1 = attributes.faces[i * 3 + 1]; // f1
                tinyobj_vertex_index_t idx2 = attributes.faces[i * 3 + 2]; // f2

                obj_vertex_t vertex[3] = {0};
                face_t faces[3] = {0};
                
                // parse each face within the triangle
                for(int v = 0; v < 3; ++v) {
                    unsigned int pos_v[3] = {
                        idx0.v_idx,
                        idx1.v_idx,
                        idx2.v_idx,
                    };

                    vec3_t v_face = {
                        .x = attributes.vertices[pos_v[v] * 3 + 0],
                        .y = attributes.vertices[pos_v[v] * 3 + 1],
                        .z = attributes.vertices[pos_v[v] * 3 + 2],
                    };

                    vertex[v].v = v_face;
                    faces[v].v = pos_v[v];
                }

                if(attributes.num_texcoords > 0) {
                    unsigned int texcoords_v[3] = {
                        idx0.vt_idx,
                        idx1.vt_idx,
                        idx2.vt_idx,
                    };

                    for(int vt = 0; vt < 3; ++vt) {
                        vec2_t vt_face = {
                            .x = attributes.texcoords[texcoords_v[vt] * 3 + 0],
                            .y = attributes.texcoords[texcoords_v[vt] * 3 + 1],
                        };
                        
                        vertex[vt].vt = vt_face;
                        faces[vt].vt = texcoords_v[vt];
                    }
                }
                
                if(attributes.num_normals > 0) {
                    unsigned int normals_v[3] = {
                        idx0.vn_idx,
                        idx1.vn_idx,
                        idx2.vn_idx,
                    };

                    for(int vn = 0; vn < 3; ++vn) {
                        vec3_t vn_face = {
                            .x = attributes.normals[normals_v[vn] * 3 + 0],
                            .y = attributes.normals[normals_v[vn] * 3 + 1],
                            .z = attributes.normals[normals_v[vn] * 3 + 2],
                        };
                        
                        vertex[vn].vn = vn_face;
                        faces[vn].vn = normals_v[vn];
                    }
                }

                for(int x = 0; x < 3; ++x) {
                    face_t face = faces[x];
                    vertex_key_t key = {
                        .v  = face.v, 
                        .vt = face.vt, 
                        .vn = face.vn
                    };

                    entry_t* e_ptr = ht_find(table, key);
                    if(e_ptr == NULL) {
                        ht_insert(table, (entry_t){key,value});
                        list_append(ib, (unsigned int *)&value);
                        list_append(vb, (obj_vertex_t*)&vertex[x]);
                        value += 1;
                    } else {
                        list_append(ib, (unsigned int *)&e_ptr->value);
                    }
                }

                start += 3;
            }
            
            model->meshes[s].vertex_buff = vb;
            model->meshes[s].index_buff = ib;
        }
        
        ht_free(table);
    }
   
    tinyobj_attrib_free(&attributes);
    tinyobj_shapes_free(shapes, num_shapes);
    tinyobj_materials_free(materials, num_materials);
    return TINYOBJ_SUCCESS;
}
