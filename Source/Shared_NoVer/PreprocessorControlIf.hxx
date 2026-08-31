#pragma once

#define UNIVERSELAN_PP_IF_0(true_value, false_value) false_value
#define UNIVERSELAN_PP_IF_1(true_value, false_value) true_value

#define UNIVERSELAN_PP_CAT_IMPL(a, b) a##b
#define UNIVERSELAN_PP_CAT(a, b) UNIVERSELAN_PP_CAT_IMPL(a, b)

#define UNIVERSELAN_PP_IF(condition, true_value, false_value) \
    UNIVERSELAN_PP_CAT(UNIVERSELAN_PP_IF_, condition)(true_value, false_value)