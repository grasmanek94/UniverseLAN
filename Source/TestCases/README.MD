[Redeem game](https://www.gog.com/redeem/IDDQD)

https://github.com/gogcom/galaxy-csharp-demo-game/blob/master/Assets/Scripts/GalaxyManager/GalaxyManager.cs


```
private readonly string clientID = "50225266424144145";
private readonly string clientSecret = "45955f1104f99b625a5733fa1848479b43d63bdb98f0929e37c9affaf900e99f";
```

```
    // List of all in-game achievements api keys
    public string[] achievementsList = new string[14] {
        "launchTheGame",
        "putBlack",
        "putBlue",
        "putBrown",
        "putGreen",
        "putPink",
        "putRed",
        "putYellow",
        "winSPRound",
        "win2PRound",
        "draw2PRound",
        "winMPRound",
        "drawMPRound",
        "loseMPRound"
    };

    // Dictionary of all in-game statistics api keys, with their full display names
    public Dictionary<string, string> statisticsFloatList = new Dictionary<string, string>() 
    {
        { "lastScore", "Last Score" },
        { "highestScore", "Highest Score"}
    };

    // Dictionary of all in-game statistics api keys with their full display names
    public Dictionary<string, string> statisticsIntList = new Dictionary<string, string> 
    {
        { "fouls", "Fouls" },
        { "shotsTaken", "Shots Taken" }
    };
    
    public Dictionary<string, string> leaderboardNames = new Dictionary<string, string>()
    {
        {"Fouls", "fouls"},
        {"Highest Score", "highestScore"},
        {"Shots Taken", "shotsTaken"}
    };
```
