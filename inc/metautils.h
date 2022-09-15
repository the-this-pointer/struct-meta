#ifndef METAUTILS_H_INCLUDED
#define METAUTILS_H_INCLUDED

#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include <any>
#include <string_view>

#ifdef META_DEBUG
#include <logger.h>

#define DBG_INIT thisptr::Logger::getInstance("main", std::cout);
#define DBG_C(x) (*thisptr::Logger::getInstance())(thisptr::Logger::CRIT) << (x) << std::endl;
#define DBG_E(x) (*thisptr::Logger::getInstance())(thisptr::Logger::ERR) << (x) << std::endl;
#define DBG_W(x) (*thisptr::Logger::getInstance())(thisptr::Logger::WARN) << (x) << std::endl;
#define DBG_I(x) (*thisptr::Logger::getInstance())(thisptr::Logger::INFO) << (x) << std::endl;
#define DBG_D(x) (*thisptr::Logger::getInstance())(thisptr::Logger::DEBUG) << (x) << std::endl;
#define DBG_T(x) (*thisptr::Logger::getInstance())(thisptr::Logger::CRIT) << (x) << std::endl;
#define DBG_FUNC DBG_D(__PRETTY_FUNCTION__);
#else
#define DBG_INIT
#define DBG_C(x)
#define DBG_E(x)
#define DBG_W(x)
#define DBG_I(x)
#define DBG_D(x)
#define DBG_T(x)
#define DBG_FUNC
#endif

namespace thisptr {
    namespace Utilities {
        template<typename T>
        struct IsVector
        {
            static constexpr bool value = false;
        };

        template<template<typename...> class C, typename U>
        struct IsVector<C<U>>
        {
            static constexpr bool value = std::is_same<C<U>,std::vector<U>>::value;
        };

        template<typename T>
        inline constexpr bool IsVectorV = IsVector<T>::value;

        template<typename T, typename U = void>
        struct IsMap
        {
            static constexpr bool value = false;
        };

        template<typename T>
        struct IsMap<T, std::void_t<typename T::key_type,
                 typename T::mapped_type,
                 decltype(std::declval<T&>()[std::declval<const typename T::key_type&>()])>>
        {
            static constexpr bool value = true;
        };

        template<typename T>
        inline constexpr bool IsMapV = IsMap<T>::value;

        template <class T>
        constexpr std::string_view type_name() {
            // added 16 to numbers because of namespace
            using namespace std;
#ifdef __clang__
    string_view p = __PRETTY_FUNCTION__;
    return string_view(p.data() + 50, p.size() - 50 - 1);
#elif defined(__GNUC__)
    string_view p = __PRETTY_FUNCTION__;
#  if __cplusplus < 201402
    return string_view(p.data() + 52, p.size() - 52 - 1);
#  else
    return string_view(p.data() + 65, p.find(';', 65) - 65);
#  endif
#elif defined(_MSC_VER)
    string_view p = __FUNCSIG__;
    return string_view(p.data() + 100, p.size() - 100 - 7);
#endif
        }

        template <typename T>
        struct FriendMaker
        {
            typedef T Type;
        };

        std::vector<std::string_view> split(std::string_view str, char delim = ',');
    }
}

#endif // METAUTILS_H_INCLUDED
