#include "ant_main_helper.h"

#include <cassert>
#include <fstream>
//#include "dsi_serial_generic.hpp"
#include "ant_receive_helper.h"



//Exported method that iterates a given int value.
#if defined _WIN32 || defined _WIN64
#include <windows.h>

#define EXAMPLELIBRARY_EXPORT __declspec(dllexport)
#else
#include <stdio.h>
#endif

#ifndef EXAMPLELIBRARY_EXPORT
#define EXAMPLELIBRARY_EXPORT
#endif


#define VERIFY(COND, RET)    if (!(COND)) { return (RET); }

static MyANTrxService* masterANTservice = nullptr;
static UCHAR master_current_channel = 0;


int start_MainAntLib() {
    VERIFY(masterANTservice == nullptr, -6);
    masterANTservice = new MyANTrxService();
    VERIFY(masterANTservice != nullptr, -7);

    master_current_channel = 0u;

    return 0;

}

int kill_MainAntLib() {
    VERIFY(masterANTservice != nullptr, -1);
    masterANTservice->Close();
    delete masterANTservice;
    masterANTservice = nullptr;
    return 0;

}

int ant_addDeviceID(unsigned short usDeviceNum,
    unsigned char ucDeviceType,
    unsigned short usMessagePeriod,
    std::function<void(unsigned char* p_aucData)> callback) {
  

    if (masterANTservice == nullptr) {
        int ret = start_MainAntLib();
        VERIFY(ret == 0, ret);
    }

    MyANTrxServiceInitStruct sInit1;


    sInit1.ucAntChannel = master_current_channel;
    sInit1.ucTransType = 0;
    sInit1.ucDeviceType = ucDeviceType;
    sInit1.usDeviceNum = usDeviceNum;
    sInit1.usMessagePeriod = 8070;



    printf("Adding ANT+ slave ID %u \n", usDeviceNum);
    masterANTservice->AddSlaveDevice(sInit1, callback);

    return master_current_channel++;


}

int ant_sendBytes(unsigned char ucChannel, unsigned char* p_aucData) {
    VERIFY(masterANTservice, -1);

    BOOL res = masterANTservice->TransmitMessage(ucChannel, p_aucData); // only channel 0 supported so far

    return res == FALSE;

}

int ant_startANT(void) {
    VERIFY(masterANTservice, -1);

    printf("Starting ANT+ lib...\n");

    if (masterANTservice->Init()) {

        masterANTservice->Start();

        return 0;

    }
    else {

        return -2;
    }

}

int ant_endANT(void) {
    return kill_MainAntLib();

}