/*	Jaime Rabago Jr
 *	tempfsm.c	SER486
 *
 *	temp finite state machine has additional states
 *	to send warnings  and send alarms for temps too high
 *	or low. Only sends alarms when significant changes in
 *	temps are detected to reduce emergency line chatter.
 */


void tempfsm_init()
{

}

void tempfsm_update(int current, int hicrit, int hiwarn, int locrit, int lowarn)
{

}

void tempfsm_reset()
{

}
