/*
 * Implements a two digit seven segment common cathode display driver.
 * The same approach will also drive a common anode with the same PCB 
 * layout by reversing the high/low logic of the pins below.
 */

#include "mcc_generated_files/mcc.h"

int value() {
    // MK11 PCB layout accident
    bool mk2 = false;
    
    if (mk2) 
        return 
            (DIN_0_GetValue() << 3) +
            (DIN_1_GetValue() << 2) +
            (DIN_2_GetValue() << 1) +
            (DIN_3_GetValue() << 0) +
            (DIN_4_GetValue() << 4) +
            (DIN_5_GetValue() << 5) +
            (DIN_6_GetValue() << 6) +
            (DIN_7_GetValue() << 7);
   
    else
        return 
            (DIN_0_GetValue() << 0) +
            (DIN_1_GetValue() << 1) +
            (DIN_2_GetValue() << 2) +
            (DIN_3_GetValue() << 3) +
            (DIN_4_GetValue() << 4) +
            (DIN_5_GetValue() << 5) +
            (DIN_6_GetValue() << 6) +
            (DIN_7_GetValue() << 7);
   
}

void display(int dig, int v) {

    bool a, b, c, d, e, f, g;
    a = b = c = d = e = f = g = false;

    switch (v) {
        case 0:
            a = b = c = d = e = f = true;
            break;
        case 1:
            b = c = true;
            break;
        case 2:
            a = b = e = d = g = true;
            break;
        case 3:
            a = b = c = d = g = true;
            break;
        case 4:
            b = c = f = g = true;
            break;
        case 5:
            a = c = d = f = g = true;
            break;
        case 6:
            a = c = d = e = f = g = true;
            break;
        case 7:
            a = b = c = true;
            break;
        case 8:
            a = b = c = d = e = f = g = true;
            break;
        case 9:
            a = b = c = d = f = g = true;
            break;
        case 10:
            a = b = c = d = e = g = true;
            break;
        case 11:
            c = d = e = f = g = true;
            break;
        case 12:
            a = d = e = f = true;
            break;
        case 13:
            b = c = d = e = g = true;
            break;
        case 14:
            a = d = e = f = g = true;
            break;
        case 15:
            a = e = f = g = true;
            break;
    }

    // turn off display
    DIGIT_L_SetHigh(); // inactive
    DIGIT_H_SetHigh(); // inactive
   
 
    if (a) {
        SEG_A_SetHigh();
    } else {
        SEG_A_SetLow();
    }
    if (b) {
        SEG_B_SetHigh();
    } else {
        SEG_B_SetLow();
    }
    if (c) {
        SEG_C_SetHigh();
    } else {
        SEG_C_SetLow();
    }
    if (d) {
        SEG_D_SetHigh();
    } else {
        SEG_D_SetLow();
    }
    if (e) {
        SEG_E_SetHigh();
    } else {
        SEG_E_SetLow();
    }
    if (f) {
        SEG_F_SetHigh();
    } else {
        SEG_F_SetLow();
    }
    if (g) {
        SEG_G_SetHigh();
    } else {
        SEG_G_SetLow();
    }
 
    if (dig == 0) {
        DIGIT_L_SetLow(); // active
    } else {
        DIGIT_H_SetLow(); // active
    }
}

// make this long enough that the display is mostly on.
void sleep() {
    // at 32MHz 30 spins wastes about 900us
    int i = 30;
    while (i-->0) {
        // pass
    }
}

/*
                         Main application
 */
#define LOWER 0
#define UPPER 1

void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    int vDisp  = value();
    while (1) {
        
        int vSample1 = value();

        // Add your application code
        display(0, vDisp & 0x0f);
        sleep();

        int vSample2 = value();

        display(1, vDisp >> 4);
        sleep();
        
        // if samples were the same then input is stable so display it
        if (vSample1 == vSample2) {
            vDisp = vSample1;
    }
}
}

/**
 End of File
 */
