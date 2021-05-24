#ifndef NMEA_H
#define NMEA_H
/** @file nmea.h
 *  @brief Constants, structures, function prototypes for NMEA functions
*/
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#define _EMPTY 0x00
#define NMEA_GPRMC 0x01
#define NMEA_GPRMC_STR "$GPRMC"
#define NMEA_GPGGA 0x02
#define NMEA_GPGGA_STR "$GPGGA"
#define NMEA_UNKNOWN 0x00
#define _COMPLETED 0x03

#define NMEA_CHECKSUM_ERR 0x80
#define NMEA_MESSAGE_ERR 0xC0
#define NMEAMSGSZ 82

typedef struct gpgga
{
	double utc;         ///< UTC Time
    double latitude;    ///< Latitude eg: 4124.8963 (XXYY.ZZKK.. DEG, MIN, SEC.SS)
    char lat;           ///< Latitude eg: N
    double longitude;   ///< Longitude eg: 08151.6838 (XXXYY.ZZKK.. DEG, MIN, SEC.SS)
    char lon;           ///< Longitude eg: W
    uint8_t quality;    ///< Quality 0, 1, 2
    uint8_t satellites; ///< Number of satellites: 1,2,3,4,5...
    double altitude;    ///< Altitude eg: 280.2 (Meters above mean sea level)
} gpgga_t;

typedef struct gprmc
{
	double utc;         ///< UTC Time
    double latitude;    ///< Latitude eg: 4124.8963 (XXYY.ZZKK.. DEG, MIN, SEC.SS)
    char lat;           ///< Latitude eg: N
    double longitude;   ///< Longitude eg: 08151.6838 (XXXYY.ZZKK.. DEG, MIN, SEC.SS)
    char lon;           ///< Longitude eg: W
    double speed;       ///< Speed
    double course;      ///< Direction
	double date;        ///< Date
} gprmc_t;

typedef struct nmeamsg
{
    char msgstr[NMEAMSGSZ+1];
} nmeamsg_s;

///\cond INTERNAL
// Function Prototypes
uint8_t nmea_get_message_type(const char *);
uint8_t nmea_valid_checksum(const char *);
void nmea_parse_gpgga(char *, gpgga_t *);
void nmea_parse_gprmc(char *, gprmc_t *);
///\endcond
#endif
