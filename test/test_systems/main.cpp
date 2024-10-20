#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "state_machine_test.h"
#include "pedals_system_test.h"
#include "drivebrain_controller_test.h"
#include "launch_controller_integration_testing.h"
#include "tc_mux_v2_testing.h"
#include "drivetrain_system_test.h"
#include "safety_system_test.h"
#include "test_CASE.h"

// #include "param_system_test.h"
// #include "steering_system_test.h"

int main(int argc, char **argv)
{

    testing::InitGoogleMock(&argc, argv);
	if (RUN_ALL_TESTS())
	;
	// Always return zero-code and allow PlatformIO to parse results
	return 0;
}
