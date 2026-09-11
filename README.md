<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Geist:wght@100..900&display=swap" rel="stylesheet">

<div align="center">
  <h1>NiForge</h1>
  <p>A robust and efficient C++ library for parsing NetImmerse / Gamebryo File (.nif) formats.</p>
  <div>
    <img src="https://img.shields.io/badge/license-CC%20BY--NC--SA%204.0-lightgrey.svg?style=for-the-badge" alt="License">
    <a href="https://discord.gg/sMFgyNRDDM"><img src="https://img.shields.io/discord/940647911182729257?color=5865F2&label=Discord&logo=discord&logoColor=white&style=for-the-badge" alt="Discord"></a>
  </div>
</div>

---
## Table of Contents
- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Integration Methods](#integration-methods)
  - [Option 1: CMake FetchContent (Recommended)](#option-1-cmake-fetchcontent-recommended)
  - [Option 2: Git Submodule or Subdirectory](#option-2-git-submodule-or-subdirectory)
  - [Option 3: Pre-built Binaries (Imported Target)](#option-3-pre-built-binaries-imported-target)
- [Usage Example](#usage-example)
- [Contributing](#contributing)
- [License](#license)

---

## Overview
**NiForge** is a modern C++ library designed for parsing and working with NetImmerse and Gamebryo `.nif` files (specifically targeted and tested with Gamebryo 20.6 / Wizard101 assets). It provides:

- Fast binary parsing directly from file paths or memory buffers.
- Structured access to NIF headers, block lists, strings, and node hierarchies.
- Type-safe block filtering (`getBlocksOfType<T>()`) and reference resolution (`Ref<T>`).
- Full support for `NiMesh`, `NiTriShapeData`, vertex streams (positions, normals, colors, UVs), materials, texturing, and transforms.

---

## Prerequisites

- **C++ Compiler**: A modern C++ compiler supporting at least **C++20** (MSVC 2019+, GCC 10+, or Clang 12+).
- **CMake**: Version **3.20** or later.

---
## Integration Methods
Depending on your workflow and project structure, you can integrate NiForge in three different ways:

### Option 1: CMake FetchContent (Recommended)

Requires no manual cloning or submodules. CMake downloads, configures, and builds NiForge automatically at configure time.

```cmake
cmake_minimum_required(VERSION 3.20)
project(MyProject)

# NiForge requires C++20 or newer
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    NiForge
    GIT_REPOSITORY https://github.com/phill030/NiForge.git
    GIT_TAG        master # Or specify a release tag / commit hash
)

FetchContent_MakeAvailable(NiForge)

# Define your application or library target
add_executable(MyProject src/main.cpp)

# Link against the NiForge target (automatically adds include directories)
target_link_libraries(MyProject PRIVATE NiForge)

# On Windows: NiForge builds as a shared library (DLL).
# Copy NiForge.dll next to your executable automatically after build:
if(WIN32)
    add_custom_command(TARGET MyProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:NiForge>
        $<TARGET_FILE_DIR:MyProject>
    )
endif()
```

---

### Option 2: Git Submodule or Subdirectory

If you prefer vendoring dependencies directly inside your repository (e.g. in `external/NiForge` or `third_party/NiForge`):

1. Add the submodule:
   ```bash
   git submodule add https://github.com/phill030/NiForge.git third_party/NiForge
   ```

2. Add it to your `CMakeLists.txt`:
   ```cmake
   cmake_minimum_required(VERSION 3.20)
   project(MyProject)

   set(CMAKE_CXX_STANDARD 20)
   set(CMAKE_CXX_STANDARD_REQUIRED ON)

   # Add NiForge subdirectory
   add_subdirectory(third_party/NiForge)

   add_executable(MyProject src/main.cpp)
   target_link_libraries(MyProject PRIVATE NiForge)

   # Copy DLL on Windows post-build
   if(WIN32)
       add_custom_command(TARGET MyProject POST_BUILD
           COMMAND ${CMAKE_COMMAND} -E copy_if_different
           $<TARGET_FILE:NiForge>
           $<TARGET_FILE_DIR:MyProject>
       )
   endif()
   ```

---

### Option 3: Pre-built Binaries (Imported Target)

If you have already built `NiForge.dll` and `NiForge.lib` and wish to link against them without compiling NiForge from source:

```cmake
cmake_minimum_required(VERSION 3.20)
project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define an imported shared library target
add_library(NiForge SHARED IMPORTED)

set_target_properties(NiForge PROPERTIES
    IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/NiForge.lib"
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/bin/NiForge.dll"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/NiForge"
)

add_executable(MyProject src/main.cpp)
target_link_libraries(MyProject PRIVATE NiForge)

# Copy NiForge.dll to the output directory
if(WIN32)
    add_custom_command(TARGET MyProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:NiForge>
        $<TARGET_FILE_DIR:MyProject>
    )
endif()
```

---
## Usage Example
```cpp
#include <Core/NiFile.hpp>
#include <Blocks/NiMesh.hpp>
#include <Blocks/NiNode.hpp>
#include <iostream>

int main() {
    try {
        // Load a NIF file from disk
        NiFile file("path/to/model.nif");

        std::cout << "Loaded NIF file successfully!\n";
        std::cout << "Total blocks: " << file.blocks.size() << "\n";

        // Query all root nodes in the hierarchy
        auto roots = file.getRootNodes();
        std::cout << "Root node count: " << roots.size() << "\n";

        // Query specific blocks by type
        auto meshes = file.getBlocksOfType<NiMesh>();
        for (NiMesh* mesh : meshes) {
            std::cout << "Found Mesh: " << mesh->name << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Failed to parse NIF file: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
```

---

## License
<p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><a property="dct:title" rel="cc:attributionURL" href="https://github.com/phill030/NiForge">NiForge</a> by <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://github.com/Phill030/">Phill030</a> is licensed under <a href="http://creativecommons.org/licenses/by-nc-sa/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">CC BY-NC-SA 4.0<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/nc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/sa.svg?ref=chooser-v1"></a></p>

## Acknowledgments
