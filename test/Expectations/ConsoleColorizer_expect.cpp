/*
 * This file has been auto-generated by CppUTestMock v0.3.
 *
 * Contents will NOT be preserved if it is regenerated!!!
 */

#include "ConsoleColorizer_expect.hpp"

namespace expect { namespace ConsoleColorizer$ {
MockExpectedCall& SetColor(CppUMockGen::Parameter<const ConsoleColorizer*> __object__, CppUMockGen::Parameter<ConsoleColorizer::Color> color)
{
    bool __ignoreOtherParams__ = false;
    MockExpectedCall& __expectedCall__ = mock().expectOneCall("ConsoleColorizer::SetColor");
    if(!__object__.isIgnored()) { __expectedCall__.onObject(const_cast<ConsoleColorizer*>(__object__.getValue())); }
    if(color.isIgnored()) { __ignoreOtherParams__ = true; } else { __expectedCall__.withIntParameter("color", static_cast<int>(color.getValue())); }
    if(__ignoreOtherParams__) { __expectedCall__.ignoreOtherParameters(); }
    return __expectedCall__;
}
MockExpectedCall& SetColor(unsigned int __numCalls__, CppUMockGen::Parameter<const ConsoleColorizer*> __object__, CppUMockGen::Parameter<ConsoleColorizer::Color> color)
{
    bool __ignoreOtherParams__ = false;
    MockExpectedCall& __expectedCall__ = mock().expectNCalls(__numCalls__, "ConsoleColorizer::SetColor");
    if(!__object__.isIgnored()) { __expectedCall__.onObject(const_cast<ConsoleColorizer*>(__object__.getValue())); }
    if(color.isIgnored()) { __ignoreOtherParams__ = true; } else { __expectedCall__.withIntParameter("color", static_cast<int>(color.getValue())); }
    if(__ignoreOtherParams__) { __expectedCall__.ignoreOtherParameters(); }
    return __expectedCall__;
}
} }

