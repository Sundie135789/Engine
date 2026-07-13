# 3D Game Engine

A custom 3D game engine pipeline written from scratch in C++ using OpenGL.

## Current Engine Features

*   **Renderer:** Handles the core OpenGL drawing loop, state management, and frame initialization.
*   **Shaders:** Loads, compiles, and links custom Vertex and Fragment shader source files.
*   **Textures & Materials:** Handles 8-bit PNG and JPEG image loading and sets material attributes
*   **Transform Engine:** Computes 3D coordinate transformations using translation, rotation, and scale parameters.
*   **Lighting:** Implements a single Directional Light source for real-time vertex and fragment illumination. (Later, Point lights and attentuation will be added)
*   **Camera System:** Manages the view matrix calculations for runtime scene navigation.
*   **GameObjects & Meshes:** Combines 3D vertex position vectors, normal vectors, and UV texture coordinates to construct and track runtime objects.
*   **State Machine:** Implements an EngineState toggle to switch context between editing variables and running active gameplay.
*   **User Interface:** Uses Dear ImGui to display real-time variables, a component Inspector window, a scene Hierarchy list, and menu navigation bars.
*   **Serialization:** Saves and loads runtime scenes created inside the engine.

## Features In Progress

* Model Loading (fbx file format)
   
   <img width="2560" height="1440" alt="image" src="https://github.com/user-attachments/assets/81542bb3-9b28-4639-9620-b15c21ee02a1" />
