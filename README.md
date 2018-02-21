Kết nối chân
======= NRF24L01 =========
NRF24	Arduino
1	GND
2	3.3V
3	D9
4	D10
5	D13
6	D11
7	D12
8	Không dùng
========= LM35 ===========
LM35	Arduino
1(VCC)	5V
2(data) A0
3(GND)	GND


Config USB NRF24l01 (usb kết nối máy tính)

- cài driver cho usb (CH340)
- Cắm usb nhận cổng COM , Ví dụ (COM6)
- Bật chương trình Terminal kết nối với COM6 với baud 9600 (mặc định)
- Setup thông số chỉ cần set up 1 lần gõ từng lệnh
	- AT? 			xem cấu hình đang sử dụng
	- AT+BAUD=n      	cài tốc độ baud với máy tính  n =  1-6 (1:4800,2:9600,3:14400,4:19200,5:38400,6:115200) (sử dụng 9600Kbps)  
	- AT+RATE=n 		cài tốc độ truyền nhận nrf24l01 where n =  1-3 (1:250K, 2:1M, 3:2M ) (sử dụng 1Mbps)
	- AT+RXA=0Xnn,0Xnn,0Xnn,0Xnn,0Xnn          địa chỉ nhận    (sử dụng 0x08,0x08,0x08,0x08,0x08)
	- AT+TXA=0Xnn,0Xnn,0Xnn,0Xnn,0Xnn          địa chỉ truyền  (sử dụng 0x08,0x08,0x08,0x08,0x08)
	- AT+FREQ=2.nnnG 	cài đặt kênh với nnn = 400 / 525 (sử dụng 2.400G) (kênh 0 ở arduino)
	- AT+CRC=n              cài đặt số bit kiểm tra khung CRC  n = 8 /16 (sử dụng : 16 bit)

- xem dữ liệu nhận trên terminal
	khung dữ liệu khi arduino truyển byte[0] : số byte truyển trong khung 
					 byte[1..31] : byte data


