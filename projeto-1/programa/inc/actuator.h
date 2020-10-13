#ifndef ACTUATOR_H_
#define ACTUATOR_H_


#define FAN RPI_V2_GPIO_P1_18 
#define RESISTANCE RPI_V2_GPIO_P1_16
#define ON 0
#define OFF 1

/*!
 * @brief Function to configure the pins
 *
 * @return void
 *
 */
// void configuration();

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
void initialize_actuators();

void on_off_actuators(int fan, int resistance);

#endif /* ACTUATOR_H_ */