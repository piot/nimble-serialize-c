/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef NIMBLE_SERIALIZE_SERVER_OUT_H
#define NIMBLE_SERIALIZE_SERVER_OUT_H

#include <stdint.h>
#include <stdlib.h>
#include <nimble-serialize/serialize.h>

struct FldOutStream;

int nimbleSerializeServerOutStepHeader(struct FldOutStream* outStream, uint32_t lastReceivedFromRemote,
                                       size_t connectionSpecificBufferCount, int8_t deltaAgainstAuthoritativeBuffer);

#endif
