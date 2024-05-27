#include <gtest/gtest.h>

#include "state_machine_test.h"
// #include "pedals_system_test.h"
#include "torque_controller_mux_test.h"
#include "drivetrain_system_test.h"
#include "safety_system_test.h"
#include "test_CASE.h"
#include "steering_system_test.h"

int main(int argc, char **argv)
{

    testing::InitGoogleMock(&argc, argv);
	if (RUN_ALL_TESTS())
	;
	// Always return zero-code and allow PlatformIO to parse results
	return 0;
}
