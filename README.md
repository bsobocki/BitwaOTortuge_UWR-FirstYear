
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

### goal of the game

The player must get 7 points which can get by sinking ships of his opponent.

The ship is sunk when enemy fleet moves onto it.

<img src="https://github.com/bsobocki/BitwaOTortuge/blob/master/images/pirate.jpg" align="right" width="250"/>

### ship card
  
Every ship card has:
  - two sides: 
    * front with visible ship,
    * reverse with sea waves,
  
<img src="https://github.com/bsobocki/BitwaOTortuge/blob/master/images/spanish.jpg" align="right" width="250"/> 
  - value, 
  - color,
  - possible directions of movement.
  
Ships with black sails belong to the pirate fleet and with red - to the spain fleet.

At the beggining of the game every card is randomly set and reversed.

### move

Every move can be just one of activities:
  - When card is reserved:
    * inversion the card and setting it in any position (1),
  - When card is exposed:
    * turn to the left or right by 90 degrees,
    * move the card according to the dots on it
    
 The player can move his card on:
  - empty field,
  - field with reversed ship,
  - field with exposed ship of opponent (then the ship is sunk and the player score increase by the ship value)
    
 The player can't move his ship on inverted card of his fleet.
 
 The Player 1 starts the game through choosing one card and doing activity (1).
 
 ### end
 
 The game ends, when one of the players scores 7 points (values of ships) or doesn't has any possibility to move. 

## Control
<img src="https://github.com/bsobocki/BitwaOTortuge/blob/master/images/directions.jpg" align="right" />

The player controls through a keyboard and a mouse:
  - to choose a card has to click on it by left button
  - to rotate a card has to click left or right arrow
  - to move a card has to click buttons on numeric keypad 
  
  (acording to the direction of the dots on card -- Image 1.3)
  
## Important informations
The author of the code is me, Bartosz Sobocki, but I'm not the author of the graphics, the game and its rules.

The author of the illustrations: Maciej Szymanowicz

The game authors: Madoka Kitao, Hiroki Kaneko

The author of the instruction used to make this descrioption of the game: Przemysław Karkosa

Graphic and DTP development of this game: Cezary Szulc.
