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
typedef uint8_t NimbleSerializeParticipantId;
typedef uint64_t NimbleSerializeNonce;
typedef uint64_t NimbleSerializeParticipantConnectionSecret;
typedef uint8_t NimbleSerializeConnectionId;
typedef uint64_t NimbleSerializeConnectionSecret;

#define NIMBLE_SERIALIZE_MAX_LOCAL_PLAYERS (4)

typedef struct NimbleSerializeConnectRequest {
    NimbleSerializeVersion applicationVersion;
    NimbleSerializeNonce nonce;
    bool useDebugStreams;
} NimbleSerializeConnectRequest;

typedef struct NimbleSerializeConnectResponse {
    bool useDebugStreams;
    NimbleSerializeNonce responseToNonce;
    NimbleSerializeConnectionId connectionId;
    NimbleSerializeConnectionSecret connectionSecret; // TODO: Exchange it in a secure way
} NimbleSerializeConnectResponse;

typedef struct NimbleSerializeJoinGameRequestPlayer {
    uint8_t localIndex;
} NimbleSerializeJoinGameRequestPlayer;

typedef enum NimbleSerializeJoinGameType {
    NimbleSerializeJoinGameTypeNoSecret,
    NimbleSerializeJoinGameTypeSecret,
    NimbleSerializeJoinGameTypeHostMigrationParticipantId
} NimbleSerializeJoinGameType;

typedef struct NimbleSerializeJoinGameRequest {
    NimbleSerializeJoinGameRequestPlayer players[NIMBLE_SERIALIZE_MAX_LOCAL_PLAYERS];
    size_t playerCount;
    NimbleSerializeNonce nonce;
    NimbleSerializeJoinGameType joinGameType;
    NimbleSerializeParticipantConnectionSecret connectionSecret;
    NimbleSerializeParticipantId participantId; // TODO: Only works for one participant per connection
} NimbleSerializeJoinGameRequest;

typedef struct NimbleSerializeJoinGameResponseParticipant {
    size_t localIndex;
    NimbleSerializeParticipantId id;
} NimbleSerializeJoinGameResponseParticipant;

typedef struct NimbleSerializeJoinGameResponse {
    NimbleSerializeParticipantConnectionIndex participantConnectionIndex;
    NimbleSerializeParticipantConnectionSecret participantConnectionSecret;
    NimbleSerializeJoinGameResponseParticipant participants[NIMBLE_SERIALIZE_MAX_LOCAL_PLAYERS];
    size_t participantCount;
} NimbleSerializeJoinGameResponse;

#endif
