IMGD 3000 
Project 3 - Final

========
 README
========

TEAM: THE VISIONEERS
Gabriel Aponte .............. gaaponte@wpi.edu
Joseph Henry Stadolnik IV ... jhstadolnik@wpi.edu

GAME: STUCK IN SPACE
You are a pilot of a ship stranded in space, under attack from enemy aliens with no fuel left. 
Survive as long as you can against the horde using whatever ammo you can scrounge to power your arsenal of weapons!

CONTROLS:
* AIM: Move Mouse
* SHOOT: Press or Hold Left Click
* CYCLE WEAPON: Press Keys A or D or Scroll Mouse Wheel
* SWAP WEAPON: Press Keys 1-6
* OVERLOAD SHIELDS: Press Space
* QUIT: Press Escape

FEATURES:
-----------
Six Weapons
-----------
There are six weapons the player can freely switch between. Most of them require ammo to use.
* MISSILE: Fire a simple projectile with infinite ammo
* LASER: Fire a fast projectile that pierces enemies
* SPREAD: Fire a wave of 4 projectiles around the target
* BOMB: Fire a projectile that explodes on impact
* PLASMA: Fire a large, slow projectile that passes through enemies
* RAPID: Rapidly fire a stream of small bullets
----------------
Six Enemy Types
----------------
There are six different enemy types the player can encounter.
* BASIC: Moves directly towards the player
* TOUGH: Moves towards the player and takes several hits
* FAST: Moves quickly towards the player
* TRICKY: Moves erratically towards the player
* SWARM: A group of enemies that moves towards the player together
* SHOOTER: Stops at a distance from the player and shoots projectiles at them
--------------------------
Procedural Wave Generation
--------------------------
The game generates waves of enemies using a Difficulty Budget system, where each enemy has a
difficulty cost and a minimum difficulty level it can spawn at. The level of difficulty increases
with every cleared wave, allow more and harder enemies to spawn.
-----------
Leaderboard
-----------
The game keeps track of your highscores (furthest wave survived) across sessions and lets you enter
your name when you get a game over.
---------------
Shield Overload
---------------
As a special defensive ability, the player can pay 15 shield integrity points to destroy all enemies
on the screen. If the player takes damage while out of shield integrity, they get destroyed.
------------
Ammo Pickups
------------
Killing enemies has a chance to drop an ammo pickup. Shooting this will give the player some ammo
of the type indicated by the letter on the ammo pickup. There are systems in place to ensure the 
player can't go too long without picking up ammo of every type, and there is a slowly-increasing minimum number of ammo pickups that will appear each wave.

====================================================================================================
RUNNING THE GAME:
To run the game, extract the .zip and set up its contents as shown below. This is intended to run 
with our version of Dragonfly, which is included in the file. Place the SFML-2.5 folder at the 
appropriate location, open the .sln file in stuck-in-space/vs-2019, and build the program.
You should be able to run it directly from Visual Studio now. As the game is now complete,
utilize the 'Release x64' configurations to build game. This will provide the most performance.
====================================================================================================

FILE STRUCTURE:
The game assumes a directory setup as follows:

Projects/            	Location of Visual Studio projects.
|
+ dragonfly-engine/     Dragonfly Engine content.
| |
| + include/		
| |
| + lib/		
|
+ SFML-2.5/           	SFML directory (version 2.5.*).
|
+ stuck-in-space/       Game content (Source code for game.cpp and other game files).
| |
| + cpp_files/     	Source code for all other .cpp game files
| |
| + header_files/  	Source code for all other header files
| |
| + sounds/            	Sounds used for game.
| |
| + sprites/           	Sprites used for game.
| |
| + vs-2019/           	Microsoft Visual Studio solution files.
| | |
| | + Debug/            Location of .exe that runs in Debug mode.
| | |
| | + Release/          Location of .exe that runs in Release mode.
| |
| - df-font.txt        	Font used by Dragonfly.
