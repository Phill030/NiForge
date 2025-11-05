<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Geist:wght@100..900&display=swap" rel="stylesheet">

<div align="center">
  <h1>NiForge</h1>
  <p>A robust and efficient C++ library for parsing NetImmerse File (NIF) formats.</p>
</div>

# Overview

# Features

# Getting Started
## Prerequisites
- A C++ 20 compatible compiler (eg. MSVC, GCC, Clang).
- CMake 3.20 or later.

## Installation
To integrate NiForge into your project, you can use CMake's FetchContent to download and build it automatically.
```cmake
include(FetchContent)

FetchContent_Declare(
  niforge
  GIT_REPOSITORY httpss://github.com/phill030/NiForge.git
  GIT_TAG        main # Or a specific release tag
)

FetchContent_MakeAvailable(niforge)

# Link against NiForge
target_link_libraries(${PROJECT_NAME} PRIVATE niforge)
```


## Building

# Usage

# Contributing

# License

# Acknowledgments
