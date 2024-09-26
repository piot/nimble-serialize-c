/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/nimble-serialize-c
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/

#ifndef NIMBLE_SERIALIZE_SERVER_IN_H
#define NIMBLE_SERIALIZE_SERVER_IN_H

#include <nimble-serialize/serialize.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct FldInStream;

int nimbleSerializeServerInConnectRequest(struct FldInStream* stream, NimbleSerializeConnectRequest* request);
int nimbleSerializeServerInJoinGameRequest(struct FldInStream* stream, NimbleSerializeJoinGameRequest* request);

#endif
