#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "debounce.hpp"

// Test the initial state of the Debounce object
void testInitialState() {
    Debounce debounce(EN_DEB_MODE_COUNT, 100, 10, nullptr);
    ASSERT_EQUAL(EN_DEB_STATE_NONE, debounce.get_state());
}

// Test trigger in count mode
void testTriggerCountMode() {
    Debounce debounce(EN_DEB_MODE_COUNT, 100, 3, nullptr);
    ASSERT_EQUAL(EN_DEB_STATE_START, debounce.trigger());
    ASSERT_EQUAL(EN_DEB_STATE_NONE, debounce.get_state());
    ASSERT_EQUAL(EN_DEB_STATE_NONE, debounce.trigger());
    ASSERT_EQUAL(EN_DEB_STATE_NONE, debounce.trigger());
    ASSERT_EQUAL(EN_DEB_STATE_READY, debounce.trigger());
}

// Test trigger in time mode
void testTriggerTimeMode() {
    Debounce debounce(EN_DEB_MODE_TIME, 100, 0, nullptr);
    ASSERT_EQUAL(EN_DEB_STATE_START, debounce.trigger());
    ASSERT_EQUAL(EN_DEB_STATE_NONE, debounce.get_state());
    // Simulate passing time
    // Assuming we have a function to provide time
    // debounce.u16_time_idx_ms = 50;
    ASSERT_EQUAL(EN_DEB_STATE_NONE, debounce.trigger());
    // debounce.u16_time_idx_ms = 100;
    ASSERT_EQUAL(EN_DEB_STATE_READY, debounce.trigger());
}

// Run all tests
void runAllTests() {
    cute::suite s;
    s.push_back(CUTE(testInitialState));
    s.push_back(CUTE(testTriggerCountMode));
    s.push_back(CUTE(testTriggerTimeMode));
    cute::ide_listener<> lis{};
    cute::makeRunner(lis)(s, "Debounce Test");
}

int main() {
    runAllTests();
    return 0;
}
