#pragma once

#ifdef NIFORGE_EXPORTS
	#define NIFORGE_API __declspec(dllexport)
#else
	#define NIFORGE_API __declspec(dllimport)
#endif
