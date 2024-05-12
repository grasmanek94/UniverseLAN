#include "ProxifySingleShotListener.hxx"

#include <IListenerRegistrar.h>

ProxifySyncHandler::ProxifySyncHandler() :
	mtx_proxify{}, proxify{}
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
