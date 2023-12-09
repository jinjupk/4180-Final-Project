#include "mbed.h"
#include "rtos.h"
#include "uLCD_4DGL.h"
#include "Servo.h"
#include "pn532.h"

 
uLCD_4DGL uLCD(p13,p14,p8); // serial tx, serial rx, reset pin;
// I2C i2c(p5, p6, p7);
// DigitalIn pb(p11); 
// Servo servo(p21);
DigitalOut relay(p10);
// Servo servo2(p22);
PN532 NFC(p5, p6, p7, p9);
Serial pc(USBTX,USBRX);
Timer readTimer;
BusOut leds(LED1, LED2, LED3, LED4);
Thread card_read;
Thread uLCD_screen;
#define PEARL 0x4530d12317680
#define SWARNA 0x48033a2c95f80
#define LAWRENCE 0x458569ac95f80

volatile int status = 0;

void invalid_card();
void valid_card();

void unlock() {
    relay = 1;
    Thread::wait(5000);
    relay = 0;
}


void valid_card() {
    uLCD.color(GREEN);
    uLCD.filled_rectangle(15, 40, 125, 120, BLACK);
    uLCD.locate(3, 6);
    uLCD.printf("CARD ACCEPTED");
    status = 0;
    for (int i = 0; i < 3; i++) {
        uLCD.line(50, 88, 61, 96, GREEN);
        uLCD.line(61, 96, 83, 73, GREEN);
        Thread::wait(300);
        uLCD.filled_rectangle(40, 70, 85, 115, BLACK);
        Thread::wait(300);
        if (status == 1) {
           valid_card();
           return;
       } else if (status == 2) {
           invalid_card();
           return;
       }
    }
}
void invalid_card() {
    uLCD.color(RED);
    pc.printf("running invalid card\n");
    uLCD.filled_rectangle(15, 40, 125, 120, BLACK);
    uLCD.locate(3, 6);
    uLCD.printf("INVALID CARD");
    uLCD.locate(3, 8);
    uLCD.printf("ACCESS DENIED");
    status = 0;
    for (int i = 0; i < 3; i++) {
        // pc.printf("for loop run");
        uLCD.line(54, 86, 73, 105, RED);
        uLCD.line(73, 86, 54, 105, RED);
        Thread::wait(300);
        uLCD.filled_rectangle(15, 80, 125, 107, BLACK);
        Thread::wait(300);
        if (status == 1) {
            valid_card();
            return;
        } else if (status == 2) {
            invalid_card();
            return;
        }
    }
}

void uLCD_message() {
    while (1) {
        uLCD.filled_rectangle(15, 40, 125, 120, BLACK);
        uLCD.color(WHITE);
        uLCD.locate(3, 6);
        uLCD.printf("SCAN CARD TO");
        uLCD.locate(4, 8);
        uLCD.printf("UNLOCK CAR");
        while (status == 0);
        pc.printf("new card detected\n\n");
        if (status == 2) {
            invalid_card();
        } else {
            valid_card();
        }
    }
}

// void lock() {
//     pc.printf("locked");
//     servo = 0.0;
// }

void loop() {
    while (1) {
        pc.printf("new loop\r\n");
        uint8_t success, i;
        uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
        uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
        static uint8_t lastUID[7];
        static uint8_t lastUIDLength;
        uint8_t newCardFound;
        leds = 0x00;

        // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
        // 'uid' will be populated with the UID, and uidLength will indicate
        // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
        success = NFC.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
        newCardFound = 0;
        pc.printf("success: %d\r\n", success);
        if (success) {
            if (uidLength == 7) {
                // We probably have a Mifare Classic card ...
                uint64_t cardid = uid[0];
                cardid <<= 8;
                cardid |= uid[1];
                cardid <<= 8;
                cardid |= uid[2];
                cardid <<= 8;
                cardid |= uid[3];
                cardid <<= 8;
                cardid |= uid[4];
                cardid <<= 8;
                cardid |= uid[5];
                cardid <<= 8;
                cardid |= uid[6];
                pc.printf("cardid: %16llX\r\n", cardid);
                if (cardid == PEARL) {
                    pc.printf("Matches Pearl\r\n");
                    status = 1;
                    unlock();
                } else if (cardid == SWARNA) {
                    pc.printf("Matches Swarna\r\n");
                    status = 1;
                    unlock();
                } else if (cardid == LAWRENCE) {
                    pc.printf("Matches Lawrence\r\n");
                    status = 1;
                    unlock();
                } else {
                    pc.printf("Does not match: wrong ID\r\n");
                    status = 2;
                }
            } else {
                pc.printf("uid length is not 7: cannot read card\r\n");
                status = 2;
            }
        }
    }
}

// void pb_hit_callback (void) {
//     pc.printf("button pressed");
// }

int main() {
    pc.printf("starting...");
    // pb.mode(PullUp);
    // // Delay for initial pullup to take effect
    // Thread::wait(1);
    // // Setup Interrupt callback function for a pb hit
    // while (1) {
    //     if (pb.read() == 0) {
    //         pc.printf("button pressed");
    //     }
    // }
    
    // Start sampling pb input using interrupts
    // pb.setSampleFrequency();
    // pc.printf("running main");
    uint32_t versiondata = NFC.getFirmwareVersion();
    if (!versiondata) {
        pc.printf("Didn't find PN53x board\r\n");
        while (1); // halt
    }
    NFC.SAMConfig();
   
    pc.printf("success!\r\n");
    pc.printf("Found chip PN5%lx\r\n", ((versiondata>>24) & 0xFF));
    pc.printf("Firmware ver. %lu.%lu\r\n", (versiondata>>16) & 0xFF,
           (versiondata>>8) & 0xFF);
    relay = 0;
    card_read.start(loop);
    uLCD_screen.start(uLCD_message);
    // uLCD_screen.set_priority(osPriorityLow);
}
