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

struct FldOutStream;

int nimbleSerializeClientOutGameJoin(struct FldOutStream* stream);

#endif
