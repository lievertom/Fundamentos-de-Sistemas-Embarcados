#ifndef THREAD_H_
#define THREAD_H_

#include "data.h"

/****************************************************************************/
/*!                         Functions                                       */

/*!
 *  @brief Function to handle preogram interuption.
 *
 *  @param[in] signal        :  interruption signal
 * 
 *  @return void.
 *
 */
void sig_handler(int signal);

void alarm_handler(int signum);

void initialize_threads();

#endif /* THREAD_H_ */
