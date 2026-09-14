if(NOT DEFINED BEHAVIOUR_TEST_BUILD_DIR)
  message(FATAL_ERROR "Set BEHAVIOUR_TEST_BUILD_DIR to the configured build directory")
endif()

if(NOT DEFINED CTEST_COMMAND)
  find_program(CTEST_COMMAND ctest REQUIRED)
endif()

if(NOT DEFINED BEHAVIOUR_TEST_LABEL)
  set(BEHAVIOUR_TEST_LABEL "behavior")
endif()

if(NOT DEFINED BEHAVIOUR_TEST_CONFIGURATION)
  set(BEHAVIOUR_TEST_CONFIGURATION "Debug")
endif()

execute_process(
  COMMAND "${CTEST_COMMAND}" --test-dir "${BEHAVIOUR_TEST_BUILD_DIR}" -C "${BEHAVIOUR_TEST_CONFIGURATION}" --output-on-failure -L "${BEHAVIOUR_TEST_LABEL}"
  RESULT_VARIABLE result)
if(NOT result EQUAL 0)
  message(FATAL_ERROR "Explicitly registered behaviour CTest labels failed")
endif()
