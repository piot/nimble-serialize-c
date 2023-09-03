/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef NIMBLE_SERIALIZE_CLIENT_OUT_H
#define NIMBLE_SERIALIZE_CLIENT_OUT_H

#include <nimble-serialize/commands.h>
#include <nimble-serialize/types.h>
#include <nimble-serialize/version.h>
#include <stdint.h>
#include <stdlib.h>

struct FldOutStream;

int nimbleSerializeClientOutJoinGameRequest(struct FldOutStream* stream, const NimbleSerializeJoinGameRequest* request);
int nimbleSerializeClientOutConnectRequest(FldOutStream* stream, const NimbleSerializeConnectRequest* request);

#endif
