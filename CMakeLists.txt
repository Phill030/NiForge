cmake_minimum_required (VERSION 3.20)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("NiForge")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

set(HEADER_FILES
    "src/Defines.hpp"
    "src/Reader.hpp"
    "src/Core/NiVersion.hpp"
    "src/Core/NiHeader.hpp"
    "src/Core/NiFile.hpp"

    "src/Types/Color3.hpp"
    "src/Types/Color4.hpp"
    "src/Types/MatchGroup.hpp"
    "src/Types/MaterialData.hpp"
    "src/Types/Matrix.hpp"
    "src/Types/MipMap.hpp"
    "src/Types/Ref.hpp"
    "src/Types/ShaderTexDesc.hpp"
    "src/Types/TexCoord.hpp"
    "src/Types/TexDesc.hpp"
    "src/Types/Triangle.hpp"
    "src/Types/Vector3.hpp"
    "src/Types/Key.hpp"
    "src/Types/KeyGroup.hpp"

    "src/Blocks/AbstractAdditionalGeometryData.hpp"
    "src/Blocks/NiAvObject.hpp"
    "src/Blocks/NiBillboardNode.hpp"
    "src/Blocks/NiBound.hpp"
    "src/Blocks/NiDataStream.hpp"
    "src/Blocks/NiDynamicEffect.hpp"
    "src/Blocks/NiFloatInterpolator.hpp"
    "src/Blocks/NiGeometry.hpp"
    "src/Blocks/NiInterpolator.hpp"
    "src/Blocks/NiKeyBasedInterpolator.hpp"
    "src/Blocks/NiMesh.hpp"
    "src/Blocks/NiNode.hpp"
    "src/Blocks/NiObject.hpp"
    "src/Blocks/NiObjectNet.hpp"
    "src/Blocks/NiPalette.hpp"
    "src/Blocks/NiPixelFormat.hpp"
    "src/Blocks/NiSkinInstance.hpp"
    "src/Blocks/NiSourceTexture.hpp"
    "src/Blocks/NiTexture.hpp"
    "src/Blocks/NiTriBasedGeom.hpp"
    "src/Blocks/NiTriShape.hpp"

    "src/Blocks/Controller/NiFloatInterpController.hpp"
    "src/Blocks/Controller/NiInterpController.hpp"
    "src/Blocks/Controller/NiMorphWeightsController.hpp"
    "src/Blocks/Controller/NiSingleInterpController.hpp"
    "src/Blocks/Controller/NiTextureTransformController.hpp"
    "src/Blocks/Controller/NiTimeController.hpp"

    "src/Blocks/Data/NiBoolData.hpp"
    "src/Blocks/Data/NiBooleanExtraData.hpp"
    "src/Blocks/Data/NiExtraData.hpp"
    "src/Blocks/Data/NiFloatData.hpp"
    "src/Blocks/Data/NiGeometryData.hpp"
    "src/Blocks/Data/NiIntegerExtraData.hpp"
    "src/Blocks/Data/NiIntegersExtraData.hpp"
    "src/Blocks/Data/NiPixelData.hpp"
    "src/Blocks/Data/NiStringExtraData.hpp"
    "src/Blocks/Data/NiTriShapeData.hpp"
    "src/Blocks/Data/NiTriBasedGeomData.hpp"

    "src/Blocks/DataStreamData/DataStreamColor.hpp"
    "src/Blocks/DataStreamData/DataStreamData.hpp"
    "src/Blocks/DataStreamData/DataStreamIndex.hpp"
    "src/Blocks/DataStreamData/DataStreamNormal.hpp"
    "src/Blocks/DataStreamData/DataStreamPosition.hpp"
    "src/Blocks/DataStreamData/DataStreamTexCoord.hpp"

    "src/Blocks/Property/NiAlphaProperty.hpp"
    "src/Blocks/Property/NiMaterialProperty.hpp"
    "src/Blocks/Property/NiProperty.hpp"
    "src/Blocks/Property/NiSpecularProperty.hpp"
    "src/Blocks/Property/NiStencilProperty.hpp"
    "src/Blocks/Property/NiTexturingProperty.hpp"
    "src/Blocks/Property/NiVertexColorProperty.hpp"
    "src/Blocks/Property/NiZBufferProperty.hpp"
)

set(SOURCE_FILES
    "src/Reader.cpp"
    "src/Core/NiFile.cpp"
)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# TESTS
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_executable(NiForgeTests
    tests/test_parser.cpp
)
# END TESTS

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE NIFORGE_EXPORTS)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# TESTS

add_custom_command(TARGET NiForgeTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/data"
    $<TARGET_FILE_DIR:NiForgeTests>/data
    COMMENT "Copying test data for NiForgeTests..."
)

target_link_libraries(NiForgeTests PRIVATE NiForge gtest_main)
include(GoogleTest)
gtest_discover_tests(NiForgeTests)
target_include_directories(NiForgeTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

#END TESTS