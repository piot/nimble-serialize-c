/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/out_stream.h>
#include <inttypes.h>
#include <nimble-serialize/client_out.h>
#include <nimble-serialize/serialize.h>

NimbleSerializeVersion g_nimbleProtocolVersion = {0, 0, 5};

static int nimbleSerializeClientOutLocalPartyJoin(FldOutStream* stream,
                                                             const struct NimbleSerializeJoinGameRequestPlayer* players,
                                                             size_t playerCount, Clog* log)
{
    if (playerCount == 0) {
        CLOG_C_ERROR(log, "player count must be greater than zero")
    }
    CLOG_C_VERBOSE(log, "writing joining player count %zu", playerCount)
    int error = fldOutStreamWriteUInt8(stream, (uint8_t) playerCount);
    if (error < 0) {
        return error;
    }

    for (size_t i = 0; i < playerCount; ++i) {
        const NimbleSerializeJoinGameRequestPlayer* player = &players[i];
        error = fldOutStreamWriteUInt8(stream, player->localIndex);
        if (error < 0) {
            return error;
        }
    }

    return 0;
}

/// Write a connection request to the octet stream
/// @param stream out stream
/// @param request connect options
/// @return negative on error
int nimbleSerializeClientOutConnectRequest(FldOutStream* stream, const NimbleSerializeConnectRequest* request,
                                           Clog* log)
{
    nimbleSerializeWriteCommand(stream, NimbleSerializeCmdConnectRequest, log);
    nimbleSerializeOutVersion(stream, &g_nimbleProtocolVersion);
    fldOutStreamWriteUInt8(stream, request->useDebugStreams);
    nimbleSerializeOutVersion(stream, &request->applicationVersion);
    return nimbleSerializeOutNonce(stream, request->nonce);
}

/// Writes a JoinGameRequest to the octet stream
/// @param stream out stream
/// @param request game join request
/// @return negative on error
int nimbleSerializeClientOutJoinGameRequest(FldOutStream* stream, const NimbleSerializeJoinGameRequest* request,
                                            Clog* log)
{
    nimbleSerializeWriteCommand(stream, NimbleSerializeCmdJoinGameRequest, log);
    nimbleSerializeOutNonce(stream, request->nonce);
    fldOutStreamWriteUInt8(stream, (uint8_t) request->joinGameType);
    if (request->joinGameType == NimbleSerializeJoinGameTypePartySecret) {
        nimbleSerializeOutPartyAndSessionSecret(stream, request->partyAndSessionSecret);
    }

    return nimbleSerializeClientOutLocalPartyJoin(stream, request->players, request->playerCount, log);
}
