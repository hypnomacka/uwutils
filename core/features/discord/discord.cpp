#include <pch.h>
#include "../features.hpp"
#include "../../../dependencies/rpc/includes/discord_rpc.h"
#include "../../../dependencies/rpc/includes/discord_register.h"

void features::discord::initialize() {
    // Initialize
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Initialize(xorstr("987838964251623444"), &Handle, 1, NULL);
    console::log(xorstr("discord rpc initialized\n"));

    // Update
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = xorstr("beta");
    discordPresence.largeImageKey = xorstr("UwU");
    Discord_UpdatePresence(&discordPresence);
}

void features::discord::release() {
    // Release
    Discord_Shutdown();
}