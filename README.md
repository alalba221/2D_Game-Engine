## How to run it
- chmod +x GenerateProject.sh
- chmod +x premake5.lua
- ./GenerateProject.sh
- make
- cd bin/Debug-linux-x86_64/Alalba_6160/
- ./Alalba_6160


## Summary
  * ### Sprite and Texture source 
   
    [ Super Mario Tileset ](https://www.spriters-resource.com/nes/supermariobros/sheet/52571/)
    
  * ### Sprite functionality class (2 pts)
		Since I learned about the Entity-Component-System architecture and immediately tried it out in this project, each animatable entity would has a AnimationComponent structure to manager different animations under different states. The class AnimateSys should control the speed and cycling of animation.
  * ### Sprite animations (1 pts)
    - STAND: the idle state
    - RUNNING: pressing A or D
		- JUMP: press W
		- DRIFT: When the speed is in the opposite direction to the acceleration
  * ### tile handler: Class MapSys (2pts)
  * ### render the viewable set of tiles from the map based on your camera (2pts)
  * ### Adding collectibles (2pts)
	
	* ### software organization and documentation (1 pts)
		Based on your feedback previously, I organizied the filespace and put ECS architexture into this project
## Others 
- [X] Add Y axis collosion detection and response.
- [ ] Add Y axis collosion detection and response.