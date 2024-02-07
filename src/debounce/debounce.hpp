#include <cstddef>
#include <cstdint>

// Debounce mode
typedef enum
{
    // count mode, debouncing via count
    EN_DEB_MODE_COUNT,
    // time mode, via time
    EN_DEB_MODE_TIME
}EN_DEB_MODE;

// Debounce state
typedef enum

{
    // no debouncing is running
    EN_DEB_STATE_NONE,
    // debouncing is started
    EN_DEB_STATE_START,
    // debouncing is ready
    EN_DEB_STATE_READY,
}EN_DEB_STATE;

// Debounce class
class Debounce
{
    private:
        // setted mode
        EN_DEB_MODE en_deb_mode;
        // setted state
        EN_DEB_STATE en_deb_state;
        // debounce time in case debounce mode is EN_DEB_MODE_TIME
        uint16_t u16_time_ms;
        // debounce count in case debounce mode is EN_DEB_MODE_COUNT
        uint16_t u16_count;

        // current time in EN_DEB_MODE_TIME
        uint16_t u16_time_idx_ms;
        // start time in EN_DEB_MODE_TIME
        uint16_t u16_time_start_ms;
        // counter index in count mode
        uint16_t u16_count_idx;

        // pointer to extern time function.
        // The function has to return a time value in ms
        uint16_t (*ptr_time_ms)(void);

        // init function (used for constructors)
        void init();

    public:
        // constructor
        Debounce(EN_DEB_MODE en_deb_mode,
                 uint16_t u16_time_ms,
                 uint16_t u16_count,
                 uint16_t (*ptr_time_ms)(void));

        // trigger for debounce
        // in EN_DEB_MODE_COUNT the trigger counts down the u16_count
        // in EN_DEB_MODE_TIME the current time is measured
        EN_DEB_STATE trigger(void);

        // returns debounce state EN_DEB_STATE
        EN_DEB_STATE get_state(void);
};
