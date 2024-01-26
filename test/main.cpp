#include "state_machine_test.h"
#include "pedals_system_test.h"
void setUp(void)
{
    // declare a component obj
    // possibly make temp class that is a freind class of PedalsSystem to access private members
    // possibly modify the
}

void tearDown(void)
{
}

int main()
{
    //   delay(2000); // service delay
    UNITY_BEGIN();

    RUN_TEST(test_pedal_is_active);
    RUN_TEST(test_state_machine_init_tick);
    

    UNITY_END(); // stop unit testing
}
