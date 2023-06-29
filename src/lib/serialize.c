/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <flood/in_stream.h>
#include <flood/out_stream.h>
#include <nimble-serialize/serialize.h>
#if defined CONFIGURATION_DEBUG
#include <nimble-serialize/debug.h>
#endif

/// Writes a channelId to the octet stream
/// @param stream out stream
/// @param channelId blob stream channel id
/// @return negative on error
int nimbleSerializeOutBlobStreamChannelId(struct FldOutStream* stream,
                                          const NimbleSerializeBlobStreamChannelId channelId)
{
#if defined CONFIGURATION_DEBUG
    fldOutStreamWriteMarker(stream, NIMBLE_SERIALIZE_MARKER_CHANNEL_ID);
#endif
    return fldOutStreamWriteUInt32(stream, channelId);
}

/// Reads a channelId from the octet stream
/// @param stream out stream
/// @param channelId blob stream channel id
/// @return negative on error
int nimbleSerializeInBlobStreamChannelId(struct FldInStream* stream, NimbleSerializeBlobStreamChannelId* channelId)
{
#if defined CONFIGURATION_DEBUG
    fldInStreamCheckMarker(stream, NIMBLE_SERIALIZE_MARKER_CHANNEL_ID);
#endif
    return fldInStreamReadUInt32(stream, channelId);
}

/// Writes a stateId to the octet stream
/// @param stream out stream
/// @param stateId state ID before applying stepID
/// @return negative on error
int nimbleSerializeOutStateId(struct FldOutStream* stream, const NimbleSerializeStateId stateId)
{
#if defined CONFIGURATION_DEBUG
    fldOutStreamWriteMarker(stream, NIMBLE_SERIALIZE_MARKER_STATE_ID);
#endif
    return fldOutStreamWriteUInt32(stream, stateId);
}

/// Reads a stateId from the octet stream
/// @param stream out stream
/// @param stateId state ID before applying stepID
/// @return negative on error
int nimbleSerializeInStateId(struct FldInStream* stream, NimbleSerializeStateId* stateId)
{
#if defined CONFIGURATION_DEBUG
    fldInStreamCheckMarker(stream, NIMBLE_SERIALIZE_MARKER_STATE_ID);
#endif
    return fldInStreamReadUInt32(stream, stateId);
}

/// Writes a nimble command to the octet stream
/// @param outStream out stream
/// @param cmd nimble command
/// @param prefix debug prefix
void nimbleSerializeWriteCommand(struct FldOutStream* outStream, uint8_t cmd, const char* prefix)
{
    (void) prefix;
    fldOutStreamWriteUInt8(outStream, cmd);
}
