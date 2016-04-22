/**************************************************************************
    Souliss - Demo Sketch

    This is the demo example, show all typicals w/out Input - Output commands.
    using SoulissApp (get it from Play Store).

    Run this code on one of the following boards:
      - Arduino Ethernet (W5100)
      - Arduino with Ethernet Shield (W5100)

    As option you can run the same code on the following, just changing the
    relevant configuration file at begin of the sketch
      - Arduino with W5200 Ethernet Shield
      - Arduino with W5500 Ethernet Shield

***************************************************************************/
// Configure the framework
#include "bconf/StandardArduino.h"          // Use a standard Arduino
#include "conf/ethW5100.h"                  // Ethernet through Wiznet W5100
#include "conf/Gateway.h"                   // The main node is the Gateway, we have just one node

// Include framework code and libraries
#include <SPI.h>
#include "Souliss.h"

// This identify the number of the LED logic
#define T11          0    // ON/OFF Digital Output with Timer Option
#define T12          1    // ON/OFF Digital Output with AUTO mode
#define T13          2    // Digital Input Value    **RANDOM IN
#define T14          3    // Pulse Digital Output
#define T15          4    // RGB IR Light
#define T16          6    // RGB LED Strip
#define T18          10   // ON/OFF Digital Output with pulse output	with Timer Option
#define T19          11   // Dimmable Single Color LED Strip

#define T22          13   // Motorized devices with limit switches and middle position

//*************** ** RANDOM IN ** **********************
#define T52          14   // Souliss_Logic_T52 - Temperature measure (-20, +50) °C
#define T53          16	  // Souliss_Logic_T53 - Humidity measure (0, 100) %

//*************** ** SETPOINTS ** **********************
#define T65          18   // Souliss_Logic_T65 - Voltage (0, 400) V
#define T66          20   // Souliss_Logic_T66 - Current (0, 25)  A
#define T67          22   // Souliss_Logic_T67 - Power (0, 6500)  W


uint8_t ip_address[4]  = {10, 14, 10, 77};
uint8_t subnet_mask[4] = {255, 255, 0, 0};
uint8_t ip_gateway[4]  = {10, 14, 10, 201};
#define myvNet_address	ip_address[3]		// The last byte of the IP address (77) is also the vNet address

void setup()
{
    Initialize();

    Souliss_SetIPAddress(ip_address, subnet_mask, ip_gateway);
    SetAsGateway(myvNet_address);

    Set_T11(T11);
    Set_T12(T12);
    Set_T13(T13);
    Set_T14(T14);
    Set_T16(T16);
    Set_T18(T18);
    Set_T19(T19);

    Set_T22(T22);

    Set_T52(T52);
    Set_T53(T53);

    Set_Voltage_Setpoint(T65);
    Set_Current_Setpoint(T66);
    Set_Power_Setpoint(T67);
}

void loop()
{
    // Here we start to play
    EXECUTEFAST() {
        UPDATEFAST();

        SHIFT_50ms(0) {   // We process the logic and relevant input and output every 50 milliseconds
            Logic_T11(T11);
            Logic_T12(T12);
        }

        SHIFT_50ms(1) {   // We process the logic and relevant input and output every 50 milliseconds
            Logic_T13(T13);
            Logic_T14(T14);
        }


        SHIFT_50ms(2) {   // We process the logic and relevant input and output every 50 milliseconds
            Logic_T16(T16);
            Logic_T18(T18);
        }

        SHIFT_50ms(3) {   // We process the logic and relevant input and output every 50 milliseconds;
            Logic_T19(T19);
            Logic_T22(T22);
        }

        SHIFT_50ms(4) {   // We process the logic and relevant input and output every 50 milliseconds;
            Logic_Voltage_Setpoint(T65);
            Logic_Current_Setpoint(T66);
            Logic_Power_Setpoint(T67);
        }

        // Here we handle here the communication with Android, commands and notification
        // are automatically assigned to MYLEDLOGIC
        FAST_GatewayComms();

    }

    EXECUTESLOW() {
        UPDATESLOW();

        SLOW_10s() {  // Process the timer every 10 seconds
            Timer_T11(T11);
            Timer_T12(T12);
            Timer_T16(T16);
            Timer_T18(T18);
            Timer_T19(T19);

            Timer_T22(T22);
        }

        SLOW_x10s(2) {

          float val = 24+random(0, 100)/100*5;
    	    ImportAnalog(T52, &val);
    	    Logic_T52(T52);

          val = 50+random(0, 100)/100*15;
    	    ImportAnalog(T53, &val);
    	    Logic_T53(T53);
        }
    }
}
