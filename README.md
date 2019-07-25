 # Caravan-battery-controller
This project contribute with a solution to control two caravan batteries of 100Ah to support eletric power at a stationary state without connection to online 220v poser line. In addition the project inteded to control charging of the battery when th caravan is running or a 220v dower line is connected. There can occur problem wiht the batteries due to overcharge og other failure when one cell of the batteries is failing. The other battery or the charger will then try ot charge the failed battery with power, genereating heat and by dangerous gasses that can result in overheating an fire and poisiness gasses. This state is not likely to occur if the two batteries are produced in the same production series. Other conmpination of the two batteries can more likely result in dangerous malfunctions. In this project a control box in the battery compartment watch the current, voltage and temperature of each battery. In addition gas level for dangerous gas level is monitored. If any failure is recorded, the faulty battery is disconnected.
##Battery monitoring
Each battery is monitored for voltage, current and temperature. If any faiure is discovered, the battery is disconnected by an relay. The battery must later be reset manually.
##WiFi connection
The controller is supporting a WiFi connection to a predefined WiFi SSID router. If no router is found, the controller estables an own router gateway.
## Watch panel
A battery powered watch panek with a 20 character 4 line LED alpnumeric display show alert contiions. In addition the panel also is able to read the parametres form the controller and can reset a battery failure conition.
## MQTT communication
The controller also has a MQTT communication ability to a watch panel configured by Node-Red.
## Pascal montor admin unit
A WiFi pascal  programmed unit i able to configure, calibrate and exteded montior the controller
