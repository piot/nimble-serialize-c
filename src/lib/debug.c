/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <nimble-serialize/debug.h>
#include <stdio.h>

const char* nimbleSerializeCmdToString(uint8_t cmd)
{
    static const char* lookup[] = {
        "NOP",      "JoinGameRequest", "GameStep",         "GameStateRequest", "GameStateStatus", "not used",
        "not used", "not used",        "GameStepResponse", "JoinGameResponse", "GameStatePart",   "GameStateResponse",
    };

    if (cmd < 0 || cmd >= sizeof(lookup) / sizeof(lookup[0])) {
        CLOG_ERROR("Unknown serialize command: %02X", cmd)
        return 0;
    }

    return lookup[cmd];
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
