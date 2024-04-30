#ifndef PARAMETERSYSTEM
#define PARAMETERSYSTEM
#include "Parameters.h"
#include "ParamMsgInterface.h"

#include <type_traits>

// A helper type trait to check if a type is one of a list of types
template <typename T, typename... Types>
struct is_one_of : std::disjunction<std::is_same<T, Types>...>
{
};

template <typename T, typename value_type>
void set_parameter(T &paramType, value_type value)
{
    static_assert(is_one_of<value_type, int, bool, float>::value, "set_parameter can only be used with int, bool, or float");
    paramType.set(value);
}

template <typename T>
auto get_parameter(T &paramType)
{
    return paramType.get();
}

void update_parameters_from_interface()
{

}

/// @brief templated function used to set parameter based on unique id
/// @tparam param_type the value type (float, bool or int)
/// @tparam param_base_type the base pointer for that is being used in the unordered map that will be updated
/// @param name id of the param
/// @param out_map map that will be updated
/// @param value the value the id will be set to
template <typename param_type, typename param_base_type>
void id_param_set_(const char *name, std::unordered_map<const char *, param_base_type *> &out_map, param_type value)
{
    out_map.at(name)->set(value);
}
/// @brief templated function used to get parameter based on unique id
/// @tparam param_type the value type (float, bool or int)
/// @tparam param_base_type the base pointer for that is being used in the unordered map
/// @param name the id of the param being retrieved
/// @param map the map to retrieve from
/// @return the value
template <typename param_type, typename param_base_type>
auto id_param_get_(const char *name, const std::unordered_map<const char *, param_base_type *> &map)
{
    return map.get(name)->get();
}

#endif