#include "rtsyn/internal/adder.h"
#include "rtsyn/internal/adder/read_state.h"

rtsyn_abi_status_t RTSYN_ABI_CALL
rtsyn_adder_read_state(const void *instance, uint32_t state_index, void *out_value)
{
    const rtsyn_adder_instance_t *adder = (const rtsyn_adder_instance_t *)instance;

    if (!adder || !out_value || state_index != RTSYN_ADDER_STATE_RESULT)
    {
        return RTSYN_ABI_STATUS_INVALID_ARGUMENT;
    }

    *(double *)out_value = adder->sum;
    return RTSYN_ABI_STATUS_OK;
}
