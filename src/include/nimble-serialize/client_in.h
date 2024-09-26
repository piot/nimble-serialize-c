/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/nimble-serialize-c
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/

#ifndef NIMBLE_SERIALIZE_CLIENT_IN_H
#define NIMBLE_SERIALIZE_CLIENT_IN_H

#include <nimble-serialize/commands.h>
#include <nimble-serialize/types.h>
#include <nimble-serialize/version.h>
#include <stdint.h>
#include <stdlib.h>

struct FldInStream;

int nimbleSerializeClientInConnectResponse(FldInStream* stream, NimbleSerializeConnectResponse* response);
int nimbleSerializeClientInJoinGameResponse(FldInStream* stream, NimbleSerializeJoinGameResponse* response);

#endif
