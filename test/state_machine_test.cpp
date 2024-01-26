#include <unity.h>
#include "MCUStateMachine.h"



void setUp(void)
{
  // set stuff up here

}

void tearDown(void)
{
  // clean stuff up here
//   STR_TO_TEST = "";
}

void test_string_concat(void)
{
//   std::string hello = "Hello, ";
//   std::string world = "world!";
//   TEST_ASSERT_EQUAL_STRING(STR_TO_TEST.c_str(), (hello + world).c_str());
}

int main(){
//   delay(2000); // service delay
  UNITY_BEGIN();

  RUN_TEST(test_string_concat);
  

  UNITY_END(); // stop unit testing
}

