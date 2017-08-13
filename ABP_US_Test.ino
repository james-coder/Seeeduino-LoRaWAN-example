#include <LoRaWan.h>


unsigned char data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA,};
char buffer[256];


void setup(void)
{
    SerialUSB.begin(115200);
    while(!SerialUSB);
    
    lora.init();
    lora.setDeviceDefault();
	
    memset(buffer, 0, 256);
    lora.getVersion(buffer, 256, 1);
    SerialUSB.print(buffer); 
       
    memset(buffer, 0, 256);
    lora.getId(buffer, 256, 1);
    SerialUSB.print(buffer);

    //void setId(char *DevAddr, char *DevEUI, char *AppEUI);
    lora.setId("26021E70", "6547567536675634", "70B3D57EF0006934");
    //void setKey(char *NwkSKey, char *AppSKey, char *AppKey);    
    lora.setKey("B185A5ABF3DE774C8E2DF6B09F042AB6", "0FDA6921BDCAD36FB666E99F39C62AD7", NULL);
    
    lora.setDeciveMode(LWABP);
    lora.setDataRate(DR0, US915);
    lora.setAdaptiveDataRate(false);
        
    // lora.setChannel(0, 902.3, DR0, DR3);
    // lora.setChannel(1, 902.5, DR0, DR3);
    // lora.setChannel(2, 902.7, DR0, DR3);

    for(uint8_t i = 0; i < 72; i ++)lora.setChannel(i, 0);
    
    lora.setChannel(0, 903.9, DR0, DR3);
    lora.setChannel(1, 904.1, DR0, DR3);
    lora.setChannel(2, 904.3, DR0, DR3);
    lora.setChannel(3, 904.5, DR0, DR3);
    lora.setChannel(4, 904.7, DR0, DR3);
    lora.setChannel(5, 904.9, DR0, DR3);
    lora.setChannel(6, 905.1, DR0, DR3);
    lora.setChannel(7, 905.3, DR0, DR3);
    //lora.setChannel(8, 904.6, DR4, DR4);
    
    lora.setReceiceWindowFirst(0);
    lora.setReceiceWindowSecond(923.3, DR8);
    
    lora.setPower(20);
}

void loop(void)
{
    bool result = false;
    
    result = lora.transferPacket("Hello Ogden!", 3);
    //result = lora.transferPacket(data, 10, 10);
    
    if(result)
    {
        short length;
        short rssi;
        
        memset(buffer, 0, 256);
        length = lora.receivePacket(buffer, 256, &rssi);
        
        if(length)
        {
            SerialUSB.print("Length is: ");
            SerialUSB.println(length);
            SerialUSB.print("RSSI is: ");
            SerialUSB.println(rssi);
            SerialUSB.print("Data is: ");
            for(unsigned char i = 0; i < length; i ++)
            {
                SerialUSB.print("0x");
                SerialUSB.print(buffer[i], HEX);
                SerialUSB.print(" ");
            }
            SerialUSB.println();
        }
    }
	
	// lora.loraDebug();
}
