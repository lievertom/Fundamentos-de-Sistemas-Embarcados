#ifndef ALARM_H_
#define ALARM_H_

/****************************************************************************/
/*                       Header includes                                    */


/****************************************************************************/
/*!                              Macros                                     */

#define COMMAND     "xdg-open"
#define PATH_AUDIO  "ast/example.mp3"

/****************************************************************************/
/*!                            Structs                                      */

/****************************************************************************/
/*!                         Functions                                       */

/*!
 *  @brief Thread function that control the alarm
 *
 * @param[in] args       : Pointer to access the data structure
 *
 *  @return void
 *
 */
bool alarm_control(Data *data);

void *play_alarm(void *args);


#endif /* ALARM_H_ */
