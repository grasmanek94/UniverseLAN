#include "Main.h"

static pgPtrCollection<ScriptThread> *scrThreadCollection;
static uint32_t activeThreadTlsOffset;
static uint32_t * scrThreadId;
static uint32_t * scrThreadCount;
static scriptHandlerMgr *g_scriptHandlerMgr;

struct NativeRegistration
{
	NativeRegistration *nextRegistration;
	ScriptEngine::NativeHandler handlers[7];
	uint32_t numEntries;
	uint64_t hashes[7];
};

static NativeRegistration **registrationTable;
static std::unordered_set<ScriptThread*> g_ownedThreads;
static std::unordered_map<uint64_t, uint64_t> foundHashCache;

static int JustNoScript(ScriptThread *thread)
{
	if(g_ownedThreads.find(thread) != g_ownedThreads.end())
	{
		thread->Run(0);
	}

	return thread->GetContext()->m_State;
}

bool ScriptEngine::Initialize()
{
	auto scrThreadCollectionPattern = hook::pattern("48 8B C8 EB 03 48 8B CB 48 8B 05");
	auto activeThreadTlsOffsetPattern = hook::pattern("48 8B 04 D0 4A 8B 14 00 48 8B 01 F3 44 0F 2C 42 20");
	auto scrThreadIdPattern = hook::pattern("89 15 ? ? ? ? 48 8B 0C D8");
	auto scrThreadCountPattern = hook::pattern("FF 0D ? ? ? ? 48 8B F9");
	auto registrationTablePattern = hook::pattern("76 61 49 8B 7A 40 48 8D 0D ? ? ? ? 4E 8B 1C C7 41 0F B6 C3 48 8B 0C C1");
	auto g_scriptHandlerMgrPattern = hook::pattern("74 17 48 8B C8 E8 ? ? ? ? 48 8D 0D");
	auto getScriptIdBlock = hook::pattern("80 78 32 00 75 34 B1 01 E8");

	hook::executable_meta executable;
	executable.EnsureInit();

	// get scrThreadCollection
	char *location = scrThreadCollectionPattern.count(1).get(0).get<char>(11);

	if(location == nullptr)
	{
		LOG_ERROR("Unable to find scrThreadCollection");
		return false;
	}

	scrThreadCollection = reinterpret_cast<decltype(scrThreadCollection)>(location + *(int32_t*)location + 4);
	LOG_DEBUG("scrThreadCollection: 0x%p (0x%.8X)", scrThreadCollection, reinterpret_cast<uintptr_t>(scrThreadCollection) - executable.begin());

	// get activet tls offset
	uint32_t *tlsLoc = activeThreadTlsOffsetPattern.count(1).get(0).get<uint32_t>(-4);

	if(tlsLoc == nullptr)
	{
		LOG_ERROR("Unable to find activeThreadTlsOffset");
		return false;
	}

	activeThreadTlsOffset = *tlsLoc;
	LOG_DEBUG("activeThreadTlsOffset: 0x%.8X", activeThreadTlsOffset);

	// get thread id
	location = scrThreadIdPattern.count(1).get(0).get<char>(2);

	if(location == nullptr)
	{
		LOG_ERROR("Unable to find scrThreadId");
		return false;
	}

	scrThreadId = reinterpret_cast<decltype(scrThreadId)>(location + *(int32_t*)location + 4);
	LOG_DEBUG("scrThreadId: 0x%p (0x%.8X)", scrThreadId, reinterpret_cast<uintptr_t>(scrThreadId) - executable.begin());

	// get thread count
	location = scrThreadCountPattern.get(0).get<char>(2);

	if(location == nullptr)
	{
		LOG_ERROR("Unable to find scrThreadCount");
		return false;
	}

	scrThreadCount = reinterpret_cast<decltype(scrThreadCount)>(location + *(int32_t*)location + 4);
	LOG_DEBUG("scrThreadCount: 0x%p (0x%.8X)", scrThreadCount, reinterpret_cast<uintptr_t>(scrThreadCount) - executable.begin());

	// get registration table
	location = registrationTablePattern.count(1).get(0).get<char>(9);

	if(location == nullptr)
	{
		LOG_ERROR("Unable to find registrationTable");
		return false;
	}

	registrationTable = reinterpret_cast<decltype(registrationTable)>(location + *(int32_t*)location + 4);
	LOG_DEBUG("registrationTable: 0x%p (0x%.8X)", registrationTable, reinterpret_cast<uintptr_t>(registrationTable) - executable.begin());

	// get scriptHandlerMgr
	location = g_scriptHandlerMgrPattern.count(1).get(0).get<char>(13);

	if(location == nullptr)
	{
		LOG_ERROR("Unable to find g_scriptHandlerMgr");
		return false;
	}

	g_scriptHandlerMgr = reinterpret_cast<decltype(g_scriptHandlerMgr)>(location + *(int32_t*)location + 4);
	LOG_DEBUG("g_scriptHandlerMgr: 0x%p (0x%.8X)", g_scriptHandlerMgr, reinterpret_cast<uintptr_t>(g_scriptHandlerMgr) - executable.begin());

	// rage::AVscriptHandler::ctor
	location = getScriptIdBlock.count(1).get(0).get<char>(4);

	if(location == nullptr)
	{
		LOG_ERROR("Unable to find getScriptIdBlock");
		return false;
	}

	LOG_DEBUG("getScriptIdBlock: 0x%p (0x%.8X)", location, reinterpret_cast<uintptr_t>(location) - executable.begin());

/*
	// ignore some error @ rage::AVscriptHandler::ctor
	hook::putVP(location, 0xEB);

	// disable ERR_SYS_PURE #1
	if(*(BYTE *)(location + 0x04) == 0xE8)
	{
		hook::putVP(hook::get_call<char *>(location + 0x04), 0xC3);
	}
*/

	// disable ERR_SYS_PURE #2
	if(*(BYTE *)(location + 0x1D) == 0xE8)
	{
		hook::putVP(hook::get_call<char *>(location + 0x1D), 0xC3);
	}

	// gtaThreadTick hook
	hook::jump(hook::pattern("48 83 EC 20 80 B9 46 01 00 00 00 8B FA").count(1).get(0).get<void>(-0xB), JustNoScript);
	return true;
}

scriptHandlerMgr * ScriptEngine::GetScriptHandleMgr()
{
	return g_scriptHandlerMgr;
}

pgPtrCollection<ScriptThread>* ScriptEngine::GetThreadCollection()
{
	return scrThreadCollection;
}

bool ScriptEngine::IsThreadCollectionEmpty()
{
	return (!scrThreadCollection->count() || !scrThreadCollection->begin());
}

scrThread * ScriptEngine::GetActiveThread()
{
	char *moduleTls = *(char**)__readgsqword(88);
	return *reinterpret_cast<scrThread**>(moduleTls + activeThreadTlsOffset);
}

void ScriptEngine::SetActiveThread(scrThread *thread)
{
	char *moduleTls = *(char**)__readgsqword(88);
	*reinterpret_cast<scrThread**>(moduleTls + activeThreadTlsOffset) = thread;
}

void ScriptEngine::CreateThread(ScriptThread *thread)
{
	// get a free thread slot
	auto collection = GetThreadCollection();
	int slot = 0;

	for(auto & thread : *collection)
	{
		auto context = thread->GetContext();

		if(context->m_iThreadId == 0)
		{
			break;
		}

		slot++;
	}

	// did we get a slot?
	if(slot == collection->count())
	{
		return;
	}

	auto context = thread->GetContext();
	thread->Reset((*scrThreadCount) + 1, nullptr, 0);

	if(*scrThreadId == 0)
	{
		*scrThreadId++;
	}

	context->m_iThreadId = *scrThreadId;

	*scrThreadCount++;
	*scrThreadId++;

	collection->set(slot, thread);

	g_ownedThreads.insert(thread);

	LOG_DEBUG("Created thread, id %d", thread->GetId());
}

ScriptEngine::NativeHandler ScriptEngine::GetNativeHandler(uint64_t oldHash)
{
	uint64_t newHash = GetNewHashFromOldHash(oldHash);

	if(newHash == 0)
	{
		return nullptr;
	}

	NativeRegistration *table = registrationTable[newHash & 0xFF];

	for(; table; table = table->nextRegistration)
	{
		for(uint32_t i = 0; i < table->numEntries; i++)
		{
			if(newHash == table->hashes[i])
			{
				return table->handlers[i];
			}
		}
	}

	LOG_DEBUG("Failed to find the native handler of 0x%016llX", oldHash);
	return nullptr;
}

uint64_t TranslateNativeHash(uintptr_t translationTable, uint32_t nativesInTable, uint64_t nativeHash)
{
	uint64_t result = NULL;

	for(uint32_t i = 0; i < nativesInTable; i++)
	{
		uintptr_t offset = i * 16;

		uint64_t oldHash = *(uint64_t *)(translationTable + offset);
		uint64_t newHash = *(uint64_t *)(translationTable + offset + 8);

		if(oldHash == nativeHash)
		{
			result = newHash;
			break;
		}
	}

	return result;
}

uint64_t ScriptEngine::GetNewHashFromOldHash(uint64_t oldHash)
{
	auto cachePair = foundHashCache.find(oldHash);

	if(cachePair != foundHashCache.end())
	{
		return cachePair->second;
	}

	uint64_t
		tempHash = NULL,
		newHash = NULL;

	switch(GameVersion::Get())
	{
		case VER_1_0_335_2_STEAM:
		case VER_1_0_335_2_NOSTEAM:
		{
			newHash = oldHash;
			break;
		}

		case VER_1_0_350_1_STEAM:
		case VER_1_0_350_2_NOSTEAM:
		{
			newHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_335to350), 5257, oldHash);
			break;
		}

		case VER_1_0_372_2_STEAM:
		case VER_1_0_372_2_NOSTEAM:
		{
			tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_335to350), 5257, oldHash);
			if(tempHash != NULL) { newHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_350to372), 5280, tempHash); }
			break;
		}

		case VER_1_0_393_2_STEAM:
		case VER_1_0_393_2_NOSTEAM:
		case VER_1_0_393_4_STEAM:
		case VER_1_0_393_4_NOSTEAM:
		{
			tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_335to350), 5257, oldHash);
			if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_350to372), 5280, tempHash);
				if(tempHash != NULL) { newHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_372to393), 5291, tempHash); }
			}
			break;
		}

		case VER_1_0_463_1_STEAM:
		case VER_1_0_463_1_NOSTEAM:
		{
			tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_335to350), 5257, oldHash);
			if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_350to372), 5280, tempHash);
				if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_372to393), 5291, tempHash);
					if(tempHash != NULL) { newHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_393to473), 5360, tempHash); }
				}
			}
			break;
		}

		case VER_1_0_505_2_STEAM:
		case VER_1_0_505_2_NOSTEAM:
		{
			tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_335to350), 5257, oldHash);
			if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_350to372), 5280, tempHash);
				if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_372to393), 5291, tempHash);
					if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_393to473), 5360, tempHash);
						if(tempHash != NULL) { newHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_473to505), 5406, tempHash); }
					}
				}
			}
			break;
		}

		case VER_1_0_573_1_STEAM:
		case VER_1_0_573_1_NOSTEAM:
		{
			tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_335to350), 5257, oldHash);
			if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_350to372), 5280, tempHash);
				if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_372to393), 5291, tempHash);
					if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_393to473), 5360, tempHash);
						if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_473to505), 5406, tempHash);
							if(tempHash != NULL) { newHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_505to573), 5487, tempHash); }
						}
					}
				}
			}
			break;
		}

		case VER_1_0_617_1_STEAM:
		case VER_1_0_617_1_NOSTEAM:
		{
			tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_335to350), 5257, oldHash);
			if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_350to372), 5280, tempHash);
				if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_372to393), 5291, tempHash);
					if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_393to473), 5360, tempHash);
						if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_473to505), 5406, tempHash);
							if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_505to573), 5487, tempHash);
								if(tempHash != NULL) { newHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_573to617), 5493, tempHash); }
							}
						}
					}
				}
			}
			break;
		}

		case VER_1_0_678_1_STEAM:
		case VER_1_0_678_1_NOSTEAM:
		{
			tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_335to350), 5257, oldHash);
			if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_350to372), 5280, tempHash);
				if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_372to393), 5291, tempHash);
					if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_393to473), 5360, tempHash);
						if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_473to505), 5406, tempHash);
							if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_505to573), 5487, tempHash);
								if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_573to617), 5493, tempHash);
									if(tempHash != NULL) { newHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_617to678), 5511, tempHash); }
								}
							}
						}
					}
				}
			}
			break;
		}
		
		case VER_1_0_757_2_STEAM:
		case VER_1_0_757_2_NOSTEAM:
		case VER_1_0_757_4_STEAM:
		case VER_1_0_757_4_NOSTEAM:
		{
			tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_335to350), 5257, oldHash);
			if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_350to372), 5280, tempHash);
				if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_372to393), 5291, tempHash);
					if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_393to473), 5360, tempHash);
						if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_473to505), 5406, tempHash);
							if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_505to573), 5487, tempHash);
								if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_573to617), 5493, tempHash);
									if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_617to678), 5511, tempHash);
										if(tempHash != NULL) { newHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_678to757), 5565, tempHash); }
									}
								}
							}
						}
					}
				}
			}
			break;
		}

		case VER_1_0_791_2_STEAM:
		case VER_1_0_791_2_NOSTEAM:
		{
			tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_335to350), 5257, oldHash);
			if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_350to372), 5280, tempHash);
				if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_372to393), 5291, tempHash);
					if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_393to473), 5360, tempHash);
						if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_473to505), 5406, tempHash);
							if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_505to573), 5487, tempHash);
								if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_573to617), 5493, tempHash);
									if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_617to678), 5511, tempHash);
										if(tempHash != NULL) { tempHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_678to757), 5565, tempHash);
											if(tempHash != NULL) { newHash = TranslateNativeHash((uintptr_t)(&nativeTranslationTable_757to791), 5591, tempHash); }
										}
									}
								}
							}
						}
					}
				}
			}
			break;
		}

		default:
		{
			/*auto pair = nativeHashMap.find(oldHash);
			if(pair != nativeHashMap.end()) {
				newHash = pair->second;
			}*/
			break;
		}
	}

	if(newHash == NULL)
	{
		LOG_ERROR("Failed to find new hash for 0x%p", oldHash);
		return 0;
	}

	foundHashCache[oldHash] = newHash;
	//LOG_PRINT("Cached 0x%p hash (new: 0x%p), native handler: 0x%p", oldHash, newHash, ScriptEngine::GetNativeHandler(oldHash));
	return newHash;
}
