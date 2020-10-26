#ifndef THREAD_H_
#define THREAD_H_

/****************************************************************************/
/*!                         Functions                                       */


void store_data(char *message);

/*!
 *  @brief Function to handle program interuption.
 *
 *  @param[in] signal        :  interruption signal
 * 
 *  @return void.
 *
 */
void sig_handler(int signal);

/*!
 *  @brief Function to handle program interuption.
 *
 *  @param[in] signal        :  interruption signal
 * 
 *  @return void.
 *
 */
void alarm_handler(int signum);

/*!
 *  @brief Function to init the main thread
 *
 *  @return void.
 *
 */
void initialize_threads();

#endif /* THREAD_H_ */
