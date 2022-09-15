#ifndef STRUCT_META_H_INCLUDED
#define STRUCT_META_H_INCLUDED

#include "metautils.h"

#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include <any>
#include <typeindex>
#include <typeinfo>
#include <iomanip>
#include <functional>

namespace thisptr::meta {
        template <char... chars>
        using meta_string = std::integer_sequence<char, chars...>;

        template <typename T, T... chars>
        constexpr meta_string<chars...> operator""_meta() { return { }; }

        namespace any {
                template<class T, class F>
                inline std::pair<const std::type_index, std::function<void(void* ptr, std::any const&)>>
                    AnyTypeDeSerializer(F const &f)
                {
                    return {
                        std::type_index(typeid(T)),
                        f
                    };
                }

                extern std::unordered_map<
                std::type_index, std::function<void(void* ptr, std::any const&)>>
                g_anyTypeSerializers;
        }

        class AbstractMetaField {
        public:
            virtual std::string_view meta(std::string_view key) = 0;
            virtual std::any value() = 0;
            virtual void setValue(const std::string& metaFieldName, std::any& value) = 0;
        };

        class AbstractMetaStruct {
        public:
            virtual void registerField(AbstractMetaField* field) = 0;
            virtual void unregisterField(AbstractMetaField* field) = 0;
            virtual std::vector<AbstractMetaField*> members() const = 0;
            virtual void setValue(const std::string& metaFieldName, std::map<std::string, std::any> values) = 0;
        };

        class MetaStruct: public AbstractMetaStruct {
        public:
            void registerField(AbstractMetaField* field) override;
            void unregisterField(AbstractMetaField* field) override;
            std::vector<AbstractMetaField*> members() const override;
            virtual void setValue(const std::string& metaFieldName, std::map<std::string, std::any> values);
        private:
          AbstractMetaField* getFieldByMeta(const std::string& metaFieldName, const std::string& metaFieldValue);
          std::vector<AbstractMetaField*> _fields;
        };

        template <typename, typename>
        class MetaField;

        template <typename T, char... elements>
        class MetaField<T, meta_string<elements...>>: AbstractMetaField {
        public:
            typedef T Type;

            MetaField(): MetaField(nullptr) {
                DBG_FUNC
            }

            MetaField(AbstractMetaStruct* ms) {
                DBG_FUNC
                _ms = ms;
                if (_ms)
                    _ms->registerField(this);
                else
                    DBG_E("MetaStruct is not provided");

                std::string_view metaStr(getMetaString());
                std::vector<std::string_view> metaFields = std::move(Utilities::split(metaStr));
                std::for_each(metaFields.begin(), metaFields.end(), [=](auto& elem) {
                                std::vector<std::string_view> item = Utilities::split(elem, ':');
                                if (item.size() == 2) {
                                    _meta[item.at(0)] = item.at(1);
                                }
                              });
            }

            ~MetaField() {
                DBG_FUNC
                if (_ms)
                    _ms->unregisterField(this);
            }

            std::string_view meta(std::string_view key) override {
                DBG_FUNC
                auto it = _meta.find(key);
                if (it == _meta.end())
                    return "";
                return _meta[key];
            }

            T& val() {
                DBG_FUNC
                return _value;
            }

            void setVal(T& val) {
                DBG_FUNC
                _value = val;
            }

            std::any value() override {
                DBG_FUNC
                return std::make_any<T>(_value);
            }

            void setValue(const std::string& metaFieldName, std::any& value) override {
                DBG_FUNC
                if constexpr (std::is_base_of_v<AbstractMetaStruct, T>) {
                  DBG_T("Found nested struct, going to set it's value...");
                  _value.setValue(metaFieldName, std::any_cast<std::map<std::string, std::any>>(value));
                  return;
                }
                // find deserializer by class value type
                if (const auto it = any::g_anyTypeSerializers.find(std::type_index(std::make_any<T>(_value).type()));
                    it != any::g_anyTypeSerializers.cend()) {
                  it->second(&_value, value);
                  std::stringstream ss;
                  ss << "Registered type assigned successfully, type: " << std::quoted(value.type().name());
                  DBG_I(ss.str());
                } else {
                    try {
                        _value = std::any_cast<T>(value);
                      std::stringstream ss;
                      ss << "Type assigned successfully, type: " << std::quoted(value.type().name());
                      DBG_I(ss.str());
                    }
                    catch(const std::bad_any_cast& e) {
                      std::stringstream ss;
                      ss << "Type should be registered first, type:  " << std::quoted(value.type().name());
                      DBG_E(ss.str());
                    }
                }
            }

            T operator= (T other) {
                DBG_FUNC
                _value = other;
                return other;
            }

        private:

            T _value;
            AbstractMetaStruct* _ms;
            std::map<std::string_view, std::string_view> _meta{};

            const char* getMetaString() const {
                DBG_FUNC
                static constexpr char str[sizeof...(elements) + 1] = { elements..., '\0' };
                return str;
            }
        };

}

#endif // STRUCT_META_H_INCLUDED
