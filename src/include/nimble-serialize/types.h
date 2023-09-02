/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef NIMBLE_SERIALIZE_TYPES_H
#define NIMBLE_SERIALIZE_TYPES_H

#include <nimble-serialize/version.h>
#include <stddef.h>
#include <stdint.h>

typedef uint32_t NimbleSerializeBlobStreamChannelId;
typedef uint32_t NimbleSerializeStateId;
typedef uint8_t NimbleSerializeParticipantConnectionIndex;
typedef uint64_t NimbleSerializeNonce;
typedef uint64_t NimbleSerializeParticipantConnectionSecret;

typedef struct NimbleSerializeConnectRequest {
    NimbleSerializeVersion applicationVersion;
    bool useDebugStreams;
} NimbleSerializeConnectRequest;

typedef struct NimbleSerializeConnectResponse {
    bool useDebugStreams;
} NimbleSerializeConnectResponse;

typedef struct NimbleSerializePlayerJoinOptions {
    uint8_t localIndex;
} NimbleSerializePlayerJoinOptions;

typedef struct NimbleSerializeGameJoinOptions {
    NimbleSerializePlayerJoinOptions players[8];
    size_t playerCount;
    NimbleSerializeNonce nonce;
    bool connectionSecretIsProvided;
    NimbleSerializeParticipantConnectionSecret connectionSecret;
} NimbleSerializeGameJoinOptions;

typedef struct NimbleSerializeParticipant {
    size_t localIndex;
    size_t id;
} NimbleSerializeParticipant;

typedef struct NimbleSerializeGameResponse {
    NimbleSerializeParticipantConnectionIndex participantConnectionIndex;
    NimbleSerializeParticipantConnectionSecret participantConnectionSecret;
    NimbleSerializeParticipant participants[8];
    size_t participantCount;
} NimbleSerializeGameResponse;

#define MAX_LOCAL_PLAYERS (4)

#endif
