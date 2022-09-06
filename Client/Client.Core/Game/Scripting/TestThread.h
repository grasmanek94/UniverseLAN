#pragma once
#include <Networking/Networking.hxx>

class TestThread : public ScriptThread, public MessageReceiver
{
private:
	bool m_bInitialized;
	bool m_bIsWaitingForPedModelToLoad;
	bool m_bIsWaitingForVehicleModelToLoad;
	std::list<scrPed> m_spawnedPeds;
	bool m_bIsWaitingForClonePedModelToLoad;
	bool m_bClonePedSpawned;
	scrPed m_clonePed;

	V_Plus_NetworkClient connection;
	bool connected;

	void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<PeerConnected>& data) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<PeerDisconnected>& data) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<ChatMessage>& message) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<PlayerJoin>& message) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<PlayerQuit>& message) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<PlayerSpawn>& message) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<PlayerDespawn>& message) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<OnFootSync>& message) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<GameSetup>& message) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<WorldUpdate>& message) override;

	void RunNetwork();

public:
	TestThread();

	virtual eScriptThreadState Reset(uint32_t scriptHash, void* pArgs, uint32_t argCount) override;
	virtual void DoRun() override;
};
