/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <nimble-serialize/client_out.h>
#include <flood/out_stream.h>
#include <nimble-serialize/serialize.h>

static int nimbleSerializeClientOutParticipantConnectionJoin(FldOutStream* stream,
                                                             const struct NimbleSerializePlayerJoinOptions* joinInfos,
                                                             size_t localParticipantCount)
{
    fldOutStreamWriteUInt8(stream, localParticipantCount);
    for (size_t i = 0; i < localParticipantCount; ++i) {
        fldOutStreamWriteUInt8(stream, joinInfos[i].localIndex);
    }

    return 0;
}


int nimbleSerializeClientOutGameJoin(FldOutStream* stream,
                                            const NimbleSerializeGameJoinOptions* options)
{
#define COMMAND_DEBUG "ClientOut"
    nimbleSerializeWriteCommand(stream, NimbleSerializeCmdJoinGameRequest, COMMAND_DEBUG);
    nimbleSerializeOutVersion(stream, &options->applicationVersion);
    nimbleSerializeClientOutParticipantConnectionJoin(stream, options->players, options->playerCount);
    return 0;
}
