MCU�ͺ�  ��STM32F103VCT6
Flash��С��256Kb
RAM��С  ��64Kb


/* LED�ƶ��� */
LED2 -> ����()
LED3 -> 485_2   Ӳ����
LED4 -> 485_1   Ӳ����
LED5 -> ����(PD2)    Ӳ����
LED6 -> ��Դ��(PC0)  Ӳ����
LED7 -> ������(PC1)  ƽʱ��������������
LED8 -> ���Ե�(PC2)  ����ģʽ��������ģʽ�� 
LED9 -> ���õ�(PC3)  



/* �ṹ�嶨�� */
������LoRaģ���շ�����
DIO1_EnableInterrupt    // ʹ��DIO1�ж�
SX126X_TxPacket         // ����
    |-> SX126xSetStandby                // ���óɴ���ģʽ
    |-> SX126xSetRegulatorMode          // ʹ��DC-DC
    |-> SX126XWriteRxTx                 // ���߿������ó� TX ģʽ
    |-> SX126xClearIrqStatus            // ������е��ж�
    |-> SX126xSetDioIrqParams           // ���� TX_DONE��TX_TIMEOUT �жϣ�ӳ�䵽DIO1
    |-> SX126xSetLoraModulationParams   // ���� SF��BW��CR�������������Ż�
    |-> SX126xSetLoraPacketParams       // ���� ǰ���볤�ȡ���ʽ/��ʽ��ͷ�����س��ȡ�CRCУ�顢�źż���
    |-> SX126xSetBufferBaseAddress      // �����շ�����ʼ��ַ
    |-> SX126xSendPayload               // �������ݣ����ó�ʱʱ��
    

DIO1_EnableInterrupt    // ʹ��DIO1�ж�
SX126X_StartRx          // ����
    |-> SX126xSetStandby                // ���óɴ���ģʽ
    |-> SX126xSetRegulatorMode          // ʹ��DC-DC
    |-> SX126XWriteRxTx                 // ���߿������ó� TX ģʽ
    |-> SX126xClearIrqStatus            // ������е��ж�
    |-> SX126xSetDioIrqParams           // ���� RX_DONE��RX_TIMEOUT �жϣ�ӳ�䵽DIO1     
    |-> SX126xSetStopRxTimerOnPreambleDetect    // �������ö�ʱ��ֹͣ�Ǽ�⵽��ͷ����ǰ����    
    |-> SX126xSetLoRaSymbNumTimeout     // ����������ȷLoRa�źŵ��ַ�������ͨ�����ó�0���� 
    |-> SX126xSetLoraModulationParams   // ���� SF��BW��CR�������������Ż�
    |-> SX126xSetLoraPacketParams       // ���� ǰ���볤�ȡ���ʽ/��ʽ��ͷ�����س��ȡ�CRCУ�顢�źż���
    |-> SX126xSetBufferBaseAddress      // �����շ�����ʼ��ַ
    |-> SX126xSetRx                     // �������ݣ����ó�ʱʱ�䣬timeout*15.625s�����Ϊ262s
                                        // 0x000000 ��ʾ�޳�ʱʱ��
                                        // 0xFFFFFF ��ʾ��������
                                        // 0x000000 - 0xFFFFFF ֮���ʾ���õĳ�ʱʱ��

flag = SX126xGetIrqStatus();
SX126xClearIrqStatus( IRQ_RADIO_ALL );  // clear flags


// RX_DONE �������
DIO1_DisableInterrupt                   // ��ֹ DIO1 �ж�
SX126X_RxPacket(RXbuffer)               
    |-> SX126xGetPacketStatus(&G_LoRaPara)  // �յ�һ�����ݺ󣬷���SNR��RSSI
    |-> SX126xClearIrqStatus(IRQ_RADIO_ALL) // ��������ж�
    |-> SX126xGetRxBufferStatus(&G_LoRaConfig.PayloadLength)    // ��ȡ�յ������ݰ�����
    |-> SX126xGetPayload(cbuf, &G_LoRaConfig.PayloadLength)     // �����Ч����

RSSI = G_LoRaPara.LastPacket_RSSI;          // ���һ�����ݵ�RSSI 
SNR = G_LoRaPara.Packet_SNR;                // SNR
Avg_RSSI = G_LoRaPara.AvgPacket_RSSI;       // ���ݰ�ƽ����RSSI








