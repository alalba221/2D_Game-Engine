## How to run it
- chmod +x GenerateProject.sh
- chmod +x premake5.lua
- chmod +x vendor/premake5
- ./GenerateProject.sh
- make
- cd bin/Debug-linux-x86_64/Alalba_6160/
- ./Alalba_6160

## Bugs
- To restart the game , double click the R buttom
- When changing the text content, We cannot just change the content of the textcomponentneed, we need remove the textcomponent from that entity and attach a new one on it.  That's weired
- some dirty work in score system.
- Need more functions on entity searching by tag

## Controls:
- Press left mouse button to place a still puck
- Hold left mouse button to move the puck
- Press and hold right mouse button to adjust the shooting angle
- Press space to shoot the puck
- Left click the screen after all the pucks stop moving to reach end screen.
- Press R to reset the board and play again.

## File Structure:
- Images and ttf are in the asset folder
- Source files are in the Alalba_6160/src folder
- In the next nested subfolder you have code split into SDL interfaces, Rendering files, and core classes.

## Program Description:
- This program uses SDL tools and the Entity Component System to create a shuffleboard simulator.
- This game loop allows for a player to use the mouse and space bar to launch multiple pucks
across a game board. The physics engine handles the unique puck interactions. We also
have added an in-game UI to show things like remaining pucks, score, and strength 
through TTF. Also, start and end screens are present.

## Future
We got it done!!!!, but we still will come back to this!!

## Final
Thanks to
- Dillon Ranwala <dranwal@g.clemson.edu> 
- Stuart Saletan <ssaleta@g.clemson.edu>


