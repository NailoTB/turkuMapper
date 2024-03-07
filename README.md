# Turku Archipelago Tile Renderer (Interview Pre-Task)

This project aims to create a tile renderer for the Turku Archipelago, providing seamless scrolling of the map, the ability to jump to specific positions, and add markers based on latitude and longitude coordinates. Coordinate transformations between WGS84 and ETRS89 are handled by Proj library.

## Necessary Dependencies

- C++ compiler
- cmake
- Qt6 (on Arch Linux, install qt6-base)
- proj (on Arch Linux, install proj)

## Project Structure

The codebase is primarily built around Qt subclasses. The structure is organized as follows:

- **src/**: Contains the source code files for Qt subclasses.
  - `main.cpp`: Entry point of the application.
  - `MapMainWindow.cpp`: Implementation of the main application window. Inherited from QtMainWindow
  - `MapToolBar.cpp`: The main toolbar containing latitude and longitude marker input functionality. Inherited from QtToolBar.
  - `MapBookmarks.cpp`: The secondary toolbar containing bookmarks. Inherited from QtToolBar.
  - `MapScene.cpp`: The main visual scene. Handles reading in the tiles and rendering them. Inherited from QtGraphicsScene.
  - `Transformations.cpp`: A namespace for transformation functions utilizing proj.

## How to Run

1. Clone Repository:
    ```bash
    git clone <repository-url>
    cd <repository-directory>
    ```

2. Build Project:
    ```bash
    cmake .
    cmake --build .
    ```

3. Run Application:
    ```bash
    ./turkuMapper
    ```

## Key Functionalities

- Seamless Scrolling: Navigate through the map seamlessly.
   
- Jump to Positions: Enter latitude and longitude coordinates to jump to specific locations on the map.

- Add Markers: Add markers to the map based on latitude and longitude coordinates.

- Adding Bookmarks (To Be Implemented): Future enhancement to allow users to add bookmarks for easy access to frequently visited locations.
