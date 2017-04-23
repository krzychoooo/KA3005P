/*
 * zachowajta mój email i róbta co chceta.
 */

/*
 * File:   ka3005p.cpp
 * Author: fajnysoft@gmail.com
 *
 * Created on 20 kwietnia 2017, 17:51
 */
#include <cstdio>
#include "ka3005p.h"
#include "rs232.h"

ka3005p::ka3005p() {
}

ka3005p::ka3005p(int com) {
    const char modeCoradKA3005P[4] = {'8', 'N', '1', 0};
    comport_number = com-1;
    baudrate = 9600;
    mode = modeCoradKA3005P;
    if (RS232_OpenComport(comport_number,ka3005p::baudrate ,ka3005p::mode )) {
        printf("Can not open comport\n");
        return ;
    }
    unsigned char command[10]={'*','I','D','N','?'};
    RS232_SendBuf(comport_number, command, 5);
    Sleep(200);
    unsigned char buf[4096];
    int n = RS232_PollComport(comport_number, buf, 4095);

        if (n > 0) {
            buf[n] = 0; /* always put a "null" at the end of a string! */

            for (int i = 0; i < n; i++) {
                if (buf[i] < 32) /* replace unreadable control-codes by dots */ {
                    buf[i] = '.';
                }
            }

            printf("received %i bytes: %s\n", n, (char *) buf);
        }
    //printf("-com=%d\n\r", ka3005p::comport_number);
    Sleep(200);
}

ka3005p::ka3005p(int com, int baud, const char *mode) {
    comport_number = com-1;
    baudrate = baud;
    ka3005p::mode = mode;
    if (RS232_OpenComport(comport_number,ka3005p::baudrate ,ka3005p::mode )) {
        printf("Can not open comport\n");
        return ;
    }
    unsigned char command[10]={'*','I','D','N','?'};
    RS232_SendBuf(comport_number, command, 5);
    Sleep(200);
    unsigned char buf[4096];
    int n = RS232_PollComport(comport_number, buf, 4095);

        if (n > 0) {
            buf[n] = 0; /* always put a "null" at the end of a string! */

            for (int i = 0; i < n; i++) {
                if (buf[i] < 32) /* replace unreadable control-codes by dots */ {
                    buf[i] = '.';
                }
            }

            printf("received %i bytes: %s\n", n, (char *) buf);
        }
    //printf("-com=%d\n\r", ka3005p::comport_number+1);
    Sleep(200);
}

ka3005p::~ka3005p() {
    //printf("zamykam com=%d\n\r", ka3005p::comport_number+1);
    RS232_CloseComport(ka3005p::comport_number);
}
void ka3005p::getCom(){
    printf("get com=%d\n\r", ka3005p::comport_number+1);
}

void ka3005p::setV(int ch, float volt){
    char command[12]={'V','S','E','T'};
    snprintf(&command[4], 3, "%d:", ch);
    snprintf(&command[6], 6, "%05.2f", volt);//5 znaków z zerami wiodacymi
    command[11]=0;
    //printf("command-%s",command);
    unsigned char *wsk = reinterpret_cast<unsigned char*>(command);
    int i=RS232_SendBuf(comport_number, wsk, 11);
    //printf(" %s i=%d com=%d\n\r", wsk, i, comport_number+1);
    Sleep(40);
}

void ka3005p::setI(int ch, float current){
    char command[12]={'I','S','E','T'};
    snprintf(&command[4], 3, "%d:", ch);
    snprintf(&command[6], 6, "%05.3f", current);//5 znaków z zerami wiodacymi
    command[11]=0;
    //printf("command-%s",command);
    unsigned char *wsk = reinterpret_cast<unsigned char*>(command);
    int i=RS232_SendBuf(comport_number, wsk, 11);
    //printf(" %s i=%d com=%d\n\r", wsk, i, comport_number+1);
    Sleep(40);
}


void ka3005p::powerEnable(bool enable){
    Sleep(50);
    char command[5]={'O','U','T'};
    if(enable){
        command[3]='1';
    }
    else{
        command[3]='0';
    }
    unsigned char *wsk = reinterpret_cast<unsigned char*>(command);
    int i=RS232_SendBuf(comport_number, wsk, 4);
    Sleep(150);
}

float ka3005p::getPower(int ch){
    unsigned char buf[32];
    float current, voltage, power;

    char command1[12]={'I','O','U','T'};
    snprintf(&command1[4], 3, "%d?", ch);
    RS232_flushRX(comport_number);
    unsigned char *wsk = reinterpret_cast<unsigned char*>(command1);
    int i=RS232_SendBuf(comport_number, wsk, 6);
    Sleep(50);
    int n = RS232_PollComport(comport_number, buf, 32);

        if (n > 0) {
            buf[n] = 0; /* always put a "null" at the end of a string! */

            for (int i = 0; i < n; i++) {
                if (buf[i] < 32) /* replace unreadable control-codes by dots */ {
                    buf[i] = '.';
                }
            }
            //printf("received %i bytes: %s\n", n, (char *) buf);
        }
    current = 0;
    current = current + (buf[0]-0x30);
    current = current + 0.1*(buf[2]-0x30);
    current = current + 0.01*(buf[3]-0x30);
    current = current + 0.001*(buf[4]-0x30);
    printf("prad=%f\n",current);

    char command2[6]={'V','O','U','T'};
    snprintf(&command2[4], 3, "%d?", ch);
    RS232_flushRX(comport_number);
    wsk = reinterpret_cast<unsigned char*>(command2);
    i=RS232_SendBuf(comport_number, wsk, 6);
    Sleep(50);
    n = RS232_PollComport(comport_number, buf, 32);

        if (n > 0) {
            buf[n] = 0; /* always put a "null" at the end of a string! */

            for (int i = 0; i < n; i++) {
                if (buf[i] < 32) /* replace unreadable control-codes by dots */ {
                    buf[i] = '.';
                }
            }
            //printf("received %i bytes: %s\n", n, (char *) buf);
        }
    voltage = 0;
    voltage = voltage + 10*(buf[0]-0x30);
    voltage = voltage + 1.0*(buf[1]-0x30);
    voltage = voltage + 0.1*(buf[3]-0x30);
    voltage = voltage + 0.01*(buf[4]-0x30);
    printf("nap=%f\n",voltage);
    power = voltage * current;
    printf("power=%f W \n",power);
    Sleep(50);
    return power;
}

float ka3005p::getCurrent(int ch){
    unsigned char buf[32];
    float current;

    char command1[12]={'I','O','U','T'};
    snprintf(&command1[4], 3, "%d?", ch);
    RS232_flushRX(comport_number);
    unsigned char *wsk = reinterpret_cast<unsigned char*>(command1);
    int i=RS232_SendBuf(comport_number, wsk, 6);
    Sleep(50);
    int n = RS232_PollComport(comport_number, buf, 32);

        if (n > 0) {
            buf[n] = 0; /* always put a "null" at the end of a string! */

            for (int i = 0; i < n; i++) {
                if (buf[i] < 32) /* replace unreadable control-codes by dots */ {
                    buf[i] = '.';
                }
            }
            //printf("received %i bytes: %s\n", n, (char *) buf);
        }
    current = 0;
    current = current + 1.0*(buf[0]-0x30);
    current = current + 0.1*(buf[2]-0x30);
    current = current + 0.01*(buf[3]-0x30);
    current = current + 0.001*(buf[4]-0x30);
    return current;
}

float ka3005p::getVoltage(int ch){
    unsigned char buf[32];
    float voltage;

    char command2[6]={'V','O','U','T'};
    snprintf(&command2[4], 3, "%d?", ch);
    RS232_flushRX(comport_number);
    unsigned char *wsk = reinterpret_cast<unsigned char*>(command2);
    int i=RS232_SendBuf(comport_number, wsk, 6);
    Sleep(50);
    int n = RS232_PollComport(comport_number, buf, 32);

        if (n > 0) {
            buf[n] = 0; /* always put a "null" at the end of a string! */

            for (int i = 0; i < n; i++) {
                if (buf[i] < 32) /* replace unreadable control-codes by dots */ {
                    buf[i] = '.';
                }
            }
            //printf("received %i bytes: %s\n", n, (char *) buf);
        }
    voltage = 0;
    voltage = voltage + 10*(buf[0]-0x30);
    voltage = voltage + 1.0*(buf[1]-0x30);
    voltage = voltage + 0.1*(buf[3]-0x30);
    voltage = voltage + 0.01*(buf[4]-0x30);
    return voltage;
}


binPrint(unsigned char c){
    for(int i=0; i!=8; i++){
        if(c&0x80)printf("1"); else printf("0");
        c <<=1;
    }
}

ka3005p::stat * ka3005p::getStatus(void){
    unsigned char buf[4];
    Sleep(50);
    char command1[8]={"STATUS?"};
    RS232_flushRX(comport_number);
    unsigned char *wsk = reinterpret_cast<unsigned char*>(command1);
    int i=RS232_SendBuf(comport_number, wsk, 7);
    Sleep(50);
    int n = RS232_PollComport(comport_number, buf, 32);

        if (n > 0) {
            buf[n] = 0; /* always put a "null" at the end of a string! */

            for (int i = 0; i < n; i++) {
                if (buf[i] < 32) /* replace unreadable control-codes by dots */ {
                    buf[i] = '.';
                }
            }
            //printf("received %i bytes: %s\n", n, (char *) buf);
        }
    unsigned char statusByte = buf[0];
    //binPrint(statusByte);
    if(statusByte & 0b00000001) status.ch1Mode = ka3005p::CV; else status.ch1Mode=ka3005p::CC;
    if(statusByte & 0b00000010) status.ch2Mode = ka3005p::CV; else status.ch2Mode=ka3005p::CC;
    if(statusByte & 0b00001100 == 0) status.tracking = ka3005p::INDEPENDENT;
        else if(statusByte & 0b00001100 == 1<<2) status.tracking = ka3005p::SERIES;
            else if(statusByte & 0b00001100 == 3<<2) status.tracking = ka3005p::PARALLEL;
    if(statusByte & 0b00010000 ) status.beep = ka3005p::ON; else  status.beep = ka3005p::OFF;
    if(statusByte & 0b00100000 ) status.lock = ka3005p::UNLOCK; else  status.lock = ka3005p::LOCK;
    if(statusByte & 0b01000000 ) status.output = ka3005p::ON; else  status.output = ka3005p::OFF;
        return &status;
}

