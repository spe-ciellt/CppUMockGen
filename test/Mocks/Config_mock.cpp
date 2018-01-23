/* This file has been auto-generated by CppUTestMock. DO NOT EDIT IT!!! */

#include "Config.hpp"

#include <CppUTestExt/MockSupport.h>

const std::string & Config::OverrideSpec::GetType() const
{
    return * static_cast<const std::string *>( mock().actualCall("Config::OverrideSpec::GetType").returnConstPointerValue() );
}

void Config::OverrideSpec::UpdateArgExpr(std::string & argExpr) const
{
    mock().actualCall("Config::OverrideSpec::UpdateArgExpr").withOutputParameterOfType("std::string", "argExpr", &argExpr);
}

const Config::OverrideSpec * Config::OverrideMap::GetOverride(const std::string & key) const
{
    return static_cast<const Config::OverrideSpec *>( mock().actualCall("Config::OverrideMap::GetOverride").withParameterOfType("std::string", "key", &key).returnConstPointerValue() );
}

bool Config::UseUnderlyingTypedefType() const
{
    return mock().actualCall("Config::UseUnderlyingTypedefType").returnBoolValue();
}

const Config::OverrideSpec * Config::GetOverride(const std::string & key) const
{
    return static_cast<const Config::OverrideSpec *>( mock().actualCall("Config::GetOverride").withStringParameter("key", key.c_str()).returnConstPointerValue() );
}

