# Architecture

## Goal

Render an object on screen. Primarily `.obj` models, with a PSX look.

## What it needs

- Window (GLFW)
- Drawing (OpenGL)
- Shaders
- Textures
- Camera

Everything else (UI, extra utilities) waits until this works.

## Modules

| Module | Job | Knows about OpenGL? |
|---|---|---|
| `app` | Owns the main loop. The only place that connects everything. | no |
| `window` | GLFW setup, GL function loading, poll events, swap buffers | yes |
| `input` | Key and mouse state | no |
| `camera` | Position, orientation, produces view and projection matrices | no |
| `renderer` | Takes a mesh, texture, and matrices, and draws. Owns shaders and the low-res PSX pass. | yes |
| `shader`, `texture` | GPU resources, used by the renderer | yes |
| `math` | vec2, vec3, mat4 | no |
| `util` | Logging, file reading | no |
| `loaders` | OBJ and image loading, file to CPU data | no |

## Dependency diagram

Arrows only point down. Nothing points back up.

```
                     +-----------------------+
                     |  app  (main loop)     |
                     +-----------------------+
                        |     |     |     |
           +------------+     |     |     +------------+
           v                  v     v                  v
      +--------+         +-------+ +--------+    +----------+
      | window |         | input | | camera |    | renderer |
      +--------+         +-------+ +--------+    +----------+
                                                     |     |
                                                     v     v
                                               +--------+ +---------+
                                               | shader | | texture |
                                               +--------+ +---------+

  app also calls the loaders directly (OBJ file -> Mesh).

  FOUNDATION  (any module may use these, none touch OpenGL)
  +------+  +------+  +------------+  +--------------+
  | math |  | util |  | OBJ loader |  | image loader |
  +------+  +------+  +------------+  +--------------+
```

## Data flow

Files become CPU data. CPU data becomes a GPU handle. Handles plus
matrices become pixels. Nothing flows backward.

### Startup (in order)

1. `window_create`
2. `renderer_create`
3. `camera_init`
4. `obj_load(path)` returns a `Mesh` (CPU data)
5. `renderer_upload(Mesh)` returns a `MeshHandle` (GPU data)
6. `texture_load(path)` returns a `TextureHandle`

### Every frame

1. `window_poll_events`
2. Update input state
3. `camera_update(dt)` from input
4. Get view and projection matrices from the camera
5. `renderer_draw(mesh, texture, matrices)`
   - bind the low-res target (320x240)
   - draw the meshes
   - blit up to the window with nearest filtering
6. `window_swap`

### Shutdown (reverse order)

Destroy handles, then renderer, then window.

## Decisions

- **The camera is not part of the renderer.** It is data and math, and the renderer takes matrices as input.
- **The main loop lives in `app.c`, as a plain `while` loop.** No callbacks for now. Every call is visible in one place. Revisit if a second backend or a web build ever needs it.
- **Loaders contain no OpenGL.** They only know about files and `Mesh` data.
- **`main.c` stays tiny:** parse args, create the app, run it, destroy it.
- **UI is out of scope** until the renderer works.

## Rules for myself

1. Every struct has a `create` and a `destroy`.
2. Every allocation has one named owner.
3. Dependencies point down only. If I want an arrow up, I pass the data in instead.
4. Each `.c` file includes what it uses. No hidden includes through big headers.
5. Check every `fopen`, `malloc`, and `realloc`.
6. Build with `-Wall -Wextra -fsanitize=address,undefined`.
7. Write the plain version first. Reach for function pointers or other patterns only when I notice copy-pasted code that differs in small ways.

## Ownership (fill in as I go)

| Struct | Created by | Destroyed by | Notes |
|---|---|---|---|
| `Mesh` | `obj_load` | `app` | CPU-side vertices |
| `MeshHandle` | `renderer_upload` | `renderer` | GPU-side |
| `Texture` | `texture_load` | `renderer` | |
| `Shader` | `renderer_create` | `renderer` | |
| `Camera` | `app` | `app` | no heap needed |

## Open questions

- Which UI library, if any, and when?
- How to handle multiple materials per mesh (later)?
- Flat normals when the OBJ has none: compute in the loader or the shader?
