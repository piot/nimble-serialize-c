/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <nimble-serialize/debug.h>
#include <stdio.h>

/// Converts a Nimble command to a string
/// Dependant on the `commands.h` header file
/// @param cmd command to log
/// @return return string representation of cmd
const char* nimbleSerializeCmdToString(uint8_t cmd)
{
    static const char* lookup[] = {
        "NOP",      "JoinGameRequest", "GameStep",         "GameStateRequest", "GameStateStatus", "not used",
        "not used", "not used",        "GameStepResponse", "JoinGameResponse", "GameStatePart",   "GameStateResponse", "JoinGameResponseParticipantFull"
    };

    if (cmd >= sizeof(lookup) / sizeof(lookup[0])) {
        CLOG_ERROR("Unknown serialize command: %02X", cmd)
        //return 0;
    }

    return lookup[cmd];
}

/// Writes the hex data to stdout. Only used for debugging
/// @param debug description prefix
/// @param data payload to log as hex
/// @param length octet size of data
void nimbleSerializeDebugHex(const char* debug, const uint8_t* data, size_t length)
{
    (void) debug;
    CLOG_INFO(" ### %s %s ###", debug, nimbleSerializeCmdToString(data[0]))

    for (size_t i = 1; i < length; ++i) {
        printf("%02X ", data[i]);
    }

    if (length > 0) {
        printf("\n");
    }
}
