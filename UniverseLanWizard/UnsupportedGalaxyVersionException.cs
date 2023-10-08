using System;

namespace UniverseLanWizard
{
    internal class UnsupportedGalaxyVersionException: SystemException
    {
        public UnsupportedGalaxyVersionException() { }
        public UnsupportedGalaxyVersionException(string message) : base(message) { }
    }
}
