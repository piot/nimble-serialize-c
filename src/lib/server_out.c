/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include "clog/clog.h"
#include <flood/out_stream.h>
#include <nimble-serialize/commands.h>
#include <nimble-serialize/server_out.h>

#define DEBUG_PREFIX "ServerOut"

/// Writes a Step (Human Player Input) to an octet stream.
/// @param outStream the target octet stream.
/// @param lastReceivedStepIdFromClient The last received authoritative step received by the client.
/// @param connectionSpecificBufferCount Indicates how many Steps that are in the server incoming buffer for that
/// connection. Negative numbers represents the number of Steps it is behind.
/// @param deltaAgainstAuthoritativeBuffer The clamped indication on how far it is behind on the actual authoritative
/// buffer.
/// @return
int nimbleSerializeServerOutStepHeader(FldOutStream* outStream, uint32_t lastReceivedStepIdFromClient,
                                       size_t connectionSpecificBufferCount, int8_t deltaAgainstAuthoritativeBuffer)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdGameStepResponse, DEBUG_PREFIX);
    fldOutStreamWriteUInt8(outStream, connectionSpecificBufferCount);
    fldOutStreamWriteInt8(outStream, deltaAgainstAuthoritativeBuffer);
    return fldOutStreamWriteUInt32(outStream, lastReceivedStepIdFromClient);
}

static int writeConnectionIndexAndParticipantIds(FldOutStream* outStream, uint8_t participantConnectionIndex,
                                                 const NimbleSerializeParticipant* participants,
                                                 size_t participantCount)
{
    int errorCode = fldOutStreamWriteUInt8(outStream, participantConnectionIndex);
    if (errorCode < 0) {
        return errorCode;
    }
    if (participantCount == 0) {
        CLOG_ERROR("participant count zero is not allowed")
        return -44;
    }

    fldOutStreamWriteUInt8(outStream, participantCount);

    for (size_t i = 0; i < participantCount; ++i) {
        const NimbleSerializeParticipant* participant = &participants[i];
        fldOutStreamWriteUInt8(outStream, participant->localIndex);
        errorCode = fldOutStreamWriteUInt8(outStream, participant->id);
        if (errorCode < 0) {
            return errorCode;
        }
    }

    return 0;
}



/// Serialize a game join response for a previously received game join request.
/// @param outStream
/// @param participantConnectionIndex
/// @param participants
/// @param participantCount
/// @return
int nimbleSerializeServerOutGameJoinResponse(FldOutStream* outStream,
                                             NimbleSerializeParticipantConnectionIndex participantConnectionIndex,
                                             const NimbleSerializeParticipant* participants, size_t participantCount)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdJoinGameResponse, DEBUG_PREFIX);

    int errorCode = writeConnectionIndexAndParticipantIds(outStream, participantConnectionIndex, participants,
                                                          participantCount);
    return errorCode;
}


int nimbleSerializeServerOutGameStateResponse(FldOutStream* outStream, SerializeGameState outGameState, NimbleSerializeBlobStreamChannelId blobStreamChannelId) {
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdGameStateResponse, "ServerOut");
    nimbleSerializeOutStateId(outStream, outGameState.stepId);
    CLOG_VERBOSE("sending octetCount %zu", outGameState.gameStateOctetCount);
    fldOutStreamWriteUInt32(outStream, outGameState.gameStateOctetCount);
    return nimbleSerializeOutBlobStreamChannelId(outStream, blobStreamChannelId);
}
