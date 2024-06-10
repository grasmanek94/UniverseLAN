#include "ProxifySingleShotListener.hxx"

#include <IListenerRegistrar.h>

ProxifySyncHandler::ProxifySyncHandler() :
	mtx_proxify{}, proxify{}, mtx_proxify_protected{}, proxify_protected{}
{}

void ProxifySyncHandler::add(galaxy::api::IGalaxyListener* real, galaxy::api::IGalaxyListener* proxy) {
	ProxifySyncHandler* _this = ProxifySyncHandler::get();

	lock_t lock{ _this->mtx_proxify };
	_this->proxify.emplace(real, proxy);
}

galaxy::api::IGalaxyListener* ProxifySyncHandler::pop(galaxy::api::IGalaxyListener* real) {
	ProxifySyncHandler* _this = ProxifySyncHandler::get();

	lock_t lock{ _this->mtx_proxify };
	auto it = _this->proxify.find(real);
	if (it == _this->proxify.end()) {
		return nullptr;
	}

	galaxy::api::IGalaxyListener* ret = it->second;
	_this->proxify.erase(it);

	return ret;
}

void ProxifySyncHandler::delete_protection_enable(galaxy::api::IGalaxyListener* real) {
	ProxifySyncHandler* _this = ProxifySyncHandler::get();

	lock_t lock{ _this->mtx_proxify_protected };
	_this->proxify_protected.insert(real);
}

bool ProxifySyncHandler::is_delete_protection_enabled(galaxy::api::IGalaxyListener* real) {
	ProxifySyncHandler* _this = ProxifySyncHandler::get();

	lock_t lock{ _this->mtx_proxify_protected };
	auto it = _this->proxify_protected.find(real);
	if (it == _this->proxify_protected.end()) {
		return false;
	}

	return true;
}

void ProxifySyncHandler::delete_protection_disable(galaxy::api::IGalaxyListener* real) {
	ProxifySyncHandler* _this = ProxifySyncHandler::get();

	lock_t lock{ _this->mtx_proxify_protected };
	_this->proxify_protected.erase(real);
}