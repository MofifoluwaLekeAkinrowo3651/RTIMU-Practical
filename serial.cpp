/** @file serial.cpp
 *  @brief serial Functions
*/
#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "serial.h"

int uart0_filestream = -1;

/** @brief Serial port setup
 *  @author Paul Moggach
 *  @date 01JAN2019
 */
void serial_init(void)
{
    uart0_filestream = open(PORTNAME, O_RDWR | O_NOCTTY | O_NDELAY);

    if (uart0_filestream == -1)
    {
        //TODO error handling...
    }
}

/** @brief Serial port configuration
 *  @author Paul Moggach
 *  @date 01JAN2019
 */
void serial_config(void)
{
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
}

/** @brief Writes a line to the serial port
 *  @author Paul Moggach
 *  @date 01JAN2019
 *  @param line char * to buffer
 *  @param len number of characters to write
 */
void serial_println(const char *line, int len)
{
    if (uart0_filestream != -1)
	{
        char *cpstr = (char *)malloc((len+1) * sizeof(char));
        strcpy(cpstr, line);
        cpstr[len-1] = '\r';
        cpstr[len] = '\n';

        int count = write(uart0_filestream, cpstr, len+1);
        if (count < 0)
		{
            //TODO: handle errors...
        }
        free(cpstr);
    }
}

/** @brief Reads a line from the serial port.
 *  @author Paul Moggach
 *  @date 01JAN2019
 *  @param buffer char *
 *  @param len int number of characters to read
 */
void serial_readln(char *buffer, int len)
{
    char c;
    char *b = buffer;
    int rx_length = -1;
    while(1)
	{
        rx_length = read(uart0_filestream, (void*)(&c), 1);

        if (rx_length <= 0)
		{
            //wait for messages
            sleep(1);
        } else
		{
            if (c == '\n')
			{
                *b++ = '\0';
                break;
            }
            *b++ = c;
        }
    }
}

/** @brief Closes serial port
 *  @author Paul Moggach
 *  @date 01JAN2019
 */
void serial_close(void)
{
    close(uart0_filestream);
}
