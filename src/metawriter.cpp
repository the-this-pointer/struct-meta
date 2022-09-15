#include "metawriter.h"

namespace thisptr::meta::json {

  std::string JsonWriter::write(std::any &obj) {
    DBG_FUNC
    if (_s.GetLength() > 0)
      _s.Clear();
    processType(obj);
    return _s.GetString();
  }

  rapidjson::Writer <rapidjson::StringBuffer> &JsonWriter::writer() {
    DBG_FUNC
    return _writer;
  }

  void JsonWriter::processType(const std::any &a) {
    DBG_FUNC
    if (const auto it = _typeSerializers.find(std::type_index(a.type()));
        it != _typeSerializers.cend()) {
      it->second(a);
    } else {
      std::stringstream ss;
      ss <<  "Unregistered type "<< std::quoted(a.type().name()) << std::endl;
      DBG_I(ss.str());
    }
  }

}
