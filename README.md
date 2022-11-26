# OpenScout

## Initial Project Thoughts

The initial project aim is to extend the current Open Scout. Extend means improve in any way deemed fit but with the idea of integrating ROS.

## Initial OpenScout Evaluation

Time was taken to appreciate and understand the previous iteration of the project which was undertaken my the previous MSc RAS cohort 3.


OpenScout currently has a main Lazy Susan version and a spin off version without a Lazy Susan. It is this spin off version that was evaluated.

### Evaluation Comments

- Many wires use Dupont cables with connectors. These connectors make extending wires simple and qucik, how-ever the trade off can been seen in that the sockets wear and open up, making the connection high resistance or prone to disconnect with movement or even vibration.
- A similar issue can be seen where these Dupont cables plug into the Arduino, some, and increasing more, become loose and cause intermittent problems. When handling one cable just touching another cable can cause the pin to lift out of the Arduino header connector.
- The position of the Ardunio is such that it is as far away as it could be from the battery and motor drivers.
- When powered up, intermittently the wheels, either one or more, will turn (motors are signalled to turn). 
- The circuit breaker, that is a safety feature as well as being an on/off switch is an AC breaker.
- The height of the OpenScout chassis is the same as the width.
- The brackets that connect the motors to the chassis rely upon being fixed very tightly to keep alignment of the wheels, one or two of these brackets have come loose.
- There is a 12v battery but no means of charging the battery.
- The clear acetate bottom and top shelves are not fixed at the corners which exposes flexing in the shelf.
- Since OpenScout had the Arduino and battery removed on first inspection, it was necessary to connect all wires to the Arduino. This exposed the fact that this proceedure was very time consuming since the circuit diagram had to be followed for each wire. Mistakes were made. Replacing the Arduino during testing or for repair is expected to be a common occurance.

### Initial Project Plan

- Replace all extended cables / wires with a single length of cable. To remove intdermittent faults.
- Shorten wires, bring Arduino down from top shelf to bottom self so that all baseline feature electronics are on same shelf. Short wires mean less weight (not too much of an issue but a principle in that you do not want to be expending energy moving unnecessary weight - helps conserve the battery, good for the planet).


