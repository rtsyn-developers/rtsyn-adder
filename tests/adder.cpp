#include <array>
#include <cstdint>
#include <cstring>
#include <gtest/gtest.h>

#include "rtsyn/adder.h"

namespace {

struct HostContext {
    std::array<double, 2> inputs;
    double output;
};

rtsyn_abi_status_t
read(const rtsyn_abi_runtime_context_t *context, uint32_t port_index, void *out_value)
{
    if (port_index >= 2 || out_value == nullptr)
    {
        return RTSYN_ABI_STATUS_INVALID_ARGUMENT;
    }
    const auto *host = static_cast<const HostContext *>(context->host_context);
    std::memcpy(out_value, &host->inputs[port_index], sizeof(double));
    return RTSYN_ABI_STATUS_OK;
}

rtsyn_abi_status_t
write(const rtsyn_abi_runtime_context_t *context, uint32_t port_index, const void *value)
{
    if (port_index != 2 || value == nullptr)
    {
        return RTSYN_ABI_STATUS_INVALID_ARGUMENT;
    }
    auto *host = const_cast<HostContext *>(static_cast<const HostContext *>(context->host_context));
    std::memcpy(&host->output, value, sizeof(double));
    return RTSYN_ABI_STATUS_OK;
}

TEST(AdderPlugin, DescribesTwoInputsAndOneOutput)
{
    const auto *descriptor = rtsyn_adder_get_descriptor();

    ASSERT_NE(descriptor, nullptr);
    EXPECT_STREQ(descriptor->name, "adder");
    ASSERT_EQ(descriptor->port_count, 3U);
    EXPECT_EQ(descriptor->ports[0].value_type, RTSYN_ABI_VALUE_F64);
    EXPECT_EQ(descriptor->ports[0].direction, RTSYN_ABI_PORT_DIRECTION_IN);
    EXPECT_EQ(descriptor->ports[1].direction, RTSYN_ABI_PORT_DIRECTION_IN);
    EXPECT_EQ(descriptor->ports[2].direction, RTSYN_ABI_PORT_DIRECTION_OUT);
    ASSERT_EQ(descriptor->param_count, 2U);
    EXPECT_STREQ(descriptor->params[0].name, "left_multiplier");
    EXPECT_EQ(descriptor->params[0].value_type, RTSYN_ABI_VALUE_F64);
    EXPECT_STREQ(descriptor->params[1].name, "right_multiplier");
    ASSERT_EQ(descriptor->state_count, 1U);
    EXPECT_STREQ(descriptor->states[0].name, "result");
    EXPECT_EQ(descriptor->states[0].value_type, RTSYN_ABI_VALUE_F64);
}

TEST(AdderPlugin, AppliesOperandMultipliersAndExposesResultState)
{
    const auto *descriptor = rtsyn_adder_get_descriptor();
    void *instance = nullptr;
    HostContext host{{2.0, 3.0}, 0.0};
    const rtsyn_abi_runtime_api_t api{read, write};
    const rtsyn_abi_runtime_context_t context{0,    0,    0, RTSYN_RUNTIME_CYCLE_STAGE_INTERMEDIATE,
                                              &api, &host};
    const double left_multiplier = 4.0;
    const double right_multiplier = 5.0;
    double result = 0.0;

    ASSERT_EQ(descriptor->callbacks.create(&instance), RTSYN_ABI_STATUS_OK);
    ASSERT_NE(instance, nullptr);
    ASSERT_EQ(descriptor->callbacks.set_param(instance, 0, &left_multiplier), RTSYN_ABI_STATUS_OK);
    ASSERT_EQ(descriptor->callbacks.set_param(instance, 1, &right_multiplier), RTSYN_ABI_STATUS_OK);
    ASSERT_EQ(descriptor->callbacks.start(instance), RTSYN_ABI_STATUS_OK);
    ASSERT_EQ(descriptor->callbacks.process(instance, &context), RTSYN_ABI_STATUS_OK);
    EXPECT_DOUBLE_EQ(host.output, 23.0);
    ASSERT_EQ(descriptor->callbacks.read_state(instance, 0, &result), RTSYN_ABI_STATUS_OK);
    EXPECT_DOUBLE_EQ(result, 23.0);
    descriptor->callbacks.destroy(instance);
}

TEST(AdderPlugin, AddsInputsDuringProcessing)
{
    const auto *descriptor = rtsyn_adder_get_descriptor();
    void *instance = nullptr;
    HostContext host{{1.25, 2.5}, 0.0};
    const rtsyn_abi_runtime_api_t api{read, write};
    const rtsyn_abi_runtime_context_t context{0,    0,    0, RTSYN_RUNTIME_CYCLE_STAGE_INTERMEDIATE,
                                              &api, &host};

    ASSERT_EQ(descriptor->callbacks.create(&instance), RTSYN_ABI_STATUS_OK);
    ASSERT_NE(instance, nullptr);
    EXPECT_EQ(descriptor->callbacks.start(instance), RTSYN_ABI_STATUS_OK);
    EXPECT_EQ(descriptor->callbacks.process(instance, &context), RTSYN_ABI_STATUS_OK);
    EXPECT_DOUBLE_EQ(host.output, 3.75);
    EXPECT_EQ(descriptor->callbacks.stop(instance), RTSYN_ABI_STATUS_OK);
    descriptor->callbacks.destroy(instance);
}

} // namespace
