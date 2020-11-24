#ifndef __CONFIG_SETTING_H__
#define __CONFIG_SETTING_H__

#include "settings.h"

class ConfigSettings
{
    private:
        uint32_t key;
    public:
        settingRow const* findSettings(uint8_t cpuId, uint8_t channelId, uint8_t speedId, uint8_t profileId);
};


#endif //__CONFIG_SETTING_H__