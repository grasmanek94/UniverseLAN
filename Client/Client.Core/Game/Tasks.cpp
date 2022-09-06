#include "Main.h"

std::wstring getTaskNameById(uint16_t taskId)
{
	std::wstring taskName = L"Unknown";

	auto pair = taskMap.find(taskId);

	if(pair != taskMap.end())
	{
		taskName = pair->second;
	}

	return taskName;
}

void addTaskListEntry(wchar_t *pwszTaskListString, size_t taskListStringLength, uint64_t pTask)
{
	uint16_t taskId = *(uint16_t *)(pTask + 0x34);
	std::wstring taskName = getTaskNameById(taskId);

	wchar_t wszTaskListEntry[128];
	swprintf_s(wszTaskListEntry, 128, L"   %ls (%d)\n", taskName.c_str(), taskId);
	wcscat_s(pwszTaskListString, taskListStringLength, wszTaskListEntry);

	uint64_t pChildTask = *(uint64_t *)(pTask + 0x20);
	uint32_t itemCount = 0;

	while(pChildTask != NULL)
	{
		uint64_t pCurrentChildTask = pChildTask;

		taskId = *(uint16_t *)(pChildTask + 0x34);
		std::wstring taskName = getTaskNameById(taskId);

		itemCount++;

		for(uint32_t i = 0; i < itemCount; i++)
		{
			wcscat_s(pwszTaskListString, taskListStringLength, L"   ");
		}

		swprintf_s(wszTaskListEntry, 128, L"   %ls (%d)\n", taskName.c_str(), taskId);
		wcscat_s(pwszTaskListString, taskListStringLength, wszTaskListEntry);

		pChildTask = *(uint64_t *)(pCurrentChildTask + 0x20);
	}
}

void getTaskTreeInfo(wchar_t *pwszTaskListString, size_t taskListStringLength, uint64_t pTaskTree)
{
	int32_t taskTreeCapacity = *(int32_t *)(pTaskTree + 0x48);

	if(taskTreeCapacity > 0)
	{
		for(int32_t i = 0; i < taskTreeCapacity; i++)
		{
			uint64_t pTask = *(uint64_t *)(pTaskTree + 0x20 + i * 0x08);

			if(pTask != NULL)
			{
				addTaskListEntry(pwszTaskListString, taskListStringLength, pTask);
			}
		}
	}
}

extern uint64_t g_pClonePed;

void drawTaskList(ID3D11DeviceContext *pD3D11DeviceContext, IFW1FontWrapper *pFW1FontWrapper)
{
	if(GameStateWatcher::GetGameState() == GameStatePlaying && GameAddresses::ppPedFactory != NULL && GameAddresses::pedIntelligenceOffset != 0)
	{
		uint64_t pPedFactory = *(uint64_t *)(GameAddresses::ppPedFactory);

		if(pPedFactory != NULL)
		{
			uint64_t pLocalPlayerPed = *(uint64_t *)(pPedFactory + 8);

			if(pLocalPlayerPed != NULL)
			{
				uint64_t pPedIntelligence = *(uint64_t *)(pLocalPlayerPed + GameAddresses::pedIntelligenceOffset);
				
				if(pPedIntelligence != NULL)
				{
					uint64_t pTaskTreePed = *(uint64_t *)(pPedIntelligence + 0x360);
					uint64_t pTaskTreeMovement = *(uint64_t *)(pPedIntelligence + 0x370);
					uint64_t pTaskTreeMotion = *(uint64_t *)(pPedIntelligence + 0x378);

					wchar_t wszTaskListString[4096];
					swprintf_s(wszTaskListString, 4096, L"\nTasks:\n");

					if(pTaskTreePed != NULL) { getTaskTreeInfo(wszTaskListString, 4096, pTaskTreePed); }
					if(pTaskTreeMovement != NULL) { getTaskTreeInfo(wszTaskListString, 4096, pTaskTreeMovement); }
					if(pTaskTreeMotion != NULL) { getTaskTreeInfo(wszTaskListString, 4096, pTaskTreeMotion); }

					if(g_pClonePed != NULL)
					{
						wcscat_s(wszTaskListString, 4096, L"\nClone Ped Tasks:\n");

						pPedIntelligence = *(uint64_t *)(g_pClonePed + GameAddresses::pedIntelligenceOffset);

						pTaskTreePed = *(uint64_t *)(pPedIntelligence + 0x360);
						pTaskTreeMovement = *(uint64_t *)(pPedIntelligence + 0x370);
						pTaskTreeMotion = *(uint64_t *)(pPedIntelligence + 0x378);

						if(pTaskTreePed != NULL) { getTaskTreeInfo(wszTaskListString, 4096, pTaskTreePed); }
						if(pTaskTreeMovement != NULL) { getTaskTreeInfo(wszTaskListString, 4096, pTaskTreeMovement); }
						if(pTaskTreeMotion != NULL) { getTaskTreeInfo(wszTaskListString, 4096, pTaskTreeMotion); }
					}

					pFW1FontWrapper->DrawString(pD3D11DeviceContext, wszTaskListString, 18.0f, 22.0f, 64.0f, 0xff000000, FW1_RESTORESTATE);
					pFW1FontWrapper->DrawString(pD3D11DeviceContext, wszTaskListString, 18.0f, 20.0f, 62.0f, 0xffffffff, FW1_RESTORESTATE);
				}
			}
		}
	}
}

bool isTaskExistInTree(uint64_t pTaskTree, uint16_t taskId)
{
	int32_t taskTreeCapacity = *(int32_t *)(pTaskTree + 0x48);

	if(taskTreeCapacity > 0)
	{
		for(int32_t i = 0; i < taskTreeCapacity; i++)
		{
			uint64_t pTask = *(uint64_t *)(pTaskTree + 0x20 + i * 0x08);

			if(pTask != NULL)
			{
				uint64_t pChildTask = *(uint64_t *)(pTask + 0x20);
				uint16_t currentTaskId = *(uint64_t *)(pChildTask + 0x34);

				if(currentTaskId == taskId)
				{
					return true;
				}

				while(pChildTask != NULL)
				{
					uint64_t pCurrentChildTask = pChildTask;
					uint16_t childTaskId = *(uint16_t *)(pChildTask + 0x34);

					if(childTaskId == taskId)
					{
						return true;
					}

					pChildTask = *(uint64_t *)(pCurrentChildTask + 0x20);
				}
			}
		}
	}

	return false;
}

uint64_t getTaskFromTreeById(uint64_t pTaskTree, uint16_t taskId)
{
	int32_t taskTreeCapacity = *(int32_t *)(pTaskTree + 0x48);

	if(taskTreeCapacity > 0)
	{
		for(int32_t i = 0; i < taskTreeCapacity; i++)
		{
			uint64_t pTask = *(uint64_t *)(pTaskTree + 0x20 + i * 0x08);

			if(pTask != NULL)
			{
				uint16_t currentTaskId = *(uint64_t *)(pTask + 0x34);

				if(currentTaskId == taskId)
				{
					return pTask;
				}

				uint64_t pChildTask = *(uint64_t *)(pTask + 0x20);

				while(pChildTask != NULL)
				{
					uint64_t pCurrentChildTask = pChildTask;
					uint16_t currentChildTaskId = *(uint16_t *)(pCurrentChildTask + 0x34);

					if(currentChildTaskId == taskId)
					{
						return pCurrentChildTask;
					}

					pChildTask = *(uint64_t *)(pCurrentChildTask + 0x20);
				}
			}
		}
	}

	return NULL;
}

int32_t getSlotOfTaskFromTreeById(uint64_t pTaskTree, uint16_t taskId)
{
	int32_t taskTreeCapacity = *(int32_t *)(pTaskTree + 0x48);

	if(taskTreeCapacity > 0)
	{
		for(int32_t i = 0; i < taskTreeCapacity; i++)
		{
			uint64_t pTask = *(uint64_t *)(pTaskTree + 0x20 + i * 0x08);

			if(pTask != NULL)
			{
				uint16_t currentTaskId = *(uint64_t *)(pTask + 0x34);

				if(currentTaskId == taskId)
				{
					return i;
				}
			}
		}
	}

	return -1;
}

int32_t getFreeSlotInTaskTree(uint64_t pTaskTree)
{
	int32_t taskTreeCapacity = *(int32_t *)(pTaskTree + 0x48);

	if(taskTreeCapacity > 0)
	{
		for(int32_t i = 0; i < taskTreeCapacity; i++)
		{
			uint64_t pTask = *(uint64_t *)(pTaskTree + 0x20 + i * 0x08);

			if(pTask == NULL)
			{
				return i;
			}
		}
	}

	return -1;
}

void removeTaskFromTreeBySlot(uint64_t pTaskTree, int32_t slot)
{
	int32_t taskTreeCapacity = *(int32_t *)(pTaskTree + 0x48);

	if(slot != -1 && slot >= 0 && taskTreeCapacity <= slot)
	{
		uint64_t pTask = *(uint64_t *)(pTaskTree + 0x20 + slot * 0x08);
		*(uint64_t *)(pTaskTree + 0x20 + slot * 0x08) = NULL;

		uint64_t pChildTask = *(uint64_t *)(pTask + 0x20);
		std::vector<uint64_t> childTasks;

		childTasks.clear();

		while(pChildTask != NULL)
		{
			uint64_t pCurrentChildTask = pChildTask;

			childTasks.push_back(pCurrentChildTask);

			pChildTask = *(uint64_t *)(pCurrentChildTask + 0x20);
		}

		for(auto &childTask : childTasks)
		{
			if(childTask != NULL)
			{
				(*(void (__fastcall **)(uint64_t, uint64_t))*(uint64_t *)(childTask))(childTask, 1i64);
			}
		}

		(*(void (__fastcall **)(uint64_t, uint64_t))*(uint64_t *)(pTask))(pTask, 1i64);
	}
}

void cloneTask(uint64_t pSourceTaskTreePed, uint64_t pTargetTaskTreePed, uint16_t taskId)
{
	int32_t slot = getFreeSlotInTaskTree(pTargetTaskTreePed);

	uint64_t pLocalTask = getTaskFromTreeById(pSourceTaskTreePed, taskId);
	uint64_t pTaskOfClone = getTaskFromTreeById(pTargetTaskTreePed, taskId);

	if(pLocalTask != NULL)
	{
		uint64_t pClonedTaskInfo = (*(uint64_t (__fastcall **)(uint64_t))(*(uint64_t *)(pLocalTask) + 0x170))(pLocalTask);

		if(pClonedTaskInfo != NULL)
		{
			if(pTaskOfClone != NULL)
			{
				(*(void (__fastcall **)(uint64_t, uint64_t))(*(uint64_t *)(pTaskOfClone) + 0x230))(pTaskOfClone, pClonedTaskInfo);
			}
			else if(slot != -1)
			{
				uint64_t pClonedTask = (*(uint64_t (__fastcall **)(uint64_t))(*(uint64_t *)(pClonedTaskInfo) + 0x40))(pClonedTaskInfo);

				if(pClonedTask != NULL)
				{
					(*(void (__fastcall **)(uint64_t, uint64_t, uint64_t, uint64_t))(*(uint64_t *)(pTargetTaskTreePed) + 16))(pTargetTaskTreePed, pClonedTask, slot, 0);
				}
			}
		}

		(*(void (__fastcall **)(uint64_t, uint64_t))*(uint64_t *)(pClonedTaskInfo))(pClonedTaskInfo, 1i64);
	}
	else if(pTaskOfClone != NULL)
	{
		removeTaskFromTreeBySlot(pTargetTaskTreePed, getSlotOfTaskFromTreeById(pTargetTaskTreePed, taskId));
	}
}
