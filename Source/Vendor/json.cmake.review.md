# Review: `Source/Vendor/json.cmake`

## Assessment

The wrapper exposes the excluded nlohmann-json include directory through a
static target and a dummy translation unit. The third-party implementation
itself is outside the review scope.

- **Low — the include glob is unrestricted.** Filter the input or use an
  interface target to keep non-source vendor files out of the target metadata.
