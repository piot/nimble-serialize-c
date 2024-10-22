/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/nimble-serialize-c
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/

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
        "NOP",
        "JoinGameRequest",
        "GameStep",
        "GameStateRequest",
        "BlobStreamFromClient",
        "Connect Request",
        "Ping Request",
        "not used",
        "GameStepResponse",
        "JoinGameResponse",
        "GameStatePart",
        "GameStateResponse",
        "JoinGameResponseParticipantFull",
        "ConnectResponse",
        "Pong Response",
    };

    if (cmd >= sizeof(lookup) / sizeof(lookup[0])) {
        CLOG_ERROR("Unknown serialize command: %02X", cmd)
        // return 0;
    }

    return lookup[cmd];
}
