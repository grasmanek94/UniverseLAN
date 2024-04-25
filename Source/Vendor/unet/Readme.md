# Unet
Unified Networking for lobbies. Provides a single unified lobby using multiple service lobbies. This
can be useful to make cross-platform play possible, as well as fallbacks to other services if one
service gets disconnected.

## Supported services
The following services and APIs are currently supported:

* Steam P2P
* GOG Galaxy P2P
* Enet P2P

## Usage
Initializing Unet and creating a lobby:

```c++
#include <Unet.h>

class MyCallbacks : public Unet::ICallbacks
{
	virtual void OnLobbyCreated(const CreateLobbyResult &result) override
	{
		printf("Lobby created!\n");
	}
}

int main()
{
	// ... initialize Steam/Galaxy/Enet here ...

	// Create the Unet context
	Unet::IContext* ctx = Unet::CreateContext();

	// Prepare context callbacks
	ctx->SetCallbacks(new MyCallbacks);

	// Initialize the services we'll be using (the first EnableService call will be the "primary" service)
	ctx->EnableService(Unet::ServiceType::Steam);
	ctx->EnableService(Unet::ServiceType::Galaxy);
	ctx->EnableService(Unet::ServiceType::Enet);

	// Create a lobby
	ctx->CreateLobby(Unet::LobbyPrivacy::Public);

	// Main loop
	while (true) {
		// Run callbacks and keep the context updated
		ctx->RunCallbacks();

		// ... do your polling/updating/rendering here ...
	}

	// Leave the lobby if we're still in it
	ctx->LeaveLobby();

	// Destroy the Unet context
	Unet::DestroyContext(ctx);
	return 0;
}
```

For a complete example, check out the `cli` folder for the Unet CLI application. Most important
header files are fully documented, so you should be able to set up your project via that pretty
easily.

## Building
Unet uses [GENie](https://github.com/bkaradzic/GENie) to build. To include GENie into your own
projects, you can choose to either build it yourself first in this repository, or by using GENie
in your project yourself, which is probably the easiest.

If you're using GENie, you have to do something like this in your build scripts:

```lua
dofile(UNET_DIR .. 'genie/genie_unet.lua')
unet_project({
	modules = {
		steam = {
			link = true,
			dir = STEAMWORKS_DIR
		},
		galaxy = {
			link = true,
			dir = GOG_DIR
		},
		enet = {
			link = true,
			dir = ENET_DIR
		}
	}
})
```

Notice that Steam, Galaxy, and Enet are **modules**. You may decide to include them or leave them,
if you don't support them. You must pass the path in which the SDK for the service is in `dir`, and
specify in `link` whether we should link to the SDK or not.

## Games that use Unet
* [Heroes of Hammerwatch](https://store.steampowered.com/app/677120/Heroes_of_Hammerwatch/)

If you're using Unet, let me know, and I'll add you to this list!

## Technical info
Internally, each service sends packets on 3 or more separate channels.

* Channel 0: Internal lobby control channel. All "internal" lobby data resides here. The transferred
  data are all encoded json objects.
* Channel 1: Relay channel. Used when clients want to send packets to clients that don't share a
  service. Same as general purpose data, except starts with the destination peer ID and desired
  channel.
* Channel 2 and up: General purpose channels.

These channels are entirely separate from the public Context `SendTo` API. There, channel 0 is
transferred internally on channel 2, channel 1 on channel 3, etc.

## Quirks
Below I'm listing some fun quirks I found out.

* When hosting a lobby yourself, searching for lobbies will not result in your own lobby showing up
  in the lobby list on Galaxy, but it does on Steam.
* While Steam's reliable packets have a send limit of 1 MB (actually 1024 * 1024), Galaxy's reliable
  packets don't seem to have a limit at all. It does get slower the more MB you send though, even
  on a gigabit network. (In my tests, transfer rate is roughly around 2 MB/s)
