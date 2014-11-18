#include "State.h"
#include "Satellite.h"

#ifndef STANDBY_H_
#define STANDBY_H_

/*
 * ---------------------------------- 
 * DATA STRUCTURES
 * ----------------------------------
 */

/**
 * Class
 * This class implement the StandBy state. Delegating state specific
 * work to this class will result in the calling thread being blocked
 * for a predfined time increment.
 *
 */
struct StandBy
{
  struct State super;
};



/*
 * ---------------------------------- 
 * FUNCTIONS
 * ----------------------------------
 */

/**
 * Initialize a StandBy object. Call this before invoking any of
 * the objects methods.
 *@param StandBy
 * The StandBy object to initialize.
 */
void standBy_new(struct StandBy *);

/**
 * Blocks the calling thread for a predined amount of time. The
 * amount of time blocked for is stored in ROM and is updated
 * as time elapses. Therefore, this method will only block
 * so long as ROM says there is time remaining to block. For example,
 * ROM says to block for 30 minutes. This method is called and
 * the calling thread has been blocked for 27 minutes then a 
 * power reset happens. The next time this method is called it
 * will only block the calling thread for 3 minutes.
 *@param StandBy
 * A pointer to the StandBy object.
 *@param Satellite
 * A pointer to the Satellite object invoking this method. The 
 * Satellite object is used to get and update the blocking time
 * in ROM. 
 */
void standBy_pursueMissionObjective(struct StandBy *,
				    struct Satellite *);

#endif /* STANDBY_H_ */
