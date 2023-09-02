/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/in_stream.h>
#include <nimble-serialize/commands.h>
#include <nimble-serialize/server_in.h>
#include <nimble-serialize/version.h>

int nimbleSerializeServerInConnectRequest(FldInStream* stream, NimbleSerializeConnectRequest* options)
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

    options->useDebugStreams = flags & 0x01;

    nimbleSerializeInVersion(stream, &options->applicationVersion);
    return 0;
}

/*
int nimbleSerializeClientOutGameJoin(FldOutStream* stream, const NimbleSerializeGameJoinOptions* options)
{
    nimbleSerializeWriteCommand(stream, NimbleSerializeCmdJoinGameRequest, COMMAND_DEBUG);
    nimbleSerializeOutNonce(stream, options->nonce);
    fldOutStreamWriteUInt8(stream, options->connectionSecretIsProvided ? 0x01 : 0x00);
    nimbleSerializeOutConnectionSecret(stream, options->connectionSecret);
    nimbleSerializeClientOutParticipantConnectionJoin(stream, options->players, options->playerCount);
*/

static int nimbleSerializeServerInParticipantConnectionJoin(FldInStream* stream,
                                                            struct NimbleSerializePlayerJoinOptions* joinInfos, size_t* outPlayerCount)
{
    uint8_t playerCount;

    fldInStreamReadUInt8(stream, &playerCount);

    if (playerCount == 0 || playerCount > 8) {
        CLOG_SOFT_ERROR("illegal participant count")
        return -1;
    }

    for (size_t i = 0; i < playerCount; ++i) {
        fldInStreamReadUInt8(stream, &joinInfos[i].localIndex);
    }

    *outPlayerCount = playerCount;

    CLOG_VERBOSE("read joining participant count %hhu", playerCount)

    return 0;
}

int nimbleSerializeServerInGameJoin(FldInStream* stream, NimbleSerializeGameJoinOptions* options)
{
    NimbleSerializeNonce requestJoinNonce;
    nimbleSerializeInNonce(stream, &requestJoinNonce);

    uint8_t masks = 0;
    fldInStreamReadUInt8(stream, &masks);

    bool secretIsProvided = masks & 0x01;

    NimbleSerializeParticipantConnectionSecret previousSecret;
    if (secretIsProvided) {
        nimbleSerializeInConnectionSecret(stream, &previousSecret);
    } else {
        previousSecret = 0;
    }

    return nimbleSerializeServerInParticipantConnectionJoin(stream, options->players, &options->playerCount);
}
