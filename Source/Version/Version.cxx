#include "Version.hxx"

#include <auto_version.h>

namespace universelan {
	// REVIEW: Version.cxx - Build version constant
	// Thread safety: GOOD - Const global, no mutations
	// Build integration: BUILD_VERSION from auto_version.h (generated at build time)
	// 
	const size_t Version_Number = BUILD_VERSION;
}