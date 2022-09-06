#pragma once

#ifdef WIN32
	#include <windows.h>
#else
	#include <pthread.h>
#endif

class CriticalSection
{
public:
	CriticalSection()
	{
#ifdef WIN32
		critical_section = new CRITICAL_SECTION;

		InitializeCriticalSection((CRITICAL_SECTION *)(critical_section));
#else
		critical_section = new pthread_mutex_t;

		pthread_mutex_init((pthread_mutex_t *)(critical_section), NULL);
#endif
	}

	~CriticalSection()
	{
#ifdef WIN32
		DeleteCriticalSection((CRITICAL_SECTION *)(critical_section));

		delete (CRITICAL_SECTION *)(critical_section);
#else
		pthread_mutex_destroy((pthread_mutex_t *)(critical_section));

		delete (pthread_mutex_t *)(critical_section);
#endif
	}

	void Lock()
	{
#ifdef WIN32
		if(critical_section)
			EnterCriticalSection((CRITICAL_SECTION *)(critical_section));
#else
		if(critical_section)
			pthread_mutex_lock((pthread_mutex_t *)(critical_section));
#endif
	}

	void Unlock()
	{
#ifdef WIN32
		if(critical_section)
			LeaveCriticalSection((CRITICAL_SECTION *)(critical_section));
#else
		if(critical_section)
			pthread_mutex_unlock((pthread_mutex_t *)(critical_section));
#endif
	}

private:
	void *critical_section;
};
