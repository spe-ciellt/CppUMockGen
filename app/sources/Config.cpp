/**
 * @file
 * @brief      Implementation of Config class
 * @project    CppUMockGen
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2017-2018 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#include "Config.hpp"

#include <set>
#include <vector>

static const char EXPR_MOD_SEPARATOR = '~';
static const char EXPR_MOD_ARG_PLACEHOLDER = '$';
static const char EXPECTATION_ARG_TYPE_SEPARATOR = '<';

Config::Config( bool useUnderlyingTypedefType, const std::vector<std::string> &paramOverrideOptions,
                const std::vector<std::string> &typeOverrideOptions )
: m_useUnderlyingTypedefType( useUnderlyingTypedefType ), m_paramOverrideMap( paramOverrideOptions, false ),
  m_typeOverrideMap( typeOverrideOptions, true )
{}

bool Config::UseUnderlyingTypedefType() const noexcept
{
    return m_useUnderlyingTypedefType;
}

const Config::OverrideSpec* Config::GetParameterOverride( const std::string& key ) const noexcept
{
    return m_paramOverrideMap.GetOverride(key);
}

const Config::OverrideSpec* Config::GetTypeOverride( const std::string& key ) const noexcept
{
    return m_typeOverrideMap.GetOverride(key);
}

static const std::vector<std::pair<std::string, MockedType>> validOverrideTypes =
{
    { "Bool", MockedType::Bool },
    { "Int", MockedType::Int },
    { "UnsignedInt", MockedType::UnsignedInt },
    { "LongInt", MockedType::Long },
    { "UnsignedLongInt", MockedType::UnsignedLong },
    { "Double", MockedType::Double },
    { "String", MockedType::String },
    { "Pointer", MockedType::Pointer },
    { "ConstPointer", MockedType::ConstPointer },
    { "Output", MockedType::Output },
    { "Skip", MockedType::Skip },
};

static const std::map<std::string, MockedType> validReturnOverrideTypes( validOverrideTypes.begin(), validOverrideTypes.end() - 2 );
static const std::map<std::string, MockedType> validParameterOverrideTypes( validOverrideTypes.begin(), validOverrideTypes.end() );

static const std::vector<std::pair<std::string, MockedType>> validTypeOfOverrideTypes =
{
    { "InputOfType:", MockedType::InputOfType },
    { "OutputOfType:", MockedType::OutputOfType },
};

Config::OverrideSpec::OverrideSpec( const std::string &value, const std::string &option, bool isReturn )
{
    if( value.empty() )
    {
        std::string errorMsg = "Override option specification cannot be empty ['" + option + "']";
        throw std::runtime_error( errorMsg );
    }

    std::string type;
    size_t exprModSepPos = value.find( EXPR_MOD_SEPARATOR );
    if( exprModSepPos != std::string::npos )
    {
        type = value.substr(0, exprModSepPos);
        if( type.empty() )
        {
            std::string errorMsg = "Override option type cannot be empty ['" + option + "']";
            throw std::runtime_error( errorMsg );
        }

        std::string argExprMod = value.substr(exprModSepPos+1);
        if( argExprMod.empty() )
        {
            std::string errorMsg = "Override option argument expression cannot be empty if specified ['" + option + "']";
            throw std::runtime_error( errorMsg );
        }

        size_t placeholderPos = argExprMod.find( EXPR_MOD_ARG_PLACEHOLDER );
        if( placeholderPos == std::string::npos )
        {
            std::string errorMsg = "Override option argument expression does not contain parameter name placeholder ($) ['" + option + "']";
            throw std::runtime_error( errorMsg );
        }

        m_exprModFront = argExprMod.substr( 0, placeholderPos );
        m_exprModBack = argExprMod.substr( placeholderPos + 1 );
    }
    else
    {
        type = value;
    }

    if( isReturn )
    {
        auto it = validReturnOverrideTypes.find( type );
        if( it != validReturnOverrideTypes.end() )
        {
            m_type = it->second;
        }
        else
        {
            std::string errorMsg = "Invalid return override option type ['" + option + "'].";
            throw std::runtime_error( errorMsg );
        }
    }
    else
    {
        auto it = validParameterOverrideTypes.find( type );
        if( it != validParameterOverrideTypes.end() )
        {
            m_type = it->second;
        }
        else
        {
            bool overrideTypeFound = false;

            for( auto overrideType : validTypeOfOverrideTypes )
            {
                if( type.find( overrideType.first ) == 0 )
                {
                    m_type = overrideType.second;
                    m_exposedTypeName = type.substr( overrideType.first.size() );

                    size_t expectArgTypeSepPos = m_exposedTypeName.find( EXPECTATION_ARG_TYPE_SEPARATOR );
                    if( expectArgTypeSepPos != std::string::npos )
                    {
                        m_expectationArgTypeName = m_exposedTypeName.substr( expectArgTypeSepPos + 1 );
                        m_exposedTypeName = m_exposedTypeName.substr( 0, expectArgTypeSepPos );

                        if( m_expectationArgTypeName.empty() )
                        {
                            std::string errorMsg = "Override option expectation argument type cannot be empty ['" + option + "'].";
                            throw std::runtime_error( errorMsg );
                        }
                    }
                    else
                    {
                        m_expectationArgTypeName = m_exposedTypeName;
                    }

                    if( m_exposedTypeName.empty() )
                    {
                        std::string errorMsg = "Override option type name cannot be empty ['" + option + "'].";
                        throw std::runtime_error( errorMsg );
                    }

                    overrideTypeFound = true;
                }
            }

            if( !overrideTypeFound )
            {
                std::string errorMsg = "Invalid parameter override option type ['" + option + "'].";
                throw std::runtime_error( errorMsg );
            }
        }
    }
}

Config::OverrideMap::OverrideMap( const std::vector<std::string> &options, bool typeOverride )
{
    for( const std::string &option : options )
    {
        size_t sepPos = option.find('=');
        if( sepPos != std::string::npos )
        {
            std::string key = option.substr(0, sepPos);
            if( key.empty() )
            {
                std::string errorMsg = "Override option key cannot be empty ['" + option + "'].";
                throw std::runtime_error( errorMsg );
            }

            bool isReturn = ( typeOverride ? ( key.front()  == '@' ) : ( key.back()  == '@' ) );

            Config::OverrideSpec spec = Config::OverrideSpec( option.substr(sepPos+1), option, isReturn );

            if( !m_map.emplace( key, spec ).second )
            {
                std::string errorMsg = "Override option key '" + key + "' can only be passed once.";
                throw std::runtime_error( errorMsg );
            }
        }
        else
        {
            std::string errorMsg = "Invalid override option '[" + option + "'].";
            throw std::runtime_error( errorMsg );
        }
    }
}

const Config::OverrideSpec* Config::OverrideMap::GetOverride( const std::string& key ) const noexcept
{
    OverrideMapType::const_iterator it = m_map.find( key );
    return ( it != m_map.end() ) ? &(it->second) : NULL;
}

MockedType Config::OverrideSpec::GetType() const noexcept
{
    return m_type;
}

const std::string& Config::OverrideSpec::GetExposedTypeName() const noexcept
{
    return m_exposedTypeName;
}

const std::string& Config::OverrideSpec::GetExprModFront() const noexcept
{
    return m_exprModFront;
}

const std::string& Config::OverrideSpec::GetExprModBack() const noexcept
{
    return m_exprModBack;
}

const std::string& Config::OverrideSpec::GetExpectationArgTypeName() const noexcept
{
    return m_expectationArgTypeName;
}
