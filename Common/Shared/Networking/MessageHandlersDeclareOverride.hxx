#define SHARED_NETWORK_IMPLEMENT_CASE_FOR(class_name) \
		virtual void Handle(ENetPeer* peer, const std::shared_ptr<class_name>& data) override

SHARED_NETWORK_IMPLEMENT_ALL_CASES();

#undef SHARED_NETWORK_IMPLEMENT_CASE_FOR