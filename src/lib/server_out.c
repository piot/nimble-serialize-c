/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/nimble-serialize-c
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/

#include <clog/clog.h>
#include <flood/out_stream.h>
#include <nimble-serialize/commands.h>
#include <nimble-serialize/server_out.h>

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
                                       Clog* log)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdGameStepResponse, log);
    fldOutStreamWriteUInt8(outStream, (uint8_t) connectionSpecificBufferCount);
    fldOutStreamWriteInt8(outStream, deltaAgainstAuthoritativeBuffer);
    return fldOutStreamWriteUInt32(outStream, lastReceivedStepIdFromClient);
}

/// Serialize a game join response for a previously received game join request.
/// Typically used on the server.
/// @param outStream out stream
/// @return negative on error
int nimbleSerializeServerOutJoinGameResponse(FldOutStream* outStream,
                                             const NimbleSerializeJoinGameResponse* gameResponse, Clog* log)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdJoinGameResponse, log);

    if (gameResponse->participantCount == 0) {
        CLOG_ERROR("participant count zero is not allowed")
        // return -44;
    }

    nimbleSerializeOutPartyAndSessionSecret(outStream, gameResponse->partyAndSessionSecret);

    int errorCode = fldOutStreamWriteUInt8(outStream, (uint8_t) gameResponse->participantCount);
    if (errorCode < 0) {
        return errorCode;
    }

    for (size_t i = 0; i < gameResponse->participantCount; ++i) {
        const NimbleSerializeJoinGameResponseParticipant* participant = &gameResponse->participants[i];
        errorCode = fldOutStreamWriteUInt8(outStream, (uint8_t) participant->localIndex);
        if (errorCode < 0) {
            return errorCode;
        }
        errorCode = nimbleSerializeOutParticipantId(outStream, participant->participantId);
        if (errorCode < 0) {
            return errorCode;
        }
    }

    return errorCode;
}

int nimbleSerializeServerOutConnectResponse(FldOutStream* outStream, const NimbleSerializeConnectResponse* response,
                                            Clog* log)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdConnectResponse, log);

    fldOutStreamWriteUInt8(outStream, response->useDebugStreams ? 0x01 : 0x00);

    return nimbleSerializeOutClientRequestId(outStream, response->responseToRequestId);
}


int nimbleSerializeServerOutPongResponse(FldOutStream* outStream, const NimbleSerializePongResponse* response,
                                            Clog* log)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdPongResponse, log);

    return fldOutStreamWriteUInt16(outStream, response->clientTime);
}


/// Serializes an out of participant slot response
/// @param outStream outstream
/// @param reqGameNonce request join game nonce
/// @return negative on error
int nimbleSerializeServerOutJoinGameOutOfParticipantSlotsResponse(FldOutStream* outStream,
                                                                  NimbleSerializeNonce reqGameNonce, Clog* log)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdJoinGameOutOfParticipantSlotsResponse, log);

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
                                              NimbleSerializeBlobStreamChannelId blobStreamChannelId, Clog* log)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdGameStateResponse, log);
    fldOutStreamWriteUInt8(outStream, clientRequestId);
    nimbleSerializeOutStateId(outStream, outGameState.stepId);
    CLOG_C_VERBOSE(log,
                   "sending game state response. request: %02X tickId: %08X blobStreamChannel %04X (octetCount %zu)",
                   clientRequestId, outGameState.stepId, blobStreamChannelId, outGameState.gameStateOctetCount)
    return nimbleSerializeOutBlobStreamChannelId(outStream, blobStreamChannelId);
}
