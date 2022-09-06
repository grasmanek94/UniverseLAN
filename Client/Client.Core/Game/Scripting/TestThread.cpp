#include "Main.h"
#include "Natives.h"

extern uintptr_t hook::baseAddress;

uint64_t g_pClonePed = NULL;

struct __Player // temporary
{
	size_t id;
	std::wstring name;
	scrPed ped;
	bool waiting_for_model_to_load;
	struct
	{
		scrHash model_hash;
		Vector3 position;
		Vector3 rotation;
	} spawn_info;
	bool spawned;
	bool was_jumping;

	__Player(size_t _id, std::wstring _name)
	{
		id = _id;
		name = _name;
		ped = -1;
		waiting_for_model_to_load = false;
		spawned = false;
		was_jumping = false;
	}
};

struct __PlayerPool // temporary
{
	std::list<__Player> players;
} player_pool;

TestThread::TestThread()
{
	m_bInitialized = false;
	m_bIsWaitingForPedModelToLoad = false;
	m_bIsWaitingForVehicleModelToLoad = false;
	m_spawnedPeds.clear();
	m_bIsWaitingForClonePedModelToLoad = false;
	m_bClonePedSpawned = false;
	m_clonePed = -1;
}

eScriptThreadState TestThread::Reset(uint32_t scriptHash, void* pArgs, uint32_t argCount)
{
	m_bInitialized = false;
	m_bIsWaitingForPedModelToLoad = false;
	m_bIsWaitingForVehicleModelToLoad = false;
	m_spawnedPeds.clear();
	m_bIsWaitingForClonePedModelToLoad = false;
	m_bClonePedSpawned = false;
	m_clonePed = -1;

	return ScriptThread::Reset(scriptHash, pArgs, argCount);
}

void TestThread::DoRun()
{
	scrPed playerPedId = PLAYER::GET_PLAYER_PED(-1);

	if(playerPedId != -1 && playerPedId != 0)
	{
		if(!m_bInitialized)
		{
			STREAMING::LOAD_SCENE(-786.44f, -48.50f, 37.75f);

			SCRIPT::SHUTDOWN_LOADING_SCREEN();
			CAM::DO_SCREEN_FADE_IN(0);

			VEHICLE::SET_GARBAGE_TRUCKS(FALSE);
			VEHICLE::SET_RANDOM_BOATS(FALSE);
			VEHICLE::SET_RANDOM_TRAINS(FALSE);

			ENTITY::SET_ENTITY_COORDS(playerPedId, -786.44f, -48.50f, 37.75f, FALSE, FALSE, FALSE, FALSE);

			int init_code = connection.GetInitCode();

			if (init_code)
			{
				// TODO custom exception class
				throw std::exception(("Cannot initialize ENET, error code: " + std::to_string(init_code)).c_str());
			}

			if (!connection.Create() || !connection.Good())
			{
				// TODO custom exception class
				throw std::exception("ENET host member creation failed");
			}

			connection.Connect("127.0.0.1", 5544);

			if(GameOverlay::IsInitialized() && GameOverlay::GetGameUI != NULL)
			{
				ChatWindow *pChatWindow = GameOverlay::GetGameUI()->GetChatWindow();

				if(pChatWindow != NULL)
				{
					pChatWindow->AddInfoMessageW(L"Connecting...");
				}
			}

			m_bInitialized = true;
		}

		static bool s_bWasF9Pressed = true;
		static bool s_bWasF10Pressed = true;
		static bool s_bWasF11Pressed = true;
		static bool s_bWasF4Pressed = true;

		if(GetAsyncKeyState(VK_F9) & 0x8000)
		{
			if(!s_bWasF9Pressed)
			{
				STREAMING::REQUEST_MODEL(0xC1AE4D16);

				m_bIsWaitingForVehicleModelToLoad = true;
				s_bWasF9Pressed = true;
			}
		}
		else
		{
			s_bWasF9Pressed = false;
		}

		if(GetAsyncKeyState(VK_F10) & 0x8000)
		{
			if(!s_bWasF10Pressed)
			{
				if(ENTITY::DOES_ENTITY_EXIST(playerPedId) != 0)
				{
					static LPCSTR weaponNames[] = {
						"WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR", 
						"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG", 
						"WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG",
						"WEAPON_COMBATMG", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
						"WEAPON_STUNGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER_SMOKE",
						"WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
						"WEAPON_MOLOTOV", "WEAPON_FIREEXTINGUISHER", "WEAPON_PETROLCAN",
						"WEAPON_SNSPISTOL", "WEAPON_SPECIALCARBINE", "WEAPON_HEAVYPISTOL", "WEAPON_BULLPUPRIFLE", "WEAPON_HOMINGLAUNCHER",
						"WEAPON_PROXMINE", "WEAPON_SNOWBALL", "WEAPON_VINTAGEPISTOL", "WEAPON_DAGGER", "WEAPON_FIREWORK", "WEAPON_MUSKET",
						"WEAPON_MARKSMANRIFLE", "WEAPON_HEAVYSHOTGUN", "WEAPON_GUSENBERG", "WEAPON_HATCHET", "WEAPON_RAILGUN"
					};

					for(int i = 0; i < sizeof(weaponNames) / sizeof(weaponNames[0]); i++)
					{
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPedId, GAMEPLAY::GET_HASH_KEY((char *)weaponNames[i]), 1000, FALSE);
					}

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::_ADD_TEXT_COMPONENT_STRING("All weapons added.");
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}

				s_bWasF10Pressed = true;
			}
			else
			{
				s_bWasF10Pressed = false;
			}
		}

		if(GetAsyncKeyState(VK_F11) & 0x8000)
		{
			if(!s_bWasF11Pressed)
			{
				STREAMING::REQUEST_MODEL(0x65B93076);

				m_bIsWaitingForPedModelToLoad = true;
				s_bWasF11Pressed = true;
			}
		}
		else
		{
			s_bWasF11Pressed = false;
		}

		if(m_bIsWaitingForVehicleModelToLoad)
		{
			if(STREAMING::HAS_MODEL_LOADED(0xC1AE4D16))
			{
				scrVector3 entityCoords = ENTITY::GET_ENTITY_COORDS(playerPedId, TRUE);
				scrVehicle vehicle = VEHICLE::CREATE_VEHICLE(0xC1AE4D16, entityCoords.x, entityCoords.y + 2, entityCoords.z, 0.0f, FALSE, TRUE);

				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0xC1AE4D16);

				UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
				UI::_ADD_TEXT_COMPONENT_STRING("Vehicle spawned.");
				UI::_DRAW_NOTIFICATION(FALSE, FALSE);

				m_bIsWaitingForVehicleModelToLoad = false;
			}
		}

		if(m_bIsWaitingForPedModelToLoad)
		{
			if(STREAMING::HAS_MODEL_LOADED(0x65B93076))
			{
				scrVector3 entityCoords = ENTITY::GET_ENTITY_COORDS(playerPedId, TRUE);
				scrPed ped = PED::CREATE_PED(1, 0x65B93076, entityCoords.x, entityCoords.y + 2, entityCoords.z, 0.0f, FALSE, TRUE);

				PED::SET_PED_CAN_BE_TARGETTED(ped, TRUE);
				WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(m_clonePed, FALSE);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(m_clonePed, TRUE);

				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0x65B93076);

				UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
				UI::_ADD_TEXT_COMPONENT_STRING("Ped spawned.");
				UI::_DRAW_NOTIFICATION(FALSE, FALSE);

				m_spawnedPeds.push_back(ped);
				m_bIsWaitingForPedModelToLoad = false;
			}
		}

		if(GetAsyncKeyState(VK_F4) & 0x8000)
		{
			if(!s_bWasF11Pressed)
			{
				if(!m_bIsWaitingForClonePedModelToLoad && !m_bClonePedSpawned)
				{
					STREAMING::REQUEST_MODEL(0x9B810FA2);

					m_bIsWaitingForClonePedModelToLoad = true;
				}

				s_bWasF4Pressed = true;
			}
		}
		else
		{
			s_bWasF4Pressed = false;
		}

		if(m_bIsWaitingForClonePedModelToLoad)
		{
			if(STREAMING::HAS_MODEL_LOADED(0x9B810FA2))
			{
				scrVector3 entityCoords = ENTITY::GET_ENTITY_COORDS(playerPedId, TRUE);
				m_clonePed = PED::CREATE_PED(1, 0x9B810FA2, entityCoords.x, entityCoords.y + 2, entityCoords.z, 0.0f, FALSE, TRUE);

				PED::SET_PED_CAN_BE_TARGETTED(m_clonePed, TRUE);
				WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(m_clonePed, FALSE);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(m_clonePed, TRUE);

				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0x9B810FA2);

				m_bClonePedSpawned = true;
				m_bIsWaitingForClonePedModelToLoad = false;
			}
		}

		if(m_bClonePedSpawned && GameAddresses::scriptHandleToPed != NULL && m_clonePed != -1)
		{
			if(ENTITY::DOES_ENTITY_EXIST(m_clonePed) && ENTITY::IS_ENTITY_A_PED(m_clonePed))
			{
				if(!ENTITY::IS_ENTITY_DEAD(m_clonePed) && !PED::IS_PED_DEAD_OR_DYING(m_clonePed, TRUE))
				{
					if(!ENTITY::IS_ENTITY_DEAD(playerPedId) && !PED::IS_PED_DEAD_OR_DYING(playerPedId, TRUE))
					{
						typedef uint64_t (__fastcall * scriptHandleToPed_t)(scrPed pedHandle);
						static scriptHandleToPed_t scriptHandleToPed = (scriptHandleToPed_t)GameAddresses::scriptHandleToPed;

						uint64_t pLocalPlayerPed = scriptHandleToPed(playerPedId);
						uint64_t pClonePed = scriptHandleToPed(m_clonePed);

						if(pLocalPlayerPed != NULL && pClonePed != NULL)
						{
							g_pClonePed = pClonePed;

							scrVector3 playerCoords;
							playerCoords.x = *(float *)(pLocalPlayerPed + 0x90);
							playerCoords.y = *(float *)(pLocalPlayerPed + 0x94);
							playerCoords.z = *(float *)(pLocalPlayerPed + 0x98);

							scrVector3 playerRotation = ENTITY::GET_ENTITY_ROTATION(playerPedId, 0);
							scrVector3 playerVelocity = ENTITY::GET_ENTITY_VELOCITY(playerPedId);

							if(PED::IS_PED_JUMPING(playerPedId) && !PED::IS_PED_JUMPING(m_clonePed))
							{
								playerCoords.z += 0.075f;
							}

							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(m_clonePed, playerCoords.x, playerCoords.y + 2, playerCoords.z, FALSE, FALSE, FALSE);
							ENTITY::SET_ENTITY_ROTATION(m_clonePed, playerRotation.x, playerRotation.y, playerRotation.z, 2, TRUE);
							ENTITY::SET_ENTITY_VELOCITY(m_clonePed, playerVelocity.x, playerVelocity.y, playerVelocity.z);

							PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(m_clonePed, TRUE);

							scrHash
								curPlayerPedWeaponHash = 0,
								curClonePedWeaponHash = 0;

							WEAPON::GET_CURRENT_PED_WEAPON(playerPedId, &curPlayerPedWeaponHash, TRUE);
							WEAPON::GET_CURRENT_PED_WEAPON(m_clonePed, &curClonePedWeaponHash, TRUE);

							if(curPlayerPedWeaponHash != curClonePedWeaponHash)
							{
								WEAPON::GIVE_WEAPON_TO_PED(m_clonePed, curPlayerPedWeaponHash, 9999, TRUE, TRUE);
								WEAPON::SET_CURRENT_PED_WEAPON(m_clonePed, curPlayerPedWeaponHash, TRUE);
							}

/*
							if(PED::IS_PED_RELOADING(playerPedId) && !PED::IS_PED_RELOADING(m_clonePed))
							{
								WEAPON::MAKE_PED_RELOAD(m_clonePed);
								AI::TASK_RELOAD_WEAPON(m_clonePed, TRUE);
							}

							if(PED::IS_PED_JUMPING(playerPedId) && !PED::IS_PED_JUMPING(m_clonePed))
							{
								AI::TASK_JUMP(m_clonePed, TRUE);
							}
*/

							if(GameAddresses::pedIntelligenceOffset != 0)
							{
								uint64_t pLocalPlayerIntelligence = *(uint64_t *)(pLocalPlayerPed + GameAddresses::pedIntelligenceOffset);
								uint64_t pClonePedIntelligence = *(uint64_t *)(pClonePed + GameAddresses::pedIntelligenceOffset);

								if(pLocalPlayerIntelligence != NULL && pClonePedIntelligence != NULL)
								{
									uint64_t pLocalTaskTreePed = *(uint64_t *)(pLocalPlayerIntelligence + 0x360);
									uint64_t pCloneTaskTreePed = *(uint64_t *)(pClonePedIntelligence + 0x360);

									if(pLocalTaskTreePed != NULL && pCloneTaskTreePed != NULL)
									{
										//cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 4); // TaskAimGunOnFoot
										cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 16); // TaskGetUp
										cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 18); // TaskFallOver
										cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 19); // TaskFallAndGetUp
										cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 50); // TaskVault
										cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 51); // TaskDropDown
										cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 56); // TaskSwapWeapon
										cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 97); // TaskDyingDead
										cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 128); // TaskMelee
										cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 289); // TaskAimAndThrowProjectile
										//cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 290); // TaskGun
										//cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 298); // TaskReloadGun
										cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 421); // TaskJump
										cloneTask(pLocalTaskTreePed, pCloneTaskTreePed, 422); // TaskFall
									}
								}
							}

							if(*(DWORD *)(pLocalPlayerPed + 1488) >> 5 & 1) // is stealth mode active
							{
								*(DWORD *)(pClonePed + 1488) |= 0x20u; // enable stealth
							}
							else
							{
								*(DWORD *)(pClonePed + 1488) &= 0xFFFFFFDF; // disable stealth
							}

							*(float *)(pClonePed + 0x578) = *(float *)(pLocalPlayerPed + 0x578); // current move blend ratio
							//*(float *)(pClonePed + 0x580) = *(float *)(pLocalPlayerPed + 0x580); // target move blend ratio
							*(float *)(pClonePed + 0x588) = *(float *)(pLocalPlayerPed + 0x578); // min move blend ratio
						}
					}
				}
				else
				{
					g_pClonePed = NULL;

					PED::DELETE_PED((scrAny *)(&m_clonePed));

					m_bClonePedSpawned = false;
					m_clonePed = -1;
				}
			}
		}

		for(auto& plyr : player_pool.players)
		{
			if(plyr.waiting_for_model_to_load && !plyr.spawned)
			{
				if(STREAMING::HAS_MODEL_LOADED(plyr.spawn_info.model_hash))
				{
					plyr.ped = PED::CREATE_PED(1, plyr.spawn_info.model_hash, plyr.spawn_info.position.x, plyr.spawn_info.position.y, plyr.spawn_info.position.z, 0.0f, FALSE, TRUE);
					
					ENTITY::SET_ENTITY_ROTATION(plyr.ped, plyr.spawn_info.rotation.x, plyr.spawn_info.rotation.y, plyr.spawn_info.rotation.z, 2, TRUE);
					WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(plyr.ped, FALSE);
					PED::SET_PED_CAN_BE_TARGETTED(plyr.ped, TRUE);
					PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(plyr.ped, TRUE);

					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(plyr.spawn_info.model_hash);

					plyr.waiting_for_model_to_load = false;
					plyr.spawned = true;
				}
			}
		}

		static long long last_onfoot_sync = 0;
		long long current_time = SharedUtility::GetTime64();

		if(GameAddresses::scriptHandleToPed != NULL && !ENTITY::IS_ENTITY_DEAD(playerPedId) && !PED::IS_PED_DEAD_OR_DYING(playerPedId, TRUE))
		{
			if(connected && current_time - last_onfoot_sync > 50)
			{
				OnFootSync onfoot_sync_data;

				typedef uint64_t (__fastcall * scriptHandleToPed_t)(scrPed pedHandle);
				static scriptHandleToPed_t scriptHandleToPed = (scriptHandleToPed_t)GameAddresses::scriptHandleToPed;

				uint64_t pLocalPlayerPed = scriptHandleToPed(playerPedId);

				Vector3
					position,
					rotation,
					velocity;

				position.x = *(float *)(pLocalPlayerPed + 0x90);
				position.y = *(float *)(pLocalPlayerPed + 0x94);
				position.z = *(float *)(pLocalPlayerPed + 0x98);

				scrVector3
					scr_rotation = ENTITY::GET_ENTITY_ROTATION(playerPedId, 0),
					scr_velocity = ENTITY::GET_ENTITY_VELOCITY(playerPedId);

				rotation.x = scr_rotation.x; rotation.y = scr_rotation.y; rotation.z = scr_rotation.z;
				velocity.x = scr_velocity.x; velocity.y = scr_velocity.y; velocity.z = scr_velocity.z;

				float
					current_move_blend_ratio = *(float *)(pLocalPlayerPed + 0x578),
					target_move_blend_ratio = *(float *)(pLocalPlayerPed + 0x580);

				scrHash current_weapon_hash = 0;
				WEAPON::GET_CURRENT_PED_WEAPON(playerPedId, &current_weapon_hash, TRUE);

				bool is_jumping = false;

				if(PED::IS_PED_JUMPING(playerPedId))
				{
					is_jumping = true;
				}

				onfoot_sync_data.SetPosition(position);
				onfoot_sync_data.SetRotation(rotation);
				onfoot_sync_data.SetVelocity(velocity);
				onfoot_sync_data.SetCurrentMoveBlendRatio(current_move_blend_ratio);
				onfoot_sync_data.SetTargetMoveBlendRatio(target_move_blend_ratio);
				onfoot_sync_data.SetCurrentWeaponHash(current_weapon_hash);
				onfoot_sync_data.SetJumping(is_jumping);

				connection.SendAsync(onfoot_sync_data);

				last_onfoot_sync = current_time;
			}
		}

		PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
		PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f, 0.0f);

		VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
		VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
		VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);

		DECISIONEVENT::SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME();
		DECISIONEVENT::SUPPRESS_AGITATION_EVENTS_NEXT_FRAME();

		PLAYER::SET_MAX_WANTED_LEVEL(0);
	}

	RunNetwork();
}

void TestThread::Handle(ENetPeer* peer, const std::shared_ptr<PeerConnected>& data)
{

}

void TestThread::Handle(ENetPeer* peer, const std::shared_ptr<PeerDisconnected>& data)
{

}

void TestThread::Handle(ENetPeer* peer, const std::shared_ptr<GameSetup>& data)
{

}

void TestThread::Handle(ENetPeer* peer, const std::shared_ptr<WorldUpdate>& data)
{

}


void TestThread::Handle(ENetPeer* peer, const std::shared_ptr<ChatMessage>& message)
{
	//std::wcout << "[" << message.GetSender() << "]: " << message.GetContents() << std::endl;

	if(GameOverlay::IsInitialized() && GameOverlay::GetGameUI != NULL)
	{
		ChatWindow *pChatWindow = GameOverlay::GetGameUI()->GetChatWindow();

		if(pChatWindow != NULL)
		{
			pChatWindow->AddInfoMessageW(L"[%d]: %ls", message->GetSender(), message->GetContents().c_str());
		}
	}
}

void TestThread::Handle(ENetPeer* peer, const std::shared_ptr<PlayerJoin>& message)
{
	__Player plyr(message->GetSender(), message->GetName());
	player_pool.players.push_back(plyr);

	if(GameOverlay::IsInitialized() && GameOverlay::GetGameUI != NULL)
	{
		ChatWindow *pChatWindow = GameOverlay::GetGameUI()->GetChatWindow();

		if(pChatWindow != NULL)
		{
			pChatWindow->AddInfoMessageW(L"%ls joined. (ID: %d)", message->GetName().c_str(), message->GetSender());
		}
	}
}

void DespawnPlayer(__Player &plyr)
{
	if(plyr.spawned)
	{
		if(ENTITY::DOES_ENTITY_EXIST(plyr.ped) && ENTITY::IS_ENTITY_A_PED(plyr.ped))
		{
			PED::DELETE_PED((scrAny *)(&plyr.ped));
		}

		plyr.ped = 0;

		plyr.waiting_for_model_to_load = false;
		plyr.spawned = false;
	}
}

void TestThread::Handle(ENetPeer* peer, const std::shared_ptr<PlayerQuit>& message)
{
	ChatWindow *pChatWindow = NULL;

	if(GameOverlay::IsInitialized() && GameOverlay::GetGameUI != NULL)
	{
		pChatWindow = GameOverlay::GetGameUI()->GetChatWindow();
	}

    for(auto iter = player_pool.players.begin(); iter != player_pool.players.end();)
    {
        auto temp_iter = iter++;

        if(temp_iter->id == message->GetSender())
		{
			DespawnPlayer(*temp_iter);

			if(pChatWindow != NULL)
			{
				pChatWindow->AddInfoMessageW(L"%ls left. (ID: %d)", temp_iter->name.c_str(), temp_iter->id);
			}

            player_pool.players.erase(temp_iter);
		}
    }
}

void TestThread::Handle(ENetPeer* peer, const std::shared_ptr<PlayerSpawn>& message)
{
	for(auto& plyr : player_pool.players)
	{
		if(plyr.id == message->GetSender() && !plyr.spawned)
		{
			uint32_t _model_hash = message->GetModelHash();

			Vector3
				_position,
				_rotation;

			message->GetPosition(_position);
			message->GetRotation(_rotation);

			plyr.spawn_info.model_hash = _model_hash;
			plyr.spawn_info.position = _position;
			plyr.spawn_info.rotation = _rotation;

			if(STREAMING::IS_MODEL_IN_CDIMAGE(_model_hash))
			{
				if(STREAMING::HAS_MODEL_LOADED(_model_hash))
				{
					plyr.ped = PED::CREATE_PED(1, _model_hash, _position.x, _position.y, _position.z, 0.0f, FALSE, TRUE);

					ENTITY::SET_ENTITY_ROTATION(plyr.ped, _rotation.x, _rotation.y, _rotation.z, 2, TRUE);
					WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(plyr.ped, FALSE);
					PED::SET_PED_CAN_BE_TARGETTED(plyr.ped, TRUE);
					PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(plyr.ped, TRUE);

					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_model_hash);
				
					plyr.waiting_for_model_to_load = false;
					plyr.spawned = true;
				}
				else
				{
					STREAMING::REQUEST_MODEL(_model_hash);

					plyr.waiting_for_model_to_load = true;
					plyr.spawned = false;
				}
			}
			else
			{
				plyr.waiting_for_model_to_load = false;
				plyr.spawned = false;
			}

			if(GameOverlay::IsInitialized() && GameOverlay::GetGameUI != NULL)
			{
				ChatWindow *pChatWindow = GameOverlay::GetGameUI()->GetChatWindow();

				if(pChatWindow != NULL)
				{
					pChatWindow->AddInfoMessageW(L"%ls spawned. (ID: %d)", plyr.name.c_str(), plyr.id);
				}
			}
		}
	}
}

void TestThread::Handle(ENetPeer* peer, const std::shared_ptr<PlayerDespawn>& message)
{
	for(auto& plyr : player_pool.players)
	{
		if(plyr.id == message->GetSender() && plyr.spawned)
		{
			DespawnPlayer(plyr);
		}
	}
}

void TestThread::Handle(ENetPeer* peer, const std::shared_ptr<OnFootSync>& message)
{
	for(auto& plyr : player_pool.players)
	{
		if(plyr.id == message->GetSender() && plyr.spawned && plyr.ped != -1)
		{
			Vector3
				position,
				rotation,
				velocity;

			message->GetPosition(position);
			message->GetRotation(rotation);
			message->GetVelocity(velocity);

			float
				current_move_blend_ratio = message->GetCurrentMoveBlendRatio(),
				target_move_blend_ratio = message->GetTargetMoveBlendRatio();

			uint32_t sync_weapon_hash = message->GetCurrentWeaponHash();
			bool is_jumping = message->IsJumping();

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(plyr.ped, position.x, position.y, position.z, FALSE, FALSE, FALSE);
			ENTITY::SET_ENTITY_ROTATION(plyr.ped, rotation.x, rotation.y, rotation.z, 2, TRUE);
			ENTITY::SET_ENTITY_VELOCITY(plyr.ped, velocity.x, velocity.y, velocity.z);

			scrHash current_weapon_hash = 0;
			WEAPON::GET_CURRENT_PED_WEAPON(plyr.ped, &current_weapon_hash, TRUE);

			if(current_weapon_hash != sync_weapon_hash)
			{
				WEAPON::GIVE_WEAPON_TO_PED(plyr.ped, sync_weapon_hash, 9999, TRUE, TRUE);
				WEAPON::SET_CURRENT_PED_WEAPON(plyr.ped, sync_weapon_hash, TRUE);
			}

			if(is_jumping && !PED::IS_PED_JUMPING(plyr.ped) && !plyr.was_jumping)
			{
				AI::TASK_JUMP(plyr.ped, TRUE);

				plyr.was_jumping = true;
			}
			else
			{
				plyr.was_jumping = false;
			}

			typedef uint64_t (__fastcall * scriptHandleToPed_t)(scrPed pedHandle);
			static scriptHandleToPed_t scriptHandleToPed = (scriptHandleToPed_t)GameAddresses::scriptHandleToPed;

			uint64_t sync_ped = scriptHandleToPed(plyr.ped);

			if(sync_ped != NULL)
			{
				*(float *)(sync_ped + 0x578) = current_move_blend_ratio;
				//*(float *)(sync_ped + 0x580) = target_move_blend_ratio;
				*(float *)(sync_ped + 0x588) = current_move_blend_ratio;
			}
		}
	}
}

void TestThread::Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& message)
{
	//std::cout << "Connected!" << std::endl;

	if(GameOverlay::IsInitialized() && GameOverlay::GetGameUI != NULL)
	{
		ChatWindow *pChatWindow = GameOverlay::GetGameUI()->GetChatWindow();

		if(pChatWindow != NULL)
		{
			pChatWindow->AddInfoMessageW(L"Connected!");
		}
	}

	connected = true;

	player_pool.players.clear();

	PlayerJoin player_join;
	player_join.SetName(L"Player");
	connection.SendAsync(player_join);

	PlayerSpawn player_spawn;

	Vector3
		position,
		rotation;

	if (GameAddresses::ppPedFactory != NULL)
	{
		uint64_t pPedFactory = *(uint64_t *)(GameAddresses::ppPedFactory);

		if (pPedFactory != NULL)
		{
			uint64_t pLocalPlayerPed = *(uint64_t *)(pPedFactory + 8);

			if (pLocalPlayerPed != NULL)
			{
				position.x = *(float *)(pLocalPlayerPed + 0x90);
				position.y = *(float *)(pLocalPlayerPed + 0x94);
				position.z = *(float *)(pLocalPlayerPed + 0x98);
			}
		}
	}

	scrPed playerPedId = PLAYER::GET_PLAYER_PED(-1);

	if (playerPedId != -1 && playerPedId != 0)
	{
		scrVector3 scr_rotation = ENTITY::GET_ENTITY_ROTATION(playerPedId, 0);
		rotation.x = scr_rotation.x; rotation.y = scr_rotation.y; rotation.z = scr_rotation.z;
	}

	player_spawn.SetModelHash(0x0D7114C9);
	player_spawn.SetPosition(position);
	player_spawn.SetRotation(rotation);

	connection.SendAsync(player_spawn);
}

void TestThread::Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& message)
{
	//std::cout << "Disconnected! Reconnecting..." << std::endl;
	connected = false;

	if(GameOverlay::IsInitialized() && GameOverlay::GetGameUI != NULL)
	{
		ChatWindow *pChatWindow = GameOverlay::GetGameUI()->GetChatWindow();

		if(pChatWindow != NULL)
		{
			pChatWindow->AddInfoMessageW(L"Disconnected! Reconnecting...");
		}
	}

	connection.Connect("127.0.0.1", 5544);
}

void TestThread::RunNetwork()
{
	//you can run RunNetworking in another thread safely
	connection.RunNetworking();
	connection.ProcessEvents(this);
}
