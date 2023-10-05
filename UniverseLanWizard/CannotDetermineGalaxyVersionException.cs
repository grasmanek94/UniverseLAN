using System;

namespace UniverseLanWizard
{
    internal class CannotDetermineGalaxyVersionException: SystemException
    {
        public CannotDetermineGalaxyVersionException() { }
        public CannotDetermineGalaxyVersionException(string message) : base(message) { }
    }
}
