#ifndef METAREADER_H_INCLUDED
#define METAREADER_H_INCLUDED

#include <rapidjson/reader.h>

#include "meta.h"

#include <iostream>
#include <any>
#include <map>
#include <vector>

namespace thisptr::meta::json {

  using JsonValue = std::any;
  using JsonObject = std::map<std::string, JsonValue>;
  using JsonArray = std::vector<JsonValue>;

  class AbstractJsonHandler {
  public:
    virtual ~AbstractJsonHandler() = default;
    virtual bool Null() = 0;
    virtual bool Bool(bool b) = 0;
    virtual bool Int(int i) = 0;
    virtual bool Uint(unsigned u) = 0;
    virtual bool Int64(int64_t i) = 0;
    virtual bool Uint64(uint64_t u) = 0;
    virtual bool Double(double d) = 0;
    virtual bool RawNumber(const char *str, rapidjson::SizeType length, bool copy) = 0;
    virtual bool String(const char *str, rapidjson::SizeType length, bool copy) = 0;
    virtual bool StartObject() = 0;
    virtual bool Key(const char *str, rapidjson::SizeType length, bool copy) = 0;
    virtual bool EndObject(rapidjson::SizeType memberCount) = 0;
    virtual bool StartArray() = 0;
    virtual bool EndArray(rapidjson::SizeType elementCount) = 0;
    virtual std::any value() = 0;
  };

  template<typename T>
  class JsonHandler;

  template<>
  class JsonHandler<JsonValue> : public AbstractJsonHandler {
  public:
    JsonHandler() = default;
    ~JsonHandler() override = default;
    bool Null() override;
    bool Bool(bool b) override;
    bool Int(int32_t i) override;
    bool Uint(uint32_t u) override;
    bool Int64(int64_t i) override;
    bool Uint64(uint64_t u) override;
    bool Double(double d) override;
    bool RawNumber(const char *str, rapidjson::SizeType length, bool copy) override;
    bool String(const char *str, rapidjson::SizeType length, bool copy) override;
    bool StartObject() override;
    bool Key(const char *str, rapidjson::SizeType length, bool copy) override;
    bool EndObject(rapidjson::SizeType memberCount) override;
    bool StartArray() override;
    bool EndArray(rapidjson::SizeType elementCount) override;
    std::any value() override;

  private:
    JsonValue _value;
    std::string _currentKey;
    AbstractJsonHandler *_innerHandler{nullptr};
    uint32_t _counter{0};
  };

  template<>
  class JsonHandler<JsonObject> : public AbstractJsonHandler {
  public:
    JsonHandler() = default;
    ~JsonHandler() override = default;
    bool Null() override;
    bool Bool(bool b) override;
    bool Int(int32_t i) override;
    bool Uint(uint32_t u) override;
    bool Int64(int64_t i) override;
    bool Uint64(uint64_t u) override;
    bool Double(double d) override;
    bool RawNumber(const char *str, rapidjson::SizeType length, bool copy) override;
    bool String(const char *str, rapidjson::SizeType length, bool copy) override;
    bool StartObject() override;
    bool Key(const char *str, rapidjson::SizeType length, bool copy) override;
    bool EndObject(rapidjson::SizeType memberCount) override;
    bool StartArray() override;
    bool EndArray(rapidjson::SizeType elementCount) override;
    std::any value() override;

  private:
    JsonObject _value;
    std::string _currentKey;
    AbstractJsonHandler *_innerHandler{nullptr};
    uint32_t _counter{0};
  };

  template<>
  class JsonHandler<JsonArray> : public AbstractJsonHandler {
  public:
    JsonHandler() = default;
    ~JsonHandler() override = default;
    bool Null() override;
    bool Bool(bool b) override;
    bool Int(int32_t i) override;
    bool Uint(uint32_t u) override;
    bool Int64(int64_t i) override;
    bool Uint64(uint64_t u) override;
    bool Double(double d) override;
    bool RawNumber(const char *str, rapidjson::SizeType length, bool copy) override;
    bool String(const char *str, rapidjson::SizeType length, bool copy) override;
    bool StartObject() override;
    bool Key(const char *str, rapidjson::SizeType length, bool copy) override;
    bool EndObject(rapidjson::SizeType memberCount) override;
    bool StartArray() override;
    bool EndArray(rapidjson::SizeType elementCount) override;
    std::any value() override;

  private:
    JsonArray _value;
    AbstractJsonHandler *_innerHandler{nullptr};
    uint32_t _counter{0};
  };

  class JsonReader {
  public:
    JsonReader() = default;
    ~JsonReader() = default;
    std::any read(const std::string &json);
    void readObject(const std::string &json, thisptr::meta::AbstractMetaStruct &ms);

  };

}


#endif // METAREADER_H_INCLUDED
