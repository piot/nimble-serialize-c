/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/out_stream.h>
#include <nimble-serialize/client_out.h>
#include <nimble-serialize/serialize.h>

NimbleSerializeVersion g_nimbleProtocolVersion = {0, 0, 2};

#define COMMAND_DEBUG "ClientOut"

static int nimbleSerializeClientOutParticipantConnectionJoin(FldOutStream* stream,
                                                             const struct NimbleSerializeJoinGameRequestPlayer* players,
                                                             size_t playerCount)
{
    if (playerCount == 0) {
        CLOG_ERROR("player count must be greater than zero")
    }
    CLOG_VERBOSE("joining player count %zu", playerCount)
    fldOutStreamWriteUInt8(stream, (uint8_t) playerCount);
    for (size_t i = 0; i < playerCount; ++i) {
        fldOutStreamWriteUInt8(stream, players[i].localIndex);
    }

    return 0;
}

/// Write a connection request to the octet stream
/// @param stream out stream
/// @param request connect options
/// @return negative on error
int nimbleSerializeClientOutConnectRequest(FldOutStream* stream, const NimbleSerializeConnectRequest* request)
{
    nimbleSerializeWriteCommand(stream, NimbleSerializeCmdConnectRequest, COMMAND_DEBUG);
    nimbleSerializeOutVersion(stream, &g_nimbleProtocolVersion);
    fldOutStreamWriteUInt8(stream, request->useDebugStreams);
    return nimbleSerializeOutVersion(stream, &request->applicationVersion);
}

/// Writes a JoinGameRequest to the octet stream
/// @param stream out stream
/// @param request game join request
/// @return negative on error
int nimbleSerializeClientOutJoinGameRequest(FldOutStream* stream, const NimbleSerializeJoinGameRequest* request)
{
    nimbleSerializeWriteCommand(stream, NimbleSerializeCmdJoinGameRequest, COMMAND_DEBUG);
    nimbleSerializeOutNonce(stream, request->nonce);
    fldOutStreamWriteUInt8(stream, request->connectionSecretIsProvided ? 0x01 : 0x00);
    if (request->connectionSecretIsProvided) {
        nimbleSerializeOutConnectionSecret(stream, request->connectionSecret);
    }

    return nimbleSerializeClientOutParticipantConnectionJoin(stream, request->players, request->playerCount);
}
