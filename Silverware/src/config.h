/**
@file
<b>Configuration.</b>

@defgroup CONFIG Configuration
@{

Configuration
=============

Adjust pids in @ref pid.c file for any non whoop builds.

@note Universal pids are already loaded for 6mm and 7mm whoops by default.  

@see config.h "All configuration options"

@defgroup BOARD Hardware selection.  
@defgroup CONTROL Remote control. 
@defgroup FLIGHT Flight mode. 
@defgroup ADVANCED Advanced settings.
@{
  @defgroup VOLTAGE Voltage settings. 
  @defgroup FILTER Filter settings. 
  @defgroup MOTOR Motor settings. 
  @}
@}
*/

#include "defines.h"
#include "hardware.h"
  



//**********************************************************************************************************************
/// @addtogroup BOARD
/// @{

/// @name Flight controller hardware.
/// @{
/// 
/// - **BWHOOP**: for bwhoop, bwhoop pro, E011C Santa Edition, and Beta FPV Lite.
/// - **E011**: for E011
/// - **H8mini_blue_board**: for the H8 mini flight controller with blue circuit board
/// - **Alienwhoop_ZERO**: set `RX_SBUS` @ref CONTROL protocol
/// Define only one board:
#define BWHOOP
//#define E011
//#define H8mini_blue_board
//#define Alienwhoop_ZERO

/// @}

/// @}



//**********************************************************************************************************************
/// @addtogroup FLIGHT
/// @{
/// 
/// Exponential from 0.00 to 1.00 , 0 = no exp
/// positive: less sensitive near center.

/// Select your preffered rate calculation format (define **SILVERWARE_RATES** or **BETAFLIGHT_RATES**)
#define SILVERWARE_RATES
//#define BETAFLIGHT_RATES


#ifdef SILVERWARE_RATES

/// @name Acro mode
/// @{
#define MAX_RATE 720.0  ///< Rate for acro mode in deg/sec.
#define MAX_RATEYAW 900.0 ///< Rate for acro mode in deg/sec.
#define ACRO_EXPO_ROLL 0.00 	///< Default 0.80
#define ACRO_EXPO_PITCH 0.00 	///< Default 0.80
#define ACRO_EXPO_YAW 0.00
/// @}

/// @name Level mode
/// @{
#define LEVEL_MAX_RATE 230.0    //Roll & Pitch axis
#define LEVEL_MAX_ANGLE 66.0f ///< max angle for level mode.
#define ANGLE_EXPO_ROLL 0.00 ///< Default 0.55
#define ANGLE_EXPO_PITCH 0.0 ///< Default 0.0
#define ANGLE_EXPO_YAW 0.00
/// @}
#endif

#ifdef BETAFLIGHT_RATES
#define BF_RC_RATE_ROLL 1.00
#define BF_RC_RATE_PITCH 1.00
#define BF_RC_RATE_YAW 1.00
#define BF_SUPER_RATE_ROLL 0.70
#define BF_SUPER_RATE_PITCH 0.70
#define BF_SUPER_RATE_YAW 0.70
#define BF_EXPO_ROLL 0.00
#define BF_EXPO_PITCH 0.00
#define BF_EXPO_YAW 0.00
#endif


/// @name Dual rates
/// @{
/// Low rates multiplier if @ref RATES are assigned to a channel.
#define LOW_RATES_MULTI 0.70f
/// @}

/// @name Sticks dead band
/// @{
/// Transmitter stick adjustable deadband for roll/pitch/yaw.
/// 01f = 1% of stick range - comment out to disable
#define STICKS_DEADBAND .002f
/// @}
///
/// @}





//**********************************************************************************************************************
/// @addtogroup CONTROL
/// @{
///
/// @name Radio protocol.
/// @{
/// - Alienwhoop_ZERO: 
///   + **RX_SBUS**
/// - Spektrum: 
///   + **RX_DSM2_1024**
///   + **RX_DSMX_2048** 
/// - Bayang options: 
///  + **RX_NRF24_BAYANG_TELEMETRY** 
///  + **RX_BAYANG_PROTOCOL_BLE_BEACON**
///  + **RX_BAYANG_PROTOCOL_TELEMETRY_AUTOBIND**
///  + **RX_BAYANG_BLE_APP**
///
/// Define only one:
#define RX_BAYANG_BLE_APP
/// @}

/// @name Transmitter
///
/// - Toy transmitter: **USE_STOCK_TX**
/// - Deviation: **USE_DEVO**
/// - Multiprotocol: **USE_MULTI**
///
/// Define only one remote controller:
#define USE_MULTI


/// @name Switch settings
/// @{
///  	
/// Assign feature to auxiliary channel.
///
/// Features
/// --------
/// - @ref ARMING Arm switch, comment out to disable.
/// - @ref IDLE_UP will behave like betaflight airmode, comment out to disable.
/// - @ref RATES 
/// - @ref PIDPROFILE Switch @ref PID profile A/B 
/// - @ref LEDS_ON swich LEDs
/// - @ref FPV_ON switch for fpv / other, requires fet, comment out to disable.
/// - @ref BUZZER_ENABLE Enable buzzer functionality on pin assigned in @ref hardware.h, comment out to disable.
/// 
/// Settings
/// --------
/// - @ref IDLE_THR Default 
/// - @ref AUX1_START_ON  Automatically remove center bias in toy tx.
/// - @ref STOCK_TX_AUTOCENTER Start in level mode for toy tx.
///
/// Leveling
/// -------- 
/// - @ref LEVELMODE Leveling mode (AKA Angle, Stab).
/// - @ref RACEMODE 
/// - @ref HORIZON 
///
/// Switching on LEVELMODE is required for any leveling modes to be active.
/// With LEVELMODE active - MCU will apply RACEMODE if racemode channel is on, 
/// HORIZON if horizon channel is on, or RACEHORIZON if both channels are on,
/// and will be standard LEVELMODE if neither racemode or horizon are switched on.
/// 
/// 
/// Available channels
/// ------------------
/// **Toy transmitter.**
/// - @ref CHAN_5 rates button
/// - @ref CHAN_6 stick gestures RRD/LLD
/// - @ref CHAN_7 headfree button
/// - @ref CHAN_8 roll trim buttons
/// - @ref CHAN_9 pitch trim buttons
///
/// **Multiprotocol / Deviation**
/// - @ref CHAN_5 through @ref CHAN_10
///
/// @note For fixed state use @ref CHAN_ON (always on) and @ref CHAN_OFF (always off) 
///

//#define ARMING CHAN_5	
#define PIDPROFILE 	CHAN_5
#define LEDS_ON 		CHAN_6
#define IDLE_UP 		CHAN_7
#define RATES 			CHAN_8	
#define LEVELMODE 	CHAN_9
#define HORIZON   	CHAN_10
#define RACEMODE  	CHAN_OFF

//#define FPV_ON CHAN_ON
/// @}




// External buzzer requires pin assignment in hardware.h before defining below
// change channel assignment from CHAN_OFF to a numbered aux switch if you want switch control
// if no channel is assigned but buzzer is set to CHAN_ON - buzzer will activate on LVC and FAILSAFE.
//#define BUZZER_ENABLE CHAN_OFF

///This designates an idle throttle of 5%
#define IDLE_THR 0.05f

//#define AUX1_START_ON

// Needs throttle off for 1 second
//#define STOCK_TX_AUTOCENTER

/// @}





//**********************************************************************************************************************
/// @addtogroup VOLTAGE
/// @{

/// Raises pids automatically as battery voltage drops in flight.
#define PID_VOLTAGE_COMPENSATION

/// Prevent oscillations in angle modes with pid_voltage_compensation enabled due to high pids.
#define LEVELMODE_PID_ATTENUATION 0.90f  

/// Compensation for battery voltage vs throttle drop.
#define VDROP_FACTOR 0.7

/// Calculate VDROP_FACTOR factor automatically.
#define AUTO_VDROP_FACTOR

/// Lower throttle when battery below threshold forced landing low voltage cutoff
/// @note This feature will be off by default even when defined.
///
/// Use stick gesture **LLL** to activate then **DDD** to save as on.
/// Led light will blink once when LVC forced landing is turned on, blink twice when turned off, and will blink multiple times upon save command
/// @name Low battery cutoff
/// @{
#define LVC_LOWER_THROTTLE
#define LVC_LOWER_THROTTLE_VOLTAGE 3.30
#define LVC_LOWER_THROTTLE_VOLTAGE_RAW 2.70
#define LVC_LOWER_THROTTLE_KP 3.0
/// @}


/// Do not start software if battery is too low.
/// 
/// Flashes 2 times repeatedly at startup (battery below 3.3v)
#define STOP_LOWBATTERY

/// Voltage to start warning led blinking
#define VBATTLOW 3.5

/// Voltage hysteresis in volts
#define HYST 0.10

/// Automatic voltage telemetry correction factor.
/// Change the values if voltage telemetry is inaccurate.
///@name Telemetry calibration
/// @{
#define ACTUAL_BATTERY_VOLTAGE 4.20
#define REPORTED_TELEMETRY_VOLTAGE 4.20
/// @}
/// 
/// @}






//**********************************************************************************************************************
/// @addtogroup FILTER
/// @{
// *************Select the appropriate filtering set for your craft's gyro, D-term, and motor output or select CUSTOM_FILTERING to pick your own values.  
// *************If your throttle does not want to drop crisply and quickly when you lower the throttle stick, then move to a stronger filter set

// *************The following is the new "beta" testing filter set.  Taking lesson from betaflight ... it seems very effective to stack 1st order filters
// *************and gives outstanding adjustability as you can stagger the first and second passes at different values as opposed to being constrained by
// ************* a second order filter at a single cut frequency.  Go test and see what you like, and report back if you feel so inclined.  I have not actually staggered my
// ************* filters yet and the filters listed below are what I am flying on my whoop so far.  For my boss 7, I am changing both pass 1 and 2 to HZ_70, and  
// ************* setting the D 2nd filter to 120hz.  FYI, whoops seem to have one noise peak somewhere around 150 to 200hz and another one closer to 400 to 500hz.  
// *************  For my brushless 4" I am running one gyro pass at 90hz, the second gyro pass at 140hz, and the 1st order D filter at 70hz. On all of these crafts I have
// *************  been able to totally eliminate the need for any motor output filtering.  It will remain in the code as an available option for now, but I hope to be able to remove
// *************  it completely from the code soon if testing continues to go well.  My thoughts on motor output filtering are here https://community.micro-motor-warehouse.com/t/notfastenuf-e011-bwhoop-silverware-fork/5501/1388?u=notfastenuf
// *************  To adjust your filters if you so desire - use these basic observations I have made:  Noise will be obvious by motors that dont want to throttle down immediately or at all.  Too much filtering will be obvious
// ************* by propwash and eventually P oscillations if you really push it too far
// *************  
// *************  At this point I feel very optimistic about this gyro filter configuration. I hope we can all work together to establish the best whoop defaults possible.
// *************  If you want to help, try to tweak in the values on pass 1 and 2 for something that runs 6 and 7mm really clean.  Go slap on some bent
// ************* props, or find some of those garbage off balance 3 blade abominations that the stock zero tune hates so much.  Lets see what we can make possible and find the limits.
// *************  Lets also see if in the end - can we say that this flies better than the previous stock filter setup.  Remember, tolerating more bent or bad props is great but
// *************  only if it doesnt compromise the feel or performance we are used to when the equipment is good.  Personally I think this already feels better and handles better ... but I have only just begun exploring different filtering values.
// ************* Feel free to unselect BETA_FILTERING and return to ALIENWHOOP_ZERO_FILTERING here for comparison to stock.  I think/hope that this will work well enough that even the
// ************* prefilled filter sets can be eventually abandoned in favor of one decent set of defaults that fly most everything very well
// *************
// *************  FINAL NOTE: If you want to try running only one gyro pass, you can comment out either pass one or pass two.  Next revision will have split 1st order D term filter 
// *************  passes just like the gyro in place of 2nd order filtering.      Thanks - NFE

//#define WEAK_FILTERING
//#define STRONG_FILTERING
//#define VERY_STRONG_FILTERING
//#define BETA_FILTERING
#define ALIENWHOOP_ZERO_FILTERING

#ifdef BETA_FILTERING  //*** ABOVE 100 ADJUST IN INCRIMENTS OF 20, BELOW 100 ADJUST IN INCRIMENTS OF 10, nothing coded beyond 500hz

//Select Gyro Filter Type *** Select Only One type
#define KALMAN_GYRO
//#define PT1_GYRO


//Select Gyro Filter Cut Frequency
#define GYRO_FILTER_PASS1 HZ_90
#define GYRO_FILTER_PASS2 HZ_90

//Select D Term Filter Cut Frequency *** Select Only one
#define  DTERM_LPF_2ND_HZ 100
//#define DTERM_LPF_1ST_HZ 70

//Select Motor Filter Type  (I am no longer using this)
//#define MOTOR_FILTER2_ALPHA MFILT1_HZ_90

#endif
/// @}





//**********************************************************************************************************************
/// @addtogroup MOTOR
/// @{
// *************invert yaw pid for "PROPS OUT" configuration - This feature is switchable to "PROPS IN" when active with stick gesture DOWN-UP-DOWN, Save selection with DOWN-DOWN-DOWN
//#define INVERT_YAW_PID


///PWM frequency for motor control. A higher frequency makes the motors more linear (in Hz).
#define PWMFREQ 32000

// *************clip feedforward attempts to resolve issues that occur near full throttle by adding any clipped motor commands to the next loop output
//#define CLIP_FF

// *************torque boost is a highly eperimental feature.  it is a lpf D term on motor outputs that will accelerate the response
// *************of the motors when the command to the motors is changing by increasing or decreasing the voltage thats sent.  It differs
// *************from throttle transient compensation in that it acts on all motor commands - not just throttle changes.  this feature
// *************is very noise sensative so D term specifically has to be lowered and gyro/d filtering may need to be increased.
// *************reccomendation right now is to leave boost at or below 2, drop your p gains a few points, then cut your D in half and 
// *************retune it back up to where it feels good.  I'm finding about 60 to 65% of my previous D value seems to work.
//#define TORQUE_BOOST 1.0

// *************makes throttle feel more poppy - can intensify small throttle imbalances visible in FPV if factor is set too high
//#define THROTTLE_TRANSIENT_COMPENSATION 
//#define THROTTLE_TRANSIENT_COMPENSATION_FACTOR 4.0 
 
// *************throttle angle compensation in level mode
//#define AUTO_THROTTLE

// *************mix lower throttle reduces thrust imbalances by reducing throttle proportionally to the adjustable reduction percent
// *************mix increase throttle increases the authority of the pid controller at lowest throttle values like airmode when combined with idle up
// *************mix3 has a stronger effect and works better with brushless
#define MIX_LOWER_THROTTLE
#define MIX_THROTTLE_REDUCTION_PERCENT 10
//#define MIX_INCREASE_THROTTLE

//#define MIX_LOWER_THROTTLE_3
#define MIX_INCREASE_THROTTLE_3
#define MIX_THROTTLE_INCREASE_MAX 0.2f

/// joelucid's yaw fix
#define YAW_FIX

/// joelucid's transient windup protection.  Removes roll and pitch bounce back after flips.
#define TRANSIENT_WINDUP_PROTECTION
/// @}





//**********************************************************************************************************************
/// @addtogroup ADVANCED
/// @{
// *************lost quad beeps using motors (30 sec timeout) - pulses motors after timeout period to help find a lost model
//#define MOTOR_BEEPS

/// Power for telemetry from 0 to 7.
#define TX_POWER 7


/// Solid lights only brightness in-flight (range 0 - 15)
#define LED_BRIGHTNESS 12


///Comment out to disable pid tuning gestures
///@name PID options
/// @{
#define PID_GESTURE_TUNING
#define COMBINE_PITCH_ROLL_PID_TUNING
/// @}

/// Flash save method
/// - FLASH_SAVE1: pids + accel calibration
/// - FLASH_SAVE2: accel calibration to option bytes
#define FLASH_SAVE1
//#define FLASH_SAVE2

// *************enable inverted flight code ( brushless only )
//#define INVERTED_ENABLE
//#define FN_INVERTED CH_OFF //for brushless only

/// Special test mode to check transmitter stick throws
/// This define will allow you to check if your radio is reaching 100% throws.
/// - Entering **RRD** gesture will disable throttle and will rapid blink the led 
///   when sticks are moved to 100% throws
/// - Entering **LLD** will return the quad to normal operation.
#define STICK_TRAVEL_CHECK
/// @}




	
//#############################################################################################################################
//#############################################################################################################################
// debug / other things
// this should not be usually changed
//#############################################################################################################################
//#############################################################################################################################

///enables use of stick accelerator and stick transition for d term lpf 1 & 2
#define ADVANCED_PID_CONTROLLER

/// Throttle must drop below this value if arming feature is enabled for arming to take place.  MIX_INCREASE_THROTTLE_3 if enabled
/// will also not activate on the ground untill this threshold is passed during takeoff for safety and better staging behavior.
#define THROTTLE_SAFETY .10f

// level mode "manual" trims ( in degrees)
// pitch positive forward
// roll positive right
#define TRIM_PITCH 0.0
#define TRIM_ROLL 0.0

// limit minimum motor output to a value (0.0 - 1.0)
#define MOTOR_MIN_ENABLE
#define MOTOR_MIN_VALUE 0.05

// flash saving features
//#define DISABLE_GESTURES2

#ifdef LVC_LOWER_THROTTLE
#define SWITCHABLE_FEATURE_2
#endif

#ifdef INVERT_YAW_PID
#define SWITCHABLE_FEATURE_3
#endif

#ifdef ALIENWHOOP_ZERO_FILTERING
#define KALMAN_GYRO
#define GYRO_FILTER_PASS1 HZ_90
#define  DTERM_LPF_2ND_HZ 100
#define MOTOR_FILTER2_ALPHA MFILT1_HZ_50
#define SWITCHABLE_MOTOR_FILTER2_ALPHA MFILT1_HZ_90
#define SWITCHABLE_FEATURE_1
#endif

#ifdef WEAK_FILTERING
#define KALMAN_GYRO
#define GYRO_FILTER_PASS1 HZ_90
#define  DTERM_LPF_2ND_HZ 100
#define MOTOR_FILTER2_ALPHA MFILT1_HZ_90
#endif

#ifdef STRONG_FILTERING
#define KALMAN_GYRO
#define GYRO_FILTER_PASS1 HZ_80
#define  DTERM_LPF_2ND_HZ 90
#define MOTOR_FILTER2_ALPHA MFILT1_HZ_80
#endif

#ifdef VERY_STRONG_FILTERING
#define KALMAN_GYRO
#define GYRO_FILTER_PASS1 HZ_70
#define  DTERM_LPF_2ND_HZ 80
#define MOTOR_FILTER2_ALPHA MFILT1_HZ_70
#endif

#ifdef BETA_FILTERING
	#if (!defined(KALMAN_GYRO) && !defined(PT1_GYRO)) || (!defined(GYRO_FILTER_PASS1) && !defined(GYRO_FILTER_PASS2))
		#define SOFT_LPF_NONE
	#endif
#endif

#define GYRO_LOW_PASS_FILTER 0

#define DISABLE_FLIP_SEQUENCER
#define STARTFLIP CHAN_OFF

// disable motors for testing
//#define NOMOTORS

// throttle direct to motors for thrust measure
// #define MOTORS_TO_THROTTLE

// throttle direct to motors for thrust measure as a flight mode
//#define MOTORS_TO_THROTTLE_MODE MULTI_CHAN_8

// *************motor curve to use - select one
// *************the pwm frequency has to be set independently
#define MOTOR_CURVE_NONE

// loop time in uS
// this affects soft gyro lpf frequency if used
#define LOOPTIME 1000

// failsafe time in uS
#define FAILSAFETIME 1000000  // one second

// debug things ( debug struct and other)
//#define DEBUG

// rxdebug structure
//#define RXDEBUG

// enable motors if pitch / roll controls off center (at zero throttle)
// possible values: 0 / 1
// use in acro build only
#define ENABLESTIX 0
#define ENABLESTIX_TRESHOLD 0.3
#define ENABLESTIX_TIMEOUT 1e6

// overclock to 64Mhz

#define ENABLE_OVERCLOCK

#pragma diag_warning 1035 , 177 , 4017
#pragma diag_error 260

//--fpmode=fast

// define logic - do not change
///////////////

// used for pwm calculations
#ifdef ENABLE_OVERCLOCK
#define SYS_CLOCK_FREQ_HZ 64000000
#else
#define SYS_CLOCK_FREQ_HZ 48000000
#endif

#ifdef MOTOR_BEEPS
#ifdef USE_ESC_DRIVER
#warning "MOTOR BEEPS_WORKS WITH BRUSHED MOTORS ONLY"
#endif
#endif

// for the ble beacon to work after in-flight reset
#ifdef RX_BAYANG_PROTOCOL_BLE_BEACON
#undef STOP_LOWBATTERY
#endif


// gcc warnings in main.c

//Hardware target defines moved from hardware.h so that board selection of bwhoop or e011 can be performed in config.h file

#ifdef BWHOOP
//LEDS
#define LED_NUMBER 2
#define LED1PIN GPIO_Pin_2
#define LED1PORT GPIOA
#define LED2PIN GPIO_Pin_3
#define LED2PORT GPIOA
#define LED1_INVERT
#define LED2_INVERT

//SOFT I2C & GYRO
#define SOFTI2C_SDAPIN GPIO_Pin_10
#define SOFTI2C_SDAPORT GPIOA
#define SOFTI2C_SCLPIN GPIO_Pin_9
#define SOFTI2C_SCLPORT GPIOA
#define SOFTI2C_GYRO_ADDRESS 0x68
#define GYRO_ID_1 0x68
#define GYRO_ID_2 0x98 // new id
#define GYRO_ID_3 0x7D
#define GYRO_ID_4 0x72
#define SENSOR_ROTATE_90_CW

// SPI PINS DEFINITONS & RADIO
#if defined(RX_SBUS) || defined(RX_DSMX_2048) || defined(RX_DSM2_1024) || defined(RX_CRSF)
#define SERIAL_RX_SPEKBIND_BINDTOOL_PIN GPIO_Pin_3
#define SERIAL_RX_PIN GPIO_Pin_14
#define SERIAL_RX_PORT GPIOA
#define SERIAL_RX_SOURCE GPIO_PinSource14
#define SERIAL_RX_CHANNEL GPIO_AF_1
#define SOFTSPI_NONE
//dummy spi placeholders
#define SPI_MOSI_PIN GPIO_Pin_x
#define SPI_MOSI_PORT GPIOA
#define SPI_CLK_PIN GPIO_Pin_y
#define SPI_CLK_PORT GPIOA
#define SPI_SS_PIN GPIO_Pin_z
#define SPI_SS_PORT GPIOA
#define RADIO_CHECK
#else
#define SOFTSPI_3WIRE
#define SPI_MOSI_PIN GPIO_Pin_0
#define SPI_MOSI_PORT GPIOA
#define SPI_CLK_PIN GPIO_Pin_1
#define SPI_CLK_PORT GPIOF
#define SPI_SS_PIN GPIO_Pin_0
#define SPI_SS_PORT GPIOF
#define RADIO_XN297L
#define RADIO_CHECK
#endif

//VOLTAGE DIVIDER
#define BATTERYPIN GPIO_Pin_5
#define BATTERYPORT GPIOA
#define BATTERY_ADC_CHANNEL ADC_Channel_5
#define ADC_SCALEFACTOR 0.001364
#define ADC_REF 1.17857f

// MOTOR PINS
#define MOTOR0_PIN_PB1 // motor 0 back-left
#define MOTOR1_PIN_PA4 // motor 1 front-left
#define MOTOR2_PIN_PA6 // motor 2 back-right
#define MOTOR3_PIN_PA7 // motor 3 front-right
#endif

#ifdef E011
//LEDS
#define LED_NUMBER 2
#define LED1PIN GPIO_Pin_2
#define LED1PORT GPIOA
#define LED2PIN GPIO_Pin_3
#define LED2PORT GPIOA
#define LED1_INVERT
#define LED2_INVERT

//SOFT I2C & GYRO
#define SOFTI2C_SDAPIN GPIO_Pin_10
#define SOFTI2C_SDAPORT GPIOA
#define SOFTI2C_SCLPIN GPIO_Pin_9
#define SOFTI2C_SCLPORT GPIOA
#define SOFTI2C_GYRO_ADDRESS 0x68
#define GYRO_ID_1 0x68
#define GYRO_ID_2 0x98 // new id
#define GYRO_ID_3 0x7D
#define GYRO_ID_4 0x72
#define SENSOR_ROTATE_90_CW
#define SOFTI2C_PUSHPULL_CLK

// SPI PINS DEFINITONS & RADIO
#if defined(RX_SBUS) || defined(RX_DSMX_2048) || defined(RX_DSM2_1024) || defined(RX_CRSF) 
#define SERIAL_RX_SPEKBIND_BINDTOOL_PIN GPIO_Pin_3
#define SERIAL_RX_PIN GPIO_Pin_14
#define SERIAL_RX_PORT GPIOA
#define SERIAL_RX_SOURCE GPIO_PinSource14
#define SERIAL_RX_CHANNEL GPIO_AF_1
#define SOFTSPI_NONE
//dummy spi placeholders
#define SPI_MOSI_PIN GPIO_Pin_x
#define SPI_MOSI_PORT GPIOA
#define SPI_CLK_PIN GPIO_Pin_y
#define SPI_CLK_PORT GPIOA
#define SPI_SS_PIN GPIO_Pin_z
#define SPI_SS_PORT GPIOA
#define RADIO_CHECK
#else
#define SOFTSPI_3WIRE
#define SPI_MOSI_PIN GPIO_Pin_0
#define SPI_MOSI_PORT GPIOF
#define SPI_CLK_PIN GPIO_Pin_1
#define SPI_CLK_PORT GPIOF
#define SPI_SS_PIN GPIO_Pin_0
#define SPI_SS_PORT GPIOA
#define RADIO_XN297L
#define RADIO_CHECK
#endif

//VOLTAGE DIVIDER
#define BATTERYPIN GPIO_Pin_5
#define BATTERYPORT GPIOA
#define BATTERY_ADC_CHANNEL ADC_Channel_5
#define ADC_SCALEFACTOR 0.001364
#define ADC_REF 1.17857f

// Assingment of pin to motor
#define MOTOR0_PIN_PA6 // motor 0 back-left
#define MOTOR1_PIN_PA4 // motor 1 front-left
#define MOTOR2_PIN_PB1 // motor 2 back-right
#define MOTOR3_PIN_PA7 // motor 3 front-right
#endif

#ifdef H8mini_blue_board
//LEDS
#define LED_NUMBER 1
#define LED1PIN GPIO_Pin_1
#define LED1PORT GPIOF
#define LED2PIN GPIO_Pin_3
#define LED2PORT GPIOA

//SOFT I2C & GYRO
#define SOFTI2C_SDAPIN GPIO_Pin_10
#define SOFTI2C_SDAPORT GPIOA
#define SOFTI2C_SCLPIN GPIO_Pin_9
#define SOFTI2C_SCLPORT GPIOA
#define SOFTI2C_GYRO_ADDRESS 0x68
#define SOFTI2C_PUSHPULL_CLK
#define GYRO_ID_1 0x68
#define GYRO_ID_2 0x78 // common h8 gyro
#define GYRO_ID_3 0x7D
#define GYRO_ID_4 0x72
#define SENSOR_ROTATE_180

// SPI PINS DEFINITONS & RADIO
#if defined(RX_SBUS) || defined(RX_DSMX_2048) || defined(RX_DSM2_1024) || defined(RX_CRSF) 
#define SERIAL_RX_SPEKBIND_BINDTOOL_PIN GPIO_Pin_3
#define SERIAL_RX_PIN GPIO_Pin_14
#define SERIAL_RX_PORT GPIOA
#define SERIAL_RX_SOURCE GPIO_PinSource14
#define SERIAL_RX_CHANNEL GPIO_AF_1
#define SOFTSPI_NONE
//dummy spi placeholders
#define SPI_MOSI_PIN GPIO_Pin_x
#define SPI_MOSI_PORT GPIOA
#define SPI_CLK_PIN GPIO_Pin_y
#define SPI_CLK_PORT GPIOA
#define SPI_SS_PIN GPIO_Pin_z
#define SPI_SS_PORT GPIOA
#define RADIO_CHECK
#else
#define SOFTSPI_3WIRE
#define SPI_MOSI_PIN GPIO_Pin_1
#define SPI_MOSI_PORT GPIOA
#define SPI_CLK_PIN GPIO_Pin_2
#define SPI_CLK_PORT GPIOA
#define SPI_SS_PIN GPIO_Pin_3
#define SPI_SS_PORT GPIOA
#define RADIO_XN297L
#define RADIO_CHECK
#endif

//VOLTAGE DIVIDER
#define BATTERYPIN GPIO_Pin_5
#define BATTERYPORT GPIOA
#define BATTERY_ADC_CHANNEL ADC_Channel_5
#define ADC_SCALEFACTOR 0.001364
#define ADC_REF 1.17857f

// Assingment of pin to motor
#define MOTOR0_PIN_PA6 // motor 0 back-left
#define MOTOR1_PIN_PA4 // motor 1 front-left
#define MOTOR2_PIN_PB1 // motor 2 back-right
#define MOTOR3_PIN_PA7 // motor 3 front-right
#endif

#ifdef Alienwhoop_ZERO
//LEDS
#define LED_NUMBER 1
#define LED1PIN GPIO_Pin_0
#define LED1PORT GPIOF
#define LED2PIN GPIO_Pin_0
#define LED2PORT GPIOA

//SOFT I2C & GYRO
#define SOFTI2C_SDAPIN GPIO_Pin_10
#define SOFTI2C_SDAPORT GPIOA
#define SOFTI2C_SCLPIN GPIO_Pin_9
#define SOFTI2C_SCLPORT GPIOA
#define SOFTI2C_GYRO_ADDRESS 0x68
//#define SOFTI2C_GYRO_ADDRESS 0x69
#define GYRO_ID_1 0x68
#define GYRO_ID_2 0x98 // new id
#define GYRO_ID_3 0x78
#define GYRO_ID_4 0x72 
#define SENSOR_ROTATE_90_CCW

// SPI PINS DEFINITONS & RADIO
#if defined(RX_SBUS) || defined(RX_DSMX_2048) || defined(RX_DSM2_1024) || defined(RX_CRSF) 
#define SERIAL_RX_SPEKBIND_BINDTOOL_PIN GPIO_Pin_2
#define SERIAL_RX_SPEKBIND_RX_PIN GPIO_Pin_3
#define SERIAL_RX_PIN GPIO_Pin_3
#define SERIAL_RX_PORT GPIOA
#define SERIAL_RX_SOURCE GPIO_PinSource3
#define SERIAL_RX_CHANNEL GPIO_AF_1
#define SOFTSPI_NONE
//dummy spi placeholders
#define SPI_MOSI_PIN GPIO_Pin_x
#define SPI_MOSI_PORT GPIOA
#define SPI_CLK_PIN GPIO_Pin_y
#define SPI_CLK_PORT GPIOA
#define SPI_SS_PIN GPIO_Pin_z
#define SPI_SS_PORT GPIOA
#define RADIO_CHECK
#else
#define SOFTSPI_3WIRE
#define SPI_MOSI_PIN GPIO_Pin_3
#define SPI_MOSI_PORT GPIOA
#define SPI_CLK_PIN GPIO_Pin_2
#define SPI_CLK_PORT GPIOA
#define SPI_SS_PIN GPIO_Pin_1
#define SPI_SS_PORT GPIOA
#define RADIO_CHECK
#define RADIO_XN297L
#endif

//VOLTAGE DIVIDER
#define BATTERYPIN GPIO_Pin_5
#define BATTERYPORT GPIOA
#define BATTERY_ADC_CHANNEL ADC_Channel_5
#define ADC_SCALEFACTOR 0.002423
#define ADC_REF 1.0f


// MOTOR PINS
// MOTOR PINS
#define MOTOR0_PIN_PA7
//#define MOTOR1_PIN_PA4  //2nd Draft prototype patch
//#define MOTOR2_PIN_PB1  //2nd Draft prototype patch
#define MOTOR1_PIN_PB1
#define MOTOR2_PIN_PA4
#define MOTOR3_PIN_PA6
#endif


//**********************************************************************************************************************
//***********************************************BETA TESTING ON STICK GESTURE******************************************
// *************DEFINE ONLY ONE OPTION FROM THIS SECTION!!!
// *************This is a new section that will allow certain beta testing features to be activated by the stick gesture
// *************auxillary channel.  Even when defined - the quad will power up with these features off.  To activate -  
// *************use the following stick gesture on the pitch/roll stick RIGHT-RIGHT-DOWN (leds will blink). To deactivate - 
// *************stick gesture LEFT-LEFT-DOWN.  Please test the features you are interested in below and give feedback!!!

