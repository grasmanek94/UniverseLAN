# Why?

This extends the ["You buy it, you own it"](https://www.gog.com/en/about_gog) and  "DRM-Free" GOG philisophy to the multiplayer portion of all games that use GOG Galaxy.

Why *Universe*LAN? Because the Universe is much bigger than the Galaxy!

# What is *UniverseLAN*?

[UniverseLAN](https://github.com/grasmanek94/UniverseLAN) is a GOG Galaxy wrapper which allows LAN / Direct IP connections for games using Galaxy Multiplayer (without using GOG Galaxy client).  

<small>I hope this does not need to be said, but:</small>   
- **UniverseLAN does not bypass or remove any DRM measures.**  
- UniverseLAN does not condone piracy, does not facilitate piracy, and will not facilitate piracy.  
- UniverseLAN is not a cheat tool and does not facilitate cheating, and will not facilitate cheating.  
- Please adhere to [GOG requirements](https://support.gog.com/hc/en-us/articles/212184489-Can-I-share-games-with-others-?product=gog):  
> Your account and games are for your personal use only. If you want to share them, you can always buy a gift for that person.
> 
> The DRM-free nature of our service means that we trust you that this will not be abused.

# What is the status of *UniverseLAN*?
[UniverseLAN](https://github.com/grasmanek94/UniverseLAN) is in development, and in beta.  
Do expect bugs, possibly lost save files, updates and fixes.  
> At this moment in time you are expected to build it yourself to get binaries.  
> [UniverseLAN](https://github.com/grasmanek94/UniverseLAN) requires a C++20 compatible compiler.  
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
- Place config files in the working directory of the game
- Place Server executable where config files are located
- Adjust config accordingly (e.g. point to a server address that hosts the UniverseLAN Backend)
- It's recommended to NOT mix x64 and x86 platforms (e.g. x64 server with x86 game)
- Do NOT mix different versions due to ABI incompatibility (e.g. 1.148.3.0 client with 1.100.2.0 server or vice versa), GOG does not keep their Galaxy library backwards compatible / upgradeable.
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

| Game       | Status                | Tested GOG Galaxy SDK Version | Notes |
| :--------- | :-------:             | :---------: | :---------: |
| Aragami 1  | :white_check_mark:(2) | 1.121.2 | |
| Forsaken Remastered | :white_check_mark:(3) | 1.124.0.0 | |
| Guns, Gore & Cannoli 2  | :white_check_mark:(3) | 1.124.0.0 | |
| Tropico 6 | :white_check_mark:(2)  | 1.139.2 | Also other games are displayed? Game has custom networking? | 
| MetalSlug3 | :construction:        | 1.100.2 | Can host and join lobby, can't get past character selection screen. |
| Serious Sams Bogus Detour | :construction: | 1.100.2 | Stuck on "Creating lobby..." or "Joining lobby..." |
| Alien vs Predator 2000 | :question: |  | It's some waay earlier version than 1.67 (smallest size around 3.5MB). <br> The AvP2K Galaxy.dll is around 1.9MB. Version is maybe 0.176.2.6? |
| Homeworld Remastered Collection | :warning:  | | | 
| Homeworld: Deserts of Kharak | :warning:  | | | 
| No Man's Sky | :warning:  | | | 
| Serious Sam 4 | :warning:  | 1.144.1 | | 
| Speed Brawl | :warning:  | 1.144.1 | | 
| Northgard | :warning:  | 1.139.2 | | 
| Niffelheim | :warning:  | 1.139.2 | | 
| DUSK | :warning:  | 1.133.6 | | 
| Tooth and Tail | :warning:  | 1.122.1 | | 
| Absolver | :warning:  | 1.104.2 | | 
| Shadow Warrior 2 | :warning: | 1.95.0 | | 
| Tropico 5 | :warning:  | 1.68.0 | | 
| Rage of Mages II: Necromancer | :left_right_arrow: | | | 
| Neverwinter Nights 2 Complete | :left_right_arrow: | | | 
| Baldur's Gate 3 | :left_right_arrow: | | | 
| Heroes of Might and Magic 3 | :left_right_arrow: | | | 
| Empire Earth 3 | :left_right_arrow: | | | 
| Jazz Jackrabbit 2 Collection | :left_right_arrow: | | | 
| Ticket to Ride | :left_right_arrow:   | 1.139.2 | Tried it with the wrapper and works, but need to create a free Wonder account | 
| Aragami 2 | :left_right_arrow: | 1.148.3 | Probably does not use GOG Galaxy for networking (doesn't work for private lobbies).<br> Can play on public lobbies without GOG Galaxy or with this patch AFAIK. |
| Roboquest | :x: | 1.148.3 | Probably does not use GOG Galaxy for networking. |

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
