/**
    TODO: sql lib, rest lib
*/

#include <iostream>
#include <meta.h>
#include <metawriter.h>
#include <metareader.h>
#include <vector>

using namespace std;
using namespace thisptr::meta;

class MetaStruct1: public MetaStruct {
public:
  MetaField<int32_t, decltype("json:field_name"_meta)> _int {this};
  MetaField<int32_t, decltype("json:field_name2"_meta)> _int2 {this};
  MetaField<bool, decltype("json:field_name3"_meta)> _bol3 {this};
  MetaField<std::string, decltype("json:field_name4"_meta)> _str4 {this};
};

class MetaStruct2: public MetaStruct {
public:
  MetaField<MetaStruct1, decltype("json:meta_struct3"_meta)> _ms3 {this};
  MetaField<std::vector<int32_t>, decltype("json:field_name5"_meta)> _vint {this};
  MetaField<std::map<std::string, int32_t>, decltype("json:field_name6"_meta)> _vmap {this};
  MetaField<double, decltype("json:dbl"_meta)> _dbl {this};
  MetaField<std::vector<std::string>, decltype("json:vstr"_meta)> _vstr{this};
};

int main()
{
  DBG_INIT;
  MetaStruct2 ms2;

  ms2._ms3.val()._bol3 = true;
  ms2._ms3.val()._int = 10;
  ms2._ms3.val()._int2 = 20;
  ms2._ms3.val()._str4 = "salam";
  ms2._vint.val() = {10, 20, 30, 55, };
  ms2._vmap.val() = { {"1", 2}, {"another", 5}, };
  ms2._dbl.val() = 2.4;
  ms2._vstr.val() = {"1", "22", "333",};

  auto* writer2 = new json::JsonWriter;
  // Meta Writer Custom Type Registration
  writer2->registerTypeSerializer<MetaStruct1>([writer2](auto x) {
    auto* ms = static_cast<AbstractMetaStruct*>(&x);
    writer2->processType(ms);
  });

  auto* _ms2 = static_cast<AbstractMetaStruct*>(&ms2);
  std::any _b = std::make_any<AbstractMetaStruct*>(_ms2);
  std::string json = writer2->write(_b);
  cout << json << endl << endl;

  auto* reader = new json::JsonReader;
  std::any obj = reader->read(json);

  MetaStruct2 ms3;
  auto m = std::any_cast<std::map<std::string, std::any>>(obj);
  ms3.setValue("json", m);

  //get json again to test values!:
  auto* writer = new json::JsonWriter;
  // Meta Writer Custom Type Registration
  writer->registerTypeSerializer<MetaStruct1>([writer](auto x) {
    auto* ms = static_cast<AbstractMetaStruct*>(&x);
    writer->processType(ms);
  });
  auto* _ms4 = static_cast<AbstractMetaStruct*>(&ms3);
  std::any _d = std::make_any<AbstractMetaStruct*>(_ms4);
  std::string jsont = writer->write(_d);
  cout << "Decoded json: " << jsont << endl << endl;

  return 0;
}
