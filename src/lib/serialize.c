/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/in_stream.h>
#include <flood/out_stream.h>
#include <nimble-serialize/serialize.h>
#include <nimble-serialize/debug.h>

#define NIMBLE_SERIALIZE_MARKER_CHANNEL_ID (0x19)
#define NIMBLE_SERIALIZE_MARKER_STATE_ID (0x9a)

int nimbleSerializeOutBlobStreamChannelId(struct FldOutStream* stream,
                                          const NimbleSerializeBlobStreamChannelId channelId)
{
    fldOutStreamWriteMarker(stream, NIMBLE_SERIALIZE_MARKER_CHANNEL_ID);
    return fldOutStreamWriteUInt32(stream, channelId);
}

int nimbleSerializeInBlobStreamChannelId(struct FldInStream* stream, NimbleSerializeBlobStreamChannelId* channelId)
{
    fldInStreamCheckMarker(stream, NIMBLE_SERIALIZE_MARKER_CHANNEL_ID);
    return fldInStreamReadUInt32(stream, channelId);
}

int nimbleSerializeOutStateId(struct FldOutStream* stream, const NimbleSerializeStateId stateId)
{
    fldOutStreamWriteMarker(stream, NIMBLE_SERIALIZE_MARKER_STATE_ID);
    return fldOutStreamWriteUInt32(stream, stateId);
}

int nimbleSerializeInStateId(struct FldInStream* stream, NimbleSerializeStateId* stateId)
{
    fldInStreamCheckMarker(stream, NIMBLE_SERIALIZE_MARKER_STATE_ID);
    return fldInStreamReadUInt32(stream, stateId);
}

void nimbleSerializeWriteCommand(struct FldOutStream* outStream, uint8_t cmd, const char* prefix)
{
    CLOG_VERBOSE("%s: cmd: %s", prefix, nimbleSerializeCmdToString(cmd));
    fldOutStreamWriteUInt8(outStream, cmd);
}
