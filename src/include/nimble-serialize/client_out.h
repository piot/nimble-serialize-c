/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef NIMBLE_SERIALIZE_CLIENT_OUT_H
#define NIMBLE_SERIALIZE_CLIENT_OUT_H

#include <nimble-serialize/commands.h>
#include <stdint.h>
#include <stdlib.h>
#include <nimble-serialize/types.h>
#include <nimble-serialize/version.h>

struct FldOutStream;

typedef struct NimbleSerializePlayerJoinOptions {
    uint8_t localIndex;
} NimbleSerializePlayerJoinOptions;

typedef struct NimbleSerializeGameJoinOptions {
    NimbleSerializeVersion applicationVersion;
    NimbleSerializePlayerJoinOptions players[8];
    size_t playerCount;
    NimbleSerializeNonce nonce;
    bool connectionSecretIsProvided;
    NimbleSerializeParticipantConnectionSecret connectionSecret;
} NimbleSerializeGameJoinOptions;

int nimbleSerializeClientOutGameJoin(struct FldOutStream* stream, const NimbleSerializeGameJoinOptions* options);

#endif
