/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/out_stream.h>
#include <nimble-serialize/client_out.h>
#include <nimble-serialize/serialize.h>
#include <inttypes.h>

NimbleSerializeVersion g_nimbleProtocolVersion = {0, 0, 3};

static int nimbleSerializeClientOutParticipantConnectionJoin(FldOutStream* stream,
                                                             const struct NimbleSerializeJoinGameRequestPlayer* players,
                                                             size_t playerCount, Clog* log)
{
    if (playerCount == 0) {
        CLOG_C_ERROR(log, "player count must be greater than zero")
    }
    CLOG_C_VERBOSE(log, "writing joining player count %zu", playerCount)
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
int nimbleSerializeClientOutConnectRequest(FldOutStream* stream, const NimbleSerializeConnectRequest* request,
                                           Clog* log)
{
    nimbleSerializeWriteCommand(stream, NimbleSerializeCmdConnectRequest, log);
    nimbleSerializeOutVersion(stream, &g_nimbleProtocolVersion);
    fldOutStreamWriteUInt8(stream, request->useDebugStreams);
    return nimbleSerializeOutVersion(stream, &request->applicationVersion);
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

    CLOG_C_DEBUG(log, "join game request type: %d", request->joinGameType)

    switch (request->joinGameType) {
        case NimbleSerializeJoinGameTypeNoSecret:
            break;
        case NimbleSerializeJoinGameTypeSecret:
            CLOG_C_DEBUG(log, "join game request secret id: %" PRIX64, request->connectionSecret)
            nimbleSerializeOutConnectionSecret(stream, request->connectionSecret);
            break;
        case NimbleSerializeJoinGameTypeHostMigrationParticipantId:
            CLOG_C_DEBUG(log, "join game request host migration participant id: %hhu", request->participantId)
            nimbleSerializeOutParticipantId(stream, request->participantId);
            break;
    }

    return nimbleSerializeClientOutParticipantConnectionJoin(stream, request->players, request->playerCount, log);
}
