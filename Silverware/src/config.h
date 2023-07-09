

 

//**********************************************************************************************************************
//***********************************************HARDWARE SELECTION*****************************************************

// *************DEFINE FLIGHT CONTROLLER HARDWARE
// *************SELECT ONLY ONE 
// *************uncomment BWHOOP define for bwhoop, bwhoop pro, E011C Santa Edition, and Beta FPV Lite Flight Controllers
// *************uncomment E011 define for E011 flight Controller
// *************uncomment H8mini_blue_board for the H8 mini flight controller with blue circuit board
//#define BWHOOP
//#define E011
//#define H8mini_blue_board
#define Silverlite_Brushless
//#define Alienwhoop_ZERO  

// *************It is possible to get a servo signal out of the M- motor pad on a brushed flight controller by inverting
// *************the signal and adding a 10k pullup resistor from M- to 5v+.  Uncomment below if this hardware hack has been performed.
//#define PWM_MOSFET_INVERSION


//**********************************************************************************************************************
//***********************************************RATES & EXPO SETTINGS**************************************************

// *************EXPO from 0.00 to 1.00 , 0 = no exp
// *************positive = less sensitive near center 
#define ACRO_EXPO_ROLL 0.65
#define ACRO_EXPO_PITCH 0.65
#define ACRO_EXPO_YAW 0.65

#define ANGLE_EXPO_ROLL 0.55	//not used yet
#define ANGLE_EXPO_PITCH 0.0	//not used yet
#define ANGLE_EXPO_YAW 0.55		//not used yet

// *************max angle for level mode
#define LEVEL_MAX_ANGLE 70.0f

// ************* low rates multiplier if rates are assigned to a channel
#define LOW_RATES_MULTI 0.5f




//**********************************************************************************************************************
//***********************************************RECEIVER SETTINGS******************************************************

// *************Radio protocol selection
// *************select only one
//#define RX_SBUS
//#define RX_CRSF                                           //Requires tbs firmware v2.88 or newer for failsafe to operate properly
//#define RX_DSMX_2048
//#define RX_DSM2_1024
//#define RX_IBUS
//#define RX_NRF24_BAYANG_TELEMETRY
//#define RX_BAYANG_BLE_APP
#define RX_BAYANG_PROTOCOL_TELEMETRY_AUTOBIND



// *******************************SWITCH SELECTION*****************************
// *************CHAN_ON - on always ( all protocols)
// *************CHAN_OFF - off always ( all protocols)
// *************Aux channels are selectable as CHAN_5 through CHAN_12 for DEVO and through CHAN_13 (but no CHAN_11) for MULTIMODULE users
// *************Toy transmitter mapping is CHAN_5 (rates button), CHAN_6 (stick gestures RRD/LLD), 
//**************CHAN_7 (headfree button), CHAN_8 (roll trim buttons), CHAN_9 (pitch trim buttons)

//*************Arm switch and Idle Up switch (idle up will behave like betaflight airmode)
//*************comment out to disable arming or idle up features ONLY if not wanted.  Other features set to CHAN_OFF to disable

//*************Assign feature to auxiliary channel.  NOTE - Switching on LEVELMODE is required for any leveling modes to 
//*************be active.  With LEVELMODE active - MCU will apply RACEMODE if racemode channel is on, HORIZON if horizon 
//*************channel is on, or racemodeHORIZON if both channels are on - and will be standard LEVELMODE if neither 
//*************racemode or horizon are switched on.
#define ARMING     CHAN_5
#define MANUALMODE CHAN_OFF
#define LEVELMODE  CHAN_6
#define RACEMODE   CHAN_OFF
#define HORIZON    CHAN_OFF
#define PIDPROFILE CHAN_OFF             //For switching stickAccelerator & stickTransition profiles on pid.c page - Keep OFF
#define RATES      CHAN_ON
#define LEDS_ON    CHAN_OFF

// *************switch for fpv / other, requires fet
// *************comment out to disable
//#define FPV_ON CHAN_ON

// *************enable buzzer functionality
// *************external buzzer requires pin assignment in hardware.h before defining below
// *************change channel assignment from CHAN_OFF to a numbered aux switch if you want switch control
// *************if no channel is assigned but buzzer is set to CHAN_ON - buzzer will activate on LVC and FAILSAFE.
//#define BUZZER_ENABLE CHAN_OFF

// *************LLD / RRD Stick Gesture - AUX 1 is currently tied to integral activity in SPORT/ACRO mode.  Uncommented will boot the FC 
// *************with integral inactive and require the RRD for fully stabilized SPORT/ACRO mode with integral.  It is suggested to maiden and
// *************manually trim the plane with AUX1 in the OFF position (gesture LLD) or in manual mode.
#define AUX1_START_ON

// *************ANALOG AUX CHANNELS
//#define USE_ANALOG_AUX
// *************Select analog feature for each channel
//#define ANALOG_RATE_MULT CHAN_14
//#define ANALOG_MAX_ANGLE CHAN_15
//#define ANALOG_RP_P  CHAN_14 // Adjust Roll and Pitch together
//#define ANALOG_RP_I  CHAN_14
//#define ANALOG_RP_D  CHAN_15
//#define ANALOG_RP_PD CHAN_15 // Adjust Roll and Pitch P & D together
//#define ANALOG_R_P   CHAN_11 // Adjust Roll only
//#define ANALOG_R_I   CHAN_12
//#define ANALOG_R_D   CHAN_12
//#define ANALOG_P_P   CHAN_14 // Adjust Pitch only
//#define ANALOG_P_I   CHAN_14
//#define ANALOG_P_D   CHAN_15
//#define ANALOG_Y_P   CHAN_14 // Adjust Yaw only
//#define ANALOG_Y_I   CHAN_11
//#define ANALOG_Y_D   CHAN_15




//**********************************************************************************************************************
//***********************************************VOLTAGE SETTINGS*******************************************************

// ************* Set your lipo cell count to override auto cell count detect logic
//#define LIPO_CELL_COUNT 1

//currently disconnected
#define LEVELMODE_PID_ATTENUATION 0.90f  //could be used to prevent wing rock oscillations in angle modes on roll axis

// *************lower throttle when battery below threshold - forced landing low voltage cutoff
// *************THIS FEATURE WILL BE OFF BY DEFAULT EVEN WHEN DEFINED - USE STICK GESTURE LEFT-LEFT-LEFT TO ACTIVATE THEN DOWN-DOWN-DOWN TO SAVE AS ON
// *************Led light will blink once when LVC forced landing is turned on, blink twice when turned off, and will blink multiple times upon save command
// *************Enter values in volts per cell
#define LVC_LOWER_THROTTLE
#define LVC_LOWER_THROTTLE_VOLTAGE 3.30
#define LVC_LOWER_THROTTLE_VOLTAGE_RAW 2.70
#define LVC_LOWER_THROTTLE_KP 3.0

// *************do not start software if battery is too low (below 3.3v per cell) - only works on 1s lipos
// *************flashes 2 times repeatedly at startup
#define STOP_LOWBATTERY

// *************voltage per cell to start warning led blinking
#define VBATTLOW 3.5

// *************automatic voltage telemetry correction/calibration factor - change the values below if voltage telemetry is inaccurate
// *************Corrects for an offset error in the telemetry measurement (same offset across the battery voltage range)
// *************Enter values in total battery volts.  This is factor is used in all voltage related calculations - ensure your transmitter is not mucking with telemetry scale before adjusting 
#define ACTUAL_BATTERY_VOLTAGE 4.20
#define REPORTED_TELEMETRY_VOLTAGE 4.20

// *************two-point automatic voltage telemetry correction/calibration factor - change the values below if voltage telemetry is inaccurate
// *************Use this method when the difference at the high end is different than the difference at the low end. Corrects both slope and offset of the _assumed_ linear error.
// *************Enter values in total battery volts.  This is factor is used in all voltage related calculations - ensure your transmitter is not mucking with telemetry scale before adjusting
//#define USE_TWO_POINT_VOLTAGE_CORRECTION
//#define ACTUAL_BATTERY_VOLTAGE_LO 3.60
//#define ACTUAL_BATTERY_VOLTAGE_HI 4.20
//#define REPORTED_TELEMETRY_VOLTAGE_LO 3.60
//#define REPORTED_TELEMETRY_VOLTAGE_HI 4.20




//**********************************************************************************************************************
//***********************************************FILTER SETTINGS********************************************************

// *************Filtering for fixed wing airplanes should be somewhere near 20hz
// *************Exactly how many passes of filtering are probably dependent on the hardware filter setting inside the gyro

//#define WEAK_FILTERING
//#define STRONG_FILTERING
//#define VERY_STRONG_FILTERING
//#define ALIENWHOOP_ZERO_FILTERING
#define BETA_FILTERING

#ifdef BETA_FILTERING  //*** ABOVE 100 ADJUST IN INCRIMENTS OF 20, BELOW 100 ADJUST IN INCRIMENTS OF 10, nothing coded beyond 500hz

//Select Gyro Filter Type *** Select Only One type
//#define KALMAN_GYRO
#define PT1_GYRO

//Select Gyro Filter Cut Frequency
#define GYRO_FILTER_PASS1 HZ_20
#define GYRO_FILTER_PASS2 HZ_20

//Select D Term Filter Cut Frequency *** Select Only one
#define  DTERM_LPF_2ND_HZ 20
//#define DTERM_LPF_1ST_HZ 70


#endif




//**********************************************************************************************************************
//***********************************************SERVO OUTPUT SETTINGS**************************************************

// *************pwm frequency for motor control
// *************a higher frequency makes the servos work harder nd is only reccomended for digital servos
// *************in Hz (set between 50 and 400)
#define PWMFREQ 50

// *************torque boost is a highly eperimental feature.  it is a lpf D term on motor outputs that will accelerate the response
// *************of the motors when the command to the motors is changing by increasing or decreasing the voltage thats sent.  It differs
// *************from throttle transient compensation in that it acts on all motor commands - not just throttle changes.  this feature
// *************is very noise sensative so D term specifically has to be lowered and gyro/d filtering may need to be increased.
// *************reccomendation right now is to leave boost at or below 2, drop your p gains a few points, then cut your D in half and 
// *************retune it back up to where it feels good.  I'm finding about 60 to 65% of my previous D value seems to work.
//#define TORQUE_BOOST 1.0		//untested on servos

// *************invert servo and pid throws together
//#define INVERT_AILERON_SERVO
//#define INVERT_ELEVATOR_SERVO
//#define INVERT_RUDDER_SERVO

// *************SERVO SUBTRIMS
// *************If craft can not be trimmed within the limits of the linear portion of the expo curve, then an offset of subtrim must be applied.  Careful
//**************this will cause servos to extend beyond the 1000 to 2000us range and will rely on servo's ability to respond to the extended range
#define ROLL_SUBTRIM 0.03
#define PITCH_SUBTRIM	0.10
#define YAW_SUBTRIM 0.07

// *************SERVO OUTPUT SCALE
#define ROLL_SCALE_POS 1.00
#define ROLL_SCALE_NEG 1.00
#define PITCH_SCALE_POS 1.00
#define PITCH_SCALE_NEG 1.00
#define YAW_SCALE_POS 1.00
#define YAW_SCALE_NEG 1.00


//**********************************************************************************************************************
//***********************************************MOTOR OUTPUT SETTINGS**************************************************
	
// *************makes throttle feel more poppy and responsive to quick changes
//#define THROTTLE_BOOST 
//#define THROTTLE_BOOST_FACTOR 4.0 




//**********************************************************************************************************************
//***********************************************ADDITIONAL FEATURES****************************************************

// *************lost quad beeps using motors (30 sec timeout) - pulses motors after timeout period to help find a lost model
//#define MOTOR_BEEPS		//untested on servos

// *************0 - 7 - power for telemetry
#define TX_POWER 7

// *************led brightness in-flight ( solid lights only)
// *************0- 15 range
#define LED_BRIGHTNESS 15

// *************Comment out to disable pid tuning gestures
#define PID_GESTURE_TUNING
#define COMBINE_PITCH_ROLL_PID_TUNING

// *************Comment out for original relative proportional inc/dec steps for PID values
#define PID_TUNING_INCDEC_FACTOR 0.5f //fixed inc/dec values for PID tuning - by SilverAG
//Default value is 0.5f which means that PID values will be increased or decreased by constant index of 0.5
//For example, if PID value is 10.0 it will be incremented by 0.5 to 10.5 or decremented by 0.5 to 9.5
//Feel free to change 0.5f value to your liking









//#############################################################################################################################
//#############################################################################################################################
// debug / other things
// things that should not be usually changed
//#############################################################################################################################
//#############################################################################################################################

//Unicorn Expo adds two degrees of exponential for a longer linear portion near center stick for increased trimmable range.
#define UNICORN_EXPO

// This is the limit of raw stick deflection that can be detected as "trim".  Suggested 0.01f without UNICORN_EXPO and up to 0.25f with
#define AUTOCENTER_TRIM_LIMIT 0.25f

//enables use of stick accelerator and stick transition for d term lpf 1 & 2
#define ADVANCED_PID_CONTROLLER

//Throttle must drop below this value if arming feature is enabled for arming to take place.  MIX_INCREASE_THROTTLE_3 if enabled
//will also not activate on the ground untill this threshold is passed during takeoff for safety and better staging behavior.
#define THROTTLE_SAFETY .10f

//Activating this setting makes the accelerometer less prone to drift or yaw slow down in angle mode but more likely to become confused in crashes or impacts.  Only use if necessary
//There may not be a downside to this increased filtering on fixed wing
//#define ACCELEROMETER_DRIFT_FIX

// level mode "manual" trims ( in degrees)
// pitch positive forward
// roll positive right
#define TRIM_PITCH -12.0
#define TRIM_ROLL 0.0

// flash saving features
//#define DISABLE_GESTURES2

// disable motors for testing
//#define NOMOTORS

// throttle direct to motors for thrust measure
//#define MOTORS_TO_THROTTLE

// throttle direct to motors for thrust measure as a flight mode		************ this could be turned into manual mode
//#define MOTORS_TO_THROTTLE_MODE CHAN_OFF

// rxdebug structure
//#define RXDEBUG

// debug things ( debug struct and other)
//#define DEBUG

//Do not uncomment this - it changes the 0 throttle behavior regarding inair flags 
#define IDLE_UP ARMING

// minimum motor output: *for brushed a % value (0.0 - 100.0)   *for brushless this sets digital idle % for DSHOT for any selection
//#define MOTOR_MIN_COMMAND  5.0




//#############################################################################################################################
//#############################################################################################################################
// to be removed
// things that are useless in a airplane
//#############################################################################################################################
//#############################################################################################################################

// *************transmitter stick adjustable deadband for roll/pitch/yaw
// *************.01f = 1% of stick range - comment out to disable
//#define STICKS_DEADBAND .01f

// *************DEFINE FLIGHT CONTROLLER HARDWARE HAS BEEN MODIFIED FOR BRUSHLESS CONVERSION   **WARNING**DO NOT ENABLE DSHOT DMA ESC DRIVER WITH BRUSHED MOTORS ATTACHED**
//#define BRUSHLESS_CONVERSION

// *************automatically remove center bias in toy tx ( needs throttle off for 1 second )
//#define STOCK_TX_AUTOCENTER

//Select Motor Filter Type  (I am no longer using this)
//#define MOTOR_FILTER2_ALPHA MFILT1_HZ_90

// *************clip feedforward attempts to resolve issues that occur near full throttle by adding any clipped motor commands to the next loop output
//#define CLIP_FF
 
// *************throttle angle compensation in level mode
//#define AUTO_THROTTLE

//**************joelucid's yaw fix
//#define YAW_FIX

// *************enable inverted flight code ( brushless only )
//#define INVERTED_ENABLE
//#define FN_INVERTED CH_OFF //for brushless only

// *************SPECIAL TEST MODE TO CHECK TRANSMITTER STICK THROWS
// *************This define will allow you to check if your radio is reaching 100% throws entering <RIGHT-RIGHT-DOWN> gesture
// ************* will disable throttle and will rapid blink the led when sticks are moved to 100% throws
// *************entering <LEFT-LEFT-DOWN> will return the quad to normal operation.
//#define STICK_TRAVEL_CHECK


//#############################################################################################################################
//#############################################################################################################################
// to be removed
// things that are useless in a airplane
//#############################################################################################################################
//#############################################################################################################################

// *************transmitter stick adjustable deadband for roll/pitch/yaw
// *************.01f = 1% of stick range - comment out to disable
//#define STICKS_DEADBAND .01f

// *************DEFINE FLIGHT CONTROLLER HARDWARE HAS BEEN MODIFIED FOR BRUSHLESS CONVERSION   **WARNING**DO NOT ENABLE DSHOT DMA ESC DRIVER WITH BRUSHED MOTORS ATTACHED**
//#define BRUSHLESS_CONVERSION

// *************automatically remove center bias in toy tx ( needs throttle off for 1 second )
//#define STOCK_TX_AUTOCENTER

//Select Motor Filter Type  (I am no longer using this)
//#define MOTOR_FILTER2_ALPHA MFILT1_HZ_90

// *************clip feedforward attempts to resolve issues that occur near full throttle by adding any clipped motor commands to the next loop output
//#define CLIP_FF
 
// *************throttle angle compensation in level mode
//#define AUTO_THROTTLE

//**************joelucid's yaw fix
//#define YAW_FIX

// *************enable inverted flight code ( brushless only )
//#define INVERTED_ENABLE
//#define FN_INVERTED CH_OFF //for brushless only

// *************SPECIAL TEST MODE TO CHECK TRANSMITTER STICK THROWS
// *************This define will allow you to check if your radio is reaching 100% throws entering <RIGHT-RIGHT-DOWN> gesture
// ************* will disable throttle and will rapid blink the led when sticks are moved to 100% throws
// *************entering <LEFT-LEFT-DOWN> will return the quad to normal operation.
//#define STICK_TRAVEL_CHECK

// ************* Raises pids automatically as battery voltage drops in flight.  Ensure voltage is calibrated before use ****CRITICAL****.
//#define PID_VOLTAGE_COMPENSATION




/*NFE Notes
101022 Flight report - tested ACCELEROMETER_DRIFT_FIX define and removed it from defaults - performance in fixed wing angle w/this was much worse than drones.  Gravity vector system got confused very fast untill roll was
still being leveled but no longer responding to input.  I suspect the vector is losing its length again somehow like it did on drones for yaw?  Eventually roll input created
a sharp pitch up response.  Total nonsense.  Without this define it took multiple 15 minute flights of carving around in levelmode before i encountered one gravity vector issue
presenting on roll axis as a loss of stick response.  Last few days have been focused on getting a levelmode working better.  I think a rate based yaw may still be a good solution but it will 
need a workover for I term like sport mode.  Overall levelmode at this point is functional but something still feels kinda wrong.  It seems sometimes I can hit the full user defined
 bank angel and sometimes I cant as easily or at all.  Also pitch authority while roll is banked is close to non existant.  So a bank and yank turn still needs a huge flying space.  Addition of the 
sport mode based rudder brings around any turn in a small space but this sport mode yaw is not going to be suitable for kids/new pilots - it can do a flat spin in levelmode and 
that's just too much for the intention of levelmode.  The craft retains its level orientation without issue even with a full 3d yaw deflection - but stick banging yaw by a new pilot will cause a
sudden loss of altitude (think flat spin).  Otherwise levelmode is a home run especially for low speed 3d training- can harrier around all day without wing rock or loss of control 
Failsafe comes down in levelmode and if the pitch trim on the accelerometer is tweaked correctly - lands nicely.  Engaging level in all sorts of crazy orientations results in a predictable and gentle return to level orientation.
Lower gains in anglepid.c were tested today and I think I have discovered the lower limits and have butter smooth control - almost too disconnected and slow for emergency corrections
and many crashes were avoided by having sportmode yaw and using that yaw input to get out away from obstacles.
Today I turned back up the integral gain on pitch  - gusseting in a high speed knife edge was reduced and i didnt feel like i was fighting I gains too much when level as had so in the past - 
I think prior issues here were due to growing pains of getting unicorn rates all in sync as rx[] gets shifted, expo'd, and then shifted back.
The trim range of unicorn rates seems acceptable and allows for a pretty wide range of centered trim points without leaving the linear band and then causing a loss of trim when switching to low rates.
Last note from today - for the first time i seem to have realized my roll rate in sportacro is faster to one side than the other.  Was hard to evaluate and switching to manual mode
didnt provide any clear insight.  Seems like i feel it too in angle mode.  This could just be torque from the motor throwing me off, and i did have one aileron pushrod in the wrong hole.
Maybe this is all just physics, but i can't help but worry if something in the pid loop is pushing the wrong way to one side.  Elevator pid response also seems less than rudder and ailerons - 
and again here i can't rule out mechanical setup but it certainly seems the same as the other axis.  Maybe it's just my imagination

thoughts after today's session 
- racemode needs to be renamed to something more applicable to planes like DIGITAL_DIHEDRAL
- DIGITAL_DIHEDRAL could be a whole new flight mode as a sum of the levelmode and sportmode controls and might behave more like an actual dihedral wing
- a heading lock (i term) can be implimented in levelmodes for yaw but it is going to need to release on either yaw or roll input instead of just yaw
- need more pitch authority in levelmode while banked
- need to test slightly higher gains in anglepid.c
- need to examine the threshold for i-term relax (iwindup=2 state) - this is still tied to setpoint variable as is the D term's stick boost response.  When lower acro
	rates are configured by a user - i think this is causing I term to be too sticky (not triggering iwindup=2) and is reducing the affect of stick boost

101222 Flight Report - Testing levelmode, sportmode & failsafe.  The new bank&yank levelmode continues to produce exactly the indended results.  Flight feels very natural and predictable 
with only minor exceptions.  The I term on pitch is working it's tail off compensating for changes in airspeed with hands off sticks.  For normal fluid throttle changes - there is no 
visible correction and it always tracks true.  However going from the edge of stall @ no throttle to full throttle abruptly will briefly balloon up as the pitch I term has been previously loaded 
up in a trim up position and it takes a second for it to unwind itself.  I think the solution to this is to use an I-term relax trigger on throttle movement for the pitch I term just like the one applied to sportmode control surfaces 
but make the trigger watch only for increases in throttle and only in the lower half of the throttle stick. This should keep i term active in a harrier when throttle is being pumped in the upper 
range of the stick, maintain I term trim when cutting throttle, and isolate the ballooning event that occurs from a sudden jump from very low to very high airspeed.  This little hack only belongs on 
levelmode.  It is not an issue in sportmode.  Failsafe behavior also tested today - Everything working as intended.  Failsafe when disarmed returns servos to neutral position.  Failsafe when armed 
and in the air puts the plane in levelmode and it floats down out of the air in a perfectly level orientation and was even easily catchable during tests.  Return of control signal in the air 
is also possible without incident.  My transmitter requires throttle to be @ 0% in order to link up - so i was not able to verify if the firmware in the plane is also going to require throttle to be 
dropped below the throttle safety cutoff in order to regain control.  This relic of drone firmware might need some adaptation for fixed wing.  I don't mind that throttle needs to be dropped below 
safety cutoff to reactivate throttle in the event of signal loss and return - but control surfaces should immediately respond upon return of signal.  Maybe I will hold levelmode active (but with surface control) 
while waiting on the throttle safety to be satisfied and then restore aux selected flight mode with return of throttle.  Final note from failsafe testing is that currently levelmode is running with an unlocked
(no I term) yaw axis.  Intention is to change this in the future for the sportmode heading hold logic, but for now - during failsafe the plane is only going to track as true as the rudder trim as it
floats down.  Stuntmaster is always out of trim (sort of the reason i got into making a firmware) and it has been flying so true in sport mode that I have already forgotten how poorly this plane
tracks.  Its no surprise that it slowly drifted off its line on the rudder... but this can be fixed as levelmode yaw logic is improved.  A brief flight was performed in manual mode - and it felt exactly 
like flying the plane on a standard receiver - which is absolutely terrible.  Stuntmaster is a sloppy sloppy plane that never flies straight and can never be put in perfect trim.  I dont miss it flying 
like this.  It makes me feel like a terrible pilot and it isnt enjoyable to watch it in the air either.  No changes have been made to sportmode - but some agressive hucking about before the packs were
drained confirms that sportmode is still functioning as intended.  Sportmode makes the plane feel like an expensive high qualitty model instead of sloppy foam garbage and I get to feel like a better pilot
and spend time practicing new 3D moves instead of just practicing trying to keep it going straight.

thoughts after today's session
- levelmode feels close enough to let the kids fly it



code todo list:
- rework pid.c - this is becoming an absolute mess and needs organization especially with regard to how different combos of pid calculations and i term behavior are required for different flight modes
- levelmode pid attenuation (maybe on roll axis only?)
-	launch mode in levelmode with pitch up till sticks are engaged
- launch mode with throttle delay for pushers
- better i term relax trigger and stick boost that isnt influenced be acro rates selections
- throttle triggered pitch I term relax
- YAW heading hold in levelmode (relaxed by yaw, or roll + pitch deflections)
- failsafe throttle safety behavior to allow control surface movement immediately upon signal return


testing todo list:
-evaluate 1st vs 2nd order D term filters and eliminate one of them if unneeded
-levelmode pid attenuation on roll - need to decide if I like higher roll gains in sport mode
-test torque boost
-crank up stick boost again
-lower default acro rates and see how this impacts i term relax trigger and stick boost
-SOLVED - figure out why there is so little elevator authority when banked on roll in levelmode
-increase levelmode strength for a slightly more connected and less squishy feel - evaluate for comfort with proximity to obstacles








*/
