/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef NIMBLE_SERIALIZE_SERVER_OUT_H
#define NIMBLE_SERIALIZE_SERVER_OUT_H

#include <nimble-serialize/serialize.h>
#include <stdint.h>
#include <stdlib.h>

struct FldOutStream;

typedef struct NimbleSerializeParticipant {
    size_t localIndex;
    size_t id;
} NimbleSerializeParticipant;

typedef struct SerializeGameState {
    uint32_t stepId;
    const uint8_t* gameState;
    size_t gameStateOctetCount;
} SerializeGameState;

int nimbleSerializeServerOutStepHeader(struct FldOutStream* outStream, uint32_t lastReceivedFromRemote,
                                       size_t connectionSpecificBufferCount, int8_t deltaAgainstAuthoritativeBuffer,
                                       uint16_t monotonicTimeLowerBitsMs);

int nimbleSerializeServerOutGameJoinResponse(struct FldOutStream* outStream,
                                             NimbleSerializeParticipantConnectionIndex connectionIndex,
                                             const NimbleSerializeParticipant* participants, size_t participantCount);

int nimbleSerializeServerOutGameJoinOutOfParticipantSlotsResponse(struct FldOutStream* outStream,
                                                                  NimbleSerializeNonce reqGameNonce);

int nimbleSerializeServerOutGameStateResponse(struct FldOutStream* outStream, SerializeGameState outGameState,
                                              uint8_t clientRequestId,
                                              NimbleSerializeBlobStreamChannelId blobStreamChannelId);

#endif
