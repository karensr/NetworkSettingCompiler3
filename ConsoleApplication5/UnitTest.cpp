// ConsoleApplication5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include "ConfigSettings.h"
#include "string.h"


const settingRow settingRomData[] = {
	{ 0x1010101, {144, 170, 68, 22, 19, 55 }},
	{ 0x1050001, {121, 51, 68, 232, 9, 1 }},
	{ 0x1050002, {122, 34, 68, 232, 9, 2 }},
	{ 0x1050101, {124, 53, 68, 232, 49, 0 }},
	{ 0x2040001, {255, 54, 68, 232, 123, 9 }},
	{ 0x3030303, {126, 55, 68, 23, 43, 8 }},
	{ 0x4050002, {132, 255, 68, 50, 89, 98 }},
	{ 0x6060606, {129, 85, 68, 232, 89, 86 }},
	{ 0x7070707, {128, 57, 68, 232, 89, 77 }},
	{ 0x8080808, {127, 56, 44, 32, 89, 7 }},
};

int getSettingRomDataLen()
{
	return sizeof(settingRomData);
}


#pragma pack(1)
struct settingTestData {
    uint8_t cpuId;
    uint8_t channelId;
    uint8_t speedId;
    uint8_t profileId;
    bool valid;
    settingData setting;
};

bool UnitTestSettingsDetection(const settingTestData * testData) {
    ConfigSettings myconfig;
    bool isValid = true;
    settingRow const* detectedRow = myconfig.findSettings(testData->cpuId, testData->channelId, testData->speedId, testData->profileId);
    if (detectedRow == NULL) {
        //cout << "config is not detected\n";
        isValid = false;
    }
    else {
        if (0 != memcmp(&detectedRow->setting, &testData->setting, sizeof(settingData))) {
            isValid = false;
        }
    }

    return (testData->valid == isValid);
}

int main()
{
    const settingTestData testData[] = {
        {1, 1, 1, 1, true, {144, 170, 68, 22, 19, 55}},         //valid
        {1, 1, 1, 2, false, {1,1,1,1,1,1}},                     //not detected
        {1, 1, 2, 1, false, {1,1,1,1,1,1}},                     //not detected
        {1, 2, 1, 1, false, {1,1,1,1,1,1}},                     //not detected
        {2, 1, 1, 1, false, {1,1,1,1,1,1}},                     //not detected
        {1, 5, 0, 1, true, {121, 51, 68, 232, 9, 1}},           //valid
        {1, 5, 0, 2, true, {122, 34, 68, 232, 9, 2}},           //valid
        {1, 5, 0, 1, false, {0x33,0x44,232,0x9,0x2}},           //invalid, other key data
        {1, 5, 0, 2, false, {34,0x44,232,9,0x1}},               //invalid other key daya
        {2, 4, 0, 1, true, {0xFF,0x36,0x44,232,123,9}},         //valid
        {2, 4, 0, 1, false, {1,0x36,0x44,232,123,9}},           //invalid only setting 0 value
        {2, 4, 0, 1, false, {0xFF,1,0x44,232,123,9}},           //invalid only setting 1 value
        {2, 4, 0, 1, false, {0xFF,0x36,1,232,123,9}},           //invalid only setting 2 value
        {2, 4, 0, 1, false, {0xFF,0x36,0x44,1,123,9}},          //invalid only setting 3 value
        {2, 4, 0, 1, false, {0xFF,0x36,0x44,232,1,9}},          //invalid only setting 4 value
        {2, 4, 0, 1, false, {0xFF,0x36,0x44,232,123,1}},        //invalid only setting 5 value
    };

    int count = sizeof(testData) / sizeof(settingTestData);
    for (int i = 0; i < count; i++) {
        cout << "Unit test # " << i + 1 << " status is " << boolalpha << UnitTestSettingsDetection(&testData[i]) << endl;
    }

    return 0;
}
