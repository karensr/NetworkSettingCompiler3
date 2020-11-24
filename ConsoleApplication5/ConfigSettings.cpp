#include <cstddef>
#include "ConfigSettings.h"

settingRow const* ConfigSettings::findSettings(uint8_t cpuId, uint8_t channelId, uint8_t speedId, uint8_t profileId)
{
    settingRow settingRom = settingRomData[0];
    int num = getSettingRomDataLen() / sizeof(settingRow);
    int i;
    key = MAKE_KEY(cpuId, channelId, speedId, profileId);
    num -= 1;
    i = 0;
    //Use binary search to find key in data structure already sorted by key (Compiler generated sorted structure)
    while (i <= num) {
        int m = i + (num - i) / 2;
        if (settingRomData[m].key == key)
            return &settingRomData[m];
        if (settingRomData[m].key < key)
            i = m + 1;
        else
            num = m - 1;
    }
    return NULL;
}
