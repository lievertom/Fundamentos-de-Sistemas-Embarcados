#ifndef UART_H_
#define UART_H_

/****************************************************************************/
/*!                              Macros                                     */
#define INTERNAL_TEMPERATURE (unsigned char *) 0xA1
#define REFERENCE_TEMPERATURE (unsigned char *) 0xA2

/****************************************************************************/
/*!                         Functions                                       */

/*!
 *  @brief Thread function that access uart to update the internal 
 *          temperature and potentiometer values
 *
 * @param[in] args       : Pointer to access the data structure
 *
 *  @return void
 *
 */
void  *uart (void *args);

#endif /* UART_H_ */