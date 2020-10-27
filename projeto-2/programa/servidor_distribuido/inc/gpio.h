#ifndef GPIO_H_
#define GPIO_H_

/****************************************************************************/
/*!                              Macros                                     */
#define AC_1               RPI_V2_GPIO_P1_23 
#define AC_2               RPI_V2_GPIO_P1_24
 
#define LAMP_1             RPI_V2_GPIO_P1_17 
#define LAMP_2             RPI_V2_GPIO_P1_18 
#define LAMP_3             RPI_V2_GPIO_P1_27 
#define LAMP_4             RPI_V2_GPIO_P1_22
 
#define OPEN_SENSOR_1      RPI_V2_GPIO_P1_05 
#define OPEN_SENSOR_2      RPI_V2_GPIO_P1_06 
#define OPEN_SENSOR_3      RPI_V2_GPIO_P1_12 
#define OPEN_SENSOR_4      RPI_V2_GPIO_P1_16 
#define OPEN_SENSOR_5      RPI_V2_GPIO_P1_20 
#define OPEN_SENSOR_6      RPI_V2_GPIO_P1_21 

#define PRESENCE_SENSOR_1  RPI_V2_GPIO_P1_18 
#define PRESENCE_SENSOR_2  RPI_V2_GPIO_P1_18

#define ON                 0
#define OFF                1

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

#endif /* GPIO_H_ */