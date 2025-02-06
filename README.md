# NFE_FixedWing
## _A unique aproach to fixed wing flight stabilization based on NFE_Silverware_

Making model airplanes behave themselves for a better piloting experience with inexpensive hardware.

- Currently supporting a standard 4 channel aircraft.
- Uses simple hardware - Stm32F0 Brushed Flight Controller is suitable with  only minor modifications to drive servos.
- Serial Receiver DSM, IBUS, SBUS, CRSF or SPI connected XN297 or NRF24L01 Bayang protocol
## Flight Modes
- Sport Mode - Direct passthrough of pilot controls overlayed on top of independent flight stabilization.
- Level Mode - Hands off self-righting behavior with bank angle limitation on roll and pitch attitudes suitable for new pilots, kids, or emergency recovery.  WARNING - This is a work in progress and does not turn very well yet for bank and yank.  Suggested radio mixing of yaw to roll stick decreases turning radius but still may turn poorly on non 3d type airframes.  Additional development pending
- Manual Mode - Direct passthrough of pilot controls with selectable high/low rates and expo applied in firmware.

## Features
- Compatible with trim inputs - No need to land and mechanically center the defelction on control surfaces, trim the aircraft for level flight on the transmitter as needed.  Newly trimmed centerpoints will be automatically sensed and adopted by firmware.
- Excellent tracking - Optional automatically engaging heading hold when pilot is "hands off" controls.
- Simple Radio setup - Auxillary switchable expo and low rates handled inside firmware.
- Safer Failsafe - Automatically engaging Level Mode if radio signal is lost during flight
- Advanced Tuning and Configurations - Stabilization gains for each axis are adjustable in flight using an auxilliary channel.
- Adjustable PWM Frequency - Update standard servos at 50hz or digital servos at 500hz


The intention of this project is to re-use inexpensive and often neglected brushed tiny whoop flight controllers to drive servos in a "fixed wing" airplane application.  This project's development will focus mainly on two flight modes:  SPORT and LEVEL.  'Sport Mode' is unique in that it directly passes through pilot stick commands to the servos to ensure that the "feel" of the aircraft is not muted by forcing the system response to adhere to predefined axial rates of rotation.  The stabilization algorithm is overlayed on top of pilot controls and works to constantly remove any uncommanded motion without fighting against commanded motion.  'Level Mode' is being developed as a beginner flight mode suitable for inexperienced pilots with gentle predictable controls suitable for teaching children to fly or for recovery from emergency situations.

> To modify a 1s brushed tiny whoop flight controller for use with this firmware:
> 1.  Power the flight controller from a 5v bec sourced from the ESC
> 2.  Solder a 10k resistor between each Motor+ and Motor- pins
> 3.  Connect each servo signal wire to a Motor- pin
> 4.  Sendit

## Discussion of Theory
Current theory of operation for 'Sport Mode' is as follows:  Sticks are always passed through the mixer directly to the servos.  Proportional stabilization assumes a constant setpoint of 0 and only tracks gyro - essentially fighting all craft motion from both stick commands and environment.  Integral stabilization, when selected on, also only tracks gyro instead of error and operates on an auto-centering algorithm .... only allowing I term to accumulate when sticks are less than 1% deflected (auto-centering compensates for pilot trims to sense a new trimmed center point for the stick deflection trigger).  Integral sum is disallowed to accumulate more when sticks are beyond 1% deflection, and is relaxed to zero upon any quickly changing stick input using a transient windup protection algorithm.  Derivative stabilization is tracking setpoint and gyro and the stick accelerator & transition features are nicely balanced against the P-gain's attempt to fight pilot stick inputs.  The end result when summed together is direct control with stabilization that isn't fighting pilot commands aided by the assistance of the I-term's heading lock effect which learns when you are hands off the sticks and fades out when you are hands on the sticks.  The system is very agnostic to trims on the radio and doesn't require landing for a total mechanical linkage rework to center control surfaces should an airplane require in flight trim.


https://www.youtube.com/watch?v=x2uHhEAmMuM&t=98s




## Additions for Analog Aux channels  - brianquad Notes

This option (controlled in config.h) adds support for Analog Aux channels to control certain pre-programmed features. These are intended to be used with a transmitter with knobs/sliders to easily alter parameters while flying. These are controlled by #define lines in config.h. Enable these features by uncommenting the "#define USE_ANALOG_AUX" line. Commenting that line disables all analog aux channels at the compiler level, meaning they do not make the built firmware bigger or slower than it was before.

Initially, these features include:
1. Analog Rate Multiplier (ANALOG_RATE_MULT)
   - Use a tranmitter knob to control your rates to help find your sweet spot without flashing in between
   - Set your MAX_RATE and MAX_RATE_YAW to the highest rate you might want
   - Use the assigned knob to adjust beween 0 and 100% of that rate in a linear scale
     - Putting the knob at its middle point will give you half of your MAX_RATE
2. Analog Max Angle for Level mode (ANALOG_MAX_ANGLE)
   - When in Angle/Level mode, the maximum angle the quad is allowed to tilt (controlling your max speed, etc.) is set by the LEVEL_MAX_ANGLE define
   - When enabling ANALOG_MAX_ANGLE, the LEVEL_MAX_ANGLE define is ignored
   - The knob controls the maximum angle from 0 to 90 degrees in a linear scale
     - Putting the knob at its middle point will give you a maximum angle of 45 degrees
3. PID adjustments (ANALOG_RP_P, etc.)
   - Assigning a knob to one of these defines lets you alter that PID setting from 0.5X to 1.5X of the current setting in pid.c
   - Each of the P, I, or D for Roll, Pitch, and Yaw can be selected in config.h, or Roll and Pitch P, I, or D can be selected together on one knob
   - The PID adjustments can be saved, just like the classic Silverware gesture PID adjustments. To save a new value, use the Down Down Down (DDD) gesture to write the current PID values to flash (including your new one(s)) and re-center your adjusted values. This means to keep your new value after saving, you must re-center your knob/slider.

These initial features are mostly meant to start a conversation on how Analog Aux channels could be used. For example, I'm sure there are better ways to do live PID adjustment with a couple of analog knobs!

###How do you access/assign analog channels? What channels can be used?

For Sbus and DSM, you can assign any of the channels to use as analog aux channels.

For Bayang, you can use a modified version of the Bayang protocol I've made to the Multiprotocol Tx and Deviation Tx firmware that adds two 8-bit analog channels to the protocol.

The Multiprotocol module uses channels 14 and 15 for these analog channels. Set the "Option/Telemetry" value for the Bayang protocol on the Taranis to 2 or 3 (2 to get only the analog channels, 3 to get both Telemetry and the analog channels).

Deviation uses channels 13 and 14. Enable the Aux Analog option for the Bayang protocol.

For both the Multiprotocol module and Deviation, Silverware will not bind with a transmitter that does not have matching options (both Telemetry and Analog Aux channels).

These modifications can be found on the analog aux branch in my forks on GitHub (for now, you _must_ select the branch rather than master):
	https://github.com/brianquad/DIY-Multiprotocol-TX-Module/tree/bayang-analog-aux
	https://github.com/brianquad/deviation/tree/bayang-analog-aux

####How to use Trim Switches for Silverware Analog Aux channels in Deviation
Example:

1. Say you want to assign the LV (left vertical) trim switch to drive the radio channel 11 as if it were a pot, each click driving the pot in one direction or the other, click up to increase and click down to decrease.

2. Go into the Model Menu/5.Trims menu and set the LV trim to Ch11, so replace whatever-is-there (probably throttle but depends on what mode you fly) with CH11 i.e. it should look like: Ch11/step size/TRIMLV+. You can highlight throttle/whatever-is-there and hit enter to get into the submenu. Set Ch11 and set Trim Step to 10. this gives 10 clicks up and 10 clicks down for full range +100 to -100. Save it (highlight Save and press and hold the Enter button).

3. Go into the MIXER menu and find CH11, set the mixer type as "simple", Src is "none", curve is 1-to-1, scale is 0 and offset is 0. Save it. 

4. Check the radio output in the Transmitter Menu/Channel Monitor, you should see the CH11 output following the trim switch, you should see the Ch11 output going from -100 to +100 in steps of 10.

