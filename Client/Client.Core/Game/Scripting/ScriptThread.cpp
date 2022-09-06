#include "Main.h"

eScriptThreadState ScriptThread::Tick(uint32_t opsToExecute)
{
	typedef eScriptThreadState (__thiscall * ScriptThreadTick_t) (ScriptThread *ScriptThread, uint32_t opsToExecute);
	static ScriptThreadTick_t threadTickGta = (ScriptThreadTick_t)hook::pattern("80 B9 46 01 00 00 00 8B  FA 48 8B D9 74 05").count(1).get(0).get<void>(-0xF);
	return threadTickGta(this, opsToExecute);
}

void ScriptThread::Kill()
{
	typedef void (__thiscall * ScriptThreadKill_t) (ScriptThread *ScriptThread);
	static ScriptThreadKill_t killScriptThread = (ScriptThreadKill_t)hook::pattern("48 83 EC 20 48 83 B9 10 01 00 00 00 48 8B D9 74 14").count(1).get(0).get<void>(-6);
	return killScriptThread(this);
}

eScriptThreadState ScriptThread::Run(uint32_t opsToExecute)
{
	if(GetScriptHandler() == nullptr)
	{
		ScriptEngine::GetScriptHandleMgr()->AttachScript(this);

		//this->m_bNetworkFlag = true;
	}

	// Set the current thread
	scrThread *activeThread = ScriptEngine::GetActiveThread();
	ScriptEngine::SetActiveThread(this);

	// Invoke the running thing if we're not dead
	if(m_Context.m_State != ThreadStateKilled)
	{
		DoRun();
	}

	ScriptEngine::SetActiveThread(activeThread);
	return m_Context.m_State;
}

void ScriptThreadInit(ScriptThread * thread)
{
	typedef void ( __thiscall * ScriptThreadInit_t) (ScriptThread * ScriptThread);
	static ScriptThreadInit_t ScriptThreadInit = (ScriptThreadInit_t)hook::pattern("83 89 38 01 00 00 FF 83 A1 50 01 00 00 F0").count(1).get(0).get<void>();
	return ScriptThreadInit(thread);
}

eScriptThreadState ScriptThread::Reset(uint32_t scriptHash, void *pArgs, uint32_t argCount)
{
	memset(&m_Context, 0, sizeof(m_Context));

	m_Context.m_State = ThreadStateIdle;
	m_Context.m_iScriptHash = scriptHash;
	m_Context.m_iUnk1 = -1;
	m_Context.m_iUnk2 = -1;
	m_Context.m_iSet1 = 1;

	ScriptThreadInit(this);

	m_pszExitMessage = "Normal exit";
	return m_Context.m_State;
}
