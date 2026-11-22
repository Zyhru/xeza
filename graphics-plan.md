# Graphics Plan

Goal: get hired as a graphics engineer at a game studio.

Path: understand the camera, light things, make it look good, move to Vulkan, build a portfolio.

The excitement you feel right now will fade in a few weeks. That's normal, and this plan is built for those weeks: small steps, no dates, no restarts.


## The plan on one page

| Phase | What you build | Rough time |
|---|---|---|
| 1. Camera | Your own math library and camera in xeza. No cglm, no copying. | 6 to 8 weeks |
| 2. Light | Textures, lighting, and a few shaders just for fun | 4 to 6 weeks |
| 3. Look good | Shadows, normal maps, HDR, post-processing, a debug UI, "N64 mode" | 6 to 8 weeks |
| 4. Vulkan | A new renderer in C and Vulkan that catches up with xeza | 3 to 4 months |
| 5. Portfolio | Two or three advanced techniques, write-ups, C++, applying | ongoing |

The times assume about 8 hours a week, so the whole thing is roughly a year. They are not deadlines. The order matters, the speed doesn't.


## Rules

1. Do the next unchecked box. There are no dates on purpose: missing a day doesn't put you behind.
2. One project. Phases 1 to 3 all happen in xeza. Vulkan is the only new project, and it starts when Phase 3 is done.
3. Write the code yourself. Read a tutorial for the idea, close the tab, then write it. Use AI to explain things, give hints and review your code, not to write it.
4. End every session by writing the next tiny step at the top of `TODO.md`. Starting the next session should take 30 seconds.
5. Stuck on the same thing for two sessions? Ask for help. Don't restart.
6. Finish every phase with screenshots and a short write-up. Those become your portfolio.


## Your week

Built around a full-time job. Change the times, keep the shape.

| Day | What | Time |
|---|---|---|
| Mon to Thu | 15 min of book or video, then 30 to 45 min on the next box | about 1 hour |
| Fri | Rest, or play a game with "graphics eyes" (below) | optional |
| Sat | Long session for the bigger boxes | 2 to 3 hours |
| Sun | Write a devlog entry in `TODO.md`, pick next week's boxes | 20 min |

Bad day? The minimum is 15 minutes: one video, one book section, or one tiny fix. A skipped day is fine. Just don't let it turn into a skipped month.

Graphics eyes: screenshot a scene you love (Ocarina of Time counts) and write down three guesses about how it was rendered. Fog? Baked lighting? Flat sprites? Later, check your guesses against real frame breakdowns.


## After a break

Breaks will happen. When you come back:

1. Build and run xeza. Fix whatever broke.
2. Read your last devlog entry.
3. Do the smallest unchecked box.

Don't reread everything, don't reorganize, and don't start over.


## Phase 1: Break the camera wall

**Goal:** your own math library and camera, written from scratch. When you're done, cglm is gone from xeza and you can explain every line of the camera.

**Main book:** *Foundations of Game Engine Development, Volume 1: Mathematics* (FGED1), the one you own. It uses the same matrix conventions as OpenGL and your code (column vectors), so what you read matches what you type.

**Second book:** FGED1 doesn't cover projection, spherical coordinates, Euler angles or lighting. For those, this plan uses *3D Math Primer for Graphics and Game Development* ("the Primer", free online, see Links).

**Videos:** 3Blue1Brown, *Essence of Linear Algebra*. FGED1 is short and dense, so watch the matching video first to get the picture.

How to use FGED1: write your own C version of each function before you look at the book's code. Do a few of the exercises at the end of each chapter; the solutions guide is free on the book's website. Skip chapter 4 (Grassmann and geometric algebra) for now. It's optional, and you can come back to it after Phase 3.

One warning about the Primer: it uses row vectors and a left-handed coordinate system, where +z points forward. Its matrices are your matrices flipped along the diagonal (transposed), and some z signs flip. The ideas are the same, and converting them is good practice.

### Step 0: Set up

- [ ] Commit `core/texture.h`. `gl_core.h` includes it, but it was never added to git, so xeza doesn't build from a fresh clone.
- [x] Install RenderDoc. Capture a frame of xeza and find your `mvp` uniform and the vertex shader output in the Mesh Viewer.
- [x] Add a `make test` target and an empty `tests/math_test.c`. This is where your math gets checked against cglm.

### Step 1: Vectors

FGED1 sections 1.1, 1.2, 1.5 and 1.6. 3Blue1Brown: "Vectors", "Linear combinations, span, and basis vectors", "Dot products and duality", "Cross products".

- [x] Rename `core/math.h` to `core/xmath.h` so it can't be confused with the standard `<math.h>`. Update the includes.
- [x] Write `vec3_add`, `vec3_sub`, `vec3_scale`, `vec3_dot`, `vec3_length`, `vec3_normalize` and `vec3_cross` for your `vec3_t`.
- [ ] Test each one against cglm in `tests/math_test.c`. Compare with a small tolerance like 1e-5.
- [x] Build a debug line drawer: `debug_line(from, to, color)` collects lines during the frame and draws them all at once with `GL_LINES`. Every visual test from here on uses it.
- [ ] Visual test: draw the world axes at the origin. X red, Y green, Z blue.
- [ ] Visual test: draw two vectors `a` and `b` and their cross product. Predict which way `a × b` points before you run it. Then swap them.
- [ ] Fix the `right` vector in `camera.c` (it points left) and fix the A and D signs to match.

### Step 2: Matrices

FGED1 sections 1.3, 1.4, 2.2, 2.4 and 2.6 (homogeneous coordinates are how translation fits into a 4×4 matrix). 3Blue1Brown: "Linear transformations and matrices", "Matrix multiplication as composition", "Three-dimensional linear transformations".

- [ ] Add `mat4_t`, stored column by column like OpenGL expects, so you can upload it with `GL_FALSE`.
- [ ] Write `mat4_identity`, `mat4_mul` and `mat4_mul_vec4`. Test them against cglm.
- [ ] Write `mat4_translate`, `mat4_scale` and `mat4_rotate_y` by writing down where each axis lands (the columns). Then write `mat4_rotate` for any axis.
- [ ] Replace cglm in `gl_apply_transform` with your functions. The model should spin exactly like before.
- [ ] Visual test: draw the model's own X, Y and Z axes using its model matrix. They should spin with it.
- [ ] Predict, then run: swap the translate and rotate calls. Write your guess down first.

### Step 3: Coordinate spaces

FGED1 section 2.1, and 2.6 again for points versus vectors. If FGED1 feels too terse here, the Primer's chapter 3 explains coordinate spaces more slowly. 3Blue1Brown: "Change of basis". Jordan Santell's article "Model View Projection".

- [ ] Add a separate `point3_t` type, like the book's `Point3D`. Point minus point gives a vector, point plus vector gives a point, and there's no function for point plus point. The compiler will now catch mix-ups like the old `center`/`dir` one. Your Step 6 camera will use it for its position.
- [ ] Pick one corner of the cube. On paper, work out where it is in world space, view space, clip space and NDC.
- [ ] Print the same corner from C in all five spaces (local through NDC) and compare with your paper.
- [ ] Find that vertex in RenderDoc's Mesh Viewer and match it against your clip space printout.

### Step 4: The view matrix

FGED1 sections 1.7 (matrix inversion) and 2.1.2 (orthogonal transforms). 3Blue1Brown: "Inverse matrices".

- [ ] Write `mat4_inverse_rigid` for matrices with only rotation and translation (like a camera). Transpose the 3×3 rotation part. The new translation is minus the transposed rotation times the old translation.
- [ ] Build the camera's own model matrix: its columns are right, up, -front and the camera's position. Invert it, and that's your view matrix. Check that it matches `glm_lookat` to about 1e-6.
- [ ] Write `mat4_look_at` directly, with right, up and -front as rows. Test it against both.
- [ ] Devlog entry: why is the view matrix the inverse of the camera's model matrix? Explain it in your own words.

### Step 5: Projection

Primer chapter 6 ("A Pinhole Camera", "Perspective Projection Matrices") and chapter 10 ("Viewing in 3D", "Coordinate Spaces"). After you've tried it yourself, check your work against Song Ho Ahn's projection matrix page, which uses OpenGL's conventions.

- [ ] On paper, use similar triangles to show that a point's screen x is proportional to x / -z.
- [ ] Write `mat4_perspective(fov_y, aspect, near, far)` starting from that idea, not from a formula. Test it against `glm_perspective`.
- [ ] Fix the stretching when the window is resized: read the size with `glfwGetFramebufferSize` every frame and compute the aspect ratio from it. Skip the update when the height is 0 (minimized window).
- [ ] Write `mat4_ortho` and switch between perspective and orthographic with a key. Shadow maps will need ortho in Phase 3.
- [ ] Predict, then run: `vec4(pos, 0.0)` instead of `vec4(pos, 1.0)` in the vertex shader. Then fov 10 against fov 90.

### Step 6: Rebuild the camera

Primer chapter 7 (spherical coordinates) and chapter 8 (Euler angles). FGED1 section 2.7 (quaternions) can wait. Freya Holmér's *Math for Game Devs* if you get stuck.

- [ ] Empty `camera.c`. With no tutorial open, write a free-fly camera from a position plus yaw and pitch. Draw the triangle on paper, turn yaw and pitch into a front vector with sin and cos, then get right and up with cross products.
- [ ] Mouse look: add mouse movement to `input_t` using `glfwGetCursorPos`, and hide the cursor with `GLFW_CURSOR_DISABLED`.
- [ ] Clamp pitch to ±89°. Then remove the clamp, look straight up, and explain what breaks.
- [ ] Fix the update order: move first, then build the matrices. Right now the view is one frame behind your input.
- [ ] Add an orbit camera on a key: yaw, pitch and distance around the model's center. Scroll to zoom with `glfwSetScrollCallback`.
- [ ] Remove cglm from xeza. Keep it only in `tests/`.

### Step 7: Boss fight

- [ ] Add a second "spectator" camera on a key. From it, draw the main camera's axes and its view frustum as debug lines. Hint: take the 8 corners of the NDC cube, transform them by the inverse of projection × view, and divide by w. You'll need a general `mat4_inverse` (FGED1 section 1.7.5).

**Done when:**

- xeza runs on your own math, and cglm only shows up in tests.
- The free-fly and orbit cameras work, and resizing the window doesn't stretch anything.
- The spectator camera shows the main camera's frustum.
- You can explain model, view and projection on a blank page without notes.

**Write-up:** "How a vertex gets to the screen", with screenshots.


## Phase 2: Light it up

**Goal:** the backpack model, textured and lit, with a light you can move. Plus a few shaders just for fun.

**Read:** Primer chapter 10 ("Surface Normals", "Texture Mapping", "The Standard Local Lighting Model", "Light Sources"). FGED1 section 3.2 for normal vectors and the normal matrix. LearnOpenGL's Lighting chapters: read, close the tab, then write.

- [ ] Shader hot reload: press R to recompile the shaders without restarting. Every shader task after this gets faster.
- [ ] Set up the UV and normal attributes in `gl_create_object`. Right now only the position is.
- [ ] Load each mesh's diffuse texture with `stb_image`. `obj.c` already stores the file name.
- [ ] Debug view: show normals as colors (`normal * 0.5 + 0.5`) and draw them as debug lines.
- [ ] Diffuse lighting from one directional light: `max(dot(N, L), 0.0)`.
- [ ] Add ambient light and Blinn-Phong specular. Use the backpack's specular map.
- [ ] Add a point light you can move with the keyboard, drawn as a small debug cross. Make it fade with distance (attenuation).
- [ ] Add a flashlight: a spotlight attached to your camera.
- [ ] Scale the model unevenly (2× on X) and watch the lighting break. Fix it with the normal matrix (the inverse transpose of the model matrix), and explain why it works.
- [ ] Fun: distance fog. Ocarina of Time used a lot of it.
- [ ] Fun: toon shading. Snap the diffuse value to 3 or 4 steps.
- [ ] Fun: recreate anything from Shadertoy or The Book of Shaders that catches your eye.

**Done when:** the backpack is textured and lit by a directional light, a movable point light and your flashlight, and hot reload works.

**Write-up:** lighting, with before and after screenshots.


## Phase 3: Make it look good

**Goal:** the techniques every modern renderer has, done in OpenGL where they're quick to try. Then xeza is finished.

**Read:** LearnOpenGL's "Framebuffers", "Gamma Correction", "Shadow Mapping", "Normal Mapping" and "HDR" chapters. Primer chapter 10 ("Bump Mapping", "Tangent Space").

- [ ] Debug UI with cimgui: light position and color, camera speed, fov, exposure.
- [ ] Render the scene to a texture (a framebuffer), then draw that texture to the screen through a post-processing shader. Start with grayscale to prove it works.
- [ ] Gamma correction: sRGB textures and an sRGB framebuffer.
- [ ] HDR: render to a floating point texture, then tone map it with an exposure slider. Reinhard first, then ACES.
- [ ] Normal mapping with the backpack's normal map. Tangent space is just one more coordinate space.
- [ ] Shadow mapping for the directional light. The light is a camera with an orthographic projection, and you've already built both.
- [ ] Fix shadow acne and peter-panning, then add PCF for soft edges. Screenshot each problem before you fix it.
- [ ] GPU timing: measure each pass in milliseconds with `GL_TIME_ELAPSED` queries.
- [ ] N64 mode, your Ocarina of Time tribute: render at 320×240 and scale it up without smoothing, add heavy fog, and imitate the N64's blurry 3-point texture filtering. (Wobbly vertices were a PS1 thing. The N64 was blurry, not wobbly.)
- [ ] Tag the repo `v1.0`. xeza is done.

**Done when:** shadows, normal maps, HDR with tone mapping, correct gamma, a UI to tweak it all, and N64 mode.

**Write-up:** shadow problems and their fixes, with screenshots. N64 mode side by side with the real game.


## Phase 4: Vulkan

**Goal:** a new renderer in C and Vulkan that catches up with xeza. This is the one planned new project.

**Why it suits you:** Vulkan makes you manage memory, synchronization and command buffers by hand. That's firmware work with a GPU attached, so your day job is good preparation.

**Guide:** vkguide.dev. It uses Vulkan 1.3 with dynamic rendering, and its author says it can be followed in C. Its code is C++, so you can't paste it. You'll have to understand each call to translate it, which is the point. Where vkguide uses vk-bootstrap (C++ only), write the setup yourself using the setup chapters of vulkan-tutorial.com, which use the plain C API.

These are milestones, not single sessions. Break each one into boxes when you get there.

- [ ] Window, instance, device and swapchain, clearing the screen to a color. Validation layers on, with zero warnings.
- [ ] A triangle.
- [ ] Vertex and index buffers, with memory managed by VMA (its API is plain C; you compile one C++ file).
- [ ] Your camera, using `xmath.h` from xeza. Uniform buffers and descriptor sets.
- [ ] Vulkan's clip space is different from OpenGL's: y points down, and depth goes from 0 to 1, not -1 to 1. Adjust your perspective matrix yourself. If Phase 1 worked, you'll know which numbers to change.
- [ ] Depth buffer, then textures.
- [ ] Load glTF scenes with cgltf, a single-header C library. Try the Sponza scene.
- [ ] Port your lighting and shadows from xeza.
- [ ] cimgui with its Vulkan backend.

**Done when:** the Vulkan renderer matches xeza (camera, textures, lighting, shadows, UI) and the validation layers stay silent.

**Write-up:** what Vulkan made you understand that OpenGL hid.


## Phase 5: Portfolio and getting hired

**Goal:** depth in a few techniques, proof that you can explain them, and the skills interviews check.

Pick two or three of these and do them well. For each, write up what it is, why it works, what goes wrong, and what it costs in milliseconds.

- PBR (Cook-Torrance) with image-based lighting. The backpack has roughness and AO maps.
- Cascaded shadow maps.
- Bloom.
- SSAO in a compute shader.
- GPU frustum culling in a compute shader.

Alongside them:

- [ ] Learn C++. Studios write their engines in C++, and the interviews are in C++. You don't need it to learn graphics, but you need it to get hired. Read *A Tour of C++* (it's short), then write one small project in it. Redoing one of the techniques above works.
- [ ] Read Fabian Giesen's *A Trip Through the Graphics Pipeline*. It explains what the GPU actually does with your draw calls.
- [ ] Get *Real-Time Rendering* (4th edition) and use it as a reference, not a cover-to-cover read.
- [ ] Read Adrian Courrèges' game frame breakdowns and compare them with your "graphics eyes" guesses.
- [ ] Portfolio: for each project, a GitHub README with screenshots and GIFs, plus your write-ups and a 1 to 2 minute video.
- [ ] Apply. Search for "graphics programmer", "rendering engineer" and "engine programmer". Junior graphics jobs are rare, so engine and tools jobs are good ways in, and you can move to rendering from inside. Your firmware background is a selling point: memory, synchronization and performance are what rendering teams care about.

If Nintendo is the dream: besides Kyoto, they have studios like Retro Studios (Austin), Next Level Games (Vancouver) and NERD (Paris).


## Links

Math

- FGED1 website (code listings, free solutions guide, errata): https://foundationsofgameenginedev.com/
- 3D Math Primer for Graphics and Game Development (free): https://gamemath.com/book/
- 3Blue1Brown, Essence of Linear Algebra: https://www.youtube.com/playlist?list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab
- Freya Holmér, Math for Game Devs: https://www.youtube.com/playlist?list=PLImQaTpSAdsArRFFj8bIfqMk2X7Vlf3XF
- Jordan Santell, Model View Projection: https://jsantell.com/model-view-projection/
- Song Ho Ahn, OpenGL Projection Matrix: https://www.songho.ca/opengl/gl_projectionmatrix.html

OpenGL and shaders

- LearnOpenGL: https://learnopengl.com/
- RenderDoc: https://renderdoc.org/
- cimgui: https://github.com/cimgui/cimgui
- The Book of Shaders: https://thebookofshaders.com/
- Shadertoy: https://www.shadertoy.com/
- Inigo Quilez's articles: https://iquilezles.org/

Vulkan

- vkguide: https://vkguide.dev/
- vulkan-tutorial.com: https://vulkan-tutorial.com/
- VMA: https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator
- cgltf: https://github.com/jkuhlmann/cgltf

Industry

- A Trip Through the Graphics Pipeline: https://fgiesen.wordpress.com/2011/07/09/a-trip-through-the-graphics-pipeline-2011-index/
- Adrian Courrèges' frame breakdowns: https://www.adriancourreges.com/blog/
- Graphics Programming Discord: https://graphics-programming.org/
