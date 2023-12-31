# Why?

This extends the ["You buy it, you own it"](https://www.gog.com/en/about_gog) and  "DRM-Free" GOG philosophy to the multiplayer portion of all games that use GOG Galaxy.

Why *Universe*LAN? Because the Universe is much bigger than the Galaxy!

# What is *UniverseLAN*?

[UniverseLAN](https://github.com/grasmanek94/UniverseLAN) is a GOG Galaxy wrapper which allows LAN / Direct IP connections for games using Galaxy Multiplayer (without using GOG Galaxy client).  
This is useful in cases where:
1) You and other people own a game
2) All or some of you don't have (reliable) internet access
3) And as such GOG Galaxy services won't work
4) The game you want to play does not natively support LAN and/or DirectIP connections
5) But you all want to play together anyway  

UniverseLAN allows you to play locally (e.g. LAN parties) without relying on internet access. UniverseLAN does not care if you are in a hotel room with bad WiFi or visiting a remote place with your friends! You can still enjoy your games, _together_.   

<small>I hope this does not need to be said, but:</small>   
- **UniverseLAN does not bypass or remove any DRM measures.**    
- **UniversLAN does not bypass any cd-key or ownership checks.**  
- **UniverseLAN does not give you free DLC, you still need to buy DLC from GOG and install the DLC before being able to use any DLC.**  
- **UniverseLAN does not and can't bypass any "always online" requirements.**  
- **UniverseLAN does not condone piracy, does not facilitate piracy, and will not facilitate piracy.**  
- **UniverseLAN is not a cheat tool and does not facilitate cheating, and will not facilitate cheating.**  
- Please adhere to [GOG requirements](https://support.gog.com/hc/en-us/articles/212184489-Can-I-share-games-with-others-?product=gog):  
> Your account and games are for your personal use only. If you want to share them, you can always buy a gift for that person.
> 
> The DRM-free nature of our service means that we trust you that this will not be abused.
- The devices that you want to play on together do need to be able to reach each other on a reliable (local) network.

# What is the status of *UniverseLAN*?
[UniverseLAN](https://github.com/grasmanek94/UniverseLAN) is in development, and in beta.  
Do expect bugs, possibly lost save files, updates and fixes.  
> At this moment in time you are expected to build it yourself to get up-to-date binaries.  
> Older binaries may be available at the '[Releases](https://github.com/grasmanek94/UniverseLAN/releases)' page.  
> [UniverseLAN](https://github.com/grasmanek94/UniverseLAN) requires a C++20 compatible compiler (VS 2019 16.10+ , GCC 13+).  
> The internal development name of this project is `LanSupportForDRMFreeGames [LSFDRMFG]`, you might see references to that in the source.  

### Note
<small>*** Some games do use GOG Galaxy but do not use GOG Galaxy for multiplayer.  
They can use other services or custom networking implementations.  
Such games might not be able to be played together using UniverseLAN wrapper.</small>

# How do you get .def files?
To generate the module definition files, use [wrap_dll](https://github.com/mavenlin/wrap_dll):  
- `python3 wrap_dll.py Galaxy64.dll`  

Then remove on each line everything after (and including) **`=` sign** in .def file.
Place in `Source/DLLs/<version>/UniverseLAN.def`
  
# Instructions

- Replace target game `Galaxy.dll`, `Galaxy64.dll`, `REDGalaxy.dll` or `REDGalaxy64.dll` to use UniverseLAN (check the .dll file properties to view the version information, else make an sha1 checksum and look in [sha1_hashes.txt](ZipFileHasher/sha1_hashes.txt) for the hash to determine the sdk version).
- Place config files in the working directory* of the game
- Place Server executable where config files are located.
- Adjust config accordingly (e.g. point to a server address that hosts the UniverseLAN Backend)
- It's recommended to NOT mix x64 and x86 platforms (e.g. x64 server with x86 game)
- Do NOT mix different versions due to ABI incompatibility (e.g. 1.148.3.0 client with 1.100.2.0 server or vice versa), GOG does not keep their Galaxy library backwards compatible / upgradeable.  
- One machine must host the server, the other machine must be correctly configured to point to the machine hosting the server.  
- Make sure the Galaxy ID numbers are different (Config.ini).  

> `*` - Usually the working directory is the root directory of the game, or where the .exe file is located. Some games use a proxy launcher .exe in the game root directory like `Game_Name\Launcher.exe`, which launches and executable from a subfolder like `Game_Name\Binaries\Win64\RealGame.exe`, this might indicate that config and server files should be placed in `Game_Name\Binaries\Win64\`.

For developers:  
- Don't add GOG stdint.h when adding new SDK versions, remove it. If you try it WILL cause errors.
- It is possible to support Galaxy SDK versions from 1.57 up to the newest ones (1.152.6+).
- If someone has earlier SDK headers and/or documentation files please share <3

# Debug Information
Debug (tracing) files can be found in `<Configuration Files Directory>/tracing/<date time when application was launched>/`.

# Compilation
## Windows
- Visual Studio 2019 16.10 or newer required  
  
## Linux
- Requires GCC 13 or newer.  
- Requires libtbb to be present (libtbb:i386 on 64-bit systems when compiling for x86)  
  
# List / status of games

:white_check_mark: (N) - Players can play together, tested with N players [(2) would mean 2 clients].  
:construction: - Work in progress.  
:warning: - May or may not work, not tested, the future will tell.  
:x: - Tested and does not work.  
:question: - Can't acquire the correct GOG Galaxy SDK version.  
:left_right_arrow: - Game supports direct connect, LAN or free multiplayer, and as such does not need UniverseLAN.  
:large_orange_diamond: - Worked before, some commit has broken this game. To be investigated.  


| Game       | Status                | Tested GOG Galaxy SDK Version | Notes |
| :--------- | :-------:             | :---------: | :---------: |
| Aragami 1  | :white_check_mark:(2) | 1.121.2 | |
| Forsaken Remastered | :white_check_mark:(3) | 1.124.0 | |
| Guns, Gore & Cannoli 2  | :white_check_mark:(3) | 1.124.0 | |
| Tropico 6 | :white_check_mark:(2) | 1.139.2 | Also other games are displayed? Game has custom networking?<br> Build 161 worked, build 243 seems to be broken (can't join lobby) <br> Update: The person testing UniverseLAN used an invalid configuration (same generated Galaxy ID numbers), after fixing this configuration issue in Config.ini the person reported the game seems to work on build 243. | 
| MetalSlug3 | :white_check_mark:(2)        | 1.100.2 | Works since build 243 |
| Serious Sam 4 | :white_check_mark:(2)  | 1.144.1 | Works since build 256 | 
| Tooth and Tail | :white_check_mark:(2)  | 1.122.1 | Works with 1.124.0, tested with build 256 | 
| Door Kickers - Action Squad | :white_check_mark:(2) | 1.133.6 | Tested with build 287 |
| Driftland - The Magic Revival | :construction: | 1.133.6 | Both games crash when joining |
| Serious Sams Bogus Detour | :construction: | 1.100.2 | Stuck on "Creating lobby..." or "Joining lobby..." <br> Can get into lobby since build 243 but host crashes on start |
| Niffelheim | :construction:  | 1.139.2 | Stuck at "Loading..." (save transfer?) | 
| Alien vs Predator 2000 | :question: |  | It's some waay earlier version than 1.67 (smallest size around 3.5MB). <br> The AvP2K Galaxy.dll is around 1.9MB. Version is maybe 0.176? |
| Homeworld Remastered Collection | :warning:  | | | 
| Homeworld: Deserts of Kharak | :warning:  | | | 
| No Man's Sky | :warning:  | | | 
| Speed Brawl | :warning:  | 1.144.1 | | 
| DUSK | :warning:  | 1.133.6 | | 
| Absolver | :warning:  | 1.104.2 | | 
| Shadow Warrior 2 | :warning: | 1.95.0 | | 
| Rage of Mages II: Necromancer | :left_right_arrow: | | | 
| Neverwinter Nights 2 Complete | :left_right_arrow: | | | 
| Baldur's Gate 3 | :left_right_arrow: | | | 
| Heroes of Might and Magic 3 | :left_right_arrow: | | | 
| Empire Earth 3 | :left_right_arrow: | | | 
| Jazz Jackrabbit 2 Collection | :left_right_arrow: | | | 
| Ticket to Ride | :left_right_arrow:   | 1.139.2 | Tried it with the wrapper and works, but need to create a free Wonder account | 
| Aragami 2 | :left_right_arrow: | 1.148.3 | Probably does not use GOG Galaxy for networking (doesn't work for private lobbies).<br> Can play on public lobbies without GOG Galaxy or with this patch AFAIK. |
| DUSK (DuskWorld) | :left_right_arrow: | 1.133.6 | Uses steam (works without Steam Client) api for free online play, doesn't use GOG Galaxy. |
| Roboquest | :x: | 1.148.3 | Probably does not use GOG Galaxy for networking. |
| Northgard | :x:  | 1.139.2 | Still thinks the game is offline, custom multiplayer? | 
| Tropico 5 | :x:  | 1.68.0 | Game uses an external service for multiplayer? | 

# Notice
I'm not affiliated in any way with GOG or CD Projekt RED.  
All trademarks and copyright are property of their respective owners.  
Any statements or expressed opinions here are each of their respective own person and do not represent any companies or other entities.  
GOG SDK documentation and SDK include files are freely available from https://docs.gog.com/galaxyapi/.  
No copyright infringement intended.  

# Is distributing header files against copyrights?  
I don't think so:  
  
1. https://en.wikipedia.org/wiki/Google_LLC_v._Oracle_America,_Inc.
2. https://softwareengineering.stackexchange.com/questions/216471/how-does-copyrights-apply-to-source-code-header-files

## `Source/DLLs/<version>/gog/` is missing files? What do I do?
The tests require the Galaxy.lib and Galaxy.dll files from GOG.  
You can get any version matching Galaxy.dll from any game that you own.  
UniverseLAN does not and will not distribute (RED)Galaxy / (RED)Galaxy64 dll files, because it's against copyright / GOG ToS.  
I don't know if .lib files should be considered API or copyrighted program code, but to play it safe UniverseLAN also does not distribute .lib files.  
For the time being; if you wish to build the tests, you need to acquire these .lib files from the GOG Galaxy SDK, available in the GOG Galaxy Developer Portal.  
Building the tests is optional.  
> Tip: By creating a project with [wrap_dll](https://github.com/mavenlin/wrap_dll) and providing a valid `(RED)Galaxy(64).dll` you can generate a wrapper project, which when compiled, should yield a compatible .lib file that you can use to build the tests.  

## Galaxy SDK Backwards Compatibility List
These GOG Galaxy SDK versions should work interchangeably.  
> For Developers: This does not neccesseraly represent version compilation compatibility, for example 1.125 and 1.125.1 are not compile-compatible (due to `uint32_t` to `enum` type change), but should be binary-compatible.  

| SDK Base Version       | Other Compatible Versions | Notable changes |  
| :--------------------: | :------------------------ | --------------- |  
| 1.57 | - |
| 1.59 | 1.60 | Added: <br> `IFriends::AvatarType` <br> `IFriends::GetFriendPersonaName` <br> `IFriends::GetFriendAvatarUrl`
| 1.61 | - | Added: <br> `IFriends::IPersonaDataChangedListener` <br> `IFriends::IRichPresenceChangeListener` <br> `IFriends::RequestUserInformation` <br> `IFriends::Set/Delete/ClearRichPresence`
| 1.62 | 1.63 <br> 1.64 | Added: <br> `IUser::IsLoggedOn` <br> `ILeaderboardEntriesRetrieveListener::FAILURE_REASON_NOT_FOUND` <br> `IErrorManager` / `GetErrorManager` <br> Renamed `Reset` to `ResetInstance`
| 1.65 | 1.66 |
| 1.67 | - |
| 1.68 | - |
| 1.69 | - |
| 1.70 | - |
| 1.71 | 1.72 |
| 1.73 | - |
| 1.74 | - |
| 1.75 | - |
| 1.76 | - |
| 1.77 | - |
| 1.78 | 1.79 <br> 1.80 |
| 1.82 | - |
| 1.83 | - |
| 1.84 | 1.85 <br> 1.86 |
| 1.87 | - |
| 1.88 | 1.89 <br> 1.90 |
| 1.91 | 1.92 |
| 1.92.1 | 1.93 <br> 1.94 <br> 1.95 <br> 1.96 <br> 1.97 <br> 1.98 |
| 1.99 | - |
| 1.100 | 1.100.2 <br> 1.101 <br> 1.101.2 <br> 1.101.4 |
| 1.102 | - |
| 1.103 | 1.103.1 <br> 1.104 <br> 1.104.1 <br> 1.104.2 |
| 1.104.3 | - |
| 1.104.4 | 1.104.5 <br> 1.104.6 <br> 1.105 |
| 1.106 | 1.107 <br> 1.108 |
| 1.109 | - |
| 1.110 | 1.110.1 <br> 1.110.2 <br> 1.110.3 |
| 1.110.4 | 1.111 <br> 1.111.2 <br> 1.112 <br> 1.112.1 <br> 1.112.2 |
| 1.113 | - |
| 1.113.2 | - |
| 1.113.3 | - |
| 1.114 | 1.114.1 <br> 1.114.2 <br> 1.114.3 <br> 1.114.4 <br> 1.114.6 <br> 1.114.7 |
| 1.114.8 | 1.114.9 <br> 1.114.12 |
| 1.120 | - |
| 1.120.1 | 1.121 <br> 1.121.1 <br> 1.121.2 |
| 1.122 | 1.122.1 <br> 1.122.3 <br> 1.122.4 <br> 1.123 <br> 1.123.1 <br> 1.124 |
| 1.125 | 1.125.1 <br> 1.125.2 |
| 1.126 | 1.126.1 |
| 1.127 | - |
| 1.128 | 1.128.1 <br> 1.128.2 <br> 1.128.3 |
| 1.129 | 1.130 <br> 1.130.1 |
| 1.131 | 1.131.1 <br> 1.131.2 <br> 1.131.3 |
| 1.132 | 1.132.1 |
| 1.133 | - |
| 1.133.1 | - |
| 1.133.3 | 1.133.4 <br> 1.133.5 <br> 1.133.6 <br> 1.133.7 <br> 1.133.9 |
| 1.134 | 1.134.1 <br> 1.134.2 <br> 1.134.3 <br> 1.134.4 <br> 1.134.5 <br> 1.134.6 <br> 1.134.7 <br> 1.134.8 | Telemetry has been added
| 1.134.9 | - |
| 1.134.10 | - |
| 1.135 | - |
| 1.136 | 1.136.4 <br> 1.137 <br> 1.137.1 <br> 1.137.2 <br> 1.137.3 <br> 1.137.4 <br> 1.137.5 <br> 1.137.6 <br> 1.138 |
| 1.138.1 | 1.139 <br> 1.139.1 <br> 1.139.2 <br> 1.139.3 <br> 1.139.4 |
| 1.139.5 | - |
| 1.139.6 | - |
| 1.139.7 | 1.139.8 <br> 1.139.9 |
| 1.140 | - | Added GalaxyThread (+to InitOptions)
| 1.141 | 1.142 |
| 1.143 | 1.143.1 <br> 1.143.2 <br> 1.143.3 <br> 1.144 <br> 1.144.1 <br> 1.144.2 <br> 1.145 <br> 1.145.1 <br> 1.145.2 <br> 1.145.3 <br> 1.145.4 <br> 1.145.5 |
| 1.146 | 1.147 |
| 1.147.1 | - |
| 1.148 | 1.148.1 |
| 1.148.2 | - | Added GetRichPresenceKeyByIndex/Copy
| 1.148.3 | 1.148.4 |  
| 1.148.5 | - | Removed SignInUWB and added SingInXbox
| 1.148.6 | - | Added CloudStorage
| 1.148.7 | 1.148.8 <br> 1.148.9 <br> 1.148.10 |  
| 1.148.11 | 1.148.12 |  
| 1.148.14 | - |  
| 1.148.15 | - |  
| 1.148.16 | 1.148.17 <br> 1.148.18 <br> 1.148.19 <br> 1.148.20 <br> 1.148.21 <br> 1.148.22 <br> 1.148.23 <br> 1.148.25 <br> 1.148.26 <br> 1.149.0 |  
| 1.149.1 | - |  
| 1.149.2 | 1.149.3 <br> 1.149.4 <br> 1.149.5 <br> 1.149.6 <br> 1.149.7 <br> 1.149.8 |  
| 1.149.9 | - |  
| 1.149.10 | - |  
| 1.149.11 | - |  
| 1.149.12 | 1.149.13 <br> 1.149.14 <br> 1.149.15 <br> 1.149.16 | Galaxy/Galaxy64 renamed to REDGalaxy/REDGalaxy64
| 1.150 | - |  GOG reverted the rename to RED prefix, it's Galaxy/Galaxy64 again.
| 1.151 | - |  
| 1.152.1 | - |  
| 1.152.2 | - |  
| 1.152.5 | 1.152.6 |  
