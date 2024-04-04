/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/in_stream.h>
#include <flood/out_stream.h>
#include <nimble-serialize/debug.h>
#include <nimble-serialize/serialize.h>

#if defined CLOG_LOG_ENABLED
#include <nimble-serialize/debug.h>
#endif

static const uint8_t NIMBLE_SERIALIZE_MARKER_CHANNEL_ID = 0x19;
static const uint8_t NIMBLE_SERIALIZE_MARKER_STATE_ID = 0x9a;
static const uint8_t NIMBLE_SERIALIZE_MARKER_NONCE_ID = 0xe2;
static const uint8_t NIMBLE_SERIALIZE_MARKER_CONNECTION_SECRET_ID = 0xe3;
static const uint8_t NIMBLE_SERIALIZE_MARKER_PARTICIPANT_ID = 0x2d;

/// Writes a nonce to the octet stream
/// @param stream out stream
/// @param nonce nonce
/// @return negative on error
int nimbleSerializeOutNonce(struct FldOutStream* stream, NimbleSerializeNonce nonce)
{
    fldOutStreamWriteMarker(stream, NIMBLE_SERIALIZE_MARKER_NONCE_ID);
    return fldOutStreamWriteUInt64(stream, nonce);
}

/// Reads a nonce from the octet stream
/// @param stream out stream
/// @param nonce nonce
/// @return negative on error
int nimbleSerializeInNonce(struct FldInStream* stream, NimbleSerializeNonce* nonce)
{
    fldInStreamCheckMarker(stream, NIMBLE_SERIALIZE_MARKER_NONCE_ID);
    return fldInStreamReadUInt64(stream, nonce);
}

/// Writes a secret to the octet stream
/// @param stream out stream
/// @param secret nonce
/// @return negative on error
int nimbleSerializeOutConnectionSecret(struct FldOutStream* stream, NimbleSerializeParticipantConnectionSecret secret)
{
    fldOutStreamWriteMarker(stream, NIMBLE_SERIALIZE_MARKER_CONNECTION_SECRET_ID);
    return fldOutStreamWriteUInt64(stream, secret);
}

/// Reads a secret from the octet stream
/// @param stream out stream
/// @param secret secret
/// @return negative on error
int nimbleSerializeInConnectionSecret(struct FldInStream* stream, NimbleSerializeParticipantConnectionSecret* secret)
{
    fldInStreamCheckMarker(stream, NIMBLE_SERIALIZE_MARKER_CONNECTION_SECRET_ID);
    return fldInStreamReadUInt64(stream, secret);
}

/// Writes a participantId to the octet stream
/// @param stream out stream
/// @param participantId nonce
/// @return negative on error
int nimbleSerializeOutParticipantId(struct FldOutStream* stream, NimbleSerializeParticipantId participantId)
{
    fldOutStreamWriteMarker(stream, NIMBLE_SERIALIZE_MARKER_PARTICIPANT_ID);
    return fldOutStreamWriteUInt8(stream, participantId);
}

/// Reads a participantId from the octet stream
/// @param stream out stream
/// @param participantId participantId
/// @return negative on error
int nimbleSerializeInParticipantId(struct FldInStream* stream, NimbleSerializeParticipantId* participantId)
{
    fldInStreamCheckMarker(stream, NIMBLE_SERIALIZE_MARKER_PARTICIPANT_ID);
    return fldInStreamReadUInt8(stream, participantId);
}

/// Writes a channelId to the octet stream
/// @param stream out stream
/// @param channelId blob stream channel id
/// @return negative on error
int nimbleSerializeOutBlobStreamChannelId(struct FldOutStream* stream,
                                          const NimbleSerializeBlobStreamChannelId channelId)
{
    fldOutStreamWriteMarker(stream, NIMBLE_SERIALIZE_MARKER_CHANNEL_ID);
    return fldOutStreamWriteUInt32(stream, channelId);
}

/// Reads a channelId from the octet stream
/// @param stream out stream
/// @param channelId blob stream channel id
/// @return negative on error
int nimbleSerializeInBlobStreamChannelId(struct FldInStream* stream, NimbleSerializeBlobStreamChannelId* channelId)
{
    fldInStreamCheckMarker(stream, NIMBLE_SERIALIZE_MARKER_CHANNEL_ID);
    return fldInStreamReadUInt32(stream, channelId);
}

/// Writes a stateId to the octet stream
/// @param stream out stream
/// @param stateId state ID before applying stepID
/// @return negative on error
int nimbleSerializeOutStateId(struct FldOutStream* stream, const NimbleSerializeStateId stateId)
{
    fldOutStreamWriteMarker(stream, NIMBLE_SERIALIZE_MARKER_STATE_ID);
    return fldOutStreamWriteUInt32(stream, stateId);
}

/// Reads a stateId from the octet stream
/// @param stream out stream
/// @param stateId state ID before applying stepID
/// @return negative on error
int nimbleSerializeInStateId(struct FldInStream* stream, NimbleSerializeStateId* stateId)
{
    fldInStreamCheckMarker(stream, NIMBLE_SERIALIZE_MARKER_STATE_ID);
    return fldInStreamReadUInt32(stream, stateId);
}

/// Writes a nimble command to the octet stream
/// @param outStream out stream
/// @param cmd nimble command
/// @param log log target
void nimbleSerializeWriteCommand(struct FldOutStream* outStream, uint8_t cmd, Clog* log)
{
#if defined CLOG_LOG_ENABLED
    CLOG_C_VERBOSE(log, "serialize cmd:%s", nimbleSerializeCmdToString(cmd))
#else
    (void) log;
#endif

    fldOutStreamWriteUInt8(outStream, cmd);
}
