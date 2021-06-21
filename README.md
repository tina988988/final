# final
## About
We use OpenMV to follow the line, and modify the direction of the car if it goes away from the line. Then it detects the Apriltag by OpenMV. BBcar follows
the line until its distance from the Apriltag is about 6.5cm. Then BBcar will turn right and follow another line. It will stop until it detect another
Apriltag.
Xbee to send what's BBcar is doing right now(3 steps in total).

## Build with
C++ Python

## Equipment
B_L4S5I_IOT01A notebook XBee PING BBcar OpenMV H7 Plus board

## Display
Show what BBcar is doing right now.

## Result
BBcar follow the line -> Apriltag -> follow the line -> Apriltag -> stop
