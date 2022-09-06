#pragma once

class scriptHandlerMgr
{
public:
	virtual ~scriptHandlerMgr();
	virtual void _Function1() = 0;
	virtual void _Function2() = 0;
	virtual void _Function3() = 0;
	virtual void _Function4() = 0;
	virtual void _Function5() = 0;
	virtual void _Function6() = 0;
	virtual void _Function7() = 0;
	virtual void _Function8() = 0;
	virtual void _Function9() = 0;
	virtual void AttachScript(scrThread *thread) = 0;
};

class scrNativeCallContext;

typedef DWORD scrVoid;
typedef DWORD scrAny;
typedef DWORD scrUint;
typedef DWORD scrHash;
typedef int scrEntity;
typedef int scrPlayer;
typedef int scrFireId;
typedef int scrPed;
typedef int scrVehicle;
typedef int scrCam;
typedef int scrCarGenerator;
typedef int scrGroup;
typedef int scrTrain;
typedef int scrPickup;
typedef int scrObject;
typedef int scrWeapon;
typedef int scrInterior;
typedef int scrBlip;
typedef int scrTexture;
typedef int scrTextureDict;
typedef int scrCoverPoint;
typedef int scrCamera;
typedef int scrTaskSequence;
typedef int scrColourIndex;
typedef int scrSphere;

struct scrVector3
{
	float x;

private:
	uint32_t pad;

public:
	float y;

private:
	uint32_t pad2;

public:
	float z;

private:
	uint32_t pad3;
};

class ScriptEngine
{
public:
	static bool Initialize();

	static pgPtrCollection<ScriptThread> * GetThreadCollection();
	static scriptHandlerMgr * GetScriptHandleMgr();

	static bool IsThreadCollectionEmpty();

	// Gets the active thread
	static scrThread * GetActiveThread();

	// Sets the currently running thread
	static void SetActiveThread(scrThread *thread);

	// Adds a precreated custom thread to the runtime and starts it
	static void CreateThread(ScriptThread *thread);

	// Native function handler type
	typedef void (__cdecl * NativeHandler) (scrNativeCallContext *context);

	// Gets a native function handler
	static NativeHandler GetNativeHandler(uint64_t oldHash);
	static uint64_t GetNewHashFromOldHash(uint64_t oldHash);
};
