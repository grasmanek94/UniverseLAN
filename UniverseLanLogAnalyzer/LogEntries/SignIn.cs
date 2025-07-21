namespace UniverseLanLogAnalyzer.LogEntries
{
    public class SignIn : Base
    {
        public static readonly string MATCH = "universelan::client::UserImpl::SignIn";

        public SignIn(Base original) : base(original)
        {
            IsKeyFrame = true;
        }

        /* Not implemented for now */
    }
}
