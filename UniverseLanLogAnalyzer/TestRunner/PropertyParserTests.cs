using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.Tests
{
    public class PropertyParserTests
    {
        [Fact]
        public void Parse_UserID_And_Type()
        {
            string[] props = { "userID: 46781906533578385(ID_TYPE_USER)" };
            ulong id = 0;
            GalaxyID.Type type = 0;

            bool result = PropertyParser.Parse(ref props, "userID: {d}({e})", out id, out type);

            Assert.True(result);
            Assert.Equal(46781906533578385UL, id);
            Assert.Equal(GalaxyID.Type.ID_TYPE_USER, type);
        }

        [Fact]
        public void Parse_PersonaStateChange_WithWildcard()
        {
            string[] props = {
                "userID: 46781906533578385(ID_TYPE_USER)",
                "personaStateChange: 0(*)"
            };
            ulong id = 0;
            GalaxyID.Type type = 0;
            PersonaStateChange state = 0;

            bool result = PropertyParser.Parse(ref props, "userID: {d}({e})\npersonaStateChange: {d}(*)", out id, out type, out state);

            Assert.True(result);
            Assert.Equal(0UL, (ulong)state);
        }

        [Fact]
        public void Parse_EnumFlags_FromString()
        {
            string[] props = {
                "userID: 46781906533578385(ID_TYPE_USER)",
                "personaStateChange: 3(PERSONA_CHANGE_NAME|PERSONA_CHANGE_AVATAR)"
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
        }

        [Fact]
        public void Parse_Boolean_And_Enum()
        {
            string[] props = {
                "lobbyType: LOBBY_TYPE_PUBLIC",
                "maxMembers: 250",
                "joinable: true",
                "lobbyTopologyType: LOBBY_TOPOLOGY_TYPE_FCM"
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
        }

        [Fact]
        public void Parse_Hexadecimal_And_Enum()
        {
            string[] props = {
                "listenerType: LOBBY_LEFT",
                "listener: 0xd882870"
            };

            ListenerType type = 0;
            ulong address = 0;

            bool result = PropertyParser.Parse(ref props, "listenerType: {e}\nlistener: {x}", out type, out address);

            Assert.True(result);
            Assert.Equal(0xd882870UL, address);
        }

        [Fact]
        public void Parse_With_Condition_True()
        {
            string[] props = {
                "lobbyID: 58815465033870437(ID_TYPE_LOBBY)",
                "data: 0xf5f410",
                "dataSize: 5",
                "result: true",
                "msg: p1234567890abcdefwoeijd213d12fhgb1239fh9"
            };

            ulong lobbyId;
            GalaxyID.Type lobbyIdType;
            ulong data;
            int dataSize;
            bool resultFlag;
            string msg;
            bool result = PropertyParser.Parse(ref props, "lobbyID: {d}({e})\ndata: {x}\ndataSize: {d}\nresult: {b}\nmsg: {s?result==true}", out lobbyId, out lobbyIdType, out data, out dataSize, out resultFlag, out msg);
            
            Assert.True(result);
            Assert.Equal("p1234567890abcdefwoeijd213d12fhgb1239fh9", msg);
        }

        [Fact]
        public void Parse_With_Condition_False_Should_Skip()
        {
            string[] props = {
                "lobbyID: 58815465033870437(ID_TYPE_LOBBY)",
                "data: 0xf5f410",
                "dataSize: 5",
                "result: false"
            };

            ulong lobbyId;
            GalaxyID.Type lobbyIdType;
            ulong data;
            int dataSize;
            bool resultFlag;
            string msg;

            bool result = PropertyParser.Parse(ref props, "lobbyID: {d}({e})\ndata: {x}\ndataSize: {d}\nresult: {b}\nmsg: {s?result==true}", out lobbyId, out lobbyIdType, out data, out dataSize, out resultFlag, out msg);
            Assert.False(result);
        }
    }

}
