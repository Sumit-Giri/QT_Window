# Project: QT_Window
 
## Overview
 
This project deals with the triangulation of data obtained from STL files. The key components of the project are as follows:
 
- **Source Files**: 
  - `point3D.cpp`
  - `triangle.cpp`
  - `triangulation.cpp`
  - `reader.cpp`
- **Header Files**: 
  - Located in the `headers` folder, containing declarations for the source files.
- **Functionality**:
  - `reader.cpp` reads data from STL files, extracting points and storing them in triangulation vectors.
  - Triangulation algorithms are implemented in `triangulation.cpp`.
  - `main.cpp` utilizes the triangulated data, creating vertices arrays for OpenGL rendering.
-  **Input**:
   - When prompted, provide the path to the input STL file.
 
-  **Visualization**:
   - The program will visualize the triangulated points using OpenGL.
 
## Output ScreenShot-
1. Sphere
  
 ![Screenshot (6)](https://github.com/Sumit-Giri/QT_Window/assets/158052390/35000d79-e860-4e0b-9eaf-77c31f7ca871)

2. Cube
  ![Screenshot (7)](https://github.com/Sumit-Giri/QT_Window/assets/158052390/cdf2b3d6-ec86-4417-9d15-1c9c433982ac)

