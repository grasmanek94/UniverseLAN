#include <GalaxyApi.h>

#include <chrono>
#include <thread>

class AuthListenerGlobal : public galaxy::api::GlobalAuthListener
{
public:
    AuthListenerGlobal() {

    }

    virtual ~AuthListenerGlobal() = default;

    virtual void OnAuthSuccess() override {

    }

    virtual void OnAuthFailure(FailureReason reason) override {

    }

    virtual void OnAuthLost() override {

    }
};

class AuthListenerLocal : public galaxy::api::IAuthListener
{
public:
    AuthListenerLocal() {

    }

    virtual ~AuthListenerLocal() = default;

    virtual void OnAuthSuccess() override {

    }

    virtual void OnAuthFailure(FailureReason reason) override {

    }

    virtual void OnAuthLost() override {

    }
};

int main()
{
    galaxy::api::InitOptions options("", "");

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
