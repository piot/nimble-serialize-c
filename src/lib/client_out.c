/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/out_stream.h>
#include <nimble-serialize/client_out.h>
#include <nimble-serialize/serialize.h>

NimbleSerializeVersion g_nimbleProtocolVersion = {0, 0, 1};

static int nimbleSerializeClientOutParticipantConnectionJoin(FldOutStream* stream,
                                                             const struct NimbleSerializePlayerJoinOptions* joinInfos,
                                                             size_t localParticipantCount)
{
    if (localParticipantCount == 0) {
        CLOG_ERROR("participant count must be greater than zero")
    }
    CLOG_VERBOSE("joining participant count %zu", localParticipantCount)
    fldOutStreamWriteUInt8(stream, (uint8_t) localParticipantCount);
    for (size_t i = 0; i < localParticipantCount; ++i) {
        fldOutStreamWriteUInt8(stream, joinInfos[i].localIndex);
    }

    return 0;
}

/// Writes a JoinGameRequest to the octet stream
/// @param stream out stream
/// @param options game join options
/// @return negative on error
int nimbleSerializeClientOutGameJoin(FldOutStream* stream, const NimbleSerializeGameJoinOptions* options)
{
#define COMMAND_DEBUG "ClientOut"
    nimbleSerializeWriteCommand(stream, NimbleSerializeCmdJoinGameRequest, COMMAND_DEBUG);
    nimbleSerializeOutVersion(stream, &g_nimbleProtocolVersion);
    nimbleSerializeOutVersion(stream, &options->applicationVersion);
    nimbleSerializeOutNonce(stream, options->nonce);
    fldOutStreamWriteUInt8(stream, options->connectionSecretIsProvided ? 0x01 : 0x00);
    nimbleSerializeOutConnectionSecret(stream, options->connectionSecret);
    nimbleSerializeClientOutParticipantConnectionJoin(stream, options->players, options->playerCount);
    return 0;
}
