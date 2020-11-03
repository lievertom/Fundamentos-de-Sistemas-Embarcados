#ifndef GPIO_H_
#define GPIO_H_

/****************************************************************************/
/*!                              Macros                                     */

#define AC_1               RPI_V2_GPIO_P1_16 
#define AC_2               RPI_V2_GPIO_P1_18
 
#define LAMP_1             RPI_V2_GPIO_P1_11 
#define LAMP_2             RPI_V2_GPIO_P1_12 
#define LAMP_3             RPI_V2_GPIO_P1_13 
#define LAMP_4             RPI_V2_GPIO_P1_15
 
#define OPEN_SENSOR_1      RPI_V2_GPIO_P1_29 
#define OPEN_SENSOR_2      RPI_V2_GPIO_P1_31 
#define OPEN_SENSOR_3      RPI_V2_GPIO_P1_32 
#define OPEN_SENSOR_4      RPI_V2_GPIO_P1_36 
#define OPEN_SENSOR_5      RPI_V2_GPIO_P1_38 
#define OPEN_SENSOR_6      RPI_V2_GPIO_P1_40 

#define PRESENCE_SENSOR_1  RPI_V2_GPIO_P1_22 
#define PRESENCE_SENSOR_2  RPI_V2_GPIO_P1_37

#define ON                 1
#define OFF                0

/****************************************************************************/
/*!                             Functions                                   */

/*!
 * @brief Function to initialize the actuators
 *
 * @return void
 *
 */
void initialize_gpio();

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
void turn_on_off(int device, int turn);

/*!
 *  @brief Thread function that controls the actuators
 *
 * @param[in] args       : Pointer to access the data structure
 *
 * @return void
 *
 */
void *sensor_control (void *args);

/*!
 *  @brief Thread function that controls the actuators
 *
 * @param[in] args       : Pointer to access the data structure
 *
 * @return void
 *
 */
void *lamp_control (void *args);


/*!
 *  @brief Thread function that controls the actuators
 *
 * @param[in] args       : Pointer to access the data structure
 *
 * @return void
 *
 */
void *ac_control (void *args);

#endif /* GPIO_H_ */