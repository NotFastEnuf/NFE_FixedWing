
#include "defines.h"
#include "util.h"

#include <math.h>
#include <string.h>



extern float GEstG[3];
extern float Q_rsqrt( float number );
extern char aux[];
extern float aux_analog[];

// error vector between stick position and quad orientation
// this is the output of this function
float errorvect[3];
// cache the last result so it does not get calculated everytime
float last_rx[2] = {13.13f , 12.12f};
float stickvector[3] = { 0 , 0 , 1};




void stick_vector( float rx_input[] , float maxangle)
{
// only compute stick rotation if values changed
if ( last_rx[0] == rx_input[0] && last_rx[1] == rx_input[1] )
{
     
}
else
{
    last_rx[0] = rx_input[0];
    last_rx[1] = rx_input[1]; 
    
// max angle
#if (defined USE_ANALOG_AUX && defined ANALOG_MAX_ANGLE)
    float max_angle = aux_analog[ANALOG_MAX_ANGLE] * 90.0f;
#else
    #define max_angle LEVEL_MAX_ANGLE
#endif
	
float pitch, roll;

	// rotate down vector to match stick position
pitch = rx_input[1] * max_angle * DEGTORAD + (float) TRIM_PITCH  * DEGTORAD;
roll = rx_input[0] * max_angle * DEGTORAD + (float) TRIM_ROLL  * DEGTORAD;

stickvector[0] = fastsin( roll );
stickvector[1] = fastsin( pitch );
stickvector[2] = fastcos( roll ) * fastcos( pitch );

		
float	mag2 = (stickvector[0] * stickvector[0] + stickvector[1] * stickvector[1]);

if ( mag2 > 0.001f ) 
{
mag2 = Q_rsqrt( mag2 / (1 - stickvector[2] * stickvector[2]) );
}
else mag2 = 0.707f;

stickvector[0] *=mag2;
stickvector[1] *=mag2;

#ifdef INVERTED_ENABLE
extern int pwmdir;

if ( pwmdir==REVERSE )
{
	stickvector[0] = - stickvector[0];
	stickvector[1] = - stickvector[1];
	stickvector[2] = - stickvector[2];
}
#endif
}

// find error between stick vector and quad orientation
// vector cross product 
  errorvect[1]= -((GEstG[1]*stickvector[2]) - (GEstG[2]*stickvector[1]));
  errorvect[0]= (GEstG[2]*stickvector[0]) - (GEstG[0]*stickvector[2]);


//COORDINATED_LEVELMODE -- Sharp flat turns every time (maybe? - need to test)
//missing from this array of vector cross products is errorvect[YAW]
//This is the amount that the levelmode error vectors from roll and pitch 
//deflected together spill over onto the yaw axis.  This motion fights against the 
//natural physics of a fixedwing  aircraft so we want to remove it anyway.... but its 
//value instead of fighting the turn can be turned around and directly mixed back into 
//the rudder servo producing the perfectly calculated rudder input for a flat coordinated turn.
//This COORDINATED_LEVELMODE needs to be ran with the "bank&yank hack levelmode" calculation group turned OFF!!!!
//	errorvect[2] = (GEstG[1]*stickvector[0]) - (GEstG[0]*stickvector[1]);
//  TODO:  come up with a plan on where to add this back in and see what happens

//BANK&YANK_LEVELMODE  --  A dirty dirty hack that works good enough to #sendit and feels natural enough to fly low altitude & proximity to obstacles.
//Cut up and re-distribute the uncalculated errorvect[YAW], putting it's pieces back
//over on to roll and pitch while keeping them in sync with deflection sign.  Basically just 
//adding back the amount from each axis that would have spilled over on to Yaw as pitch and roll
//are deflected together.  This mode should be ran with an "unlocked" (no I term allowed) rudder 
//servo whenever pitch && roll is deflected
if (stickvector[PITCH] < 0) errorvect[PITCH] += -fabsf(GEstG[0]*stickvector[1]);
else												errorvect[PITCH] +=  fabsf(GEstG[0]*stickvector[1]);

if (stickvector[ROLL] < 0)	errorvect[ROLL] += -fabsf(GEstG[1]*stickvector[0]);
else												errorvect[ROLL] +=  fabsf(GEstG[1]*stickvector[0]);

// some limits just in case
limitf( &errorvect[0] , 1.0);
limitf( &errorvect[1] , 1.0);
//limitf( &errorvect[2] , 1.0);

// fix to recover if triggered inverted
// the vector cross product results in zero for opposite vectors, so it's bad at 180 error
// without this the quad will not invert if angle difference = 180 

#ifdef INVERTED_ENABLE

static int flip_active_once = 0;
static int flipaxis = 0;
static int flipdir = 0;
int flip_active = 0;

#define rollrate 2.0f
#define g_treshold 0.125f
#define roll_bias 0.25f

if ( aux[FN_INVERTED]  && (GEstG[2] > g_treshold) )
{
	flip_active = 1;
	// rotate around axis with larger leaning angle

		if ( flipdir ) 
		{
			errorvect[flipaxis] = rollrate;
		}
		else 
		{
			errorvect[flipaxis] = -rollrate;			
		}
		
}
else if ( !aux[FN_INVERTED]  && (GEstG[2] < -g_treshold) )
{
	flip_active = 1;

		if ( flipdir ) 
		{
			errorvect[flipaxis] = -rollrate;
		}
		else 
		{
			errorvect[flipaxis] = rollrate;			
		}

}
else
	flip_active_once = 0;

// set common things here to avoid duplication
if ( flip_active )
{
	if ( !flip_active_once )
	{
		// check which axis is further from center, with a bias towards roll
		// because a roll flip does not leave the quad facing the wrong way
		if( fabsf(GEstG[0])+ roll_bias > fabsf(GEstG[1]) )
		{
			// flip in roll axis
			flipaxis = 0;
		}
		else
			flipaxis = 1;
	
	if (  GEstG[flipaxis] > 0 )
		flipdir = 1;
	else
		flipdir = 0;
	
	flip_active_once = 1;
	}
	
	// set the error in other axis to return to zero
	errorvect[!flipaxis] = GEstG[!flipaxis]; 
	
}
#endif


}



