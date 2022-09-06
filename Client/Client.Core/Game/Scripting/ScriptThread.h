#pragma once

enum eScriptThreadState
{
	ThreadStateIdle,
	ThreadStateRunning,
	ThreadStateKilled,
	ThreadState3,
	ThreadState4,
};

class scrThreadContext
{
public:
	uint32_t					m_iThreadId; 		//0x0000 
	uint32_t					m_iScriptHash; 		//0x0004 
	eScriptThreadState			m_State; 			//0x0008 
	uint32_t					m_iIP; 				//0x000C 
	uint32_t					m_iFrameSP; 		//0x0010 
	uint32_t					m_iSP; 				//0x0014 
	uint32_t					m_iTimerA; 			//0x0018 
	uint32_t					m_iTimerB; 			//0x001C 
	uint32_t					m_iTimerC; 			//0x0020 
	uint32_t					m_iUnk1; 			//0x0024 
	uint32_t					m_iUnk2;			//0x0028 
	char _0x002C[52];
	uint32_t					m_iSet1;			//0x0060 
	char _0x0064[68];
};

class scrThread
{
protected:
	scrThreadContext			m_Context;			//0x0008
	__int64						m_pStack;			//0x00B0
	char _0x00B8[16];
	char *						m_pszExitMessage;	//0x00C8

public:
	virtual ~scrThread() {}
	virtual eScriptThreadState Reset(uint32_t scriptHash, void* pArgs, uint32_t argCount) = 0;
	virtual eScriptThreadState Run(uint32_t opsToExecute) = 0;
	virtual eScriptThreadState Tick(uint32_t opsToExecute) = 0;
	virtual void Kill() = 0;

	inline scrThreadContext * GetContext() { return &m_Context; }
	inline uint32_t GetId() { return m_Context.m_iThreadId; }
};

class ScriptThread : public scrThread
{
private:
	char _0x00D0[64];
	void *						m_pScriptHandler;	//0x0110 
	char _0x0118[40];
	uint8_t						m_bFlag1;			//0x0140 
	uint8_t						m_bNetworkFlag;		//0x0141 
	char _0x0142[22];

public:
	virtual void DoRun() = 0;

	virtual eScriptThreadState Reset( uint32_t scriptHash, void* pArgs, uint32_t argCount );
	virtual eScriptThreadState Run( uint32_t opsToExecute );
	virtual eScriptThreadState Tick( uint32_t opsToExecute );
	virtual void Kill();

	inline void * GetScriptHandler() { return m_pScriptHandler; }
	inline void SetScriptHandler(void* scriptHandler) { m_pScriptHandler = scriptHandler; }

};
