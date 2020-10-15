#ifndef EXTERNAL_SENSOR_H_
#define EXTERNAL_SENSOR_H_

/****************************************************************************/
/*!                         Functions                                       */

/*!
 * @brief Function to initialize the sensor
 *
 * @return void
 *
 */
void initialize_external_sensor();

/*!
 *  @brief Thread function that get external temperature
 *
 * @param[in] args       : Pointer to access the data structure
 *
 * @return void
 *
 */
void *get_external_temperature(void *args);

#endif /* EXTERNAL_SENSOR_H_ */
