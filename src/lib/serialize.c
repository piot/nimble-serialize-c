/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <nimble-serialize/serialize.h>
#include <nimble-serialize/debug.h>

#include "clog/clog.h"
#include <flood/in_stream.h>
#include <flood/out_stream.h>

int nimbleSerializeOutBlobStreamChannelId(struct FldOutStream* stream, const NimbleSerializeBlobStreamChannelId channelId)
{
    fldOutStreamWriteMarker(stream, 0x19);
    return fldOutStreamWriteUInt32(stream, channelId);
}

int nimbleSerializeInBlobStreamChannelId(struct FldInStream* stream, NimbleSerializeBlobStreamChannelId* channelId)
{
    fldInStreamCheckMarker(stream, 0x19);
    return fldInStreamReadUInt32(stream, channelId);
}

int nimbleSerializeOutStateId(struct FldOutStream* stream, const NimbleSerializeStateId stateId)
{
    fldOutStreamWriteMarker(stream, 0x9a);
    return fldOutStreamWriteUInt32(stream, stateId);
}

int nimbleSerializeInStateId(struct FldInStream* stream, NimbleSerializeStateId* stateId)
{
    fldInStreamCheckMarker(stream, 0x9a);
    return fldInStreamReadUInt32(stream, stateId);
}

void nimbleSerializeWriteCommand(struct FldOutStream* outStream, uint8_t cmd, const char* prefix)
{
    CLOG_VERBOSE("%s: cmd: %s", prefix, nimbleSerializeCmdToString(cmd));
    fldOutStreamWriteUInt8(outStream, cmd);
}
