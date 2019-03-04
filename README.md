

          Ralph.IV 
      by Tom Watters 
      
- Python Script uses open CV to track faces, referancing their postion against the 0,0 position of the camera, 
  this then sends the X and Y offsets via serial, where the Cpp script maps and transfers the positions to the Servos
 
- in future itterations id like to add full chassis to rotate at a certain threshhold

- AMT102-V file is for use with the Rotary encoders used for closed loop feedback, this libary is in development as i work out   what embedded functionality it needs. 

- the L298D file is a framework in development for utiilizing the l298 motor driver, for use in controlling the motors, i plan   to write a library with closed loop control. 

- the mbed.h file is a part of mbeds web compiller and incorporates basic functionallity of the NODE board implemented.
  i opted to use this to not get bogged down writing the simple stuff, and start problem solving! 


  -------   PLANNED IMPROVEMENTS   -------
  
- ROS support is intended for future updates. 
- i also plan to implement a kinectV2 instead of the webcam currently, as a way of using 3D data for future SLAM and object     avoidence protocols 
