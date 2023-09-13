This extends the ["You buy it, you own it"](https://www.gog.com/en/about_gog) GOG philisophy to the multiplayer portion of all games that use GOG Galaxy.

Why Universe? Because Universe >> Galaxy.

To generate the module definition files, use [wrap_dll](https://github.com/mavenlin/wrap_dll).  
  
- Replace target game `Galaxy.dll` or `Galaxy64.dll` to use UniverseLAN.
- Place config files in the working directory of the game
- Adjust config accordingly (e.g. point to a server address that hosts the Universe LAN Backend)
- It's recommended to NOT mix x64 and x86 platforms (e.g. x64 server with x86 game)
- Do NOT mix different versions due to ABI incompatibility (e.g. 1.148.3.0 client with 1.100.2.0 server or vice versa), GOG does not keep their Galaxy library backwards compatible / upgradeable.
- Don't add GOG stdint.h, remove it. If you try it WILL cause errors.