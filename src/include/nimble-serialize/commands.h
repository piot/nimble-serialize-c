/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef NIMBLE_SERIALIZE_COMMANDS_H
#define NIMBLE_SERIALIZE_COMMANDS_H

#include <stdint.h>

#define NimbleSerializeCmdNop (0x00)

// Requests from Client to Server
#define NimbleSerializeCmdJoinGameRequest (0x01)
#define NimbleSerializeCmdGameStep (0x02)
#define NimbleSerializeCmdDownloadGameStateRequest (0x03)
#define NimbleSerializeCmdDownloadGameStateStatus (0x04)

// Responses from Server to client
#define NimbleSerializeCmdGameStepResponse (0x08)
#define NimbleSerializeCmdJoinGameResponse (0x09)
#define NimbleSerializeCmdGameStatePart (0x0a)
#define NimbleSerializeCmdGameStateResponse (0x0b)

#endif
