/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/in_stream.h>
#include <nimble-serialize/client_in.h>
#include <nimble-serialize/serialize.h>

int nimbleSerializeClientInConnectResponse(FldInStream* stream, NimbleSerializeConnectResponse* options)
{
    uint8_t flags;

    fldInStreamReadUInt8(stream, &flags);

    options->useDebugStreams = flags & 0x01;

    nimbleSerializeInNonce(stream, &options->responseToNonce);
    nimbleSerializeInConnectionId(stream, &options->connectionId);
    return nimbleSerializeInConnectSecret(stream, &options->connectionSecret);
}

int nimbleSerializeClientInJoinGameResponse(FldInStream* inStream, NimbleSerializeJoinGameResponse* response)
{
    int errorCode = fldInStreamReadUInt8(inStream, &response->participantConnectionIndex);
    if (errorCode < 0) {
        return errorCode;
    }

    nimbleSerializeInConnectionSecret(inStream, &response->participantConnectionSecret);

    uint8_t participantCount;

    fldInStreamReadUInt8(inStream, &participantCount);

    response->participantCount = participantCount;
    if (response->participantCount == 0) {
        CLOG_SOFT_ERROR("participant count zero is not allowed")
        return -44;
    }
    for (size_t i = 0; i < participantCount; ++i) {
        NimbleSerializeJoinGameResponseParticipant* participant = &response->participants[i];
        uint8_t localIndex;
        fldInStreamReadUInt8(inStream, &localIndex);
        participant->localIndex = localIndex;

        uint8_t participantId;
        errorCode = fldInStreamReadUInt8(inStream, &participantId);
        if (errorCode < 0) {
            return errorCode;
        }
        participant->id = participantId;
    }

    return 0;
}
