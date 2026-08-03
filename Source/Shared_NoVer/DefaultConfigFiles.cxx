#include "DefaultConfigFiles.hxx"

#include <filesystem>
#include <fstream>
#include <string>

namespace universelan::defaults {

	void create_boot_file(const std::filesystem::path& filename) {
		const std::string default_boot_file = R"---(
; This is the base config file for both the Client AND the Server
; It is part of the UniverseLAN project located at https://github.com/grasmanek94/UniverseLAN
[Storage]

; GameDataPath is used by the game/DLL
;
GameDataPath = UniverseLANData

; ServerDataPath is user by UniverseLANServer executable
;
ServerDataPath = UniverseLANServerData

[Authentication]

; Client and server must have the same authentication key
;
; If a client doesn't have the right key, the server will refuse the connection
;
; Can be generated with OpenSSL:
;   openssl rand -base64 64 | paste --delimiters '' --serial 
; With PowerShell:
;   powershell -command "[Convert]::ToBase64String((1..64|%{[byte](Get-Random -Max 256)}))"
;
; THIS IS NOT AN ENCRYPTION KEY! MERELY AN AUTHENTICATION KEY 
; (so that random clients cannot willy-nilly connect to your server)
;
Key = 9g5tA53SLyiNkBTqsX3BmBgy/PPVTU6VGKWNNw3wUIY5nK1C2MOT4UsZ2pauCb8fm5UQSJRijid+w1t9WpDaKQ==


[Tracing]

; Disable to improve performance
;
CallTracing = 0

; If we should handle unhandled exceptions?
;
UnhandledExceptionLogging = 0

; Create minidump when unhandled exception occurs
;
MiniDumpOnUnhandledException = 0

; 0 - Normal minidump
; 1 - More data, ram etc
; 2 - Almost everything possible
;
MiniDumpVerbosityLevel = 0

; Disable to improve tracing performance
;
AlwaysFlush = 0

; Which tracing flags to enable
;
; Combine with a pipe symbol |
; Like: CallTracingFlags = INFORMATIONAL | HIGH_FREQUENCY_CALLS | ARGUMENTS
;
; INFORMATIONAL (always enabled)
; HIGH_FREQUENCY_CALLS
; ARGUMENTS
; RETURN_VALUES
; DETAILED
; ICHAT
; NETCLIENT
; ICUSTOMNETWORKING
; IERROR
; IFRIENDS
; GALAXYDLL
; GALAXYDLL_GAMESERVERAPI
; LISTENERREGISTRAR
; ILOGGER
; IMATCHMAKING
; INETWORKING
; ISTATS
; ISTORAGE
; ITELEMETRY
; IUSER
; IUTILS
; IGAMESERVERAPI
; IGALAXYTHREAD
; IAPPS
; CUSTOMCONSOLE
; ICLOUDSTORAGE
; NOTIFICATION_INVOCATIONS
; 
; TRACE_ALL_FLAGS (this one will trace ALL of the above with a single option)
; 
; (check Tracer.hxx for all possible flags)
;
; Prepending ! or ~ allows to disable a certain option
; Like: CallTracingFlags = TRACE_ALL_FLAGS | !HIGH_FREQUENCY_CALLS
;
CallTracingFlags = INFORMATIONAL

; Enables tracing to console (in addition to tracing to tracefiles)
; Can slow down the game extremely in some cases.
;
TraceToConsole = 0

)---";

		std::error_code ec;
		std::filesystem::create_directories(filename.parent_path(), ec);

		std::fstream data_stream{ filename, std::ios::out | std::ios::trunc };
		if (data_stream) {
			data_stream.unsetf(std::ios::skipws);
			data_stream.write(default_boot_file.c_str(), default_boot_file.size());
		}
	}

	void create_client_config_file(const std::filesystem::path& filename) {
		const std::string default_client_config_file = R"---(
[Settings]
Language = english

; Language code consists of ISO-639 language code and ISO-3166 country code, ex. "en-US", "pl-PL".
LanguageCode = en-US

; Enable all downloaded and installed DLC which you already own
EnableAllDLC = 0

; When enabled, client will save any requested DLC product IDs into UniverseLAN\DLC.ini
SaveUnknownDLCIDs = 1

SaveAchievementsAndStats = 1

EnableConsole = 1

[Storage]
AllowFileSharingDownload = 1
AllowFileSharingUpload = 0

[Telemetry]
Store = 0

[Client]
ServerAddress = 127.0.0.1
Port = 19486

[User]
; PersonaNameType can be:
; - @WindowsAccountName
; - @WindowsAccountNameHash
; - @ComputerName
; - @ComputerNameHash
; - @MachineID
; - @MachineIDHash
; - @NetworkAdapterMACHash
; - @ProcessID
; - @DebugID
; - @Custom (allows you to specify your username in CustomPersonaName)
;
PersonaNameType = @Custom
CustomPersonaName = Player

; If true (1) then CustomPersonaName will be appended to 
; whatever option has been chosen for PersonaNameType.
;
; For example if 
;  "PersonaNameType = @ComputerName" 
; and 
;  "CustomPersonaName = Player" 
; then the resulting name will be 
;  "ComputerNamePlayer"
;
SuffixPersonaNameTypeResultWithCustomPersonaName = 1

; GalaxyIDType can be:
; - @WindowsAccountNameHash
; - @ComputerNameHash
; - @MachineIDHash
; - @NetworkAdapterMACHash
; - @Custom
;
GalaxyIDType = @NetworkAdapterMACHash

; 64bit unsigned integer
CustomGalaxyID = 1

; static offset that is applied to the custom or calculated GalaxyID
; Can be:
; - a literal / number
; -  @ProcessID
; -  @DebugID
; @ProcessID can be used to offset the GalaxyID with the ID value of the current process
; Useful when running multiple instances on a single computer (e.g. during tests)
GalaxyIDOffset = 0

; filename of the avatar
Avatar = me.png

SignedIn = 1

; Automatically accept game invitations when received
AutoAcceptGameInvitations = 1

[Interceptor]

OverrideInitKeys = 0
OverrideInitKeyId = 0
OverrideInitKeySecret = 0

OverrideSignIn = 0
OverrideSignInId = 0
OverrideSignInPassword = 0

)---";

		std::error_code ec;
		std::filesystem::create_directories(filename.parent_path(), ec);

		std::fstream data_stream{ filename, std::ios::out | std::ios::trunc };
		if (data_stream) {
			data_stream.unsetf(std::ios::skipws);
			data_stream.write(default_client_config_file.c_str(), default_client_config_file.size());
		}
	}

	void create_server_config_file(const std::filesystem::path& filename) {
		const std::string default_server_config_file = R"---(
[Storage]

AllowFileSharingDownload = 1
AllowFileSharingUpload = 1

[Server]

; Use:
;   BindAddress = localhost
; to bind to both IPv4 and IPv6 (dual stack server)
BindAddress = 0.0.0.0
Port = 19486
MaxConnections = 1024
MaxTickRate = 200 ; in Hz

)---";

		std::error_code ec;
		std::filesystem::create_directories(filename.parent_path(), ec);

		std::fstream data_stream{ filename, std::ios::out | std::ios::trunc };
		if (data_stream) {
			data_stream.unsetf(std::ios::skipws);
			data_stream.write(default_server_config_file.c_str(), default_server_config_file.size());
		}
	}
}
