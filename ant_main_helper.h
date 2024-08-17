#pragma once
#ifndef ANT_MAIN_HELPER_H
#define ANT_MAIN_HELPER_H
#include <functional>

int start_MainAntLib();

int kill_MainAntLib();

int ant_addDeviceID(unsigned short usDeviceNum,
    unsigned char ucDeviceType,
    unsigned short usMessagePeriod,
    std::function<void(unsigned char* p_aucData)> callback);

int ant_sendBytes(unsigned char ucChannel, unsigned char* p_aucData);

int ant_startANT(void);

int ant_endANT(void);

#endif