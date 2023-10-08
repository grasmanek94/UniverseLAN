using System;
using System.Security.RightsManagement;

namespace UniverseLanWizard
{
    internal class InstallWizardAction
    {
        public Func<bool> InstallAction { get; private set; }
        public Func<bool> ReverseAction { get; private set; }
        public Func<bool> CleanupAction { get; private set; }
        public string Description { get; private set; }

        public InstallWizardAction(Func<bool> install_action, Func<bool> reverse_operation_action, string description, Func<bool> cleanup_operation_action = null)
        {
            InstallAction = install_action;
            ReverseAction = reverse_operation_action;
            Description = description;
            CleanupAction = cleanup_operation_action;
        }

        override public string ToString() {
            return Description;
        }
    }
}
