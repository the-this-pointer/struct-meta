#include "metareader.h"

namespace thisptr::Meta::Json {

  bool JsonHandler<JsonValue>::StartObject() {
    
    if (_counter > 0 && _innerHandler) {
      _innerHandler->StartObject();
    } else if (!_innerHandler) {
      _innerHandler = new JsonHandler<JsonObject>();
    }
    _counter++;
    return true;
  }

  bool JsonHandler<JsonValue>::StartArray() {
    
    if (_counter > 0 && _innerHandler) {
      _innerHandler->StartArray();
    } else if (!_innerHandler) {
      _innerHandler = new JsonHandler<JsonArray>();
    }
    _counter++;
    return true;
  }

  bool JsonHandler<JsonValue>::Bool(bool b) {

    if (_innerHandler) {
      _innerHandler->Bool(b);
      return true;
    }
    _value = std::make_any<bool>(b);
    return true;
  }

  bool JsonHandler<JsonValue>::Null() {

    if (_innerHandler) {
      _innerHandler->Null();
      return true;
    }
    _value.reset();
    return true;
  }

  bool JsonHandler<JsonValue>::Int(int32_t i) {

    if (_innerHandler) {
      _innerHandler->Int(i);
      return true;
    }
    _value = std::make_any<int32_t>(i);
    return true;
  }

  bool JsonHandler<JsonValue>::Double(double d) {

    if (_innerHandler) {
      _innerHandler->Double(d);
      return true;
    }
    _value = std::make_any<double>(d);
    return true;
  }

  bool JsonHandler<JsonValue>::String(const char *str, rapidjson::SizeType length, bool copy) {

    if (_innerHandler) {
      _innerHandler->String(str, length, copy);
      return true;
    }
    _value = std::make_any<std::string>(str);
    return true;
  }

  bool JsonHandler<JsonValue>::EndObject(rapidjson::SizeType memberCount) {

    if (_counter == 1 && _innerHandler) {

      _value = std::move(_innerHandler->value());
      delete _innerHandler;
      _innerHandler = nullptr;
    } else if (_counter > 1 && _innerHandler) {
      _innerHandler->EndObject(memberCount);
    }
    _counter--;
    return true;
  }

  bool JsonHandler<JsonValue>::EndArray(rapidjson::SizeType elementCount) {

    if (_counter == 1 && _innerHandler) {

      _value = std::move(_innerHandler->value());
      delete _innerHandler;
      _innerHandler = nullptr;
    } else if (_counter > 1 && _innerHandler) {
      _innerHandler->EndArray(elementCount);
    }
    _counter--;
    return true;
  }

  std::any JsonHandler<JsonValue>::value() {

    return _value;
  }

  bool JsonHandler<JsonValue>::Key(const char *str, rapidjson::SizeType length, bool copy) {

    if (_innerHandler) {
      _innerHandler->Key(str, length, copy);
      return true;
    }
    _currentKey = std::string(str);
    return true;
  }

  bool JsonHandler<JsonValue>::RawNumber(const char *str, rapidjson::SizeType length, bool copy) {

    if (_innerHandler) {
      _innerHandler->RawNumber(str, length, copy);
      return true;
    }
    return true;
  }

  bool JsonHandler<JsonValue>::Uint64(uint64_t u) {

    if (_innerHandler) {
      _innerHandler->Uint64(u);
      return true;
    }
    _value = std::make_any<uint64_t>(u);
    return true;
  }

  bool JsonHandler<JsonValue>::Int64(int64_t i) {

    if (_innerHandler) {
      _innerHandler->Int64(i);
      return true;
    }
    _value = std::make_any<int64_t>(i);
    return true;
  }

  bool JsonHandler<JsonValue>::Uint(uint32_t u) {

    if (_innerHandler) {
      _innerHandler->Uint(u);
      return true;
    }
    _value = std::make_any<uint32_t>(u);
    return true;
  }

  bool JsonHandler<JsonObject>::StartObject() {

    if (_counter > 0 && _innerHandler) {
      _innerHandler->StartObject();
    } else if (!_innerHandler) {
      _innerHandler = new JsonHandler<JsonObject>();
    }
    _counter++;
    return true;
  }

  bool JsonHandler<JsonObject>::StartArray() {

    if (_counter > 0 && _innerHandler) {
      _innerHandler->StartArray();
    } else if (!_innerHandler) {
      _innerHandler = new JsonHandler<JsonArray>();
    }
    _counter++;
    return true;
  }

  bool JsonHandler<JsonArray>::StartObject() {

    if (_counter > 0 && _innerHandler) {
      _innerHandler->StartObject();
    } else if (!_innerHandler) {
      _innerHandler = new JsonHandler<JsonObject>();
    }
    _counter++;
    return true;
  }

  bool JsonHandler<JsonArray>::StartArray() {

    if (_counter > 0 && _innerHandler) {
      _innerHandler->StartArray();
    } else if (!_innerHandler) {
      _innerHandler = new JsonHandler<JsonArray>();
    }
    _counter++;
    return true;
  }

  bool JsonHandler<JsonArray>::Null() {

    if (_innerHandler) {
      _innerHandler->Null();
      return true;
    }
    _value.push_back(std::any());
    return true;
  }

  bool JsonHandler<JsonObject>::Bool(bool b) {

    if (_innerHandler) {
      _innerHandler->Bool(b);
      return true;
    }
    _value.insert({_currentKey, std::make_any<bool>(b)});
    return true;
  }

  bool JsonHandler<JsonObject>::Null() {

    if (_innerHandler) {
      _innerHandler->Null();
      return true;
    }
    _value.insert({_currentKey, std::any()});
    return true;
  }

  bool JsonHandler<JsonObject>::Int(int32_t i) {

    if (_innerHandler) {
      _innerHandler->Int(i);
      return true;
    }
    _value.insert({_currentKey, std::make_any<int32_t>(i)});
    return true;
  }

  bool JsonHandler<JsonArray>::Bool(bool b) {

    if (_innerHandler) {
      _innerHandler->Bool(b);
      return true;
    }
    _value.push_back(std::make_any<bool>(b));
    return true;
  }

  bool JsonHandler<JsonArray>::Int(int32_t i) {

    if (_innerHandler) {
      _innerHandler->Int(i);
      return true;
    }
    _value.push_back(std::make_any<int32_t>(i));
    return true;
  }

  bool JsonHandler<JsonArray>::Uint(uint32_t u) {

    if (_innerHandler) {
      _innerHandler->Uint(u);
      return true;
    }
    _value.push_back(std::make_any<uint32_t>(u));
    return true;
  }

  bool JsonHandler<JsonObject>::Double(double d) {

    if (_innerHandler) {
      _innerHandler->Double(d);
      return true;
    }
    _value.insert({_currentKey, std::make_any<double>(d)});
    return true;
  }

  bool JsonHandler<JsonObject>::String(const char *str, rapidjson::SizeType length, bool copy) {

    if (_innerHandler) {
      _innerHandler->String(str, length, copy);
      return true;
    }
    _value.insert({_currentKey, std::make_any<std::string>(str)});
    return true;
  }

  bool JsonHandler<JsonObject>::EndObject(rapidjson::SizeType memberCount) {

    if (_counter == 1 && _innerHandler) {

      _value.insert({_currentKey, std::move(_innerHandler->value())});
      delete _innerHandler;
      _innerHandler = nullptr;
    } else if (_counter > 1 && _innerHandler) {
      _innerHandler->EndObject(memberCount);
    }
    _counter--;
    return true;
  }

  bool JsonHandler<JsonObject>::EndArray(rapidjson::SizeType elementCount) {

    if (_counter == 1 && _innerHandler) {

      _value.insert({_currentKey, std::move(_innerHandler->value())});
      delete _innerHandler;
      _innerHandler = nullptr;
    } else if (_counter > 1 && _innerHandler) {
      _innerHandler->EndArray(elementCount);
    }
    _counter--;
    return true;
  }

  std::any JsonHandler<JsonObject>::value() {

    return _value;
  }

  bool JsonHandler<JsonObject>::Key(const char *str, rapidjson::SizeType length, bool copy) {

    if (_innerHandler) {
      _innerHandler->Key(str, length, copy);
      return true;
    }
    _currentKey = std::string(str);
    return true;
  }

  bool JsonHandler<JsonObject>::RawNumber(const char *str, rapidjson::SizeType length, bool copy) {

    if (_innerHandler) {
      _innerHandler->RawNumber(str, length, copy);
      return true;
    }
    return true;
  }

  bool JsonHandler<JsonObject>::Uint64(uint64_t u) {

    if (_innerHandler) {
      _innerHandler->Uint64(u);
      return true;
    }
    _value.insert({_currentKey, std::make_any<uint64_t>(u)});
    return true;
  }

  bool JsonHandler<JsonObject>::Int64(int64_t i) {

    if (_innerHandler) {
      _innerHandler->Int64(i);
      return true;
    }
    _value.insert({_currentKey, std::make_any<int64_t>(i)});
    return true;
  }

  bool JsonHandler<JsonObject>::Uint(uint32_t u) {

    if (_innerHandler) {
      _innerHandler->Uint(u);
      return true;
    }
    _value.insert({_currentKey, std::make_any<uint32_t>(u)});
    return true;
  }

  bool JsonHandler<JsonArray>::Int64(int64_t i) {

    if (_innerHandler) {
      _innerHandler->Int64(i);
      return true;
    }
    _value.push_back(std::make_any<int64_t>(i));
    return true;
  }

  bool JsonHandler<JsonArray>::Uint64(uint64_t u) {

    if (_innerHandler) {
      _innerHandler->Uint64(u);
      return true;
    }
    _value.push_back(std::make_any<uint64_t>(u));
    return true;
  }

  bool JsonHandler<JsonArray>::Double(double d) {

    if (_innerHandler) {
      _innerHandler->Double(d);
      return true;
    }
    _value.push_back(std::make_any<double>(d));
    return true;
  }

  bool JsonHandler<JsonArray>::RawNumber(const char *str, rapidjson::SizeType length, bool copy) {

    if (_innerHandler) {
      _innerHandler->RawNumber(str, length, copy);
      return true;
    }
    return true;
  }

  bool JsonHandler<JsonArray>::String(const char *str, rapidjson::SizeType length, bool copy) {

    if (_innerHandler) {
      _innerHandler->String(str, length, copy);
      return true;
    }
    _value.push_back(std::make_any<std::string>(str));
    return true;
  }

  bool JsonHandler<JsonArray>::Key(const char *str, rapidjson::SizeType length, bool copy) {

    if (_innerHandler) {
      _innerHandler->Key(str, length, copy);
      return true;
    }
    return true;
  }

  bool JsonHandler<JsonArray>::EndObject(rapidjson::SizeType memberCount) {

    if (_counter == 1 && _innerHandler) {

      _value.push_back(std::move(_innerHandler->value()));
      delete _innerHandler;
      _innerHandler = nullptr;
    } else if (_counter > 1 && _innerHandler) {
      _innerHandler->EndObject(memberCount);
    }
    _counter--;
    return true;
  }

  bool JsonHandler<JsonArray>::EndArray(rapidjson::SizeType elementCount) {

    if (_counter == 1 && _innerHandler) {

      _value.push_back(std::move(_innerHandler->value()));
      delete _innerHandler;
      _innerHandler = nullptr;
    } else if (_counter > 1 && _innerHandler) {
      _innerHandler->EndArray(elementCount);
    }
    _counter--;
    return true;
  }

  std::any JsonHandler<JsonArray>::value() {

    return _value;
  }

  std::any JsonReader::read(const std::string &json) {
    JsonHandler<JsonValue> handler;
    rapidjson::Reader reader;
    rapidjson::StringStream ss(json.c_str());
    reader.Parse(ss, handler);

    return handler.value();
  }

  void JsonReader::readObject(const std::string &json, AbstractMetaStruct &ms) {
    std::any obj = read(json);
    JsonObject m = std::any_cast<JsonObject const &>(obj);
    ms.setValue("json", m);
  }
}
