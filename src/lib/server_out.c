/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/out_stream.h>
#include <nimble-serialize/commands.h>
#include <nimble-serialize/server_out.h>

#define DEBUG_PREFIX "ServerOut"

/// Writes a Step (Human Player Input) to an octet stream.
/// Typically used on the server.
/// @param outStream the target octet stream.
/// @param lastReceivedStepIdFromClient The last received authoritative step received by the client.
/// @param connectionSpecificBufferCount Indicates how many Steps that are in the server incoming buffer for that
/// connection. Negative numbers represents the number of Steps it is behind.
/// @param deltaAgainstAuthoritativeBuffer The clamped indication on how far it is behind on the actual authoritative
/// buffer.
/// @return negative on error
int nimbleSerializeServerOutStepHeader(FldOutStream* outStream, uint32_t lastReceivedStepIdFromClient,
                                       size_t connectionSpecificBufferCount, int8_t deltaAgainstAuthoritativeBuffer,
                                       uint16_t monotonicShortMs)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdGameStepResponse, DEBUG_PREFIX);
    fldOutStreamWriteUInt8(outStream, (uint8_t) connectionSpecificBufferCount);
    fldOutStreamWriteInt8(outStream, deltaAgainstAuthoritativeBuffer);
    fldOutStreamWriteUInt16(outStream, monotonicShortMs);
    return fldOutStreamWriteUInt32(outStream, lastReceivedStepIdFromClient);
}


/// Serialize a game join response for a previously received game join request.
/// Typically used on the server.
/// @param outStream out stream
/// @return negative on error
int nimbleSerializeServerOutGameJoinResponse(FldOutStream* outStream,
                                             const NimbleSerializeGameResponse* gameResponse)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdJoinGameResponse, DEBUG_PREFIX);

    int errorCode = fldOutStreamWriteUInt8(outStream, gameResponse->participantConnectionIndex);
    if (errorCode < 0) {
        return errorCode;
    }
    if (gameResponse->participantCount == 0) {
        CLOG_ERROR("participant count zero is not allowed")
        // return -44;
    }

    nimbleSerializeOutConnectionSecret(outStream, gameResponse->participantConnectionSecret);

    fldOutStreamWriteUInt8(outStream, (uint8_t) gameResponse->participantCount);

    for (size_t i = 0; i < gameResponse->participantCount; ++i) {
        const NimbleSerializeParticipant* participant = &gameResponse->participants[i];
        fldOutStreamWriteUInt8(outStream, (uint8_t) participant->localIndex);
        errorCode = fldOutStreamWriteUInt8(outStream, (uint8_t) participant->id);
        if (errorCode < 0) {
            return errorCode;
        }
    }

    return errorCode;
}


int nimbleSerializeServerOutConnectResponse(FldOutStream* outStream,
                                             const NimbleSerializeConnectResponse* response)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdConnectResponse, DEBUG_PREFIX);

    return fldOutStreamWriteUInt8(outStream, response->useDebugStreams ? 0x01 : 0x00);
}

/// Serializes an out of participant slot response
/// @param outStream outstream
/// @param reqGameNonce request join game nonce
/// @return negative on error
int nimbleSerializeServerOutGameJoinOutOfParticipantSlotsResponse(FldOutStream* outStream,
                                                                  NimbleSerializeNonce reqGameNonce)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdJoinGameOutOfParticipantSlotsResponse, DEBUG_PREFIX);

    int errorCode = nimbleSerializeOutNonce(outStream, reqGameNonce);

    return errorCode;
}

/// Writes a response to a download game state request
/// Typically used on the server.
/// @param outStream ut stream
/// @param outGameState application specific total state
/// @param clientRequestId ID of the previous request
/// @param blobStreamChannelId the channel to transfer the state on
/// @return negative on error
int nimbleSerializeServerOutGameStateResponse(FldOutStream* outStream, SerializeGameState outGameState,
                                              uint8_t clientRequestId,
                                              NimbleSerializeBlobStreamChannelId blobStreamChannelId)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdGameStateResponse, "ServerOut");
    fldOutStreamWriteUInt8(outStream, clientRequestId);
    nimbleSerializeOutStateId(outStream, outGameState.stepId);
    CLOG_VERBOSE("sending octetCount %zu", outGameState.gameStateOctetCount)
    fldOutStreamWriteUInt32(outStream, (uint32_t) outGameState.gameStateOctetCount);
    return nimbleSerializeOutBlobStreamChannelId(outStream, blobStreamChannelId);
}
