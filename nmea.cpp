/** @file nmea.c
 *  @brief NMEA Functions
 */
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cmath>
#include "nmea.h"

/** @brief Parses GPGGA Message
 *  @author Paul Moggach
 *  @date 25MAR2019
 *  @param char * nmea Pointer to message
 *  @param gpgg_t * loc Pointer to output data structure
 */
void nmea_parse_gpgga(char *nmea, gpgga_t *loc)
{
    char *p = nmea;

    p = strchr(p, ',')+1; // time
	loc->utc = atof(p);

    p = strchr(p, ',')+1;
    loc->latitude = atof(p);

    p = strchr(p, ',')+1;
    switch (p[0])
	{
        case 'N':
            loc->lat = 'N';
            break;
        case 'S':
            loc->lat = 'S';
            break;
        case ',':
            loc->lat = '\0';
            break;
    }

    p = strchr(p, ',')+1;
    loc->longitude = atof(p);

    p = strchr(p, ',')+1;
    switch (p[0])
	{
        case 'W':
            loc->lon = 'W';
            break;
        case 'E':
            loc->lon = 'E';
            break;
        case ',':
            loc->lon = '\0';
            break;
    }

    p = strchr(p, ',')+1;
    loc->quality = (uint8_t)atoi(p);

    p = strchr(p, ',')+1;
    loc->satellites = (uint8_t)atoi(p);

    p = strchr(p, ',')+1;

    p = strchr(p, ',')+1;
    loc->altitude = atof(p);
}

/** @brief Parses GPRMC Message
 *  @author Paul Moggach
 *  @date 25MAR2019
 *  @param char * nmea Pointer to message
 *  @param gpgg_t * loc Pointer to output data structure
 */
void nmea_parse_gprmc(char *nmea, gprmc_t *loc)
{
    char *p = nmea;

    p = strchr(p, ',')+1; // skip time
	p = strchr(p, ',')+1; //skip status
    p = strchr(p, ',')+1;
    loc->latitude = atof(p);
    p = strchr(p, ',')+1;
    switch (p[0])
	{
        case 'N':
            loc->lat = 'N';
            break;
        case 'S':
            loc->lat = 'S';
            break;
        case ',':
            loc->lat = '\0';
            break;
    }

    p = strchr(p, ',')+1;
    loc->longitude = atof(p);
    p = strchr(p, ',')+1;
    switch (p[0])
	{
        case 'W':
            loc->lon = 'W';
            break;
        case 'E':
            loc->lon = 'E';
            break;
        case ',':
            loc->lon = '\0';
            break;
    }

    p = strchr(p, ',')+1;
    loc->speed = atof(p);

    p = strchr(p, ',')+1;
    loc->course = atof(p);

    p = strchr(p, ',')+1;
    loc->date = atof(p);
}

/** @brief Get the message type (GPGGA, GPRMC, etc..)
 *  @param message The NMEA message
 *  @return The type of message if it is valid
 */
uint8_t nmea_get_message_type(const char *message)
{
    uint8_t checksum = 0;
    if ((checksum = nmea_valid_checksum(message)) != _EMPTY){ return checksum; }

    if (strstr(message, NMEA_GPGGA_STR) != NULL) { return NMEA_GPGGA; }

    if (strstr(message, NMEA_GPRMC_STR) != NULL) { return NMEA_GPRMC; }

    return NMEA_UNKNOWN;
}

/** @brief Checks Message Checksum
 *  @author Paul Moggach
 *  @date 25MAR2019
 *  @param char * nmea Pointer to message
 *  @return uint8_t Checksum
 */
uint8_t nmea_valid_checksum(const char *message)
{
    uint8_t checksum= (uint8_t)strtol(strchr(message, '*')+1, NULL, 16);

    char p;
    uint8_t sum = 0;
    ++message;
    while ((p = *message++) != '*') { sum ^= p; }

    if (sum != checksum) { return NMEA_CHECKSUM_ERR; }

    return _EMPTY;
}
