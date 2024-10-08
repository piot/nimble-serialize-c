/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/nimble-serialize-c
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/

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

int nimbleSerializeOutClientRequestId(struct FldOutStream* stream, NimbleSerializeClientRequestId requestId);
int nimbleSerializeInClientRequestId(struct FldInStream* stream, NimbleSerializeClientRequestId* requestId);

int nimbleSerializeOutConnectionId(struct FldOutStream* stream, NimbleSerializeConnectionId connectionId);
int nimbleSerializeInConnectionId(struct FldInStream* stream, NimbleSerializeConnectionId* connectionId);


int nimbleSerializeOutSessionSecret(struct FldOutStream* stream, NimbleSerializeSessionSecret secret);
int nimbleSerializeInSessionSecret(struct FldInStream* stream, NimbleSerializeSessionSecret* secret);


int nimbleSerializeOutParticipantId(struct FldOutStream* stream, NimbleSerializeParticipantId participantId);
int nimbleSerializeInParticipantId(struct FldInStream* stream, NimbleSerializeParticipantId* participantId);

int nimbleSerializeOutPartyId(struct FldOutStream* stream, NimbleSerializeLocalPartyId partyId);
int nimbleSerializeInPartyId(struct FldInStream* stream, NimbleSerializeLocalPartyId* partyId);

int nimbleSerializeOutPartyAndSessionSecret(struct FldOutStream* stream, NimbleSerializePartyAndSessionSecret secret);
int nimbleSerializeInPartyAndSessionSecret(struct FldInStream* stream, NimbleSerializePartyAndSessionSecret* secret);

int nimbleSerializeOutBlobStreamChannelId(struct FldOutStream* stream,
                                          const NimbleSerializeBlobStreamChannelId channelId);
int nimbleSerializeInBlobStreamChannelId(struct FldInStream* stream, NimbleSerializeBlobStreamChannelId* channelId);

int nimbleSerializeOutStateId(struct FldOutStream* stream, const NimbleSerializeStateId stateId);
int nimbleSerializeInStateId(struct FldInStream* stream, NimbleSerializeStateId* stateId);

void nimbleSerializeWriteCommand(struct FldOutStream* outStream, uint8_t cmd, struct Clog* log);

#endif
