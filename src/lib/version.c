/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/nimble-serialize-c
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/

#include <flood/in_stream.h>
#include <flood/out_stream.h>
#include <nimble-serialize/version.h>
#include <tiny-libc/tiny_libc.h>

/// Write a version to an FldOutStream.
/// @param outStream out stream
/// @param version version to write
/// @return negative on error
int nimbleSerializeOutVersion(struct FldOutStream* outStream, const NimbleSerializeVersion* version)
{
    int error = fldOutStreamWriteUInt16(outStream, version->major);
    if (error < 0) {
        return error;
    }
    error = fldOutStreamWriteUInt16(outStream, version->minor);
    if (error < 0) {
        return error;
    }

    error = fldOutStreamWriteUInt16(outStream, version->patch);

    return error;
}

/// Read a version from a FldInStream.
/// @param inStream stream to read from
/// @param[out] targetVersion version read from stream
/// @return negative on error
int nimbleSerializeInVersion(struct FldInStream* inStream, NimbleSerializeVersion* targetVersion)
{
    int error = fldInStreamReadUInt16(inStream, &targetVersion->major);
    if (error < 0) {
        return error;
    }

    error = fldInStreamReadUInt16(inStream, &targetVersion->minor);
    if (error < 0) {
        return error;
    }

    error = fldInStreamReadUInt16(inStream, &targetVersion->patch);

    return error;
}

/// Check two versions for equality.
/// @param a first to compare with
/// @param b second to compare with
/// @return true if equal
bool nimbleSerializeVersionIsEqual(const NimbleSerializeVersion* a, const NimbleSerializeVersion* b)
{
    return a->major == b->major && a->minor == b->minor && a->patch == b->patch;
}

/// Returns a human readable string for the version
/// @param version version to stringify
/// @param buf target character buffer
/// @param maxBufSize maximum number of octets of buf
/// @return buf
const char* nimbleSerializeVersionToString(const NimbleSerializeVersion* version, char* buf, size_t maxBufSize)
{
    tc_snprintf(buf, maxBufSize, "%d.%d.%d", version->major, version->minor, version->patch);
    return buf;
}
