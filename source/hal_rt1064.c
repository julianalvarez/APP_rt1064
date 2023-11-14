/*
 * hal_rt1064.c
 *
 *  Created on: 14 nov. 2023
 *      Author: PLANTIUM
 */
#include "j1939.h"
#include "hal.h"
#include "can_ext.h"
#include "can.h"



void init_CAN (uint32_t ctrl, uint32_t baudrate)
{
    init_can (ctrl, 0, 0, 0, baudrate/1000);
}

void PutMSG_CAN (uint32_t ctrl, J1939_MESSAGE_T* pJ1939Msg)
{
    tSend            Msg;

    Msg.dwId = (((uint32_t)pJ1939Msg->Priority) << 26) |
               (((uint32_t)pJ1939Msg->Pgn) << 8)       |
               (uint32_t)pJ1939Msg->SourceAddress;
    Msg.bDlc = pJ1939Msg->Length;
    Msg.bXtd = pJ1939Msg->bfEFF;
    memcpy (Msg.abData, pJ1939Msg->Data, Msg.bDlc);

    send_can_msg (ctrl, 0, &Msg);
}
