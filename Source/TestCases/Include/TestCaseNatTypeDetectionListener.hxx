#pragma once

#if GALAXY_BUILD_FEATURE_HAS_NAT_FUNCTIONALITY

#include "TestCaseClientDetails.hxx"

class NatTypeDetectionListenerImplGlobal : public galaxy::api::GlobalNatTypeDetectionListener
{
public:
	using on_nat_type_detection_success_func_t = std::function<void(NatType)>;
	using on_nat_type_detection_failure_func_t = std::function<void()>;

private:
	on_nat_type_detection_success_func_t on_nat_type_detection_success;
	on_nat_type_detection_failure_func_t on_nat_type_detection_failure;

public:
	NatTypeDetectionListenerImplGlobal(
		on_nat_type_detection_success_func_t on_nat_type_detection_success = nullptr,
		on_nat_type_detection_failure_func_t on_nat_type_detection_failure = nullptr) :
		on_nat_type_detection_success{ on_nat_type_detection_success },
		on_nat_type_detection_failure{ on_nat_type_detection_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~NatTypeDetectionListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnNatTypeDetectionSuccess(NatType natType) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"natType: {}",
			magic_enum::enum_name(natType)
		).c_str());


		if (on_nat_type_detection_success != nullptr) {
			on_nat_type_detection_success(natType);
		}
	}

	virtual void OnNatTypeDetectionFailure() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_nat_type_detection_failure != nullptr) {
			on_nat_type_detection_failure();
		}
	}
};

class NatTypeDetectionListenerImplLocal : public galaxy::api::INatTypeDetectionListener
{
public:
	using on_nat_type_detection_success_func_t = std::function<void(NatType)>;
	using on_nat_type_detection_failure_func_t = std::function<void()>;

private:
	on_nat_type_detection_success_func_t on_nat_type_detection_success;
	on_nat_type_detection_failure_func_t on_nat_type_detection_failure;

public:
	NatTypeDetectionListenerImplLocal(
		on_nat_type_detection_success_func_t on_nat_type_detection_success = nullptr,
		on_nat_type_detection_failure_func_t on_nat_type_detection_failure = nullptr) :
		on_nat_type_detection_success{ on_nat_type_detection_success },
		on_nat_type_detection_failure{ on_nat_type_detection_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~NatTypeDetectionListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnNatTypeDetectionSuccess(NatType natType) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"natType: {}",
			magic_enum::enum_name(natType)
		).c_str());


		if (on_nat_type_detection_success != nullptr) {
			on_nat_type_detection_success(natType);
		}
	}

	virtual void OnNatTypeDetectionFailure() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_nat_type_detection_failure != nullptr) {
			on_nat_type_detection_failure();
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerNatTypeDetectionListenerImplGlobal : public galaxy::api::GameServerGlobalNatTypeDetectionListener
{
public:
	using on_nat_type_detection_success_func_t = std::function<void(NatType)>;
	using on_nat_type_detection_failure_func_t = std::function<void()>;

private:
	on_nat_type_detection_success_func_t on_nat_type_detection_success;
	on_nat_type_detection_failure_func_t on_nat_type_detection_failure;

public:
	GameServerNatTypeDetectionListenerImplGlobal(
		on_nat_type_detection_success_func_t on_nat_type_detection_success = nullptr,
		on_nat_type_detection_failure_func_t on_nat_type_detection_failure = nullptr) :
		on_nat_type_detection_success{ on_nat_type_detection_success },
		on_nat_type_detection_failure{ on_nat_type_detection_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerNatTypeDetectionListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnNatTypeDetectionSuccess(NatType natType) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"natType: {}",
			magic_enum::enum_name(natType)
		).c_str());


		if (on_nat_type_detection_success != nullptr) {
			on_nat_type_detection_success(natType);
		}
	}

	virtual void OnNatTypeDetectionFailure() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_nat_type_detection_failure != nullptr) {
			on_nat_type_detection_failure();
		}
	}
};

#endif
#endif
