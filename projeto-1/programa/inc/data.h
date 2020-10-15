#ifndef DATA_H_
#define DATA_H_

/****************************************************************************/
/*!                              Macros                                     */

#define PATH_DATA "dat/data.csv"
#define DATE_SIZE 11
#define HOUR_SIZE 9

/****************************************************************************/
/*!                            Structs                                      */

typedef struct Data 
{
    float internal_temperature;
    float external_temperature;
    float reference_temperature;
    float hysteresis;
    int potentiometer;
} Data;

/****************************************************************************/
/*!                         Functions                                       */

/*!
 *  @brief Thread function that saves data
 *
 * @param[in] args       : Pointer to access the data structure
 *
 *  @return void
 *
 */
void *save_data (void *args);

#endif /* DATA_H_ */
