#include "PyThreadState.h"
#include "PyFrameObject.h"

#include "fieldAsPyObject.h"
#include "ExtHelpers.h"

#include <engextcpp.hpp>

#include <memory>
using namespace std;

namespace PyExt::Remote {

	PyThreadState::PyThreadState(Offset objectAddress)
		: RemoteType(objectAddress, "PyThreadState")
	{
	}


	PyThreadState::~PyThreadState()
	{
	}


	auto PyThreadState::next() const -> std::unique_ptr<PyThreadState>
	{
		auto nextPtr = remoteType().Field("next").GetPtr();
		if (nextPtr == 0)
			return { };

		return make_unique<PyThreadState>(nextPtr);
	}


	auto PyThreadState::frame() const -> std::unique_ptr<PyFrameObject>
	{
		return utils::fieldAsPyObject<PyFrameObject>(remoteType(), "frame");
	}


	auto PyThreadState::recursion_depth() const -> long
	{
		auto field = remoteType().Field("recursion_depth");
		return utils::readIntegral<long>(field);
	}


	auto PyThreadState::tracing() const -> long
	{
		auto field = remoteType().Field("tracing");
		return utils::readIntegral<long>(field);
	}


	auto PyThreadState::use_tracing() const -> long
	{
		auto field = remoteType().Field("use_tracing");
		return utils::readIntegral<long>(field);
	}


	auto PyThreadState::thread_id() const -> long
	{
		auto field = remoteType().Field("thread_id");
		return utils::readIntegral<long>(field);
	}

}