#include "TestCaseClientDetails.hxx"

#include <GalaxyApi.h>

#include <Tracer.hxx>

#include <chrono>
#include <thread>

namespace tracer = universelan::tracer;

class AuthListenerImplGlobal : public galaxy::api::GlobalAuthListener
{
public:
    AuthListenerImplGlobal() {

    }

    virtual ~AuthListenerImplGlobal() = default;

    virtual void OnAuthSuccess() override {

    }

    virtual void OnAuthFailure(FailureReason reason) override {

    }

    virtual void OnAuthLost() override {

    }
};

class AuthListenerImplLocal : public galaxy::api::IAuthListener
{
public:
    AuthListenerImplLocal() {

    }

    virtual ~AuthListenerImplLocal() = default;

    virtual void OnAuthSuccess() override {

    }

    virtual void OnAuthFailure(FailureReason reason) override {

    }

    virtual void OnAuthLost() override {

    }
};

int main()
{
    tracer::Trace::InitTracing(".", false, true, false, 0, true);
    tracer::Trace trace{};

    galaxy::api::InitOptions options(galaxy::api::CLIENT_ID_STR.data(), galaxy::api::CLIENT_SECRET.data());

    galaxy::api::Init(options);

    while (true)
    {
        galaxy::api::ProcessData();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    return 0;
}

#ifdef _WIN32
#include <windows.h>

int
#ifndef _WIN64
__stdcall
#endif
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	return main();
}
#endif
