 # Caravan-battery-controller
This project controls two caravan batteries of 100Ah/13.4v to support eletric power when the caravan i parking without connection to online 220v power line. In addition the project controls charging the batteries when the caravan is running or is connected to a 220v power line. 
There can occur problems with the batteries due to overcharging or other failures when one cell of the batteries is failing. The other battery or the charger will then try to charge the failed battery, genereating heat and dangerous gasses that can result in overheating and fire or emit toxic gasses. This state is not likely to happend if the two batteries are produced in the same production series. Other configuration of the two batteries can more likely result in dangerous malfunctions. 
In this project a control box in the battery compartment watches the current, voltage and temperature of each battery. In addition gas level for toxic gasses is monitored. If any failure is detected, the faulty battery is disconnected.
##Battery monitoring
Each battery is monitored for voltage, current and temperature. If any faiure is detected, the battery is disconnected by a relay. The battery can later be reset manually from a connected online monitor.
##WiFi connection
The controller is supporting a WiFi connection to a predefined WiFi SSID router. If no router is found, the controller estables its own router gateway.
## Watch panel
A battery powered watch panel with a 20 character 4 line LED alpnumeric display show alert contiions. In addition the panel also is able to read the parametres from the controller and can reset a battery failure conition.
## MQTT communication
The controller also has a MQTT communication ability to a watch panel configured by Node-Red. A connection is then established from the controller to a MQTT server which can communicate over the Internet of Things network.
## Nextion displayed montior. 
A second monitor using Nection display is also made, to have a second montor available at another location.
## Pascal montor admin unit
A WiFi pascal  program unit is able to configure, calibrate and exteded montior the controller.
