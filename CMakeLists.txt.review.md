# Review: `CMakeLists.txt`

## Finding — invalid architecture configuration succeeds without configuring targets

- **Severity:** Medium
- **Evidence:** For non-MSVC builds, an architecture other than `x86`/`x64` reaches lines 45–48, emits a plain `message()`, and executes `return()` instead of failing configuration.
- **Impact:** A typo or omitted `GALAXY_ARCH` can produce a successful but empty build tree; CI may report success without producing binaries.
- **Suggested fix:** Replace the message/`return()` path with `message(FATAL_ERROR ...)`, and validate the MSVC architecture path as well.

## Finding — toolchain flags are overwritten

- **Severity:** Medium
- **Evidence:** Lines 60–61 and 66–67 assign `CMAKE_C_FLAGS` and `CMAKE_CXX_FLAGS` directly to `-m32`/`-m64`.
- **Impact:** User/toolchain flags (hardening, sanitizers, optimization, sysroot, and warning settings) are discarded, making cross-builds fragile and potentially removing security compiler options.
- **Suggested fix:** Use target/toolchain configuration or append only the architecture option (for example with `add_compile_options`), preserving existing flags.
