/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <nimble-serialize/commands.h>
#include <nimble-serialize/debug.h>
#include <stdio.h>

const char* nimbleSerializeCmdToString(uint8_t t)
{
    switch (t) {
        case NimbleSerializeCmdNop:
            return "Nop";
        case NimbleSerializeCmdGameStep:
            return "GameStep";
        case NimbleSerializeCmdGameStepResponse:
            return "GameStepResponse";
        case NimbleSerializeCmdGameStateResponse:
            return "GameStateResponse";
        case NimbleSerializeCmdDownloadGameStateRequest:
            return "DownloadStateRequest";
        case NimbleSerializeCmdDownloadGameStateStatus:
            return "DownloadStateStatus";
        default:
        {
            static char buf[128];
            tc_snprintf(buf, 128, "no idea %02X", t);
            return buf;
        }

    }
}

// Responses

void nimbleSerializeDebugHex(const char* debug, const uint8_t* data, size_t length)
{
    CLOG_INFO(" ### %s %s ###", debug, nimbleSerializeCmdToString(data[0]));

    for (size_t i = 1; i < length; ++i) {
        printf("%02X ", data[i]);
    }

    if (length > 0) {
        printf("\n");
    }
}
