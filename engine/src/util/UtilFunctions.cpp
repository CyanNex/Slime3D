#include <util/UtilFunctions.h>
#include <system.h>

void sleep_ms(const uint uiSleepDurationMs)
{
#if defined(LINUX)
    usleep(uiSleepDurationMs * 1000); // usleep takes sleep time in us (1 millionth of a second)
#elif defined(WINDOWS)
    Sleep(uiSleepDurationMs);
#endif
}
