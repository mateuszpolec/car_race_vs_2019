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

- [x] Created an empty git repository for game
- [x] Create an empty SFML project
- [x] Created a basic connect with API for network playing 
- [x] Move project from VS Code to VS 2019 enviroment
- [x] Created a way to pass authentictaion token from APIConnector to Player Builder Class
- [x] Created test way to move player on board
- [x] Created a class for saving ang getting token from file
- [x] Made a first racing map
- [x] Added tmlxlite to project for map loading
- [x] Included all libaries needed for map loading
- [x] Reworked structure of code - headers and cpp files.
- [x] Loaded map into the game
- [x] Added m_ prefix for members of classes
- [x] Override sfml_layer_loader assign operator
- [x] Created a class for rendering map
- [x] Created a class for Player Camera
- [x] Refilled documentation
- [x] Made it possible to move player with W, A, S, D
- [x] Moved main CPP and Main SFML features to classes

RAPORT II (15.11.2020)

- [x] Created a starting line for player
- [x] Created a functionality for handling what is the current lap
- [x] Moved all event block tiles to one png file, and TSX files to one file
- [x] Loadding the enemy texture and object into the game
- [x] Added #ifndef, define and endif statement for preprocessor to avoid collisions and class redefinition error.
- [x] Added bezier curve for enemies track line
- [x] Created a functionality for following the line by enemy

RAPORT III (22.11.2020)

- [x] Created testing method for drawing bezier curve on map
- [x] Created a vector in enemy class for handling points to follow
- [x] Create an normal acceleration for enmey 
- [x] Added documentation for new methods and classes
- [x] Fix spelling mistakes in project
- [x] Move createTrack to enemy.cpp
- [x] Created separate line to follow for each enemy
- [x] Extend current lap with functionality checking player chekpoints reached
- [x] Rework the Bezier Curve to work for all enemies, not only test object

RAPORT IV (20.12.2020)

- [x] Removed commented code from project
- [x] Filled the documentation for new lines of code
- [x] Changed all of constructor to member init list
- [x] Add s_ prefixes for all static variables
- [x] Modified the grass friction
- [x] Created a collision between map and player sprite
- [x] Created a text telling nickname of player/enemy above sprites
- [x] Created new map, and adapted enemies to race at it

RAPORT V (29.12.2020)

- [x] Created a time measurment for player, enemy and global
- [x] Create a text manager for qualification round
- [x] Created a function that can freeze everyone in game
- [x] Changed some useless OOP code to Functions
- [x] Created a timer for start of each round
- [x] Added lap counter for enemies
- [x] Created a function to count how mainy points has enemy done
- [x] Created an starting places points
- [x] Removed duplicates from starting places points
- [x] Created a gameplay system for qualification round
- [x] Refractored all names of classes and headers to "one family"
- [x] Refractored the way of changing max velocity for objects on race track
- [x] Repaired all bugs with player object and enemy object
- [x] Changed the timer to int precision
- [x] Complete documentation of new functions
- [x] Gameplay system for main race round
- [x] Created a const pixel size in options
- [x] Removed unneccesary code
- [x] Created simple HUD for the game

