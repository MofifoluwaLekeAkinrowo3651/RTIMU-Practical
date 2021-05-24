/** @file vdl.cpp
 *  @author Dieko Akinrowo
 *  @date 17MAY2020
 *  @brief Vehicle Data Logger main function
 */

#include <cstdio>
#include <unistd.h>
#include "logger.h"

/** @brief Vehicle Data Logger main function
 *  @author Dieko Akinrowo
 *  @date 17MAY21
 *  @param None void
 *  @return int program status
 */
int main(void)
{
    readings lgread = {0};

    DlInitialization();
    while(1)
    {
        lgread = DlGetLoggerReadings();
        DlDisplayLoggerReadings(lgread);
        DlSaveLoggerData(lgread);
        sleep(5);
    }
    return 1;
}

