#ifndef GALAXY_EXPORT_H
#define GALAXY_EXPORT_H

/**
 * @file
 * Contains a macro used for DLL export.
 */

#if defined(_WIN32)
	#if defined(GALAXY_EXPORT)
		#define GALAXY_DLL_EXPORT __declspec(dllexport)
	#else
		#define GALAXY_DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#define GALAXY_DLL_EXPORT
#endif

#if defined(_WIN32)
	#define GALAXY_CALLTYPE __cdecl
#else
	#define GALAXY_CALLTYPE
#endif

#endif
