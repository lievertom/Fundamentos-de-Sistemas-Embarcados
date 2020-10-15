#ifndef ACTUATOR_H_
#define ACTUATOR_H_


#define FAN RPI_V2_GPIO_P1_18 
#define RESISTANCE RPI_V2_GPIO_P1_16
#define ON 0
#define OFF 1

/*!
 * @brief Function to initialize the sensor
 *
 * @return void
 *
 */
void initialize_actuators();

void on_off_actuators(int fan, int resistance);

void *actuators_control (void *args);

#endif /* ACTUATOR_H_ */