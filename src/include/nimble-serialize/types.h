/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/nimble-serialize-c
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/

#ifndef NIMBLE_SERIALIZE_TYPES_H
#define NIMBLE_SERIALIZE_TYPES_H

#include <nimble-serialize/version.h>
#include <stddef.h>
#include <stdint.h>

typedef uint16_t NimbleSerializeBlobStreamChannelId;
typedef uint32_t NimbleSerializeStateId;
typedef uint8_t NimbleSerializeLocalPartyId;
typedef uint8_t NimbleSerializeParticipantId;
typedef uint64_t NimbleSerializeNonce;
typedef uint8_t NimbleSerializeClientRequestId;
typedef uint8_t NimbleSerializeConnectionId;
typedef uint64_t NimbleSerializeConnectionIdSecret;

#define NIMBLE_SERIALIZE_MAX_LOCAL_PLAYERS (4)

typedef struct {
    uint64_t value;
} NimbleSerializeSessionSecret;


typedef struct {
    NimbleSerializeSessionSecret sessionSecret;
    NimbleSerializeLocalPartyId partyId;
} NimbleSerializePartyAndSessionSecret;

typedef struct {
    NimbleSerializeParticipantId participantIds[NIMBLE_SERIALIZE_MAX_LOCAL_PLAYERS];
    size_t participantCount;
} NimbleSerializeLocalPartyInfo;



typedef struct NimbleSerializePingRequest {
    uint16_t clientTime;
} NimbleSerializePingRequest;

typedef struct NimbleSerializePongResponse {
    uint16_t clientTime;
} NimbleSerializePongResponse;


typedef struct NimbleSerializeConnectRequest {
    NimbleSerializeVersion applicationVersion;
    NimbleSerializeClientRequestId clientRequestId;
    bool useDebugStreams;
} NimbleSerializeConnectRequest;

typedef struct NimbleSerializeConnectResponse {
    bool useDebugStreams;
    NimbleSerializeClientRequestId responseToRequestId;
    NimbleSerializeConnectionId connectionId;
} NimbleSerializeConnectResponse;

typedef enum NimbleSerializeJoinGameType {
    NimbleSerializeJoinGameTypeNoSecret,
    NimbleSerializeJoinGameTypePartySecret,
} NimbleSerializeJoinGameType;

typedef struct NimbleSerializeJoinGameRequestPlayer {
    uint8_t localIndex;
    NimbleSerializeParticipantId participantId;
} NimbleSerializeJoinGameRequestPlayer;

typedef struct NimbleSerializeJoinGameRequest {
    NimbleSerializeJoinGameRequestPlayer players[NIMBLE_SERIALIZE_MAX_LOCAL_PLAYERS];
    size_t playerCount;
    NimbleSerializeNonce nonce;
    NimbleSerializeJoinGameType joinGameType;
    NimbleSerializePartyAndSessionSecret partyAndSessionSecret;
} NimbleSerializeJoinGameRequest;

typedef struct NimbleSerializeJoinGameResponseParticipant {
    size_t localIndex;
    NimbleSerializeParticipantId participantId;
} NimbleSerializeJoinGameResponseParticipant;

typedef struct NimbleSerializeJoinGameResponse {
    NimbleSerializePartyAndSessionSecret partyAndSessionSecret;
    NimbleSerializeJoinGameResponseParticipant participants[NIMBLE_SERIALIZE_MAX_LOCAL_PLAYERS];
    size_t participantCount;
} NimbleSerializeJoinGameResponse;

#endif
