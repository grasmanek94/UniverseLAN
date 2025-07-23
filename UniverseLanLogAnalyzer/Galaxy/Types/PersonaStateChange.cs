namespace UniverseLanLogAnalyzer.Galaxy.Types
{
    [Flags]
    public enum PersonaStateChange
    {
        PERSONA_CHANGE_NONE = 0x0000, ///< No information has changed.
        PERSONA_CHANGE_NAME = 0x0001, ///< Persona name has changed.
        PERSONA_CHANGE_AVATAR = 0x0002, ///< Avatar, i.e. its URL, has changed.
        PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_SMALL = 0x0004, ///< Small avatar image has been downloaded.
        PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_MEDIUM = 0x0008, ///< Medium avatar image has been downloaded.
        PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_LARGE = 0x0010, ///< Large avatar image has been downloaded.
        PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_ANY = PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_SMALL | PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_MEDIUM | PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_LARGE ///< Any avatar images have been downloaded.
    };
}