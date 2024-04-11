/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/in_stream.h>
#include <nimble-serialize/commands.h>
#include <nimble-serialize/server_in.h>
#include <nimble-serialize/version.h>

/// Connect request sent from the client to the server
/// It checks if the nimble protocol version and the application version is exactly the same
/// The application must be 100% deterministic, so it is vital that everyone in the session
/// is running an executable of the same version.
/// @param stream stream to read from
/// @param request the request
/// @return negative on error
int nimbleSerializeServerInConnectRequest(FldInStream* stream, NimbleSerializeConnectRequest* request)
{
    NimbleSerializeVersion nimbleProtocolVersion;

    nimbleSerializeInVersion(stream, &nimbleProtocolVersion);

    if (!nimbleSerializeVersionIsEqual(&nimbleProtocolVersion, &g_nimbleProtocolVersion)) {
        char buf[32];
        CLOG_SOFT_ERROR("wrong version of nimble protocol version. expected %s, but encountered %s",
                        nimbleSerializeVersionToString(&g_nimbleProtocolVersion, buf, 32),
                        nimbleSerializeVersionToString(&nimbleProtocolVersion, buf, 32))
        return -2;
    }

    uint8_t flags;
    fldInStreamReadUInt8(stream, &flags);

    request->useDebugStreams = flags & 0x01;

    nimbleSerializeInVersion(stream, &request->applicationVersion);

    return nimbleSerializeInNonce(stream, &request->nonce);
}

static int nimbleSerializeServerInJoinGameRequestPlayers(FldInStream* stream,
                                                         struct NimbleSerializeJoinGameRequestPlayer* players,
                                                         size_t* outPlayerCount)
{
    uint8_t playerCount;

    fldInStreamReadUInt8(stream, &playerCount);

    if (playerCount == 0 || playerCount > 8) {
        CLOG_SOFT_ERROR("illegal player count %hhu in join game request."
                        "local players are usually 1-2, and maybe up to 4 in splitscreen.",
                        playerCount)
        *outPlayerCount = 0;
        return -1;
    }

    for (size_t i = 0; i < playerCount; ++i) {
        fldInStreamReadUInt8(stream, &players[i].localIndex);
    }

    *outPlayerCount = playerCount;

    CLOG_VERBOSE("server read joining player count %hhu", playerCount)

    return 0;
}

/// Reads join game request sent from the client to the server.
/// @param stream to read from
/// @param request filled in by the deserialization
/// @return negative on error
int nimbleSerializeServerInJoinGameRequest(FldInStream* stream, NimbleSerializeJoinGameRequest* request)
{
    nimbleSerializeInNonce(stream, &request->nonce);

    uint8_t joinGameType = 0;

    fldInStreamReadUInt8(stream, &joinGameType);

    request->joinGameType = (NimbleSerializeJoinGameType) joinGameType;

    switch (request->joinGameType) {
        case NimbleSerializeJoinGameTypeNoSecret:
            break;
        case NimbleSerializeJoinGameTypeSecret:
            nimbleSerializeInConnectionSecret(stream, &request->connectionSecret);
            break;
        case NimbleSerializeJoinGameTypeHostMigrationParticipantId:
            nimbleSerializeInParticipantId(stream, &request->participantId);
            break;
    }

    return nimbleSerializeServerInJoinGameRequestPlayers(stream, request->players, &request->playerCount);
}
