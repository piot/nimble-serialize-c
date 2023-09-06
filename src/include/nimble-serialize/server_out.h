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
struct Clog;

typedef struct SerializeGameState {
    uint32_t stepId;
    const uint8_t* gameState;
    size_t gameStateOctetCount;
} SerializeGameState;

int nimbleSerializeServerOutStepHeader(struct FldOutStream* outStream, uint32_t lastReceivedFromRemote,
                                       size_t connectionSpecificBufferCount, int8_t deltaAgainstAuthoritativeBuffer,
                                       uint16_t monotonicTimeLowerBitsMs, struct Clog* log);

int nimbleSerializeServerOutConnectResponse(struct FldOutStream* outStream,
                                            const NimbleSerializeConnectResponse* response, struct Clog* log);

int nimbleSerializeServerOutJoinGameResponse(struct FldOutStream* outStream,
                                             const NimbleSerializeJoinGameResponse* response, struct Clog* log);

int nimbleSerializeServerOutJoinGameOutOfParticipantSlotsResponse(struct FldOutStream* outStream,
                                                                  NimbleSerializeNonce reqGameNonce, struct Clog* log);

int nimbleSerializeServerOutGameStateResponse(struct FldOutStream* outStream, SerializeGameState outGameState,
                                              uint8_t clientRequestId,
                                              NimbleSerializeBlobStreamChannelId blobStreamChannelId, struct Clog* log);

#endif
