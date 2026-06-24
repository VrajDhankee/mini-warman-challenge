# Mini Warman Challenge - Robotic Arm
Autonomous robotic arm built for the Mini-Warman Design & Build Competition. 
The system uses a rotating base and a two-segment arm to collect and deposit 
tennis balls into a target bunker, controlled via Arduino.

## My Contribution
- Designed and built the motor control circuit (Arduino + MX-1508 motor driver)
- Wrote all embedded C++ control software, including a modular motor control system
- Replaced unreliable timing-based positioning with bumper switch feedback control

## How It Works
The robot uses three DC motors controlled via an Arduino Uno and MX-1508 PWM 
motor drivers: one to rotate the base, and two to control the angle of a 
two-segment arm (lower and upper).

**Positional control:** The base rotates continuously until a roller switch, 
mounted on the base, is triggered by one of three physical markers positioned 
around the track. This replaced an earlier time-based approach, which proved 
inconsistent due to variability in motor behaviour. Vertical arm movement uses 
timed control, as the required precision was lower for this axis.

**Sequence of operation:**
1. Base rotates to the first marker (meteorite collection point)
2. Arm lowers and angles to collect the first object
3. Base rotates to the second marker
4. Arm collects the second object
5. Base rotates to the drop-off position
6. Arm releases both objects into the target bunker

**Motor control:** A custom `MOTOR` struct pairs each motor's control pins 
together, and a `runMotor()` function handles direction (via positive/negative 
power values) and optional timed duration, allowing both timed and indefinite 
(switch-controlled) motor operation from a single reusable function.

## Tech Used
- Arduino Uno
- C++ (PlatformIO)
- MX-1508 PWM motor driver modules

## Photos
<img width="2048" height="1536" alt="IMG_4788" src="https://github.com/user-attachments/assets/706008f1-7d83-4d36-afd0-d069f214881d" />
<img width="1536" height="2048" alt="IMG_4792" src="https://github.com/user-attachments/assets/6674cbe2-2eff-473f-84bd-94cd636e89f5" />

