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

#define NIMBLE_SERIALIZE_MAX_LOCAL_PLAYERS (4)

typedef struct NimbleSerializeConnectRequest {
    NimbleSerializeVersion applicationVersion;
    bool useDebugStreams;
} NimbleSerializeConnectRequest;

typedef struct NimbleSerializeConnectResponse {
    bool useDebugStreams;
} NimbleSerializeConnectResponse;

typedef struct NimbleSerializeJoinGameRequestPlayer {
    uint8_t localIndex;
} NimbleSerializeJoinGameRequestPlayer;

typedef struct NimbleSerializeJoinGameRequest {
    NimbleSerializeJoinGameRequestPlayer players[NIMBLE_SERIALIZE_MAX_LOCAL_PLAYERS];
    size_t playerCount;
    NimbleSerializeNonce nonce;
    bool connectionSecretIsProvided;
    NimbleSerializeParticipantConnectionSecret connectionSecret;
} NimbleSerializeJoinGameRequest;

typedef struct NimbleSerializeJoinGameResponseParticipant {
    size_t localIndex;
    size_t id;
} NimbleSerializeJoinGameResponseParticipant;

typedef struct NimbleSerializeJoinGameResponse {
    NimbleSerializeParticipantConnectionIndex participantConnectionIndex;
    NimbleSerializeParticipantConnectionSecret participantConnectionSecret;
    NimbleSerializeJoinGameResponseParticipant participants[NIMBLE_SERIALIZE_MAX_LOCAL_PLAYERS];
    size_t participantCount;
} NimbleSerializeJoinGameResponse;

#endif
