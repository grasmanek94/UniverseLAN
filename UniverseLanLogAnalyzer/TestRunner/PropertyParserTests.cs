using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.Tests
{
    public class PropertyParserTests
    {
        [Fact]
        public void Parse_UserID_And_Type()
        {
            List<string> props = new List<string> { 
                "aaa: bbb(ccc)",
                "userID: 46781906533578385(ID_TYPE_USER)",
                "ddd: eee(fff)"
            };

            ulong id = 0;
            GalaxyID.Type type = 0;

            bool result = PropertyParser.Parse(ref props, "userID: {d}({e})", out id, out type);

            Assert.True(result);
            Assert.Equal(46781906533578385UL, id);
            Assert.Equal(GalaxyID.Type.ID_TYPE_USER, type);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_UserID_And_Type_GID()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "userID: 46781906533578385(ID_TYPE_USER)",
                "ddd: eee(fff)"
            };

            GalaxyID galaxy_id;

            bool result = PropertyParser.Parse(ref props, "userID: {gid}", out galaxy_id);

            Assert.True(result);
            Assert.Equal(46781906533578385UL, galaxy_id.GetID());
            Assert.Equal(GalaxyID.Type.ID_TYPE_USER, galaxy_id.GetIDType());

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_PersonaStateChange_WithWildcard()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "userID: 46781906533578385(ID_TYPE_USER)",
                "personaStateChange: 0()",
                "ddd: eee(fff)"
            };
            ulong id = 0;
            GalaxyID.Type type = 0;
            PersonaStateChange state = 0;

            bool result = PropertyParser.Parse(ref props, "userID: {d}({e})\npersonaStateChange: {d}({*})", out id, out type, out state);

            Assert.True(result);
            Assert.Equal(0UL, (ulong)state);
            Assert.Equal(GalaxyID.Type.ID_TYPE_USER, type);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_EnumFlags_FromString()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "userID: 46781906533578385(ID_TYPE_USER)",
                "personaStateChange: 3(PERSONA_CHANGE_NAME|PERSONA_CHANGE_AVATAR)",
                "ddd: eee(fff)"
            };

            ulong id = 0;
            GalaxyID.Type type = 0;
            PersonaStateChange stateNum = 0;
            PersonaStateChange stateFlags = 0;

            bool result = PropertyParser.Parse(ref props, "userID: {d}({e})\npersonaStateChange: {d}({ef})", out id, out type, out stateNum, out stateFlags);

            Assert.True(result);
            Assert.Equal(3UL, (ulong)stateNum);
            Assert.True(stateFlags.HasFlag(PersonaStateChange.PERSONA_CHANGE_NAME));
            Assert.True(stateFlags.HasFlag(PersonaStateChange.PERSONA_CHANGE_AVATAR));
            Assert.Equal(GalaxyID.Type.ID_TYPE_USER, type);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_Boolean_And_Enum()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "lobbyType: LOBBY_TYPE_PUBLIC",
                "maxMembers: 250",
                "joinable: true",
                "lobbyTopologyType: LOBBY_TOPOLOGY_TYPE_FCM",
                "ddd: eee(fff)"
            };

            LobbyType lobbyType = 0;
            int maxMembers = 0;
            bool joinable = false;
            LobbyTopologyType topology = 0;

            bool result = PropertyParser.Parse(ref props, "lobbyType: {e}\nmaxMembers: {d}\njoinable: {b}\nlobbyTopologyType: {e}",
                out lobbyType, out maxMembers, out joinable, out topology);

            Assert.True(result);
            Assert.Equal(LobbyType.LOBBY_TYPE_PUBLIC, lobbyType);
            Assert.Equal(250, maxMembers);
            Assert.True(joinable);
            Assert.Equal(LobbyTopologyType.LOBBY_TOPOLOGY_TYPE_FCM, topology);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_Hexadecimal_And_Enum()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "listenerType: LOBBY_LEFT",
                "listener: 0xd882870",
                "ddd: eee(fff)"
            };

            ListenerType type = 0;
            ulong address = 0;

            bool result = PropertyParser.Parse(ref props, "listenerType: {e}\nlistener: {x}", out type, out address);

            Assert.True(result);
            Assert.Equal(0xd882870UL, address);
            Assert.Equal(ListenerType.LOBBY_LEFT, type);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_With_Condition_True()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "lobbyID: 58815465033870437(ID_TYPE_LOBBY)",
                "data: 0xf5f410",
                "dataSize: 5",
                "result: true",
                "msg: p1234567890abcdefwoeijd213d12fhgb1239fh9",
                "something_else: 1337",
                "ddd: eee(fff)"
            };

            ulong lobbyId;
            GalaxyID.Type lobbyIdType;
            ulong data;
            int dataSize;
            bool resultFlag;
            Optional<string> msg;
            int somethingElse;

            bool result = PropertyParser.Parse(ref props, "lobbyID: {d}({e})\ndata: {x}\ndataSize: {d}\nresult: {b}\nmsg: {s}\nsomething_else: {d}", out lobbyId, out lobbyIdType, out data, out dataSize, out resultFlag, out msg, out somethingElse);
            
            Assert.True(result);
            Assert.Equal(58815465033870437UL, lobbyId);
            Assert.Equal(GalaxyID.Type.ID_TYPE_LOBBY, lobbyIdType);
            Assert.Equal(0xf5f410UL, data);
            Assert.Equal(5, dataSize);
            Assert.True(resultFlag);
            Assert.True(msg.Available);
            Assert.Equal("p1234567890abcdefwoeijd213d12fhgb1239fh9", msg.Value);
            Assert.Equal(1337, somethingElse);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_With_Condition_False_Should_Skip()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "lobbyID: 58815465033870437(ID_TYPE_LOBBY)",
                "data: 0xf5f410",
                "dataSize: 5",
                "result: false",
                "something_else: 1337",
                "ddd: eee(fff)"
            };

            ulong lobbyId;
            GalaxyID.Type lobbyIdType;
            ulong data;
            int dataSize;
            bool resultFlag;
            Optional<string> msg;
            int somethingElse;

            bool result = PropertyParser.Parse(ref props, "lobbyID: {d}({e})\ndata: {x}\ndataSize: {d}\nresult: {b}\nmsg: {s}\nsomething_else: {d}", out lobbyId, out lobbyIdType, out data, out dataSize, out resultFlag, out msg, out somethingElse);
            
            Assert.True(result);
            Assert.Equal(58815465033870437UL, lobbyId);
            Assert.Equal(GalaxyID.Type.ID_TYPE_LOBBY, lobbyIdType);
            Assert.Equal(0xf5f410UL, data);
            Assert.Equal(5, dataSize);
            Assert.False(resultFlag);
            Assert.False(msg.Available);
            Assert.Equal(1337, somethingElse);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_AllFieldsPresent_ShouldSucceed()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "lobbyType: LOBBY_TYPE_PUBLIC",
                "maxMembers: 255",
                "joinable: true",
                "lobbyTopologyType: LOBBY_TOPOLOGY_TYPE_FCM",
                "lobbyCreatedListener: 0xabcdef0099",
                "lobbyEnteredListener: 0x1234567899",
                "something_else: 1337",
                "ddd: eee(fff)"
            };

            LobbyType lobbyType;
            int maxMembers;
            Optional<bool> joinable;
            Optional<LobbyTopologyType> lobbyTopologyType;
            Optional<ulong> createdListenerAddress;
            Optional<ulong> enteredListenerAddress;
            int somethingElse;

            bool result = PropertyParser.Parse(ref props,
                "lobbyType: {e}\nmaxMembers: {d}\njoinable: {b}\nlobbyTopologyType: {e}\nlobbyCreatedListener: {x}\nlobbyEnteredListener: {x}\nsomething_else: {d}",
                out lobbyType, out maxMembers, out joinable, out lobbyTopologyType, out createdListenerAddress, out enteredListenerAddress, out somethingElse);

            Assert.True(result);
            Assert.True(joinable.Available);
            Assert.True(joinable.Value);
            Assert.True(lobbyTopologyType.Available);
            Assert.Equal(LobbyTopologyType.LOBBY_TOPOLOGY_TYPE_FCM, lobbyTopologyType.Value);
            Assert.True(createdListenerAddress.Available);
            Assert.Equal(0xabcdef0099UL, createdListenerAddress.Value);
            Assert.True(enteredListenerAddress.Available);
            Assert.Equal(0x1234567899UL, enteredListenerAddress.Value);
            Assert.Equal(1337, somethingElse);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_MissingJoinableAndTopology_ShouldSucceed()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "lobbyType: LOBBY_TYPE_PUBLIC",
                "maxMembers: 255",
                "lobbyCreatedListener: 0xabcdef0099",
                "lobbyEnteredListener: 0x1234567899",
                "something_else: 1337",
                "ddd: eee(fff)"
            };

            LobbyType lobbyType;
            int maxMembers;
            Optional<bool> joinable;
            Optional<LobbyTopologyType> lobbyTopologyType;
            Optional<ulong> createdListenerAddress;
            Optional<ulong> enteredListenerAddress;
            int somethingElse;

            bool result = PropertyParser.Parse(ref props,
                "lobbyType: {e}\nmaxMembers: {d}\njoinable: {b}\nlobbyTopologyType: {e}\nlobbyCreatedListener: {x}\nlobbyEnteredListener: {x}\nsomething_else: {d}",
                out lobbyType, out maxMembers, out joinable, out lobbyTopologyType, out createdListenerAddress, out enteredListenerAddress, out somethingElse);

            Assert.True(result);
            Assert.False(joinable.Available);
            Assert.False(lobbyTopologyType.Available);
            Assert.True(createdListenerAddress.Available);
            Assert.True(enteredListenerAddress.Available);
            Assert.Equal(1337, somethingElse);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_MissingListeners_ShouldSucceed()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "lobbyType: LOBBY_TYPE_PUBLIC",
                "maxMembers: 255",
                "joinable: true",
                "lobbyTopologyType: LOBBY_TOPOLOGY_TYPE_FCM",
                "something_else: 1337",
                "ddd: eee(fff)"
            };

            LobbyType lobbyType;
            int maxMembers;
            Optional<bool> joinable;
            Optional<LobbyTopologyType> lobbyTopologyType;
            Optional<ulong> createdListenerAddress;
            Optional<ulong> enteredListenerAddress;
            int somethingElse;

            bool result = PropertyParser.Parse(ref props,
                "lobbyType: {e}\nmaxMembers: {d}\njoinable: {b}\nlobbyTopologyType: {e}\nlobbyCreatedListener: {x}\nlobbyEnteredListener: {x}\nsomething_else: {d}",
                out lobbyType, out maxMembers, out joinable, out lobbyTopologyType, out createdListenerAddress, out enteredListenerAddress, out somethingElse);

            Assert.True(result);
            Assert.True(joinable.Available);
            Assert.True(joinable.Value);
            Assert.True(lobbyTopologyType.Available);
            Assert.Equal(LobbyTopologyType.LOBBY_TOPOLOGY_TYPE_FCM, lobbyTopologyType.Value);
            Assert.False(createdListenerAddress.Available);
            Assert.False(enteredListenerAddress.Available);
            Assert.Equal(1337, somethingElse);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_OnlyRequiredFields_ShouldSucceed()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "lobbyType: LOBBY_TYPE_PUBLIC",
                "maxMembers: 255",
                "something_else: 1337",
                "ddd: eee(fff)"
            };

            LobbyType lobbyType;
            int maxMembers;
            Optional<bool> joinable;
            Optional<LobbyTopologyType> lobbyTopologyType;
            Optional<ulong> createdListenerAddress;
            Optional<ulong> enteredListenerAddress;
            int somethingElse;

            bool result = PropertyParser.Parse(ref props,
                "lobbyType: {e}\nmaxMembers: {d}\njoinable: {b}\nlobbyTopologyType: {e}\nlobbyCreatedListener: {x}\nlobbyEnteredListener: {x}\nsomething_else: {d}",
                out lobbyType, out maxMembers, out joinable, out lobbyTopologyType, out createdListenerAddress, out enteredListenerAddress, out somethingElse);

            Assert.True(result);
            Assert.False(joinable.Available);
            Assert.False(lobbyTopologyType.Available);
            Assert.False(createdListenerAddress.Available);
            Assert.False(enteredListenerAddress.Available);
            Assert.Equal(1337, somethingElse);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_EnumFlags_FromString_WithIgnore1()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "personaStateChange: 3(PERSONA_CHANGE_NAME|PERSONA_CHANGE_AVATAR)",
                "ddd: eee(fff)"
            };

            PersonaStateChange stateFlags = 0;

            bool result = PropertyParser.Parse(ref props, "personaStateChange: {*}({ef})", out stateFlags);

            Assert.True(result);
            Assert.True(stateFlags.HasFlag(PersonaStateChange.PERSONA_CHANGE_NAME));
            Assert.True(stateFlags.HasFlag(PersonaStateChange.PERSONA_CHANGE_AVATAR));
         
            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_EnumFlags_FromString_WithIgnore2()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "personaStateChange: 3(PERSONA_CHANGE_NAME|PERSONA_CHANGE_AVATAR)",
                "ddd: eee(fff)"
            };

            PersonaStateChange stateFlags = 0;

            bool result = PropertyParser.Parse(ref props, "personaStateChange: {d}({*})", out stateFlags);

            Assert.True(result);
            Assert.True(stateFlags.HasFlag(PersonaStateChange.PERSONA_CHANGE_NAME));
            Assert.True(stateFlags.HasFlag(PersonaStateChange.PERSONA_CHANGE_AVATAR));

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_EnumFlags_FromString_WithIgnore3()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "personaStateChange: 0()",
                "ddd: eee(fff)"
            };

            PersonaStateChange stateFlags = PersonaStateChange.PERSONA_CHANGE_NAME;

            bool result = PropertyParser.Parse(ref props, "personaStateChange: {d}({*})", out stateFlags);

            Assert.True(result);
            Assert.Equal(PersonaStateChange.PERSONA_CHANGE_NONE, stateFlags);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }

        [Fact]
        public void Parse_EnumFlags_FromString_WithIgnore4()
        {
            List<string> props = new List<string> {
                "aaa: bbb(ccc)",
                "personaStateChange: 0()",
                "ddd: eee(fff)"
            };

            PersonaStateChange stateFlags = PersonaStateChange.PERSONA_CHANGE_NAME;

            bool result = PropertyParser.Parse(ref props, "personaStateChange: {*}({ef})", out stateFlags);

            Assert.True(result);
            Assert.Equal(PersonaStateChange.PERSONA_CHANGE_NONE, stateFlags);

            Assert.Equal("aaa: bbb(ccc)", props.First());
            Assert.Equal("ddd: eee(fff)", props.Last());
            Assert.Equal(2, props.Count());
        }
    }
}
