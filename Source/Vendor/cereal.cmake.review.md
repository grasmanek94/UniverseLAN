# Review: `Source/Vendor/cereal.cmake`

## Assessment

The wrapper exposes the vendored cereal include directory through a target and
adds a dummy C translation unit so CMake can create a static target. The
implementation under `Source/Vendor/cereal-1.3.2/**` is explicitly excluded by
the repository instructions.

- **Low — the include glob is unrestricted.** It registers every file under
  the vendored include tree as target source metadata. Prefer an interface
  target with an explicit include directory or filter the intended extensions.
