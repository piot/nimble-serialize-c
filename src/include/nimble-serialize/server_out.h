/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef NIMBLE_SERIALIZE_SERVER_OUT_H
#define NIMBLE_SERIALIZE_SERVER_OUT_H

#include <nimble-serialize/serialize.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct FldOutStream;

typedef struct SerializeGameState {
    uint32_t stepId;
    const uint8_t* gameState;
    size_t gameStateOctetCount;
} SerializeGameState;

int nimbleSerializeServerOutStepHeader(struct FldOutStream* outStream, uint32_t lastReceivedFromRemote,
                                       size_t connectionSpecificBufferCount, int8_t deltaAgainstAuthoritativeBuffer,
                                       uint16_t monotonicTimeLowerBitsMs);

int nimbleSerializeServerOutConnectResponse(struct FldOutStream* outStream,
                                            const NimbleSerializeConnectResponse* response);

int nimbleSerializeServerOutJoinGameResponse(struct FldOutStream* outStream,
                                             const NimbleSerializeJoinGameResponse* response);

int nimbleSerializeServerOutJoinGameOutOfParticipantSlotsResponse(struct FldOutStream* outStream,
                                                                  NimbleSerializeNonce reqGameNonce);

int nimbleSerializeServerOutGameStateResponse(struct FldOutStream* outStream, SerializeGameState outGameState,
                                              uint8_t clientRequestId,
                                              NimbleSerializeBlobStreamChannelId blobStreamChannelId);

#endif
