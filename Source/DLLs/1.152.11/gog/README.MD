Place here:

Galaxy.dll
Galaxy64.dll
Galaxy.lib
Galaxy64.lib

These must be downloaded from GOG:
GalaxyPeer.dll
GalaxyPeer64.dll

For the local-only channel-8 peer overlay used by BehaviourTests, use
https://cfg.gog.com/desktop-galaxy-peer/8/master/files-windows.json and verify
the extracted `peer/msvc-18/GalaxyPeer64.dll` against its manifest hashes. Do
not replace or commit the base `Galaxy64.dll` or downloaded peer; see
`Source/BehaviourTests/README.md` for the exact process.
