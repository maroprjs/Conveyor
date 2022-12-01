# Conveyor
Controllino Code (Arduino Compatible) to control vetter conveyor belts via serial port or udp. 

The IP address defined in "Defines.h". Server Address needs to be adjusted.
 
The server based on NodeJs, found on "server"-branch above or StatusDisplay branch, which runs on the Raspberry. 

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
 
 Extended command set:
 In order to be able to change the IP setting without reprogramming the controllino, those settings are stored in EEPROM and its values can be changed with an extended command set via serial interface or UDP interface. 
 To activate the extensions send captial 'X' either via serial console or via UDP. The three status lights will start blinking at the controllino. 
 following commands can be sent:
 
 "factory reset" - it will initialize the EEPROM to it's default (all bytes to 255) and read the OWN_IP, UDPSERVER_IP and UDPSERVER_PORT from the definitions of the original used Defines.h and write them into the EEPROM 
 "set own ip" - sets the controllino's own ip addresses and stores the value in EEPROM. The value "0.0.0.0" means dhcp in use.
 "set server ip" - will save new IP address for the udp server in EEPROM and take it into use
 "set server port" - will save the receiving port for the udp server in EEPROM and takes it into use
 
 For the latter three commands: First send the command (with ot without space) , e.g "setownip", will wait for entry of IP address in string format (but there is no indication) e.g. send "192.168.0.111".....after that the controllino IP e.g. would have address 192.168.0.111 and the status lights stop flashing.
 If you made a  mistake, the "factoryreset" via serial interface will revert to initial configuration. 
 
 
