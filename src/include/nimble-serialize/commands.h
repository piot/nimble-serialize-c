/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef NIMBLE_SERIALIZE_COMMANDS_H
#define NIMBLE_SERIALIZE_COMMANDS_H

#include <stdint.h>

// Requests from Client to Server
#define NimbleSerializeCmdNop (0x00)
#define NimbleSerializeCmdGameStep (0x05)
#define NimbleSerializeCmdDownloadGameStateRequest (0x06)
#define NimbleSerializeCmdDownloadGameStateStatus (0x07)

// Responses from Server to client
#define NimbleSerializeCmdGameStepResponse (0x24)
#define NimbleSerializeCmdGameStatePart (0x27)
#define NimbleSerializeCmdGameStateResponse (0x28)

#endif
