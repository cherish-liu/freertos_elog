MCU型号  ：STM32F103VCT6
Flash大小：256Kb
RAM大小  ：64Kb


/* LED灯定义 */
LED2 -> 无线()
LED3 -> 485_2   硬件灯
LED4 -> 485_1   硬件灯
LED5 -> 蓝牙(PD2)    硬件灯
LED6 -> 电源灯(PC0)  硬件灯
LED7 -> 工作灯(PC1)  平时闪亮，升级常亮
LED8 -> 调试灯(PC2)  调试模式亮，工程模式灭 
LED9 -> 备用灯(PC3)  



/* 结构体定义 */
利尔达LoRa模块收发过程
DIO1_EnableInterrupt    // 使能DIO1中断
SX126X_TxPacket         // 发送
    |-> SX126xSetStandby                // 设置成待机模式
    |-> SX126xSetRegulatorMode          // 使用DC-DC
    |-> SX126XWriteRxTx                 // 天线开关设置成 TX 模式
    |-> SX126xClearIrqStatus            // 清除所有的中断
    |-> SX126xSetDioIrqParams           // 开启 TX_DONE、TX_TIMEOUT 中断，映射到DIO1
    |-> SX126xSetLoraModulationParams   // 设置 SF、BW、CR、低数据速率优化
    |-> SX126xSetLoraPacketParams       // 设置 前导码长度、显式/隐式报头、负载长度、CRC校验、信号极性
    |-> SX126xSetBufferBaseAddress      // 设置收发的起始地址
    |-> SX126xSendPayload               // 发送数据，设置超时时间
    

DIO1_EnableInterrupt    // 使能DIO1中断
SX126X_StartRx          // 接收
    |-> SX126xSetStandby                // 设置成待机模式
    |-> SX126xSetRegulatorMode          // 使用DC-DC
    |-> SX126XWriteRxTx                 // 天线开关设置成 TX 模式
    |-> SX126xClearIrqStatus            // 清除所有的中断
    |-> SX126xSetDioIrqParams           // 开启 RX_DONE、RX_TIMEOUT 中断，映射到DIO1     
    |-> SX126xSetStopRxTimerOnPreambleDetect    // 用来设置定时器停止是检测到报头还是前导码    
    |-> SX126xSetLoRaSymbNumTimeout     // 用来设置正确LoRa信号的字符个数，通常设置成0即可 
    |-> SX126xSetLoraModulationParams   // 设置 SF、BW、CR、低数据速率优化
    |-> SX126xSetLoraPacketParams       // 设置 前导码长度、显式/隐式报头、负载长度、CRC校验、信号极性
    |-> SX126xSetBufferBaseAddress      // 设置收发的起始地址
    |-> SX126xSetRx                     // 发送数据，设置超时时间，timeout*15.625s，最大为262s
                                        // 0x000000 表示无超时时间
                                        // 0xFFFFFF 表示连续接收
                                        // 0x000000 - 0xFFFFFF 之间表示设置的超时时间

flag = SX126xGetIrqStatus();
SX126xClearIrqStatus( IRQ_RADIO_ALL );  // clear flags


// RX_DONE 接收完成
DIO1_DisableInterrupt                   // 禁止 DIO1 中断
SX126X_RxPacket(RXbuffer)               
    |-> SX126xGetPacketStatus(&G_LoRaPara)  // 收到一包数据后，返回SNR、RSSI
    |-> SX126xClearIrqStatus(IRQ_RADIO_ALL) // 清除所有中断
    |-> SX126xGetRxBufferStatus(&G_LoRaConfig.PayloadLength)    // 获取收到的数据包长度
    |-> SX126xGetPayload(cbuf, &G_LoRaConfig.PayloadLength)     // 获得有效数据

RSSI = G_LoRaPara.LastPacket_RSSI;          // 最后一包数据的RSSI 
SNR = G_LoRaPara.Packet_SNR;                // SNR
Avg_RSSI = G_LoRaPara.AvgPacket_RSSI;       // 数据包平均的RSSI








