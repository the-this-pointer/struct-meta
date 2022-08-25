#include "metawriter.h"

namespace thisptr::Meta::Json {

  std::string JsonWriter::write(std::any &obj) {
    if (_s.GetLength() > 0)
      _s.Clear();
    processType(obj);
    return _s.GetString();
  }

  rapidjson::Writer <rapidjson::StringBuffer> &JsonWriter::writer() {
    return _writer;
  }

  void JsonWriter::processType(const std::any &a) {
    if (const auto it = _typeSerializers.find(std::type_index(a.type()));
        it != _typeSerializers.cend()) {
      it->second(a);
    } else {
      std::cout << "Unregistered type "<< std::quoted(a.type().name()) << std::endl;
    }
  }

}
