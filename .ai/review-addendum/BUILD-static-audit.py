"""Read-only BUILD review evidence; no configure/compiler/test/native DLL execution.

Run from any directory with Python -B. Prints derived evidence only. Git commands
are read-only (ls-tree and hash-object without -w). This is a review sidecar.
"""
from pathlib import Path
from collections import Counter, defaultdict
import hashlib
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
BASE = "b30e83872c0006e8240c8b4f565da5351bf10080"
DLL = ROOT / "Source/DLLs"

def text(path):
    return path.read_text(encoding="utf-8-sig", errors="replace")

def version(v):
    return tuple(map(int, v.split(".")))

VERSIONS = sorted((p.name for p in DLL.iterdir() if p.is_dir() and re.fullmatch(r"\d+\.\d+\.\d+", p.name)), key=version)
scope = {"CMakeLists.txt", "Source/CMakeLists.txt", "Source/galaxy_sdk_features.cmake"}
scope.update(p.relative_to(ROOT).as_posix() for p in DLL.rglob("*") if p.is_file() and p.suffix in {".cxx", ".hxx", ".cmake", ".txt"} and not {"galaxy", "gog"}.intersection(p.relative_to(DLL).parts))
scope.update(p.relative_to(ROOT).as_posix() for p in (ROOT / "Source/Vendor").iterdir() if p.is_file() and p.suffix in {".cmake", ".txt"})
scope = sorted(scope)

def git(*args, data=None):
    return subprocess.check_output(["git", *args], cwd=ROOT, input=data).decode("utf-8")

def baseline_hashes(paths):
    tree = {}
    for row in git("ls-tree", "-r", BASE).splitlines():
        meta, name = row.split("\t", 1)
        tree[name] = meta.split()[2]
    current = git("hash-object", "--stdin-paths", data=("\n".join(paths) + "\n").encode()).splitlines()
    return tree, dict(zip(paths, current))

FEATURE_ROWS = re.findall(r"^\s*afvd\((\w+)\s+([\d.]+)(?:\s+([\d.]+))?\s*\)", text(ROOT / "Source/galaxy_sdk_features.cmake"), re.M)
FEATURES = sorted({name for name, _, _ in FEATURE_ROWS})

def enabled(v):
    values = {name: False for name in FEATURES}
    for name, lo, hi in FEATURE_ROWS:
        values[name] |= version(v) >= version(lo) and (not hi or version(v) <= version(hi))
    return values

def strip_comments(s):
    return re.sub(r"/\*.*?\*/|//[^\n]*", "", s, flags=re.S)

def inventory():
    tree, current = baseline_hashes(scope)
    print("PATHS", len(scope), "BASELINE_MATCHES", sum(tree.get(p) == current[p] for p in scope))
    print("DIFFERENCES", [p for p in scope if tree.get(p) != current[p]])
    print("PATHSET_SHA256", hashlib.sha256(("\n".join(scope) + "\n").encode()).hexdigest())
    print("PATH_BLOB_SHA256", hashlib.sha256("".join(f"{p}\t{current[p]}\n" for p in scope).encode()).hexdigest())
    groups = defaultdict(list)
    for p in scope:
        if re.fullmatch(r"Source/DLLs/[^/]+/x(?:86|64)/CMakeLists.txt", p):
            group = "dispatchers"
        elif re.fullmatch(r"Source/DLLs/[^/]+/(?:Factory|Dll).cxx", p):
            group = "markers"
        elif p.endswith("/compat_list.txt"):
            group = "manifests"
        else:
            group = "unique-build"
        groups[group].append(p)
    for g, ps in groups.items():
        print("GROUP", g, len(ps), "BLOBS", dict(Counter(current[p] for p in ps)))
        print("RAW_SHA256_GROUPS", dict(Counter(hashlib.sha256((ROOT / p).read_bytes()).hexdigest() for p in ps)))
    for v in VERSIONS:
        d = DLL / v
        markers = [p.name for p in d.glob("*.cxx")]
        arches = [a for a in ("x86", "x64") if (d / a / "CMakeLists.txt").is_file() and (d / a / "UniverseLAN.def").is_file()]
        manifest = text(d / "compat_list.txt").splitlines() if (d / "compat_list.txt").is_file() else None
        print("VERSION", v, "MARKER", markers, "ARCHES_WITH_DEFS", arches, "MANIFEST", manifest)
    print("FEATURE_ROWS", len(FEATURE_ROWS), "UNIQUE_FEATURES", len(FEATURES), "CELLS", len(FEATURES) * len(VERSIONS))
    numbers = defaultdict(list)
    for v in VERSIONS:
        numbers[int(v.replace(".", ""))].append(v)
    print("NUMERIC_COLLISIONS", {k: vs for k, vs in numbers.items() if len(vs) > 1})
    context = sorted(p.relative_to(ROOT).as_posix() for v in VERSIONS for p in (DLL / v).rglob("*") if p.is_file() and p.suffix in {".h", ".def"})
    tree, current = baseline_hashes(context)
    print("SDK_DEF_CONTEXT", len(context), "BASELINE_MATCHES", sum(tree.get(p) == current[p] for p in context))
    print("CONTEXT_DIFFERENCES", [p for p in context if tree.get(p) != current[p]])

# Each probe is a declaration sentinel, not proof of a whole ABI or of runtime
# behavior. Patterns run on comment-stripped SDK text; signature probes stop at
# semicolons to avoid accidentally accepting a later declaration.
PROBES_TEXT = r"""
HAS_IGALAXY|IGalaxy.h|class\s+GALAXY_DLL_EXPORT\s+IGalaxy
HAS_ISERVERNETWORKING|*|\b(?:Get)?ServerNetworking\s*\(
IFRIENDS_HAS_PERSONANAME_AND_AVATARURL|IFriends.h|\bGetFriendPersonaName\s*\(
IFRIENDS_ONPERSONADATACHANGED|IFriends.h|\bOnPersonaDataChanged\s*\(
IFRIENDS_SET_DEL_CLR_RICHPRESENCE|IFriends.h|\bSetRichPresence\s*\(
HAS_IRICHPRECENSECHANGELISTENER|IFriends.h|class\s+IRichPresenceChangeListener
HAS_IERRORMANAGER|Errors.h|class\s+IErrorManager
FACTORY_RESET_RENAMED_TO_RESETINSTANCE|GalaxyFactory.h|\bResetInstance\s*\(
LEADERBOARDENTRY_REASON_NOT_FOUND|IStats.h|FAILURE_REASON_NOT_FOUND
IUSER_HAS_ISLOGGEDON|IUser.h|\bIsLoggedOn\s*\(
HAS_GAMEJOINREQUESTEDLISTENER|IFriends.h|class\s+IGameJoinRequestedListener
HAS_OPERATIONALSTATECHANGELISTENER|IUser.h|class\s+IOperationalStateChangeListener
FACTORY_HAS_CALLTYPE|GalaxyFactory.h|GALAXY_CALLTYPE\s+GetInstance
ENCRYPTED_APP_TICKET|IUser.h|\bRequestEncryptedAppTicket\s*\(
HAS_IFRIENDLISTLISTENER|IFriends.h|class\s+IFriendListListener
HAS_IOVERLAYSTATECHANGELISTENER|*|class\s+IOverlayStateChangeListener
HAS_GETLEADERBORDENTRYCOUNT|IStats.h|\bGetLeaderboardEntryCount\s*\(
HAS_LEADERBOARD_WITH_DETAILS|IStats.h|\bGetRequestedLeaderboardEntryWithDetails\s*\(
HAS_ILEADERBOARDRETRIEVELISTENER|IStats.h|class\s+ILeaderboardRetrieveListener
HAS_IACCESSTOKENLISTENER|IUser.h|class\s+IAccessTokenListener
HAS_SIGNIN_WITH_SERVERKEY|IUser.h|\bSignIn(?:ServerKey)?\s*\(const char\* serverKey
HAS_GALAXYID_GETREALID|GalaxyID.h|\bGetRealID\s*\(
IFRIENDS_GET_FRIEND_PERSONA_AVATAR_COPY|IFriends.h|\bGetFriendPersonaNameCopy\s*\(
IMATCHMAKING_GET_DATA_MEMBER_COPY|IMatchmaking.h|\bGetLobbyMemberDataCopy\s*\(
ISTATS_LEADERBORDSORTMETHOD_1_71_ARG_CHANGE|IStats.h|FindOrCreateLeaderboard\([^;]*?,\s*LeaderboardSortMethod\s+sortMethod
ISTATS_GET_ACHIEVEMENT_LEADERBOARD_COPY|IStats.h|\bGetAchievementDisplayNameCopy\s*\(
IUSER_GET_DATA_ACCESSTOKEN_COPY|IUser.h|\bGetAccessTokenCopy\s*\(
HAS_IUTILS|IUtils.h|class\s+IUtils
HAS_IAPPS|IApps.h|class\s+IApps
HAS_SPECIFICUSERDATALISTENER|IUser.h|class\s+ISpecificUserDataListener
HAS_ISENDINVITATIONLISTENER|IFriends.h|class\s+ISendInvitationListener
HAS_IUSERTIMEPLAYEDRETRIEVELISTENER|IStats.h|class\s+IUserTimePlayedRetrieveListener
HAS_1_73_AVATARTYPE_CRITERIA|IFriends.h|\bGetFriendAvatarImageID\s*\(
HAS_1_73_LOBBY_FEATURES|IMatchmaking.h|\bIsLobbyJoinable\s*\(
ADDED_RICH_PRESENCE_LISTENERS|IFriends.h|class\s+IRichPresenceListener\b
HAS_INOTIFICATIONLISTENER|IUtils.h|class\s+INotificationListener
HAS_ILOBBYDATARETRIEVELISTENER|IMatchmaking.h|class\s+ILobbyDataRetrieveListener
HAS_IGAMEINVITATIONRECEIVEDLISTENER|IFriends.h|class\s+IGameInvitationReceivedListener
IFRIENDS_HAS_ISAVATARRGBAIMAGEAVAILABLE|IFriends.h|\bIsFriendAvatarImageRGBAAvailable\s*\(
HAS_IFRIEND_ISAVATARAVAILABLE|IFriends.h|\bIsFriendAvatarImageRGBAAvailable\s*\(
HAS_IUSERTIMEPLAYEDRETRIEVELISTENER_UPDATE|IStats.h|class\s+IUserTimePlayedRetrieveListener\s*:\s*public\s+GalaxyTypeAwareListener<USER_TIME_PLAYED_RETRIEVE>
HAS_IUTILS_SHOWOVERLAYWITHWEBPAGE|IUtils.h|\bShowOverlayWithWebPage\s*\(
HAS_SIGNIN_PS4|IUser.h|\bSignIn\s*\(\s*const char\* ps4ClientID
HAS_SIGNIN_REQUIREONLINE|IUser.h|\bSignIn(?:Galaxy)?\s*\(\s*bool requireOnline
HAS_PERSONASTATE_ENUM|IFriends.h|enum\s+PersonaState\b
HAS_LOBBYTOPOLOGYTYPE_ENUM|IMatchmaking.h|enum\s+LobbyTopologyType
HAS_P2P_SEND_IMMEDIATE|INetworking.h|P2P_SEND_RELIABLE_IMMEDIATE
HAS_INITOPTIONS|*|struct\s+InitOptions
HAS_IOTHERSESSIONSTARTLISTENER|IUser.h|class\s+IOtherSessionStartListener
HAS_REQUESTLOBBYLIST_ARGS_ALLOWFULL|IMatchmaking.h|RequestLobbyList\([^;]*\ballowFull
HAS_INITOPTIONS_GALAXYPEERPATH|IGalaxy.h|const char\* galaxyPeerPath;
HAS_SIGNIN_CLASSIC_XBOX|IUser.h|\bSignIn\s*\(\s*uint32_t xboxOneUserID
HAS_ISTORAGE|IStorage.h|class\s+IStorage
HAS_GETCURRENTGAMELANGUAGE|IApps.h|\bGetCurrentGameLanguage\s*\(
HAS_ISTORAGE_SYNCHRONIZE|IStorage.h|\bSynchronize\s*\(
IUTILS_NOTIFICATION_ID_TYPEDEF|IUtils.h|typedef\s+uint64_t\s+NotificationID
HAS_ICUSTOMNETWORKING|ICustomNetworking.h|class\s+ICustomNetworking
ENCRYPTED_APP_TICKET_CONST|IUser.h|RequestEncryptedAppTicket\(\s*const void\*
OVERLAYSTATE_ENUM|IUtils.h|enum\s+OverlayState
HAS_ICHAT|IChat.h|class\s+IChat
NEW_FRIEND_FEATURES_104_3|IFriends.h|\bSendFriendInvitation\s*\(
HAS_ICHAT_ROOMID_IN_INDEX|IChat.h|GetChatRoomMessageByIndex\([^;]*ChatRoomID&
HAS_FRIENDADDLISTENER|IFriends.h|class\s+IFriendAddListener
HAS_IFRIEND_INVITEEXTRAFAILREASONS|IFriends.h|class\s+IFriendInvitationRespondToListener[^}]*FAILURE_REASON_USER_ALREADY_FRIEND
GALAXYID_HAS_IDTYPE|GalaxyID.h|enum\s+IDType
HAS_DISABLEOVERLAYPOPUPS|IUtils.h|\bDisableOverlayPopups\s*\(
FIND_USER|IFriends.h|\bFindUser\s*\(
HAS_ICHATROOMMESSAGERETRIEVELISTENER|IChat.h|class\s+IChatRoomMessagesRetrieveListener
HAS_IUSERFINDLISTENER|IFriends.h|class\s+IUserFindListener
HAS_ICHAT_MESSAGETYPE|IChat.h|enum\s+ChatMessageType
HAS_NAT_FUNCTIONALITY|INetworking.h|\bGetNatType\s*\(
HAS_USERDATAINFOAVAILABLE|IUser.h|\bIsUserDataAvailable\s*\(
SEND_LOBBY_MESSAGE_CHAR_TO_VOID|IMatchmaking.h|SendLobbyMessage\([^;]*const void\*
HAS_CONNECTION_TYPE|INetworking.h|enum\s+ConnectionType
GetImageRGBA_CHAR_TO_VOID|IUtils.h|GetImageRGBA\([^;]*void\*
HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER|IFriends.h|class\s+ISentFriendInvitationListRetrieveListener
HAS_INITOPTIONS_MODERN|InitOptions.h|struct\s+InitOptions
ALLOCATOR|GalaxyAllocator.h|struct\s+GalaxyAllocator
EXCEPTION_HELPER|GalaxyExceptionHelper.h|\bThrowIfGalaxyError\s*\(
GAME_SERVER_API|GalaxyGameServerApi.h|\bInitGameServer\s*\(
NEEDS_DLL_IMPL|GalaxyApi.h|GALAXY_DLL_EXPORT\s+void\s+GALAXY_CALLTYPE\s+Init
HAS_GAMESERVERSERVERNETWORKINGLISTENER|INetworking.h|\bGameServerGlobalServerNetworkingListener\b
USER_SIGNIN_LISTENERS|IUser.h|SignIn(?:Credentials)?\([^;]*IAuthListener\*
HAS_INITOPTIONS_STORAGEPATH|InitOptions.h|const char\* storagePath;
LOBBY_LISTENERS|IMatchmaking.h|CreateLobby\([^;]*ILobbyCreatedListener\*
MATCHMAKING_RET_TYPE_VOID|IMatchmaking.h|virtual\s+void\s+SetLobbyData\s*\(
HAS_IUSER_CONST_LISTENERS|IUser.h|SignIn(?:Credentials)?\([^;]*IAuthListener\*\s+const
ISTATS_UPDATE_1_125|IStats.h|RequestUserStatsAndAchievements\([^;]*IUserStatsAndAchievementsRetrieveListener\*
HAS_LISTENERTYPE|IListenerRegistrar.h|Register\(ListenerType\s+listenerType
IFRIENDS_INFORMATIONLISTENERS|IFriends.h|RequestUserInformation\([^;]*IUserInformationRetrieveListener\*
IFRIENDS_ISTATS_UPDATE_1_127_0|IFriends.h|virtual\s+void\s+GetRichPresenceByIndex\s*\(
HAS_ISUSERINTHESAMEGAME|IFriends.h|\bIsUserInTheSameGame\s*\(
HAS_CONNECTION_FAILURE_REASON|IMatchmaking.h|FAILURE_REASON_CONNECTION_FAILURE
HAS_IMATCHMAKING_LOBBY_LIST_RESULT|IMatchmaking.h|enum\s+LobbyListResult\b
IUTILS_GETNOTIFICATION_1_129_CHANGE|IUtils.h|GetNotification\([^;]*bool&\s+consumable
USER_ACCESS_TOKEN_INFO|IUser.h|ReportInvalidAccessToken\([^;]*\binfo
MATCHMAKING_RESULT_COUNT|IMatchmaking.h|\bAddRequestLobbyListResultCountFilter\s*\(
HAS_INITOPTIONS_HOST_PORT|InitOptions.h|uint16_t\s+port;
HAS_GAMESERVER_UTILS|GalaxyGameServerApi.h|\bGameServerUtils\s*\(
HAS_GOGSERVICECONNECTIONSTATELISTENER|IUtils.h|class\s+IGogServicesConnectionStateListener
HAS_IMATCHMAKING_LOBBY_LEAVE_REASON|IMatchmaking.h|\bLOBBY_LEAVE_REASON_LOBBY_CLOSED\b
SIGNIN_RENAMED_TO_SIGNINCREDENTIALS|IUser.h|\bSignInCredentials\s*\(
SIGNIN_RENAMED_TO_SIGNINSTEAM|IUser.h|\bSignInSteam\s*\(
SIGNIN_RENAMED_TO_SIGNINGALAXY|IUser.h|\bSignInGalaxy\s*\(
SIGNIN_RENAMED_TO_SIGNINPS4|IUser.h|\bSignInPS4\s*\(
SIGNIN_RENAMED_TO_SIGNINXB1|IUser.h|\bSignInXB1\s*\(
SIGNIN_RENAMED_TO_SIGNINSERVERKEY|IUser.h|\bSignInServerKey\s*\(
HAS_SIGNINTOKEN|IUser.h|\bSignInToken\s*\(
HAS_SIGNINUWP|IUser.h|\bSignInUWP\s*\(
HAS_SIGNINXB1|IUser.h|\bSignInXB1\s*\(
HAS_SIGNOUT|IUser.h|\bSignOut\s*\(
HAS_GAMESERVERGLOBALGOGSERVICESCONNECTIONSTATELISTENER|IUtils.h|\bGameServerGlobalGogServicesConnectionStateListener\b
HAS_IUTILS_AUTHLOST|IUtils.h|\bGOG_SERVICES_CONNECTION_STATE_AUTH_LOST\b
HAS_ITELEMETRY|ITelemetry.h|class\s+ITelemetry
HAS_GAMESERVERTELEMETRY|GalaxyGameServerApi.h|\bGameServerTelemetry\s*\(
HAS_REQUESTUSERDATA_ISPECIFICLISTENER|IUser.h|RequestUserData\([^;]*ISpecificUserDataListener\*
HAS_ICHAT_ROOMLISTENERS|IChat.h|RequestChatRoomWithUser\([^;]*IChatRoomWithUserRetrieveListener\*
HAS_ISTORAGE_FILESHARELISTENERS|IStorage.h|FileShare\([^;]*IFileShareListener\*
HAS_GAMESERVERNETWORKINGLISTENER|INetworking.h|\bGameServerGlobalNetworkingListener\b
HAS_SETUSERDATA_ISPECIFICLISTENER|IUser.h|SetUserData\([^;]*ISpecificUserDataListener\*
HAS_ICONNECTIONLISTENERS|ICustomNetworking.h|OpenConnection\([^;]*IConnectionOpenListener\*
IUSER_SIGNINEPIC|IUser.h|\bSignInEpic\s*\(
ITELEMETRY_1_139_6_UPDATE|ITelemetry.h|\bSendAnonymousTelemetryEvent\s*\(
ITELEMETRY_1_139_7_UPDATE|ITelemetry.h|\bGetVisitID\s*\(
HAS_IGALAXYTHREADFACTORY|GalaxyThread.h|class\s+IGalaxyThreadFactory
HAS_ITELEMETRY_SAMPLING_CLASS|ITelemetry.h|\bSetSamplingClass\s*\(
IGALAXYTHREAD_JOINABLE_DETACH|GalaxyThread.h|\bJoinable\s*\(
IUSER_SIGNINXBLIVE|IUser.h|\bSignInXBLive\s*\(
IUSER_SIGNINLAUNCHER|IUser.h|\bSignInLauncher\s*\(
HAS_GETRICHPRESENCEKEYBYINDEX|IFriends.h|\bGetRichPresenceKeyByIndex\s*\(
IUSER_UWP_TO_XBOX_RENAME|IUser.h|\bSignInXbox\s*\(
HAS_ICLOUDSTORAGE|ICloudStorage.h|class\s+ICloudStorage
HAS_ICLOUDSTORAGE_METADATAIDX_FUNCS|ICloudStorage.h|\bGetFileMetadataKeyByIndex\s*\(
HAS_ICLOUDSTORAGE_PUTFILE_TIMESTAMP|ICloudStorage.h|PutFile\([^;]*uint32_t timeStamp
HAS_IUSER_REFRESHTOKEN|IUser.h|\bGetRefreshToken\s*\(
HAS_ICLOUDSTORAGE_GETFILEHASHBYINDEX|ICloudStorage.h|\bGetFileHashByIndex\s*\(
HAS_ICLOUDSTORAGE_SAVEGAME|ICloudStorage.h|\bOpenSavegame\s*\(
HAS_ICLOUDSTORAGE_HASHING|ICloudStorage.h|\bCalculateHash\s*\(
HAS_INITOPTIONS_GAMESERVICEPLATFORM|InitOptions.h|\bgameServicePlatform\b
HAS_IUSER_REPORTGAMEOWNERSHIP|IUser.h|\bReportGameOwnership\s*\(
HAS_GAMERSERVICEPLATFORM_TOKEN|InitOptions.h|\bgameServicePlatformToken\b
HAS_GAMERSERVICEPLATFORM_TOKEN_LENGTH|InitOptions.h|\bgameServicePlatformTokenLength\b
HAS_ITELEMETRY_GENERATEUUIDSTR|ITelemetry.h|\bGenerateUUIDStr\s*\(
HAS_RED_PREFIX|*|\bREDGalaxy\b
HAS_SHUTDOWNOPTIONS|ShutdownOptions.h|struct\s+ShutdownOptions
HAS_IAPPS_LANGUAGECODE|IApps.h|\bGetCurrentGameLanguageCode\s*\(
HAS_IUSER_AUTHORIZATION_IDTOKEN|IUser.h|\bSignInAuthorizationCode\s*\(
HAS_IAPPS_ISDLCOWNED|IApps.h|\bIsDlcOwned\s*\(
HAS_IUSER_OPENID|IUser.h|\bCreateOpenIDConnection\s*\(
HAS_IUSER_SIGNINGALAXY_TIMEOUT|IUser.h|SignInGalaxy\([^;]*uint32_t timeout
HAS_ISTATS_ACHIEVEMENTSNUMBER|IStats.h|\bGetAchievementsNumber\s*\(
NEAR_FILTER_ENUM|IMatchmaking.h|LOBBY_COMPARISON_NEAR
"""

UNRESOLVED_FEATURES = {"USER_DATA_LISTENERS", "USER_SIGNIN_CROSSPLATFORM"}

def features():
    probes = dict((n, (f, p)) for n, f, p in (line.split("|", 2) for line in PROBES_TEXT.strip().splitlines()))
    print("UNMAPPED", sorted(set(FEATURES) - probes.keys() - UNRESOLVED_FEATURES))
    print("EXTRA_PROBES", sorted(probes.keys() - set(FEATURES)))
    headers = {v: {p.name: strip_comments(text(p)) for p in (DLL / v / "galaxy").glob("*.h")} for v in VERSIONS}
    matrix = []
    for name in FEATURES:
        if name in UNRESOLVED_FEATURES:
            print("UNRESOLVED_SEMANTIC_PROBE", name, "unused in production; name does not uniquely identify a declaration change")
            continue
        if name not in probes:
            continue
        file, pattern = probes[name]
        mismatches = []
        count = 0
        for v in VERSIONS:
            # These concepts only apply to the factory-era declaration domain.
            if name in {"HAS_IERRORMANAGER", "FACTORY_RESET_RENAMED_TO_RESETINSTANCE", "FACTORY_HAS_CALLTYPE"} and not enabled(v)["HAS_IGALAXY"]:
                continue
            s = "\n".join(headers[v].values()) if file == "*" else headers[v].get(file, "")
            actual = bool(re.search(pattern, s, re.S))
            expected = enabled(v)[name]
            count += 1
            matrix.append(f"{v}\t{name}\t{int(expected)}\t{int(actual)}\n")
            if actual != expected:
                mismatches.append(f"{v}({int(expected)}->{int(actual)})")
        print("PROBE", name, "CELLS", count, "MISMATCHES", ",".join(mismatches) or "none")
    print("PROBED_CELLS", len(matrix), "MATRIX_SHA256", hashlib.sha256("".join(matrix).encode()).hexdigest())

def consumers():
    used = defaultdict(list)
    for directory in ["Client", "Client_NoVer", "Shared", "Shared_NoVer", "Server", "InterceptionLogger", "Version", "Tracer"]:
        for p in (ROOT / "Source" / directory).rglob("*"):
            if p.suffix not in {".cxx", ".hxx", ".cmake", ".txt"}:
                continue
            s = strip_comments(text(p))
            for number, line in enumerate(text(p).splitlines(), 1):
                if re.search(r"#\s*(?:ifdef|ifndef).*GALAXY_BUILD_FEATURE|#\s*if.*defined.*GALAXY_BUILD_FEATURE|GALAXY_VERSION\s*\)?\s*(?:[<>=])", line):
                    print("VALUE_USE", p.relative_to(ROOT).as_posix(), number, line.strip())
            for name in set(re.findall(r"GALAXY_BUILD_FEATURE_(\w+)", s)):
                used[name].append(p.relative_to(ROOT).as_posix())
    print("UNDEFINED_FEATURE_READS", {n: ps for n, ps in used.items() if n not in FEATURES})
    print("NO_PRODUCTION_READ", sorted(set(FEATURES) - used.keys()))

def feature_preprocess(s, values):
    """Only evaluate feature guards in the four small export facade sources.

    No includes, general macro expansion or C++ compilation is performed.
    Reject unrecognized conditions rather than silently assuming their values.
    """
    stack = []
    active = True
    output = []
    for line in strip_comments(s).splitlines():
        m = re.match(r"\s*#\s*(ifdef|if|else|endif)\b(.*)", line)
        if not m:
            if active:
                output.append(line)
            continue
        op, expr = m.groups()
        if op == "if" or op == "ifdef":
            condition = re.fullmatch(r"\s*(!?)GALAXY_BUILD_FEATURE_(\w+)\s*", expr)
            if op == "ifdef" and expr.strip() == "_WIN32":
                val = True
            elif condition:
                neg, name = condition.groups()
                val = values[name] != bool(neg)
            else:
                raise ValueError("Unhandled preprocessor condition " + expr)
            stack.append((active, val))
            active = active and val
        elif op == "else":
            parent, val = stack[-1]
            active = parent and not val
        else:
            active, _ = stack.pop()
    if stack:
        raise ValueError("Unclosed preprocessor condition")
    return "\n".join(output)

def exports():
    total = 0
    delta_groups = defaultdict(list)
    calltype_groups = defaultdict(list)
    for v in VERSIONS:
        vals = enabled(v)
        h = {p.name: strip_comments(text(p)) for p in (DLL / v / "galaxy").glob("*.h")}
        api = "\n".join(h.get(f, "") for f in ("GalaxyApi.h", "GalaxyGameServerApi.h", "IListenerRegistrar.h", "Errors.h"))
        declared = {}
        for m in re.finditer(r"GALAXY_DLL_EXPORT\s+([\w\s*]+?)\s+GALAXY_CALLTYPE\s+(\w+)\s*\(([^;{}]*)\)\s*;", api):
            result, name, args = m.groups()
            declared[name] = (" ".join(result.split()), " ".join(args.split()))
        for component in ("Client", "InterceptionLogger"):
            cpp = "\n".join(feature_preprocess(text(ROOT / "Source" / component / f), vals) for f in ("GalaxyApi.cxx", "GalaxyGameServerApi.cxx"))
            implemented = set(re.findall(r"GALAXY_DLL_EXPORT\s+[\w\s*]+?\s+GALAXY_CALLTYPE\s+(\w+)\s*\(", cpp))
            if vals["NEEDS_DLL_IMPL"]:
                delta_groups[(component + "-export-definitions-minus-sdk", tuple(sorted(implemented - declared.keys())))].append(v)
                delta_groups[("sdk-minus-" + component + "-export-definitions", tuple(sorted(declared.keys() - implemented)))].append(v)
        convention = re.search(r"#define\s+GALAXY_CALLTYPE\s+(__\w+)", h["GalaxyExport.h"])
        calltype_groups[convention.group(1) if convention else "none"].append(v)
        for arch in ("x86", "x64"):
            rows = []
            for line in text(DLL / v / arch / "UniverseLAN.def").splitlines():
                m = re.match(r"\s*(\?\S+|load)(?:\s+@(\d+))?\s*$", line)
                if m:
                    rows.append(m.groups())
                elif line.strip() and not line.strip().startswith(("LIBRARY", "EXPORTS", ";")):
                    print("UNPARSED_DEF", v, arch, line)
            total += len(rows)
            ordinals = [o for _, o in rows if o is not None]
            if len({n for n, _ in rows}) != len(rows) or len(set(ordinals)) != len(ordinals):
                print("DUPLICATE_DEF", v, arch)
            symbols = {n for n, _ in rows}
            if vals["NEEDS_DLL_IMPL"]:
                expected = set()
                for name, (result, args) in declared.items():
                    if result == "void" and not args:
                        suffix = "YAXXZ"
                    elif result == "void" and "Options" in args:
                        typ = re.search(r"(\w+Options)", args).group(1)
                        suffix = "YAX" + ("AEBU" if arch == "x64" else "ABU") + typ + "@12@@Z"
                    elif "*" in result and not args:
                        typ = result.replace("const", "").replace("*", "").strip()
                        ptr = ("PE" if arch == "x64" else "P") + ("B" if "const" in result else "A") + "V"
                        suffix = "YA" + ptr + typ + "@12@XZ"
                    else:
                        print("UNHANDLED_DECLARATION", v, arch, name, result, args)
                        continue
                    expected.add("?" + name + "@api@galaxy@@" + suffix)
                delta_groups[("sdk-mangled-missing-in-" + arch + "-def", tuple(sorted(expected - symbols)))].append(v)
                delta_groups[(arch + "-def-extra-vs-sdk", tuple(sorted(symbols - expected - {"load"})))].append(v)
            else:
                # All currently defined factory static methods are cdecl. Verify
                # decoration of every named factory method, not compiler-generated
                # special members or data exports (which have different rules).
                for sym in symbols:
                    if re.match(r"\?(?:GetInstance|GetErrorManager|CreateInstance|Reset|ResetInstance)@GalaxyFactory", sym) and "@@SA" not in sym:
                        print("FACTORY_CALLTYPE_MISMATCH", v, arch, sym)
                expected = set()
                for result, name in re.findall(r"static\s+(IGalaxy\*|IErrorManager\*|void)\s+(?:GALAXY_CALLTYPE\s+)?(\w+)\(\);", h.get("GalaxyFactory.h", "")):
                    suffix = "SAXXZ" if result == "void" else "SA" + ("PEAV" if arch == "x64" else "PAV") + result[:-1] + "@23@XZ"
                    expected.add("?" + name + "@GalaxyFactory@api@galaxy@@" + suffix)
                delta_groups[("factory-declaration-missing-in-" + arch + "-def", tuple(sorted(expected - symbols)))].append(v)
    print("DEF_FILES", len(VERSIONS) * 2, "EXPORT_RECORDS", total)
    print("GALAXY_CALLTYPE_GROUPS", dict(calltype_groups))
    for (kind, diff), vs in delta_groups.items():
        print("EXPORT_COMPARISON", kind, "DIFFERENCE", diff or "none", "VERSIONS", ",".join(vs))

def notebooks():
    # This mode is used only after independent source inspection.
    old_build = text(ROOT / ".ai/review-baseline/BUILD.MD")
    old_wrappers = text(ROOT / ".ai/review-baseline/WRAPPER-COVERAGE.MD")
    old = set(re.findall(r"^- `([^`]+)`", old_build, re.M))
    old.update(re.findall(r"^Source/DLLs/[^\r\n]+", old_wrappers, re.M))
    print("PREVIOUS_INVENTORY", len(old), "CURRENT", len(scope), "MISSING", sorted(set(scope) - old), "EXTRA", sorted(old - set(scope)))
    tree, current = baseline_hashes(scope)
    bad = []
    for p in scope:
        if re.fullmatch(r"Source/DLLs/[^/]+/(?:x(?:86|64)/CMakeLists.txt|(?:Factory|Dll).cxx|compat_list.txt)", p):
            if current[p] not in text(ROOT / (p + ".review.MD")):
                bad.append(p)
    print("WRAPPER_SIDECAR_RECORDED_HASH_MISMATCHES", bad)

def inheritance():
    collisions = defaultdict(list)
    classes = 0
    for v in VERSIONS:
        by_tag = defaultdict(set)
        for p in (DLL / v / "galaxy").glob("*.h"):
            for cls, tag in re.findall(r"class\s+(\w+)\s*:\s*public\s+GalaxyTypeAwareListener<(\w+)>", strip_comments(text(p))):
                by_tag[tag].add(cls)
                classes += 1
        for tag, names in by_tag.items():
            if len(names) > 1:
                collisions[(tag, tuple(sorted(names)))].append(v)
    print("LISTENER_CLASS_DECLARATIONS", classes)
    for (tag, names), vs in collisions.items():
        print("INHERITED_LISTENER_TAG_COLLISION", tag, names, vs)

def numbers():
    bits = "".join(v + "\t" + "".join(str(int(enabled(v)[f])) for f in FEATURES) + "\n" for v in VERSIONS)
    print("FEATURE_VALUE_CELLS", len(FEATURES) * len(VERSIONS), "FEATURE_BITS_SHA256", hashlib.sha256(bits.encode()).hexdigest())
    print("VALUE_VS_TUPLE_11240_DIFFERENCES", [v for v in VERSIONS if (int(v.replace(".", "")) > 11240) != (version(v) > (1, 124, 0))])
    print("ADJACENT_VALUE_ORDER_REVERSALS", [(a, b) for a, b in zip(VERSIONS, VERSIONS[1:]) if int(a.replace(".", "")) > int(b.replace(".", ""))])
    all_versions = set(VERSIONS)
    all_versions.update(x for _, lo, hi in FEATURE_ROWS for x in (lo, hi) if x)
    for v in VERSIONS:
        p = DLL / v / "compat_list.txt"
        if p.is_file():
            for token in text(p).split():
                token = token.rstrip("?")
                if re.fullmatch(r"\d+\.\d+(?:\.\d+)?", token):
                    all_versions.add(token + ".0" if token.count(".") == 1 else token)
    by_number = defaultdict(list)
    for v in sorted(all_versions, key=version):
        by_number[int(v.replace(".", ""))].append(v)
    print("DIRECTORY_BOUNDARY_MANIFEST_VERSION_UNION", len(all_versions), "COLLISIONS", {k: vs for k, vs in by_number.items() if len(vs) > 1})

def resolvers():
    groups = defaultdict(list)
    profiles = 0
    queries = 0
    source = text(ROOT / "Source/InterceptionLogger/UniverseLANInterceptor.cxx")
    for v in VERSIONS:
        s = feature_preprocess(source, enabled(v))
        for gameserver in ([False] if enabled(v)["HAS_IGALAXY"] else [False, True]):
            for arch in ("x86", "x64"):
                profiles += 1
                definition = text(DLL / v / arch / "UniverseLAN.def")
                exports = re.findall(r"^\s*(\?\S+|load)(?:\s+@\d+)?\s*$", definition, re.M)
                for line in s.splitlines():
                    if not re.search(r"\b(?:assign_func|interceptor_make_unique)\(", line):
                        continue
                    names = re.findall(r'"(\?[^"\n]+)"', line)
                    if not names:
                        continue
                    if len(names) == 2 and "gameserver ?" in line:
                        name = names[0 if gameserver else 1]
                    elif len(names) == 1:
                        name = names[0]
                    else:
                        raise ValueError("Unhandled resolver query " + line)
                    queries += 1
                    matches = [symbol for symbol in exports if name in symbol]
                    if len(matches) != 1:
                        groups[("game-server" if gameserver else "client", name, len(matches))].append(v + "/" + arch)
    print("RESOLVER_PROFILES", profiles, "QUERIES", queries)
    for (session, query, matches), versions in groups.items():
        print("RESOLVER_DEF_MISMATCH", session, query, "MATCHES", matches, "VERSIONS", ",".join(versions))

if __name__ == "__main__":
    {"inventory": inventory, "features": features, "consumers": consumers, "exports": exports, "notebooks": notebooks, "inheritance": inheritance, "numbers": numbers, "resolvers": resolvers}[sys.argv[1] if len(sys.argv) > 1 else "inventory"]()
