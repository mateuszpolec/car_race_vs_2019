# Car Race Project
Project is on going process for my University Classes - Project in C++ Language

## 1. Idea

- Create API for handle information about player, map, auth tokens.
- Create Multiplayer 2D Game, where players can compete with each other on diffrent maps.
- Whole project is based on Racing Games ideas, where player will have to take three laps and end whole race on first position to win.

## 2. Development Plan

With Python, Django and Django REST API Libary build an API for handling real time informations about players. Test everything with pytest libary.

With C++ (don't know what version yet) and SFML 2.5 libary (using Networking an Graphics tools) create game.

## 3. Technologies

**NETWORKING AND BACKEND**: Pytohn, Django, Django REST API, Pytest
**GAME ENGINE**: C++, SFML

## 4. TODO List:


[Trello](https://trello.com/b/abXLx3YW/car-race-game-cpp-project)

## 4. Raports

RAPORT I (01.11.2020)

- [*] Created an empty git repository for game
- [*] Create an empty SFML project
- [*] Created a basic connect with API for network playing 
- [*] Move project from VS Code to VS 2019 enviroment
- [*] Created a way to pass authentictaion token from APIConnector to Player Builder Class
- [*] Created test way to move player on board
- [*] Created a class for saving ang getting token from file
- [*] Made a first racing map
- [*] Added tmlxlite to project for map loading
- [*] Included all libaries needed for map loading
- [*] Reworked structure of code - headers and cpp files.
- [*] Loaded map into the game
- [*] Added m_ prefix for members of classes
- [*] Override sfml_layer_loader assign operator
- [*] Created a class for rendering map
- [*] Created a class for Player Camera
- [*] Refilled documentation
- [*] Made it possible to move player with W, A, S, D
- [*] Moved main CPP and Main SFML features to classes

RAPORT II (15.11.2020)

- [*] Created a starting line for player
- [*] Created a functionality for handling what is the current lap
- [*] Moved all event block tiles to one png file, and TSX files to one file
- [*] Loadding the enemy texture and object into the game
- [*] Added #ifndef, define and endif statement for preprocessor to avoid collisions and class redefinition error.
- [*] Added bezier curve for enemies track line
- [*] Created a functionality for following the line by enemy

RAPORT III (22.11.2020)

- [*] Created testing method for drawing bezier curve on map
- [*] Created a vector in enemy class for handling points to follow
- [*] Create an normal acceleration for enmey 
- [*] Added documentation for new methods and classes
- [*] Fix spelling mistakes in project
- [*] Move createTrack to enemy.cpp
- [*] Created separate line to follow for each enemy
- [*] Extend current lap with functionality checking player chekpoints reached
- [*] Rework the Bezier Curve to work for all enemies, not only test object

RAPORT IV (20.21.2020)

- [*] Removed commented code from project
- [*] Filled the documentation for new lines of code
- [*] Changed all of constructor to member init list
- [*] Add s_ prefixes for all static variables
- [*] Modified the grass friction
- [*] Created a collision between map and player sprite
- [*] Created a text telling nickname of player/enemy above sprites
- [*] Created new map, and adapted enemies to race at it

RAPORT V (29.12.2020)

- [*] Created a time measurment for player, enemy and global
- [*] Create a text manager for qualification round
- [*] Created a function that can freeze everyone in game
- [*] Changed some useless OOP code to Functions
- [*] Created a timer for start of each round
- [*] Added lap counter for enemies
- [*] Created a function to count how mainy points has enemy done
- [*] Created an starting places points
- [*] Removed duplicates from starting places points
- [*] Created a gameplay system for qualification round
- [*] Refractored all names of classes and headers to "one family"
- [*] Refractored the way of changing max velocity for objects on race track
- [*] Repaired all bugs with player object and enemy object
- [*] Changed the timer to int precision
- [*] Complete documentation of new functions
- [*] Gameplay system for main race round
- [*] Created a const pixel size in options
- [*] Removed unneccesary code
- [*] Created simple HUD for the game

