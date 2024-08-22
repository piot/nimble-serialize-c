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
    return nimbleSerializeInConnectionIdSecret(stream, &options->connectionIdSecret);
}

int nimbleSerializeClientInJoinGameResponse(FldInStream* inStream, NimbleSerializeJoinGameResponse* response)
{
    uint8_t participantCount;

    int error = nimbleSerializeInPartyAndSessionSecret(inStream, &response->partyAndSessionSecret);
    if (error < 0) {
        return error;
    }


    error = fldInStreamReadUInt8(inStream, &participantCount);
    if (error < 0) {
        return error;
    }

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
        error = nimbleSerializeInParticipantId(inStream, &participant->participantId);
        if (error < 0) {
            return error;
        }
    }

    return 0;
}
