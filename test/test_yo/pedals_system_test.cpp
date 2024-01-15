/*
basic test cases for the pedals component class 
version 1.0
rough draft
author: Lucas Plant
*/
#include <unity.h>
#include <string>
#include <Pedals.h>

/*
ToDo:
    edit pedals system file to accommodate friend wrapper
    methods to test:
        constructor
        evaluate pedals
        linearize_accel_pedal_values_
        evaluate pedal_implausibilities_
        evaluate_brake_and_accel_pressed_
        pedal_is_active


*/

class PedalsFriend {
    //friend class to allow access to private fields of Pedals system
    public:
    static std::tuple<int, int> access_linearize_accel_pedal_values_(PedalsComponent& pedals_component, int accel1, int accel2)
    {
        return pedals_component.linearize_accel_pedal_values_(accel1, accel2)
    }

    static bool access_evaluate_pedal_implausibilities_(PedalsComponent& pedals_component, int sense_1, int sense_2, const PedalsParams &params, float max_percent_differnce)
    {
        return pedals_component.evaluate_pedal_implausibilities_(sense_1, sense_2, params, max_percent_differnce)
    }

    static bool access_evaluate_brake_and_accel_pressed_(PedalsComponent& pedals_component, const PedalsDriverInterface &data)
    {
        return pedals_component.evaluate_brake_and_accel_pressed_(data)
    }

    static bool access_pedal_is_active_(PedalsComponent& pedalsComponent pedals_component, int sense1, int sense_2, const PedalsParams& pedalParams, float percent_threshold)
    {
        return pedal_is_active(PedalsComponent pedalsComponent pedals_component, int sense1, int sense_2, const PedalsParams& pedalParams, percent_threshold)
    }

    static PedalsParams access_accel_pedals_params(PedalsComponent& pedals_component)
    {
        return pedals_component.accelParams_
    }

    static PedalsParams access_brake_pedals_params(PedalsComponent& pedals_component)
    {
        return pedals_component.brakeParams_
    }
}

void setUp(void)
{
    //declare a component obj
    //possibly make temp class that is a freind class of PedalsComponent to access private members
    //possibly modify the 

    PedalsComponent pedals_component;

}

void tearDown(void)
{

}

struct PedalIsActiveTestCase {
    //defines input and output params
    
    //input params
    int sense1;
    int sense2;
    //for now the pedalsparams will be kept constant however this can become a part of the tests as well
    float percent_threshold;

    //expected output
    bool expect_active;
}
void test_pedal_is_active_(void)
{
    //define the test cases in a vector
    std::vector<PedalIsActiveTestCase> test_cases = {
        {1, 1, 1, true}
        //add more test cases later on
    };

    PedalsParams params_for_test = {1, 1, 10, 10, 5, 5, 7, 7}

    for (const auto& test_case : test_cases) {
        out = pedal_activePedalsFriend::access_pedal_is_active_(pedals_component, test_case.sense1, test_case.sense2, params_for_test, test_case.percent_threshold);
        TEST_ASSERT_EQUAL(test_case.expect_active, out)
    }
}

/*
void test_evaluate_brake_and_accel_pressed(void)
{
    PedalsDriverInterface data = {}
    PedalsFriend(pedal_component, data)
}
*/



int main() {

    UNITY_BEGIN();

    //tests go here


    UNITY_END();
}