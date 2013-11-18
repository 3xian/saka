#pragma once

#define FOR_EACH(iter, collect) for (auto iter = (collect).begin();\
        iter != (collect).end(); ++iter)

#define BOOL_NAME(b) ((b) ? "true" : "false")

#define ASSERT_RT(exp, ret) \
    do { \
        if (!(exp)) { \
            UB_LOG_WARNING("[%s]ASSERT_RT(%s)", __func__, #exp); \
            return ret; \
        } \
    } while(0)
