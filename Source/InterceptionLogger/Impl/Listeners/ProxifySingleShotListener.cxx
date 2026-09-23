#include "ProxifySingleShotListener.hxx"

#include <IListenerRegistrar.h>

#include <vector>

ProxifySyncHandler::ProxifySyncHandler() :
	mtx_proxify{}, proxify{}, mtx_proxify_protected{}, proxify_protected{}
{}

void ProxifySyncHandler::add(galaxy::api::IGalaxyListener* proxy, galaxy::api::IGalaxyListener* real) {
	ProxifySyncHandler* _this = ProxifySyncHandler::get();

	lock_t lock{ _this->mtx_proxify };
	_this->proxify.emplace(proxy, real);
}

std::vector<galaxy::api::IGalaxyListener*> ProxifySyncHandler::pop_proxies_from_real(galaxy::api::IGalaxyListener* real) {
	ProxifySyncHandler* _this = ProxifySyncHandler::get();

	lock_t lock{ _this->mtx_proxify };
	std::vector<galaxy::api::IGalaxyListener*> removed_keys{};

	for (auto it = _this->proxify.begin(); it != _this->proxify.end();)
	{
		if (it->second == real)
		{
			removed_keys.push_back(it->first);
			it = _this->proxify.erase(it);
		}
		else
		{
			++it;
		}
	}

	return removed_keys;
}

galaxy::api::IGalaxyListener* ProxifySyncHandler::pop_real_from_proxy(galaxy::api::IGalaxyListener* proxy) {
	ProxifySyncHandler* _this = ProxifySyncHandler::get();

	lock_t lock{ _this->mtx_proxify };
	auto it = _this->proxify.find(proxy);
	if (it == _this->proxify.end()) {
		return nullptr;
	}

	galaxy::api::IGalaxyListener* ret = it->second;
	_this->proxify.erase(it);

	return ret;
}

void ProxifySyncHandler::delete_protection_enable(galaxy::api::IGalaxyListener* proxy) {
	ProxifySyncHandler* _this = ProxifySyncHandler::get();

	lock_t lock{ _this->mtx_proxify_protected };
	_this->proxify_protected.insert(proxy);
}

bool ProxifySyncHandler::is_delete_protection_enabled(galaxy::api::IGalaxyListener* proxy) {
	ProxifySyncHandler* _this = ProxifySyncHandler::get();

	lock_t lock{ _this->mtx_proxify_protected };
	auto it = _this->proxify_protected.find(proxy);
	if (it == _this->proxify_protected.end()) {
		return false;
	}

	return true;
}

bool ProxifySyncHandler::delete_if_not_protected(galaxy::api::IGalaxyListener* proxy) {
	ProxifySyncHandler* _this = ProxifySyncHandler::get();

	lock_t lock{ _this->mtx_proxify_protected };
	auto it = _this->proxify_protected.find(proxy);
	if (it == _this->proxify_protected.end()) {
		delete proxy;
		return true;
	}

	return false;
}

void ProxifySyncHandler::delete_protection_disable(galaxy::api::IGalaxyListener* proxy) {
	ProxifySyncHandler* _this = ProxifySyncHandler::get();

	lock_t lock{ _this->mtx_proxify_protected };
	_this->proxify_protected.erase(proxy);
}