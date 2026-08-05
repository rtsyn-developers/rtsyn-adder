#include "rtsyn/internal/adder.h"
#include "rtsyn/internal/adder/process.h"

rtsyn_abi_status_t RTSYN_ABI_CALL
rtsyn_adder_process(void *instance, const rtsyn_abi_runtime_context_t *context)
{
    rtsyn_adder_instance_t *adder = (rtsyn_adder_instance_t *)instance;
    rtsyn_abi_status_t status = RTSYN_ABI_STATUS_OK;

    if (!adder || !context || !context->api || !context->api->read || !context->api->write)
    {
        return RTSYN_ABI_STATUS_INVALID_ARGUMENT;
    }

    status = context->api->read(context, RTSYN_ADDER_PORT_LEFT, &adder->left);
    if (status < 0)
    {
        return status;
    }

    status = context->api->read(context, RTSYN_ADDER_PORT_RIGHT, &adder->right);
    if (status < 0)
    {
        return status;
    }

    adder->sum = adder->left * adder->left_multiplier
               + adder->right * adder->right_multiplier;
    return context->api->write(context, RTSYN_ADDER_PORT_SUM, &adder->sum);
}
