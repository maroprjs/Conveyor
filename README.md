# Conveyor
Controllino Code (Arduino Compatible) to control vetter conveyor belts via serial port or udp. 

The IP address defined in "Defines.h". Server Address needs to be adjusted.
 
The server based on NodeJs, found on "server"-branch above. 

/****************************
 * Commands via serial or udp:
 
 *  a - (a)ll on; electronics and motor on with middle speed (and forward dierction at first start after PLC power)
 *  e - (e)lectronics on
 *  x - turn electronics power off
 *  m - (m)otor on
 *  z - turn motor power off
 *  f - (f)orward direction of conveyor (resumes same speed as before) - this is towards camera
 *  r - (r)everse direction of conveyor (resumes same speed as before) - away from cam
 *  o - (o)ff, sets speed to zero and turns off motor power and electronics
 *  0...9 - speed levels, where '0' has no movement and '9' the max speed
 *  p - (p)unainen on = red on
 *  q - red off
 *  k - (k)eltainen on = yellow on
 *  l - yellow off
 *  v - (v)ihrea on = green on
 *  w - green off
 *  b - buzzer on
 *  c - buzzer off*
 */
