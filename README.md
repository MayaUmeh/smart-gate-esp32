Smart Gate Control System (ESP32)

An automated gate that opens when someone approaches and can be opened manually with a button. Built in C++ for the Computing Things (IoT) module at the University of Hertfordshire.


What it does
Motion opens the gate: when the PIR sensor detects someone, the servo swings the gate open to 90°.
Button override: pressing the pushbutton opens the gate manually.
Auto close: the gate closes by itself after 10 seconds with no new activity.
Smart extend: if someone is still there (new motion or a button press) while the gate is open, the 10 second timer restarts, so the gate never closes on them.
Hardware and wiring
Part	ESP32 pin	Purpose
Servo motor (signal)	GPIO 18	Opens and closes the gate
PIR motion sensor (output)	GPIO 23	Detects people approaching
Pushbutton	GPIO 19 (internal pull up, other leg to GND)	Manual override
How the code works
Non blocking timing with millis(): I used millis() instead of delay(), so the ESP32 keeps checking the sensor and button the whole time the gate is open. With delay(), the board would freeze and miss new events.
Edge detection on the PIR: the code reacts only when the sensor changes from LOW to HIGH, not every loop while it stays HIGH, so one person triggers one event.
Button debouncing (50 ms): physical buttons "bounce" and can register several presses from one push. The code only accepts a button state once it has been stable for 50 ms.
Spam protection: an extendUsed flag stops the serial monitor being flooded with "extending time" messages while someone holds the button or keeps moving.
Serial logging: every event (PIR triggered, opening, extending, closing) is printed at 115200 baud, which made testing and debugging much easier.
Testing

I simulated the full circuit in Wokwi before building it, then tested each behaviour:

Test	Expected result
Trigger the PIR sensor	Gate opens to 90° and "Gate Opening" is logged
Wait 10 seconds with no activity	Gate closes to 0° and "Gate Closing" is logged
Trigger motion while the gate is open	Timer restarts, gate stays open
Press the button	Gate opens manually
Hold or tap the button rapidly	Debounce stops false triggers

Each test was checked against the serial monitor output, which logs every event.

Tech

C++ · ESP32 · Arduino framework · ESP32Servo library · Wokwi

