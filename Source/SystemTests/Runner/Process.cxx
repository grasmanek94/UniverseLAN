#include "Runner.hxx"

#include "Common/Protocol.hxx"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace universelan::systemtest::runner
{
namespace
{
#ifdef _WIN32
std::string quoteWindows(const std::string& value)
{
    std::string result = "\"";
    for (const char character : value) result += character == '\"' ? "\\\"" : std::string(1, character);
    return result + "\"";
}
#endif
}

bool startChild(Child& child, const fs::path& executable, const std::vector<std::string>& arguments, const fs::path& workingDirectory)
{
#ifdef _WIN32
    HANDLE log = CreateFileW(child.log.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (log == INVALID_HANDLE_VALUE) return false;
    if (!SetHandleInformation(log, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT)) { CloseHandle(log); return false; }
    std::string command = quoteWindows(executable.string());
    for (const std::string& argument : arguments) command += " " + quoteWindows(argument);
    std::wstring commandLine = fs::u8path(command).wstring();
    std::vector<wchar_t> writable(commandLine.begin(), commandLine.end());
    writable.push_back(L'\0');
    STARTUPINFOW startup{};
    startup.cb = sizeof(startup);
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startup.hStdOutput = log;
    startup.hStdError = log;
    PROCESS_INFORMATION information{};
    const BOOL started = CreateProcessW(executable.c_str(), writable.data(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW, nullptr, workingDirectory.c_str(), &startup, &information);
    CloseHandle(log);
    if (!started) return false;
    CloseHandle(information.hThread);
    child.process = information.hProcess;
    return true;
#else
    const int log = open(child.log.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (log < 0) return false;
    child.process = fork();
    if (child.process == 0)
    {
        dup2(log, STDOUT_FILENO);
        dup2(log, STDERR_FILENO);
        close(log);
        if (chdir(workingDirectory.c_str()) != 0) _exit(127);
        std::vector<char*> command;
        command.push_back(const_cast<char*>(executable.c_str()));
        for (const std::string& argument : arguments) command.push_back(const_cast<char*>(argument.c_str()));
        command.push_back(nullptr);
        execv(executable.c_str(), command.data());
        _exit(127);
    }
    close(log);
    return child.process > 0;
#endif
}

void updateChild(Child& child)
{
    if (child.exited) return;
#ifdef _WIN32
    DWORD status = STILL_ACTIVE;
    if (GetExitCodeProcess(child.process, &status) && status != STILL_ACTIVE) { child.exited = true; child.exitCode = static_cast<int>(status); }
#else
    int status = 0;
    const pid_t result = waitpid(child.process, &status, WNOHANG);
    if (result == child.process) { child.exited = true; child.exitCode = WIFEXITED(status) ? WEXITSTATUS(status) : 1; }
#endif
}

void stopChild(Child& child)
{
    if (child.process ==
#ifdef _WIN32
        nullptr
#else
        -1
#endif
    ) return;
    updateChild(child);
    if (!child.exited)
    {
#ifdef _WIN32
        TerminateProcess(child.process, 1);
        WaitForSingleObject(child.process, 5000);
        updateChild(child);
#else
        kill(child.process, SIGTERM);
        const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        while (std::chrono::steady_clock::now() < deadline)
        {
            updateChild(child);
            if (child.exited) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        if (!child.exited)
        {
            kill(child.process, SIGKILL);
            const auto forceDeadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
            while (std::chrono::steady_clock::now() < forceDeadline)
            {
                updateChild(child);
                if (child.exited) break;
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
        }
#endif
    }
#ifdef _WIN32
    CloseHandle(child.process);
    child.process = nullptr;
#else
    child.process = -1;
#endif
}

std::vector<std::string> readLines(Child& child)
{
    std::error_code error;
    const std::uintmax_t size = fs::file_size(child.log, error);
    if (error || size <= child.logOffset) return {};
    std::ifstream input(child.log, std::ios::binary);
    if (!input) return {};
    input.seekg(static_cast<std::streamoff>(child.logOffset));
    std::string bytes(static_cast<std::size_t>(size - child.logOffset), '\0');
    input.read(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    bytes.resize(static_cast<std::size_t>(input.gcount()));
    child.logOffset += bytes.size();
    child.pendingLog += bytes;
    std::vector<std::string> lines;
    std::size_t newline = 0;
    while ((newline = child.pendingLog.find('\n')) != std::string::npos)
    {
        std::string line = child.pendingLog.substr(0, newline);
        child.pendingLog.erase(0, newline + 1);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(line);
    }
    return lines;
}

bool handleLine(const std::string& line, const Host& host, Child& child, std::set<std::string>& events)
{
    if (line.rfind("SYSTEM_TEST ", 0) != 0) return true;
    if (line.rfind(common::eventPrefix, 0) == 0)
    {
        const std::string event = line.substr(common::eventPrefix.size());
        if (!common::token(event) || !std::count(host.signals.begin(), host.signals.end(), event)) return false;
        return events.insert(event).second;
    }
    if (line == std::string(common::passPrefix) + host.role && !child.sawPass) { child.sawPass = true; return true; }
    if (line.rfind(common::failPrefix, 0) == 0) return false;
    return false;
}
}
