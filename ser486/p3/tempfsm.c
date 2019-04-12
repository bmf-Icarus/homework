/*	Jaime Rabago Jr
 *	tempfsm.c	SER486
 *
 *	temp finite state machine has additional states
 *	to send warnings  and send alarms for temps too high
 *	or low. Only sends alarms when significant changes in
 *	temps are detected to reduce emergency line chatter.
 */

#include "config.h"


#define NORM1      0
#define NORM2      1
#define NORM3      2
#define WARNLO1    3
#define WARNLO2    4
#define CRITLO     5
#define WARNHI1    6
#define WARNHI2    7
#define CRITHI     8

static int t_state;

void tempfsm_init()
{
    t_state = NORM1;


}

void tempfsm_update(int current, int hicrit, int hiwarn, int locrit, int lowarn)
{

}

void tempfsm_reset()
{
    t_state = NORM1;
}
