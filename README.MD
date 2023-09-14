This extends the ["You buy it, you own it"](https://www.gog.com/en/about_gog) GOG philisophy to the multiplayer portion of all games that use GOG Galaxy.

Why Universe? Because Universe >> Galaxy.

To generate the module definition files, use [wrap_dll](https://github.com/mavenlin/wrap_dll).  
  
- Replace target game `Galaxy.dll` or `Galaxy64.dll` to use UniverseLAN.
- Place config files in the working directory of the game
- Adjust config accordingly (e.g. point to a server address that hosts the Universe LAN Backend)
- It's recommended to NOT mix x64 and x86 platforms (e.g. x64 server with x86 game)
- Do NOT mix different versions due to ABI incompatibility (e.g. 1.148.3.0 client with 1.100.2.0 server or vice versa), GOG does not keep their Galaxy library backwards compatible / upgradeable.
- Don't add GOG stdint.h, remove it. If you try it WILL cause errors.
- It is possible to support Galaxy SDK versions from 1.57 up to the newest ones (1.148.+).
- If someone has earlier SDK files please share <3

# List / status of games

:white_check_mark: (N) - Players can play together, tested with N players [(2) would mean 2 clients].  
:construction: - Work in progress.  
:warning: - May or may not work, not tested, the future will tell.  
:x: - Tested and does not work.  
:question: - Can't acquire the correct GOG Galaxy SDK version.  
:left_right_arrow: - Game supports direct connect, LAN or free multiplayer, and as such does not need UniverseLAN.  

| Game       | Status                | Tested GOG Galaxy SDK Version | Notes |
| :--------- | :-------:             | :---------: | :---------: |
| Aragami 1  | :white_check_mark:(2) | 1.121.2 |
| MetalSlug3 | :construction:        | 1.100.2 | Can host and join lobby, can't get past character selection screen. |
| Alien vs Predator 2000 | :question: |  | It's some waay earlier version than 1.67 (smallest size around 3.5MB). <br> The AvP2K Galaxy.dll is around 1.9MB. Version is maybe 0.176.2.6? |
| Roboquest | :x: | 1.148.3 | Probably does not use GOG Galaxy for networking. |
| Aragami 2 | :left_right_arrow: | 1.148.3 | Probably does not use GOG Galaxy for networking (doesn't work for private lobbies).<br> Can play on public lobbies without GOG Galaxy or with this patch AFAIK. |
| Shadow Warrior 2 | :warning: | | | 
| Baldur's Gate 3 | :left_right_arrow: | | | 
| Heroes of Might and Magic 3 | :left_right_arrow: | | | 
| Empire Earth 3 | :left_right_arrow: | | | 
| Jazz Jackrabbit 2 Collection | :left_right_arrow: | | | 
| Homeworld Remastered Collection | :warning:  | | | 
| Rage of Mages II: Necromancer | :left_right_arrow: | | | 
| Neverwinter Nights 2 Complete | :left_right_arrow: | | | 
| Homeworld: Deserts of Kharak | :warning:  | | | 
| No Man's Sky | :warning:  | | | 
| Serious Sam 4 | :warning:  | | | 
| Forsaken Remastered | :white_check_mark:(3) | 1.124.0.0 | |
