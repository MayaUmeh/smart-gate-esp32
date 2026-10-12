Smart Gate Control System (ESP32)

An automated gate that opens when motion is detected and can be overridden with a pushbutton. Built for the Computing Things (IoT) module at the University of Hertfordshire.


How it works
A PIR motion sensor detects someone approaching the gate.
The ESP32 reads the sensor and drives a servo motor to open the gate.
After a set delay with no motion, the gate closes again.
A pushbutton gives a manual override.
Hardware
Part	Purpose
ESP32 dev board	Microcontroller running the logic
PIR motion sensor	Detects people approaching
Servo motor	Opens and closes the gate
Pushbutton	Manual override
Testing and debugging

I simulated the full circuit in Wokwi before building it, then tested each behaviour (motion opens the gate, timed close, button override) and refined the logic through structured debugging. The design, test cases and evaluation are in the technical report in this repository.

What I learned
Writing embedded C++ that reacts to real time sensor input
Testing in simulation before touching hardware
Documenting design decisions and test results clearly
Tech

C++ · ESP32 · Arduino framework · Wokwi
