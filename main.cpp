#include"mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

DigitalOut led1(LED1);
DigitalInOut ping(D12);
BufferedSerial pc(USBTX,USBRX); 
BufferedSerial uart(D1,D0); 
BufferedSerial xbee(D10,D9);
Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BBCar car(pin5, pin6, servo_ticker);

Thread t;
int swich = 0;
char data[18];
char data2[13];
int first = 0; 
int second = 0; 
int third = 0;
int re = 1;
int finish = 0;
int cnt = 0;
void right();
int dd = 0;

/*
void right() {
    char buff[20];
   // xbee.set_baud(9600);
    while (1) {
        if(first == 0) {
            sprintf(buff,r\n");
            xbee.write(buff,sizeof(buff));
            first = 1;
            //ThisThread::sleep_for(100ms);
        }
        if(second == 1) {
            sprintf(buff, "\r\n");
            xbee.write(buff,sizeof(buff));
           // ThisThread::sleep_for(100ms);
            second = -1;
        }
        if(third==1) {
            sprintf(buff, !\r\n");
            xbee.write(buff,sizeof(buff));
           // ThisThread::sleep_for(100ms);
            third = -1;
        }
        ThisThread::sleep_for(100ms);
    }
}*/

void inform() {
    float Tx, Tz, Ry;
    int x1, x2, del;
    char buff[20];
    //xbee.set_baud(9600);
   // float val;
    pc.set_baud(9600);
    car.stop();
    
    while(1) {
      //  re = 1;
        if(data2[0] == 'S') {
            x1 = 100 * (int(data2[1])-48) + 10 * (int(data2[2])-48) + int(data2[3])-48;
            x2 = 100 * (int(data2[4])-48) + 10 * (int(data2[5])-48) + int(data2[6])-48;
        }
        if(data[0] == '+') {
            Tx = (int(data[1])-48)*((int(data[2])-48) + 0.1*(int(data[4])-48) + 0.01*(int(data[5])-48));
            Tz = (10*(int(data[7])-48) + (int(data[8])-48) + 0.1*(int(data[10])-48) + 0.01*(int(data[11])-48));
            Ry = 100*(int(data[12])-48) + 10*(int(data[13])-48) + (int(adatat[14])-48) + 0.1*(int(data[16]-48)) + 0.01*(int(data[17])-48);
        }
        if (data[6] == '-') Tz = -Tz;
        cnt++;

        /*if(st == 0) {
            sprintf(buff, "Line\r\n");
            xbee.write(buff,6);
            st = 1;
            //ThisThread::sleep_for(100ms);
        }*/

      //  printf(" %d %d %f %f %f ", x1, x2, Tx,abs(Tz),Ry);
        del = x2-x1;
        re = 1;
       // printf("re %d", re);
      // sprintf(buff, "Line Follow\r\n");
        //xbee.write(buff,13);
        if(first == 0) {
            sprintf(buff, "Line\r\n");
            xbee.write(buff,6);
            first = 1;
            //ThisThread::sleep_for(100ms);
        }
        if (abs(Tz) >=  6.5 && re >= 1 && cnt > 5) {
          //  printf("go");
            if (del < 0) {
                del = -del;
                car.follow(18, 20 + del / 2, 0.5, 1);
               // car.goStraight(100);
                ThisThread::sleep_for(100ms);
            }
            else {
               // del = -del;
                car.follow(18+del/2,20,0.4,1);
               // car.goStraight(-100);
                ThisThread::sleep_for(100ms);
            }
        }
        else if(abs(Tz) < 6.5 && cnt > 5) {
            re++;
           
           // printf("hello");
          //  finish = 0;
            if(finish == 0) {
              //  re = 1;
                finish = 1;
                right();
            }
            else if(dd == 0) {
                third = 1;
                car.stop();
                ThisThread::sleep_for(1s);
                sprintf(buff, "finish!!!\r\n");
                xbee.write(buff,11);
                ThisThread::sleep_for(1s);
                dd = 1;
            }

        }
    }
}
void right() {
   // printf("finish = %d", finish);
    char buff[20];
   // xbee.set_baud(9600);
    if (re == 2) {
        second = 1;
        sprintf(buff, "Turn right\r\n");
        xbee.write(buff,12);
        car.follow(28, -30, 0.8, 1);
        ThisThread::sleep_for(1900ms);
        car.stop();
        ThisThread::sleep_for(100ms);
        car.goStraight(30);
        ThisThread::sleep_for(1500ms);
        // re = 0;
    }
}

int main(){
    uart.set_baud(9600);
    t.start(inform);
    int i = 0;
    int j = 0;
  //  parallax_ping  ping1(pin10);
    while(1){
        
        if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
          //  pc.write(recv, sizeof(recv));
            if(recv[0] == 'S') swich = 0;
            if(recv[0] == '+') swich = 1;
            if (swich == 0) {
                if (i < 12) {
                    data2[i] = recv[0];
                    i++;
                }
                else if(i == 12){
                   data2[i] = recv[0];
                   i = 0;
                }
           }
            if (swich == 1) {
                if(j < 17) {
                        data[j] = recv[0];ss
                        j++;
                    }
                }
                else if(j == 17){
                    data[j] = recv[0];
                    j = 0;
                }
                   
            }
        }
    }
}