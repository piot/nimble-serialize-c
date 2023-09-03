/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef NIMBLE_SERIALIZE_VERSION_H
#define NIMBLE_SERIALIZE_VERSION_H

#include <stdbool.h>
#include <stdint.h>

typedef struct NimbleSerializeVersion {
    uint16_t major;
    uint16_t minor;
    uint16_t patch;
} NimbleSerializeVersion;

extern NimbleSerializeVersion g_nimbleProtocolVersion;

struct FldOutStream;
struct FldInStream;

int nimbleSerializeOutVersion(struct FldOutStream* outStream, const NimbleSerializeVersion* version);
int nimbleSerializeInVersion(struct FldInStream* inStream, NimbleSerializeVersion* targetVersion);
bool nimbleSerializeVersionIsEqual(const NimbleSerializeVersion* a, const NimbleSerializeVersion* b);
const char* nimbleSerializeVersionToString(const NimbleSerializeVersion* version, char* buf, size_t maxBufSize);

#endif
