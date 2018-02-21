
#include <SPI.h>
#include "RF24.h"

/*************  Hardware configuration *****************************/                                      // 
RF24 radio(9,10);                          // Set up nRF24L01 radio on SPI bus plus pins 7 & 8
int PinLM35 = A0;                         // chân analog kết nối tới cảm biến LM35
/***************************************************************/

const uint64_t pipes[2] = { 0x0808080808LL, 0x0808080808LL };   //địa chỉ truyền nhận 
byte data[32];                                   //Data buffer for testing data transfer speeds              
float voltage,temp;
int reading,nguyen,thapphan;

void setup(void) {

  Serial.begin(115200);

  radio.begin();                            // Setup and configure rf radio
  radio.setChannel(0);                      // chọn kênh 0 để truyển (2.400 Ghz)
  radio.setPALevel(RF24_PA_MAX);            // Max cường độ sóng
  radio.setDataRate(RF24_1MBPS);            // tốc độ truyền 1Mbi
  radio.setAutoAck(1);                      // Ensure autoACK is enabled
  radio.setRetries(2,15);                   // Optionally, increase the delay between retries & # of retries
  radio.setCRCLength(RF24_CRC_16);          // Use 16-bit CRC for performance
  radio.printDetails();                 
  radio.powerUp();                          //Power up the radio
  Serial.println("================== Do Nhiet DO ================== ");
  radio.openWritingPipe(pipes[1]);          // bật đường truyền với địa chỉ 
  radio.openReadingPipe(1,pipes[0]);        // bật đường nhận với địa chỉ 
  radio.stopListening();                    // tắt lắng nghe nhận
  
}

void loop(void){

    reading = analogRead(PinLM35);              // đọc giá trị adc
    voltage = reading * 5.0 / 1024.0;           //tính toán nhiệt độ
    temp = voltage * 100.0;                     //tính toán nhiệt độ
    nguyen=temp/1;                              // lấy phần nguyên và thập phân do sprintf không sử dụng %f được
    thapphan=((float)temp - nguyen) *100;       // lấy phần nguyên và thập phân do sprintf không sử dụng %f được
    
    sprintf(&data[1],"Nhiet do: %d.%d \n",nguyen,thapphan);               //truyền giá trị nhiệt độ vào buff truyền
    Serial.print("Nhiet do : ");                                          // truyển nhiệt độ lên sdk arduino
    Serial.println(temp);                                                 // truyển nhiệt độ lên sdk arduino
   
    data[0]=strlen(&data[1]);         // gán độ dài chuỗi vào data[0] để truyển cho master nhận
    radio.writeFast(&data,32);        // ghi dữ liệu vào fifo nrf24l01 truyền nrf24l01     

    delay(1000);                      // tạo trễ 1s
}
