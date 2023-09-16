cmake_minimum_required(VERSION 3.12)

add_library(universelan-client-${GALAXY_VERSION} SHARED Dll.cxx UniverseLAN.def)

target_include_directories(universelan-client-${GALAXY_VERSION} PUBLIC ".")

target_compile_definitions(universelan-client-${GALAXY_VERSION} PUBLIC "CLIENT_DLL")

target_link_libraries(universelan-client-${GALAXY_VERSION} PUBLIC universelan-lib-${GALAXY_VERSION})

set_target_properties(universelan-client-${GALAXY_VERSION} PROPERTIES OUTPUT_NAME "Galaxy-${GALAXY_VERSION}")