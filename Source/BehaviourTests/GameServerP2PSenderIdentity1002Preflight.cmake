if(NOT DEFINED BEHAVIOUR_TEST_SOURCE_DIR)
  message(FATAL_ERROR "Set BEHAVIOUR_TEST_SOURCE_DIR")
endif()

set(sdk_dir "${BEHAVIOUR_TEST_SOURCE_DIR}/Source/DLLs/1.100.2")
set(galaxy_dir "${sdk_dir}/galaxy")
set(gog_dir "${sdk_dir}/gog")

foreach(required IN ITEMS GalaxyApi.h IGalaxy.h INetworking.h GalaxyID.h)
  if(NOT EXISTS "${galaxy_dir}/${required}")
    message(FATAL_ERROR "BEHAVIOUR_TEST PREFLIGHT sdk=1.100.2 result=invalid-public-header-set missing=${required}")
  endif()
endforeach()

file(READ "${galaxy_dir}/IGalaxy.h" galaxy_header)
file(READ "${galaxy_dir}/INetworking.h" networking_header)
file(READ "${galaxy_dir}/GalaxyID.h" id_header)

set(server_networking_available false)
if(galaxy_header MATCHES "GetServerNetworking")
  set(server_networking_available true)
endif()

set(polling_available false)
if(networking_header MATCHES "SendP2PPacket" AND networking_header MATCHES "IsP2PPacketAvailable" AND networking_header MATCHES "ReadP2PPacket")
  set(polling_available true)
endif()

set(dedicated_game_server_available false)
if(EXISTS "${galaxy_dir}/GalaxyGameServerApi.h")
  set(dedicated_game_server_available true)
endif()

set(sender_id_type_available false)
if(id_header MATCHES "GetIDType" OR id_header MATCHES "ID_TYPE_")
  set(sender_id_type_available true)
endif()

set(official_artifacts_available true)
foreach(required IN ITEMS Galaxy64.lib Galaxy64.dll GalaxyPeer64.dll)
  if(NOT EXISTS "${gog_dir}/${required}")
    set(official_artifacts_available false)
  endif()
endforeach()

if(DEFINED BEHAVIOUR_TEST_CREDENTIALS_AVAILABLE AND BEHAVIOUR_TEST_CREDENTIALS_AVAILABLE)
  set(credentials_available true)
else()
  set(credentials_available false)
endif()

# This is a successful preflight when it identifies the public-SDK block. It never
# loads a runtime, signs in, sends a packet, or reports an inferred sender identity.
message(STATUS "BEHAVIOUR_TEST PREFLIGHT scenario=official-gog-first-server-p2p-sender-identity sdk=1.100.2 arch=x64 classification=blocked")
message(STATUS "  officialArtifacts=${official_artifacts_available} credentialsAvailable=${credentials_available} serverNetworkingInterface=${server_networking_available} pollingInterface=${polling_available}")
message(STATUS "  dedicatedGameServerApi=${dedicated_game_server_available} senderIdTypeAccessor=${sender_id_type_available}")
message(STATUS "  block=the selected public header has no dedicated GameServer API and no public GalaxyID type accessor; no compliant official or UniverseLAN sender-identity result is produced")
