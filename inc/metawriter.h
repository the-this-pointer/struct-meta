#ifndef METAWRITER_H_INCLUDED
#define METAWRITER_H_INCLUDED

#include <type_traits>
#include <any>
#include <functional>
#include <iomanip>
#include <iostream>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <type_traits>

#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "metautils.h"
#include "meta.h"

namespace thisptr::meta::json {

  class JsonWriter {
  public:
    JsonWriter() = default;
    ~JsonWriter() = default;

    template<class T, class F>
    inline void registerTypeSerializer(F const &f);

    std::string write(std::any &obj);
    rapidjson::Writer <rapidjson::StringBuffer> &writer();
    inline void processType(const std::any &a);

  private:

    template<class T, class F>
    inline std::pair<const std::type_index, std::function<void(std::any const &)>>
    TypeSerializer(F const &f);

    template<class T, class F>
    inline std::pair<const std::type_index, std::function<void(std::any const &)>>
    TypeSerializerV(F const &f) {
      return {
          std::type_index(typeid(T)),
          [this, g = f](std::any const &a) {
            T v = std::any_cast<T const &>(a);

            _writer.StartArray();
            for (const auto &item: v) {
              g(item);
            }
            _writer.EndArray();
          }
      };
    }

    template<class T, class F>
    inline std::pair<const std::type_index, std::function<void(std::any const &)>>
    TypeSerializerMS(F const &f) {
      return {
          std::type_index(typeid(T)),
          [this, g = f](std::any const &a) {
            T m = std::any_cast<T const &>(a);

            _writer.StartObject();
            for (const auto &pair: m) {
              _writer.Key(pair.first);
              g(pair.second);
            }
            _writer.EndObject();
          }
      };
    }

    std::unordered_map<
        std::type_index, std::function<void(std::any const &)>>
        _typeSerializers{
        TypeSerializer<void>([this] { _writer.Null(); }),
        TypeSerializer<bool>([this](bool x) { _writer.Bool(x); }),
        TypeSerializer<int32_t>([this](int32_t x) { _writer.Int(x); }),
        TypeSerializer<uint32_t>([this](uint32_t x) { _writer.Uint(x); }),
        TypeSerializer<int64_t>([this](int64_t x) { _writer.Int64(x); }),
        TypeSerializer<uint64_t>([this](uint64_t x) { _writer.Uint64(x); }),
        TypeSerializer<float>([this](float x) { _writer.Double(x); }),
        TypeSerializer<double>([this](double x) { _writer.Double(x); }),
        TypeSerializer<char const *>([this](char const *s) { _writer.String(s); }),
        TypeSerializer<std::string>([this](std::string s) { _writer.String(s); }),
        TypeSerializerV<std::vector<bool>>([this](bool x) { _writer.Bool(x); }),
        TypeSerializerV<std::vector<int32_t>>([this](int32_t x) { _writer.Int(x); }),
        TypeSerializerV<std::vector<uint32_t>>([this](uint32_t x) { _writer.Uint(x); }),
        TypeSerializerV<std::vector<int64_t>>([this](int64_t x) { _writer.Int64(x); }),
        TypeSerializerV<std::vector<uint64_t>>([this](uint64_t x) { _writer.Uint64(x); }),
        TypeSerializerV<std::vector<float>>([this](float x) { _writer.Double(x); }),
        TypeSerializerV<std::vector<double>>([this](double x) { _writer.Double(x); }),
        TypeSerializerV<std::vector<std::string>>([this](std::string s) { _writer.String(s); }),
        TypeSerializerV<std::vector<std::any>>([this](std::any a) { processType(a); }),
        TypeSerializerMS<std::map<std::string, bool>>([this](bool x) { _writer.Bool(x); }),
        TypeSerializerMS<std::map<std::string, int32_t>>([this](int32_t x) { _writer.Int(x); }),
        TypeSerializerMS<std::map<std::string, uint32_t>>([this](uint32_t x) { _writer.Uint(x); }),
        TypeSerializerMS<std::map<std::string, int64_t>>([this](int64_t x) { _writer.Int64(x); }),
        TypeSerializerMS<std::map<std::string, uint64_t>>([this](uint64_t x) { _writer.Uint64(x); }),
        TypeSerializerMS<std::map<std::string, float>>([this](float x) { _writer.Double(x); }),
        TypeSerializerMS<std::map<std::string, double>>([this](double x) { _writer.Double(x); }),
        TypeSerializerMS<std::map<std::string, std::string>>([this](std::string s) { _writer.String(s); }),
        TypeSerializerMS<std::map<std::string, std::any>>([this](std::any a) { processType(a); }),
        TypeSerializer<AbstractMetaStruct *>([this](AbstractMetaStruct *ms) {
          _writer.StartObject();
          for (const auto &member: ms->members()) {
            std::string_view json = member->meta("json");
            if (json.length() == 0 || json == "-")
              continue;

            _writer.Key(std::string(json));
            processType(member->value());
          }
          _writer.EndObject();
        }),
    };

    rapidjson::StringBuffer _s;
    rapidjson::Writer <rapidjson::StringBuffer> _writer{_s};
  };

  template<class T, class F>
  void JsonWriter::registerTypeSerializer(const F &f) {
    std::cout << "Register type " << std::quoted(typeid(T).name()) << std::endl;
    _typeSerializers.insert(TypeSerializer<T>(f));
  }

  template<class T, class F>
  std::pair<const std::type_index, std::function<void(std::any const &)>> JsonWriter::TypeSerializer(const F &f) {
    return {
        std::type_index(typeid(T)),
        [g = f](std::any const &a)
        {
          if constexpr (std::is_void_v<T>)
            g();
          else
            g(std::any_cast<T const&>(a));
        }
    };
  }
}

#endif // METAWRITER_H_INCLUDED
