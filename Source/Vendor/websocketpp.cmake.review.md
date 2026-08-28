# Review: `Source/Vendor/websocketpp.cmake`

## Assessment

The wrapper resolves the excluded websocketpp package, exposes its include
directory, and links the imported target. The vendored implementation is
outside review scope.

- **Low — the wrapper's source glob is unrestricted.** Filter the include-tree
  inputs or use an interface target so new non-code files do not become target
  sources.
