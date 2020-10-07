#ifndef GPIO_H_
#define GPIO_H_

/* Header includes */
#include <bcm2835.h>

/*!
 * @brief Function to configure the pins
 *
 * @return void
 *
 */
void configuration();

/*!
 *  @brief Function to handle preogram interuption.
 *
 *  @param[in] signal        :  interruption signal
 * 
 *  @return void.
 *
 */
void shut_down(int signal);

/*!
 * @brief Function to initialize the sensor
 *
 * @return void
 *
 */
void gpio();

void on_off(int fan, int resistance);

#endif /* GPIO_H_ */