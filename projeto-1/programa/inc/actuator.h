#ifndef ACTUATOR_H_
#define ACTUATOR_H_

/****************************************************************************/
/*!                              Macros                                     */
#define FAN RPI_V2_GPIO_P1_18 
#define RESISTANCE RPI_V2_GPIO_P1_16
#define ON 0
#define OFF 1

/****************************************************************************/
/*!                             Functions                                   */

/*!
 * @brief Function to initialize the actuators
 *
 * @return void
 *
 */
void initialize_actuators();

/*!
 *  @brief Function to switch actuators on or off
 *
 *  @param[in] fan            : fan 
 *  @param[in] resistence     : resistence
 *
 *  0 -> ON
 *  1 -> OFF
 *
 *  @return void
 *
 */
void on_off_actuators(int fan, int resistance);

/*!
 *  @brief Thread function that controls the actuators
 *
 * @param[in] args       : Pointer to access the data structure
 *
 * @return void
 *
 */
void *actuators_control (void *args);

#endif /* ACTUATOR_H_ */