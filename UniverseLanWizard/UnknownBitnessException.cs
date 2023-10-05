using System;

namespace UniverseLanWizard
{
    internal class UnknownBitnessException: SystemException
    {
        public UnknownBitnessException() { }
        public UnknownBitnessException(string message) : base(message) { }
    }
}
