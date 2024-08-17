// Ant+_Testing_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


#include "ant_main_helper.h"

static unsigned short power1 = 0u;


static void _pw1_callback(unsigned char* p_aucData) {

    unsigned char ucPageNum = p_aucData[0];
    power1 = p_aucData[0];
    uint8_t heart_rate = p_aucData[7];
    std::cout << (int)heart_rate;
    std::cout << "\n";
}

#define FEC_DEVICE_TYPE 0x120u  ///< Device type reserved for ANT+ HRM
#define FEC_ANTPLUS_RF_FREQ        0x39u               ///< Frequency, decimal 57 (2457 MHz).
#define FEC_MSG_PERIOD             8070u               ///< Message period, decimal 8182 (4 Hz).
int main()
{
    start_MainAntLib();
    ant_addDeviceID(0, 0, FEC_MSG_PERIOD, _pw1_callback);
    ant_startANT();

    

    while (true)
    {
        
    }
   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
