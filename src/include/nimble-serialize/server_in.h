/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef NIMBLE_SERIALIZE_SERVER_IN_H
#define NIMBLE_SERIALIZE_SERVER_IN_H

#include <nimble-serialize/serialize.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

struct FldInStream;

int nimbleSerializeServerInConnectRequest(struct FldInStream* stream, NimbleSerializeConnectRequest* options);
int nimbleSerializeServerInGameJoin(struct FldInStream* stream, NimbleSerializeGameJoinOptions* options);

#endif
