namespace UniverseLanLogAnalyzer.Galaxy.Types
{
    [Flags]
    public enum AvatarType
    {
        AVATAR_TYPE_NONE = 0x0000, ///< No avatar type specified.
        AVATAR_TYPE_SMALL = 0x0001, ///< Avatar resolution size: 32x32.
        AVATAR_TYPE_MEDIUM = 0x0002, ///< Avatar resolution size: 64x64.
        AVATAR_TYPE_LARGE = 0x0004 ///< Avatar resolution size: 184x184.
    };
}