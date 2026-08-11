# 3D Game Engine

A custom 3D game engine pipeline written from scratch in C++ using OpenGL.

## Current Engine Features

*   **Renderer:** Handles the core OpenGL drawing loop, state management, and frame initialization, along with rendering all objects in the scene.
*   **Shaders:** Loads, compiles, and links custom Vertex and Fragment shader source files.
*   **Textures**: Handles 8-bit PNG and JPEG image loading.
*   **Materials**: Contains visual data about an object, like albedo, roughness, etc.
*   **Transform Engine:** Computes 3D coordinate transformations using translation, rotation, and scale parameters.
*   **Lighting:** Implements a single Directional Light source for real-time  illumination. (Later, Point lights and attentuation will be added)
*   **Camera System:** Manages the view matrix calculations for runtime scene navigation.
*   **User Interface:** Uses Dear ImGui to display real-time variables and custom menus.
*   **Serialization:** Saves and loads runtime worlds created inside the engine.
*   **Logging:** Runtime logs available for Success, Warning, Fatal, and Info types.
*   **Transform Gizmos:** Runtime Transformation Gizmos available for all objects.
*   **Post Processing:** Current engine design allows all kinds of post processing like bloom, grayscale, etc.
*   **PBR Lighting:** Physically based rendering system for higher realism than phong shading.
*   **Texture tiling**: Repeatable textures for large ground / wall textures without scaling minute details
      

<img width="2560" height="1440" alt="image" src="https://github.com/user-attachments/assets/b2e5a7c1-a078-4a76-8382-0e6871bf84a4" />
