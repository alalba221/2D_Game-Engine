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
    
  * ### Sprite functionality class
		Since I learned about the Entity-Component-System architecture and immediately tried it out in this project, each animatable entity would has a AnimationComponent structure to manager different animations under different states. The class AnimateSys should control the speed and cycling of animation.
  * ### Sprite animations 
    - STAND: the idle state
    - RUNNING: pressing A or D
		- JUMP: press W
		- DRIFT: When the speed is in the opposite direction to the acceleration
  * ### Relationship to Computer Animation (optional) 
    – If it is not obvious how
    your topic relates to computer animation, you should explain it here. 
    
    For Augmented Reality Games, the device has to know its 3D position in the world. This project provides a method of calculating this
    through the spatial relationship between itself and multiple key points. This is an important aspect to implement computer
    animation, virtual reality and augmented reality.
## Goals 
  – You should give a list of final goals, specifying what you hope to 
  accomplish by the end of the semester. Your goals should be as specific as 
  possible
  - Build a map of an `unknown space`. 
  - Locate the `uncontrolled device` within that space.
  - Real-time.
  - Drift-free. 

## Work Breakdown 


- [X] Build programming enviroment on Ubuntu 16.04 
    - [X] OpenCV 
    - [x] PCL: 
      `sudo apt-get install libpcl-dev libpcl-tools`
      Head files of plc will be installed in `/usr/include/pcl-1.7` and Lib files are in `/usr/lib`
      
- [X] Implement a conversion program from 2D images to 3D point clouds
- [X] Extract and match the features in one frame with another, and use these features to estimate the motion of the camera by PnP Ransac algorithm.
- [X] Joint combination of point cloud. 
- [X] Add ability to cope with a video stream.  
- [X] Implement the graph optimization backend to reduces the drift in the trajectory estimate using G2O library. 
- [X] Loop closure. 
- [X] Map Representation
