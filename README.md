# Crashed and Deserted
 
 Authors: \<[Aramis Masarati](https://github.com/Aramismas)\>
 \<[Daria Senchylova](https://github.com/Bumblebee2019)\>
 \<[Joseph Mangapit](https://github.com/badminininja)\>

## Project Description
 * We plan on creating  a story driven game where the user has crash landed on an island and is essentially deserted. The user will have to pick choices given which will determine the unique ending for the user based off all their choices throughout the story. We plan to have multiple endings and routes which creates a butterfly-effect story.
 * This game is important because we are all interested in video game development and we want all users to have a fun and unique experience with the game!
 * The languages/tools/technologies we plan to user are:
   * C++ 
 * Input: text from the keyboard where the user will be able to pick different options that will determine their path in the story.
 * Output: text displayed on the command line terminal. (Terminal based game)
 * For our 3 design patterns, we will use Abstract Factory, Composite, and Strategy.
   * Abstract Factory - This will allow us to implement a base Character class which will be the hierarchy for multiple types of characters. Since we have many different characters with similar traits and actions, it will be useful for us to have an abstract class which contains the interface for the characters. The user will have a character selection in the beginning of the game where we will implement Abstract Factory.
   * Strategy - This will allow us to create algorithms for general use in our game which we can constantly refer to despite being in different situations and progression in the game. This covers alot of code so that the user doesn't see what's going on in the backend of the game. The user will be able to use complicated algorithms with a click of a button regardless of their knowledge of the actual algorithm.
   * Composite - this is a useful pattern for a game since we will be using multiple classes and objects similarly. Since the game will have several characters and some powers they inherit from the base class will be similar, a composite pattern is useful when dealing with repeating code. We will also use some child class manipulation methods that the composite will help us implement.

## Class Diagrams
 
 ![ABSDesignPattern](https://user-images.githubusercontent.com/5094397/101873790-74e25a80-3b3c-11eb-9e8d-b673be0be67a.PNG)
 ![stratPattern](https://user-images.githubusercontent.com/5094397/101940998-3a100f00-3b9c-11eb-8dc1-dd0ec5b9bc28.PNG)
 ![SingletonPat](https://user-images.githubusercontent.com/5094397/101873803-79a70e80-3b3c-11eb-89a9-886a5635f624.PNG)

 ## Screenshots
 ![screen1](https://user-images.githubusercontent.com/5094397/101889374-2f318c00-3b54-11eb-9de3-c1e845d83979.png)
 ![screen2](https://user-images.githubusercontent.com/5094397/101889377-2fca2280-3b54-11eb-9fef-46059a88c4e0.png)
 ![screen3](https://user-images.githubusercontent.com/5094397/101889378-2fca2280-3b54-11eb-87b8-c63438aa98f0.png)
 ![screen4](https://user-images.githubusercontent.com/5094397/101889379-2fca2280-3b54-11eb-8f31-a1a80c5959c2.png)
 ![screen5](https://user-images.githubusercontent.com/5094397/101889380-3062b900-3b54-11eb-8095-7cbe7f5fd04a.png)
 ![screen6](https://user-images.githubusercontent.com/5094397/101889382-3062b900-3b54-11eb-9095-daba4e748e15.png)
 ![screen7](https://user-images.githubusercontent.com/5094397/101889386-30fb4f80-3b54-11eb-9e9a-74c826850fb1.png)
 ## Installation/Usage
 * First, clone the repository
 * Open the terminal and cd into final-projct-amasa004-dsenc002-jmang018 
 * Then, run cd ./CrashedAndDesertred/CrashedAndDeserted 
 * Run the following commands in the terminal: 
 * cmake3 .
 * make
 * ./game

 ## Running with Docker
 * Prefer not to install a C++ toolchain? A Docker setup is included that builds the game and its tests in a container — you only need [Docker Desktop](https://www.docker.com/products/docker-desktop/).
 * From the repository root:
   * Play the game (interactive): `docker compose run --rm game`
   * Run the unit tests: `docker compose run --rm test`
 * The first run builds the image (compiles the game and tests); later runs reuse it. Verified to build and pass all 74 unit tests on Ubuntu 24.04 with g++ 13.

 ## Testing
 * To ensure that the large number of classes we implemented is error free, we used googletest. With the help of the googeltest, we created unit tests and tested every single function in our classes and verified that they passed their tests through running the test executable.
 ![unittests](https://user-images.githubusercontent.com/5094397/101940987-367c8800-3b9c-11eb-96da-a9fb61f6b56f.png)
 * Main Function Tests
   * Selecting Human Mage
     ![HumanMage](https://user-images.githubusercontent.com/5094397/101886244-11fabe80-3b50-11eb-953d-7d29b90c0715.png)
   * Selecting Animal Mage
     ![AnimalMage](https://user-images.githubusercontent.com/5094397/101887694-10ca9100-3b52-11eb-88ea-7f9abb01607d.png)
   * Selecting Animal Warrior
    ![AnimalWarrior](https://user-images.githubusercontent.com/5094397/101888011-7c146300-3b52-11eb-9750-bff1cf259a9e.png)
   * Selecting Human Warrior
     ![HumanWarrior](https://user-images.githubusercontent.com/5094397/101888016-7cacf980-3b52-11eb-87f5-a7d4f7c65dfd.png)
   * Battle Scenes
   
     ![Battle1](https://user-images.githubusercontent.com/5094397/101888022-7e76bd00-3b52-11eb-8452-a84a3e33e143.png)
     ![Battle2](https://user-images.githubusercontent.com/5094397/101888028-7f0f5380-3b52-11eb-9a9d-338e289572f9.png)

 
