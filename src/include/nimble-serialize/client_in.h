/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef NIMBLE_SERIALIZE_CLIENT_IN_H
#define NIMBLE_SERIALIZE_CLIENT_IN_H

#include <nimble-serialize/commands.h>
#include <stdint.h>
#include <stdlib.h>
#include <nimble-serialize/types.h>
#include <nimble-serialize/version.h>

struct FldInStream;

int nimbleSerializeClientInConnectResponse(FldInStream* stream, NimbleSerializeConnectResponse* options);
int nimbleSerializeClientInGameJoinResponse(FldInStream* stream, NimbleSerializeGameResponse* options);

#endif
