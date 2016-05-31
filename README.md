#Ms Pacman 

Link to the wiki: https://github.com/tomaticgang/Ms-Pac-Man/wiki

##What is Tomàtic Gang?

Hello everyone, we are a group of students from the UPC university (affiliated center CITM). Our goal is to make a tribute to that iconic 80s game called Ms. Pac Man, so we will create our own version of it.

##Introduction

Ms. Pac-Man is an arcade video game from the Golden Age. It was produced by Illinois-based Bally/Midway Manufacturing corporation, the North American publisher of Pac-Man. Ms. Pac-Man was released in North America in January 1982, and is one of the most popular arcade video games of all time. This popularity led to its adoption as an official title by Namco, the creator of Pac-Man, which was released in the United States in late 1980. Ms Pac-Man introduced the first female protagonist of videogames, new maze designs, and several other improved gameplay changes over the original Pac-Man. Ms Pac-Man became the most successful American-produced arcade game, selling 115,000 arcade cabinets. Wikipedia - MsPacMan   

##Version 1.0

Added levels 3 and 4 and removed levels 1 and 2.     
Added Module Score that shows the current score and the max score of every session.     
Added a coin system that only allows player to play if he has coins remaining.     
Added some more sounds and musics.    
Edited ghosts so they move as similar as possible to the original game.   
Things ghosts don't do in our game but they do in the original:    
- Orange ghost: when Ms Pacman eats a superpower pill this ghost doen't run away from her.   
- Pink ghost: when Ms Pacman faces him this ghost doesn't change his direction.   
- Red ghost: this ghost doesn't wait before starting to chase Ms Pacman.   
- Blue ghost: this ghost's behaviour is the same as the red's.   

Things that aren't the same as in the original:   
- Timings and speeds aren't exactly equals.   
- When the player eats a ghost it gets teleported back to its spawn spot rather than making its way to it.   
- Score caps at 9999 points.   
- The game doesn't spawn any fruits.   

Relevant fixed bugs:   
- Ghosts behaviour followed a certain pattern (the blue ghost would disappear to the top of the screen after having died once) -> when they died their stats didn't reset.   
- Pink ghost wouldn't continue to move after meeting an intersection -> there was a problem with the pixel calculations.   
- Player could eat the same ghost twice or more with the same super power pill -> ghosts didn't have any variable that allowed the game to know if they had already been eaten.    
- Player would sometimes die when walking across certain spots of the map -> some ghost colliders didn't get unabled and they remained in their last position.   
- Sometimes ghosts would get stuck in tunnels -> there was a problem with pixel calculation.    
- The game didn't reset properly when playing for a second time -> some variables weren't being resetted properly.   
- The game would crash sometimes -> all modules were missing the Cleanup().

##Version 0.5

Game intro added.    
Level 1 added: Ms Pacman can move through all the level while eating every pill. She will die every time he collides with a ghost. There are 4 of them and they move randomly through the level. Eating special pills will give Ms Pacman the ability to eat them for a few seconds.    
Ms Pacman lives have been set to 3. If player loses all of them he will be sent to the "select players" screen.   

##Controls

- use WASD to move across the labrinth.   
- use space to move between certain phases.   
- use 1 to add coins.   
- press F1 to show the colliders.   
- press G to activate God Mode (player can't kill ghosts and he cannot be killed either).     
- press H to activate God Mode (player can kill ghosts and he cannot be killed by them).    

##Group

- (Management) -> Elliot Jimenez https://github.com/elliotjb   
- (Q&A) -> Arnau Morgado https://github.com/morgadoCV   
- (Programmer) -> Albert Llopart https://github.com/albertllopart   
- (Artist) -> Alfonso Sanchez https://github.com/AlfonsoSanchez   
- (Programmer) -> Gerard Gil https://github.com/Gerard346   

*All members in the group have been programming.   
*The game can be played infinitely (potentially).   
