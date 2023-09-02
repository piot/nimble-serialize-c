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

/// Write a connection request to the octet stream
/// @param stream out stream
/// @param options connect options
/// @return negative on error
int nimbleSerializeClientOutConnect(FldOutStream* stream, const NimbleSerializeConnectRequest* options)
{
    nimbleSerializeWriteCommand(stream, NimbleSerializeCmdConnectRequest, COMMAND_DEBUG);
    nimbleSerializeOutVersion(stream, &g_nimbleProtocolVersion);
    fldOutStreamWriteUInt8(stream, options->useDebugStreams);
    nimbleSerializeOutVersion(stream, &options->applicationVersion);
    return 0;
}

/// Writes a JoinGameRequest to the octet stream
/// @param stream out stream
/// @param options game join options
/// @return negative on error
int nimbleSerializeClientOutGameJoin(FldOutStream* stream, const NimbleSerializeGameJoinOptions* options)
{
    nimbleSerializeWriteCommand(stream, NimbleSerializeCmdJoinGameRequest, COMMAND_DEBUG);
    nimbleSerializeOutNonce(stream, options->nonce);
    fldOutStreamWriteUInt8(stream, options->connectionSecretIsProvided ? 0x01 : 0x00);
    if (options->connectionSecretIsProvided) {
        nimbleSerializeOutConnectionSecret(stream, options->connectionSecret);
    }
    nimbleSerializeClientOutParticipantConnectionJoin(stream, options->players, options->playerCount);
    return 0;
}
