#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #ifdef NIFORGE_EXPORTS
        #define NIFORGE_API __declspec(dllexport)
    #else
        #define NIFORGE_API __declspec(dllimport)
    #endif
#else
    #ifdef NIFORGE_EXPORTS
        #define NIFORGE_API __attribute__((visibility("default")))
    #else
        #define NIFORGE_API
    #endif
#endif
