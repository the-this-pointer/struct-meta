#include "metareader.h"

namespace thisptr::meta::json {

  bool JsonHandler<JsonValue>::StartObject() {
    DBG_FUNC
    if (_counter > 0 && _innerHandler) {
      _innerHandler->StartObject();
    } else if (!_innerHandler) {
      _innerHandler = new JsonHandler<JsonObject>();
    }
    _counter++;
    return true;
  }

  bool JsonHandler<JsonValue>::StartArray() {
    DBG_FUNC
    if (_counter > 0 && _innerHandler) {
      _innerHandler->StartArray();
    } else if (!_innerHandler) {
      _innerHandler = new JsonHandler<JsonArray>();
    }
    _counter++;
    return true;
  }

  bool JsonHandler<JsonValue>::Bool(bool b) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Bool(b);
      return true;
    }
    _value = std::make_any<bool>(b);
    return true;
  }

  bool JsonHandler<JsonValue>::Null() {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Null();
      return true;
    }
    _value.reset();
    return true;
  }

  bool JsonHandler<JsonValue>::Int(int32_t i) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Int(i);
      return true;
    }
    _value = std::make_any<int32_t>(i);
    return true;
  }

  bool JsonHandler<JsonValue>::Double(double d) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Double(d);
      return true;
    }
    _value = std::make_any<double>(d);
    return true;
  }

  bool JsonHandler<JsonValue>::String(const char *str, rapidjson::SizeType length, bool copy) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->String(str, length, copy);
      return true;
    }
    _value = std::make_any<std::string>(str);
    return true;
  }

  bool JsonHandler<JsonValue>::EndObject(rapidjson::SizeType memberCount) {
    DBG_FUNC
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
    DBG_FUNC
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
    DBG_FUNC
    return _value;
  }

  bool JsonHandler<JsonValue>::Key(const char *str, rapidjson::SizeType length, bool copy) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Key(str, length, copy);
      return true;
    }
    _currentKey = std::string(str);
    return true;
  }

  bool JsonHandler<JsonValue>::RawNumber(const char *str, rapidjson::SizeType length, bool copy) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->RawNumber(str, length, copy);
      return true;
    }
    return true;
  }

  bool JsonHandler<JsonValue>::Uint64(uint64_t u) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Uint64(u);
      return true;
    }
    _value = std::make_any<uint64_t>(u);
    return true;
  }

  bool JsonHandler<JsonValue>::Int64(int64_t i) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Int64(i);
      return true;
    }
    _value = std::make_any<int64_t>(i);
    return true;
  }

  bool JsonHandler<JsonValue>::Uint(uint32_t u) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Uint(u);
      return true;
    }
    _value = std::make_any<uint32_t>(u);
    return true;
  }

  bool JsonHandler<JsonObject>::StartObject() {
    DBG_FUNC
    if (_counter > 0 && _innerHandler) {
      _innerHandler->StartObject();
    } else if (!_innerHandler) {
      _innerHandler = new JsonHandler<JsonObject>();
    }
    _counter++;
    return true;
  }

  bool JsonHandler<JsonObject>::StartArray() {
    DBG_FUNC
    if (_counter > 0 && _innerHandler) {
      _innerHandler->StartArray();
    } else if (!_innerHandler) {
      _innerHandler = new JsonHandler<JsonArray>();
    }
    _counter++;
    return true;
  }

  bool JsonHandler<JsonArray>::StartObject() {
    DBG_FUNC
    if (_counter > 0 && _innerHandler) {
      _innerHandler->StartObject();
    } else if (!_innerHandler) {
      _innerHandler = new JsonHandler<JsonObject>();
    }
    _counter++;
    return true;
  }

  bool JsonHandler<JsonArray>::StartArray() {
    DBG_FUNC
    if (_counter > 0 && _innerHandler) {
      _innerHandler->StartArray();
    } else if (!_innerHandler) {
      _innerHandler = new JsonHandler<JsonArray>();
    }
    _counter++;
    return true;
  }

  bool JsonHandler<JsonArray>::Null() {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Null();
      return true;
    }
    _value.push_back(std::any());
    return true;
  }

  bool JsonHandler<JsonObject>::Bool(bool b) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Bool(b);
      return true;
    }
    _value.insert({_currentKey, std::make_any<bool>(b)});
    return true;
  }

  bool JsonHandler<JsonObject>::Null() {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Null();
      return true;
    }
    _value.insert({_currentKey, std::any()});
    return true;
  }

  bool JsonHandler<JsonObject>::Int(int32_t i) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Int(i);
      return true;
    }
    _value.insert({_currentKey, std::make_any<int32_t>(i)});
    return true;
  }

  bool JsonHandler<JsonArray>::Bool(bool b) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Bool(b);
      return true;
    }
    _value.push_back(std::make_any<bool>(b));
    return true;
  }

  bool JsonHandler<JsonArray>::Int(int32_t i) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Int(i);
      return true;
    }
    _value.push_back(std::make_any<int32_t>(i));
    return true;
  }

  bool JsonHandler<JsonArray>::Uint(uint32_t u) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Uint(u);
      return true;
    }
    _value.push_back(std::make_any<uint32_t>(u));
    return true;
  }

  bool JsonHandler<JsonObject>::Double(double d) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Double(d);
      return true;
    }
    _value.insert({_currentKey, std::make_any<double>(d)});
    return true;
  }

  bool JsonHandler<JsonObject>::String(const char *str, rapidjson::SizeType length, bool copy) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->String(str, length, copy);
      return true;
    }
    _value.insert({_currentKey, std::make_any<std::string>(str)});
    return true;
  }

  bool JsonHandler<JsonObject>::EndObject(rapidjson::SizeType memberCount) {
    DBG_FUNC
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
    DBG_FUNC
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
    DBG_FUNC
    return _value;
  }

  bool JsonHandler<JsonObject>::Key(const char *str, rapidjson::SizeType length, bool copy) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Key(str, length, copy);
      return true;
    }
    _currentKey = std::string(str);
    return true;
  }

  bool JsonHandler<JsonObject>::RawNumber(const char *str, rapidjson::SizeType length, bool copy) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->RawNumber(str, length, copy);
      return true;
    }
    return true;
  }

  bool JsonHandler<JsonObject>::Uint64(uint64_t u) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Uint64(u);
      return true;
    }
    _value.insert({_currentKey, std::make_any<uint64_t>(u)});
    return true;
  }

  bool JsonHandler<JsonObject>::Int64(int64_t i) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Int64(i);
      return true;
    }
    _value.insert({_currentKey, std::make_any<int64_t>(i)});
    return true;
  }

  bool JsonHandler<JsonObject>::Uint(uint32_t u) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Uint(u);
      return true;
    }
    _value.insert({_currentKey, std::make_any<uint32_t>(u)});
    return true;
  }

  bool JsonHandler<JsonArray>::Int64(int64_t i) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Int64(i);
      return true;
    }
    _value.push_back(std::make_any<int64_t>(i));
    return true;
  }

  bool JsonHandler<JsonArray>::Uint64(uint64_t u) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Uint64(u);
      return true;
    }
    _value.push_back(std::make_any<uint64_t>(u));
    return true;
  }

  bool JsonHandler<JsonArray>::Double(double d) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Double(d);
      return true;
    }
    _value.push_back(std::make_any<double>(d));
    return true;
  }

  bool JsonHandler<JsonArray>::RawNumber(const char *str, rapidjson::SizeType length, bool copy) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->RawNumber(str, length, copy);
      return true;
    }
    return true;
  }

  bool JsonHandler<JsonArray>::String(const char *str, rapidjson::SizeType length, bool copy) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->String(str, length, copy);
      return true;
    }
    _value.push_back(std::make_any<std::string>(str));
    return true;
  }

  bool JsonHandler<JsonArray>::Key(const char *str, rapidjson::SizeType length, bool copy) {
    DBG_FUNC
    if (_innerHandler) {
      _innerHandler->Key(str, length, copy);
      return true;
    }
    return true;
  }

  bool JsonHandler<JsonArray>::EndObject(rapidjson::SizeType memberCount) {
    DBG_FUNC
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
    DBG_FUNC
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
    DBG_FUNC
    return _value;
  }

  std::any JsonReader::read(const std::string &json) {
    DBG_FUNC
    JsonHandler<JsonValue> handler;
    rapidjson::Reader reader;
    rapidjson::StringStream ss(json.c_str());
    reader.Parse(ss, handler);

    return handler.value();
  }

  void JsonReader::readObject(const std::string &json, AbstractMetaStruct &ms) {
    DBG_FUNC
    std::any obj = read(json);
    JsonObject m = std::any_cast<JsonObject const &>(obj);
    ms.setValue("json", m);
  }
}
