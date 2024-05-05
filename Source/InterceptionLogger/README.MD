# InterceptionLogger

The `InterceptionLogger` is a lightweight logging filter between a target (Game, Application, etc.) and a Galaxy API provider (Real GOG Galaxy SDK DLL or UniverseLAN Client DLL).  
The purpose is comparing behaviour of UniverseLAN against real GOG Galaxy SDK.  
This allows for faster debugging of issues when games do not work with UniverseLAN.  

The output of this sub project is (`RED`?) `GalaxyInterceptor64.dll`/`GalaxyInterceptor.dll` which should be renamed to (`RED`?) `Galaxy64.dll`/`Galaxy.dll`.  
The file that this interceptor will load **from the working directory** must be called `RealGalaxy64.dll` / `RealGalaxy.dll` / `RealREDGalaxy64.dll`/`RealREDGalaxy.dll`.  
The **working directory** is **NOT** always the same as the original Galaxy SDK DLL location, keep that in mind!  
  
Output is by default logged to `<working directory>/UniverseLANData/Interceptor/`.  
This interceptor reads all the config from `UniverseLAN.ini` and `Config.ini`.  
All tracing options applied there, not only apply to UniverseLAN Client, but also to the Interceptor.