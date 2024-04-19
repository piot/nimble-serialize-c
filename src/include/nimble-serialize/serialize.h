/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef NIMBLE_SERIALIZE_SERIALIZE_H
#define NIMBLE_SERIALIZE_SERIALIZE_H

#include <stdint.h>
#include <stdlib.h>

#include <nimble-serialize/types.h>

struct FldOutStream;
struct FldInStream;
struct Clog;

int nimbleSerializeOutNonce(struct FldOutStream* stream, NimbleSerializeNonce nonce);
int nimbleSerializeInNonce(struct FldInStream* stream, NimbleSerializeNonce* nonce);

int nimbleSerializeOutConnectionId(struct FldOutStream* stream, NimbleSerializeConnectionId connectionId);
int nimbleSerializeInConnectionId(struct FldInStream* stream, NimbleSerializeConnectionId* connectionId);


int nimbleSerializeOutSessionSecret(struct FldOutStream* stream, NimbleSerializeSessionSecret secret);
int nimbleSerializeInSessionSecret(struct FldInStream* stream, NimbleSerializeSessionSecret* secret);

int nimbleSerializeOutConnectionIdSecret(struct FldOutStream* stream, NimbleSerializeConnectionIdSecret secret);
int nimbleSerializeInConnectionIdSecret(struct FldInStream* stream, NimbleSerializeConnectionIdSecret* secret);

int nimbleSerializeOutParticipantId(struct FldOutStream* stream, NimbleSerializeParticipantId participantId);
int nimbleSerializeInParticipantId(struct FldInStream* stream, NimbleSerializeParticipantId* participantId);

int nimbleSerializeOutPartyId(struct FldOutStream* stream, NimbleSerializeParticipantPartyId partyId);
int nimbleSerializeInPartyId(struct FldInStream* stream, NimbleSerializeParticipantPartyId* partyId);

int nimbleSerializeOutPartyAndSessionSecret(struct FldOutStream* stream, NimbleSerializePartyAndSessionSecret secret);
int nimbleSerializeInPartyAndSessionSecret(struct FldInStream* stream, NimbleSerializePartyAndSessionSecret* secret);

int nimbleSerializeOutBlobStreamChannelId(struct FldOutStream* stream,
                                          const NimbleSerializeBlobStreamChannelId channelId);
int nimbleSerializeInBlobStreamChannelId(struct FldInStream* stream, NimbleSerializeBlobStreamChannelId* channelId);

int nimbleSerializeOutStateId(struct FldOutStream* stream, const NimbleSerializeStateId stateId);
int nimbleSerializeInStateId(struct FldInStream* stream, NimbleSerializeStateId* stateId);

void nimbleSerializeWriteCommand(struct FldOutStream* outStream, uint8_t cmd, struct Clog* log);

#endif
