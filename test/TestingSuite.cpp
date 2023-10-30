#include <gtest/gtest.h>
#include "../main.h"
#include "../Graph.h"
#include "../Christofides.h"
using namespace std;
#define TEST_INPUT_DIR "../../test/testInputs/"


/*
Kinds of assertions: 

ASSERT_* = Use this when there is no point in continuing execution of program once the assert fails. Program will terminate. 
EXPECT_* = Use this when the program should try to keep going eventhough the expect fails. Program will continue. 
*/


/*
This class is called a test fixture. We can use it whenever we need to perform several tests that 
use the same set up of resources. Eg: setting up a really big graph and such. The name of this particular
test fixture is called SetUpBigGraph. We can have several test fixtures in this file. 
The function SetUp() is called before running every single test that uses this test fixture, 
and the TearDown() is called after executing every single test that uses this test fixture. Inbetween tests, the test
fixture is deleted completely, so any changes in one will not affect the other. 

To write a test that utilizes a test fixture? 
Begin the test with the macro: TEST_F, instead of TEST. And the group for the test is the name of the test fixture.
In this particular case: It is SetUpBigGraph. 
*/
// class SetUpBigGraph : public ::testing::Test {
// protected:
//     Graph g;
//     // Set up code (optional)
//     void SetUp() override {
//         // Initialize common resources or state
//         string filename = string(TEST_INPUT_DIR) + "setUpBigGraph.txt";
//         g = Graph(filename);
//     }

//     // Tear down code (optional)
//     void TearDown() override {
//         // Release any resources or clean up
//     }
// };

/* 
A test that utilizes test fixture SetUpBigGraph. 
*/

// TEST_F(SetUpBigGraph, testFixture1){
//     //ASSERT: very big graph etc.. 
// };



/*ARGS:

First Argument - name of the group. Eg: Maybe all of our tests testing for incorrect inputs to Christofides could 
fall under the same group called "ChristofidesIncorrectInpt" ?. For same class, it's easier to group different kinds of 
tests. 
Second Argument - the test’s name within the test suite.

OBS - Don't use underscores for the names of tests.

*/
