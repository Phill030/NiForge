<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Geist:wght@100..900&display=swap" rel="stylesheet">

<div align="center">
  <h1>NiForge</h1>
  <p>A robust and efficient C++ library for parsing NetImmerse File (NIF) formats.</p>
  <div>
    <img src="https://img.shields.io/badge/license-CC%20BY--NC--SA%204.0-lightgrey.svg?style=for-the-badge" alt="License">
    <a href="https://discord.gg/sMFgyNRDDM"><img src="https://img.shields.io/discord/940647911182729257?color=5865F2&label=Discord&logo=discord&logoColor=white&style=for-the-badge" alt="Discord"></a>
  </div>
</div>

---
## Table of Contents
- [Overview](#Overview)
- [Features](#Features)
- [Getting Started](#Getting-Started)
- [Usage](#Usage)
- [Contributing](#Contributing)
- [License](#License)

---

## Overview

---

## Features

---

## Getting Started
### Prerequisites
- A C++ 20 compatible compiler (eg. MSVC, GCC, Clang).
- CMake 3.20 or later.

### Installation
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

### Building

---

## Usage

---

## Contributing

---

## License
<p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><a property="dct:title" rel="cc:attributionURL" href="https://github.com/phill030/NiForge">NiForge</a> by <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://github.com/Phill030/">Phill030</a> is licensed under <a href="http://creativecommons.org/licenses/by-nc-sa/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">CC BY-NC-SA 4.0<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/nc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/sa.svg?ref=chooser-v1"></a></p>

## Acknowledgments
