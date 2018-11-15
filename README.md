
<img src="https://github.com/bsobocki/BitwaOTortuge/blob/master/images/title.jpg" />

# Bitwa O Tortugę
A computer version of the board game "Bitwa O Tortugę" by Madoka Kitao and Hiroki Kaneko.

Project for a programming course written in C++.
## How to run 
1) download repository
2) open the "BOT" folder
3) run "BitwaOTortuge.exe"

All files available in the "BOT" are necessary to run!

## Rules of the game

<img src="https://github.com/bsobocki/BitwaOTortuge/blob/master/images/pirate.jpg" align="right" width="250"/>

### pawn
  
Every pawn has:
  - two sides: 
    * front with visible ship,
    * reverse with sea waves,
  
<img src="https://github.com/bsobocki/BitwaOTortuge/blob/master/images/spanish.jpg" align="right" width="250"/> 
   
  (Image 1.1)

  - value, 
  - color,
  - possible directions of movement. 
  
  (Image 1.2)
  
Ships with black sails belong to the pirate fleet and with red - to the spain fleet.

At the beggining of the game every pawn is randomly set and reversed.

### move

Every move can be just one of activities:
  - When pawn is reserved:
    * inversion the pawn and setting it in any position,
  - When pawn is exposed:
    * turn to the left or right by 90 degrees,
    * move the pawn according to the dots on it
    
 Player can move his pawn on:
  - empty field,
  - field with reversed ship,
  - field with exposed ship of opponent (then the ship is sunk and the player score increase by the ship value)
    
 (this description will be completed soon! :) ...)
