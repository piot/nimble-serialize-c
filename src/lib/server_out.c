/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include "clog/clog.h"
#include "nimble-serialize/debug.h"
#include <flood/out_stream.h>
#include <nimble-serialize/commands.h>
#include <nimble-serialize/server_out.h>

#define DEBUG_PREFIX "ServerOut"

int nimbleSerializeServerOutStepHeader(FldOutStream* outStream, uint32_t lastReceivedStepIdFromClient, size_t connectionSpecificBufferCount, int8_t deltaAgainstAuthoritativeBuffer)
{
    nimbleSerializeWriteCommand(outStream, NimbleSerializeCmdGameStepResponse, DEBUG_PREFIX);
    fldOutStreamWriteUInt8(outStream, connectionSpecificBufferCount);
    fldOutStreamWriteInt8(outStream, deltaAgainstAuthoritativeBuffer);
    fldOutStreamWriteUInt32(outStream, lastReceivedStepIdFromClient);

    return 0;
}
