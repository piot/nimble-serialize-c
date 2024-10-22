/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/nimble-serialize-c
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/

#ifndef NIMBLE_SERIALIZE_COMMANDS_H
#define NIMBLE_SERIALIZE_COMMANDS_H

#include <stdint.h>

#define NimbleSerializeCmdNop (0x00)

// Requests from Client to Server
#define NimbleSerializeCmdJoinGameRequest (0x01)
#define NimbleSerializeCmdGameStep (0x02)
#define NimbleSerializeCmdDownloadGameStateRequest (0x03)
#define NimbleSerializeCmdClientOutBlobStream (0x04)
#define NimbleSerializeCmdConnectRequest (0x05)
#define NimbleSerializeCmdPingRequest (0x06)

// Responses from Server to client
#define NimbleSerializeCmdGameStepResponse (0x08)
#define NimbleSerializeCmdJoinGameResponse (0x09)
#define NimbleSerializeCmdServerOutBlobStream (0x0c)
#define NimbleSerializeCmdGameStateResponse (0x0b)
#define NimbleSerializeCmdJoinGameOutOfParticipantSlotsResponse (0x0e)
#define NimbleSerializeCmdConnectResponse (0x0d)
#define NimbleSerializeCmdPongResponse (0x0e)

#endif
