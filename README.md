# Collision and Heat Avoidance Robot
My first proper project in Arduino! I made this to learn more about the language and venture deeper into electronics and robotics.  
I'm still working on it and plan to improve and optimise the code and add new features.
# Components Used
I used the following components to make the robot. If you cannot obtain them, use TinkerCAD.  
However, I feel learning hands-on is a better approach to learning!  
Parts Used:
1. **Arduino UNO.**
2. **L298D motor driver shield.** (You can use the IC too, but using the shield saves quite a bit of time.)
3. **HC-SR04** - Ultrasonic distance sensor.
4. **KY-013** - Analog temperature sensor Module. (Uses a thermistor calibrated at 10kΩ. Based on the Steinhart–Hart model.)
5. Jumper cables and a soldering iron kit.
6. A breadboard and a breadboard power supply to power the motor driver. _(Can be substituted with a battery)_
7. A metal frame for the robot and 2 standard rubber wheels.
8. 2 DC motors, with a max rotation speed of 200 rpm.
# Libraries Used:
* [AFMotor.h](https://learn.adafruit.com/afmotor-library-reference)
# Sections of the Code:
The source code for the robot has been broken down into sections, and here I will explain the logic of each portion.
## int dist()
This function finds out the distance between the obstacle (if within range of the sensor) at any moment in time. It sends the data as an integer to the main function, **loop()**.
For a detailed explanation on how this works, click [here.](https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6)  
## double temp()
This function uses the KY-013 Module and gets temperature data from the surroundings. It then returns the value as a floating-point number to loop(). For an in-depth explanation, click [here.](https://arduinomodules.info/ky-013-analog-temperature-sensor-module/)
## void forward()
This function orders the robot to move forward. The code snippet is given below. It uses functions from the AFMotor.h library, so make sure to read the documentation to understand it fully.
```leftm.run(FORWARD);
   rightm.run(FORWARD);
   leftm.setSpeed(255);
   rightm.setSpeed(253);
   ```
Here, leftm denotes the left wheel, and rightm indicates the right wheel.  
  
  
You must have noticed an interesting thing - Both the motors have a slight offset in their speeds.  
  
  
Strangely, setting the same speed values for both motors created unequal torques in both of them, causing the robot to move slightly to the left. Hence, I had to use a lower speed for my right motor.  
This is however, luck-dependent and you might not need to add this offset.
## void left()
