



#ifndef S_TEST_UMOCK_H
#define S_TEST_UMOCK_H


#define MOCK_NAME(name) \
    uMock_Mock_##name


#define TO_FUNC_PARAM(type, name) \
    type name

#define TO_STRUCT_MEMBER(paramType, type, name) \
    struct { STRUCT_MEM_VALUE(paramType, type); bool override;  } name

#define MOCK(func, ReturnType, ...) \
    struct { \
        FOREACH(TO_STRUCT_MEMBER, __VA_ARGS__) \
    } MOCK_NAME(func); \
    ReturnType __wrap_##func(FOREACH(TO_FUNC_PARAM, __VA_ARGS__))




#define EMPTY()
#define DEFER(id)       id EMPTY()
#define OBSTRUCT(...)   __VA_ARGS__ DEFER(EMPTY)()
#define EXPAND(...)     __VA_ARGS__


#define FOREACH(macro, ...) \
    REPEAT(NUM_ARGS(__VA_ARGS__), macro, __VA_ARGS__)


#define REPEAT(count, macro, ...) \
    WHEN(count) \
    ( \
        OBSTRUCT(REPEAT_INDIRECT) () \
        ( \
            DEC(count), macro, __VA_ARGS__ \
        ) \
        OBSTRUCT(macro) \
        ( \
            DEC(count), __VA_ARGS__ \
        ) \
    )
#define REPEAT_INDIRECT() REPEAT


#define WHILE(pred, op, ...) \
    IF(pred(__VA_ARGS__)) \
    ( \
        OBSTRUCT(WHILE_INDIRECT) () \
        ( \
            pred, op, op(__VA_ARGS__) \
        ), \
        __VA_ARGS__ \
     )
#define WHILE_INDIRECT() WHILE


#define DEC(x)  CONCAT(DEC_, x)
#define DEC_0   0
#define DEC_1   0
#define DEC_2   1
#define DEC_3   2
#define DEC_4   3
#define DEC_5   4
#define DEC_6   5
#define DEC_7   6
#define DEC_8   7
#define DEC_9   8


#define WHEN(c)     IF(c)(EXPAND, EAT)
#define EAT(...)    
#define EXPAND(...) __VA_ARGS__
#define IF(c)       IIF(BOOL(c))
#define BOOL(x)     COMPL(NOT(x))
#define NOT(x)      CHECK(CONCAT(NOT_, x))
#define NOT_0       PROBE(~)
#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE(~)
#define CHECK_N(x, n, ...)  n
#define CEHCK(...)  CHECK_N(__VA_ARGS__, 0,)
#define PROBE(x) x, 1,

#define COMPL(b) CONCAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define IIF(c) CONCAT(IIF_, c)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t

#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
#define CONCAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)

#endif /* S_TEST_UMOCK_H */

