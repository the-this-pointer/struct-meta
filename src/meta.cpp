#include "meta.h"

namespace thisptr {
    namespace meta {
        namespace any {
            std::unordered_map<
                std::type_index, std::function<void(void* ptr, std::any const&)>>
                g_anyTypeSerializers {
                    AnyTypeDeSerializer<bool>([](void* ptr, std::any const &a){ *((bool *)ptr) = std::any_cast<bool const&>(a); }),
                    AnyTypeDeSerializer<int32_t>([](void* ptr, std::any const &a){ *((int32_t *)ptr) = std::any_cast<uint32_t const&>(a); }),
                    AnyTypeDeSerializer<uint32_t>([](void* ptr, std::any const &a){ *((uint32_t *)ptr) = std::any_cast<uint32_t const&>(a); }),
                    AnyTypeDeSerializer<int64_t>([](void* ptr, std::any const &a){ *((int64_t *)ptr) = std::any_cast<int64_t const&>(a); }),
                    AnyTypeDeSerializer<uint64_t>([](void* ptr, std::any const &a){ *((uint64_t *)ptr) = std::any_cast<uint64_t const&>(a); }),
                    AnyTypeDeSerializer<float>([](void* ptr, std::any const &a){ *((float *)ptr) = std::any_cast<double const&>(a); }),
                    AnyTypeDeSerializer<double>([](void* ptr, std::any const &a){ *((double *)ptr) = std::any_cast<double const&>(a); }),
                    AnyTypeDeSerializer<std::string>([](void* ptr, std::any const &a){ *((std::string *)ptr) = std::any_cast<std::string const&>(a); }),
                    AnyTypeDeSerializer<std::vector<bool>>([](void* ptr, std::any const &a){
                        std::vector<bool>* vp = (std::vector<bool>*)ptr;
                        std::vector<std::any> v = std::any_cast<std::vector<std::any>>(a);

                        for (const auto& item: v) {
                            vp->push_back(std::any_cast<bool const&>(item));
                        }
                    }),
                    AnyTypeDeSerializer<std::vector<int32_t>>([](void* ptr, std::any const &a){
                        std::vector<int32_t>* vp = (std::vector<int32_t>*)ptr;
                        std::vector<std::any> v = std::any_cast<std::vector<std::any>>(a);

                        // check for any type name, maybe i (int32) or j (uint32)
                        for (const auto& item: v) {
                            vp->push_back((int32_t)std::any_cast<uint32_t const&>(item));
                        }
                    }),
                    AnyTypeDeSerializer<std::vector<uint32_t>>([](void* ptr, std::any const &a){
                        std::vector<uint32_t>* vp = (std::vector<uint32_t>*)ptr;
                        std::vector<std::any> v = std::any_cast<std::vector<std::any>>(a);

                        for (const auto& item: v) {
                            vp->push_back(std::any_cast<uint32_t const&>(item));
                        }
                    }),
                    AnyTypeDeSerializer<std::vector<int64_t>>([](void* ptr, std::any const &a){
                        std::vector<int64_t>* vp = (std::vector<int64_t>*)ptr;
                        std::vector<std::any> v = std::any_cast<std::vector<std::any>>(a);

                        // check for any type name, maybe i (int32) or j (uint32)
                        for (const auto& item: v) {
                            vp->push_back((int64_t)std::any_cast<uint64_t const&>(item));
                        }
                    }),
                    AnyTypeDeSerializer<std::vector<uint64_t>>([](void* ptr, std::any const &a){
                        std::vector<uint64_t>* vp = (std::vector<uint64_t>*)ptr;
                        std::vector<std::any> v = std::any_cast<std::vector<std::any>>(a);

                        // check for any type name, maybe i (int32) or j (uint32)
                        for (const auto& item: v) {
                            vp->push_back((uint64_t)std::any_cast<uint64_t const&>(item));
                        }
                    }),
                    AnyTypeDeSerializer<std::vector<float>>([](void* ptr, std::any const &a){
                        std::vector<float>* vp = (std::vector<float>*)ptr;
                        std::vector<std::any> v = std::any_cast<std::vector<std::any>>(a);

                        for (const auto& item: v) {
                            vp->push_back((float)std::any_cast<float const&>(item));
                        }
                    }),
                    AnyTypeDeSerializer<std::vector<double>>([](void* ptr, std::any const &a){
                        std::vector<double>* vp = (std::vector<double>*)ptr;
                        std::vector<std::any> v = std::any_cast<std::vector<std::any>>(a);

                        for (const auto& item: v) {
                            vp->push_back(std::any_cast<double const&>(item));
                        }
                    }),
                    AnyTypeDeSerializer<std::vector<std::string>>([](void* ptr, std::any const &a){
                        std::vector<std::string>* vp = (std::vector<std::string>*)ptr;
                        std::vector<std::any> v = std::any_cast<std::vector<std::any>>(a);

                        for (const auto& item: v) {
                            vp->push_back(std::any_cast<std::string const&>(item));
                        }
                    }),
                    AnyTypeDeSerializer<std::map<std::string, bool>>([](void* ptr, std::any const &a){
                        std::map<std::string, bool>* mp = (std::map<std::string, bool>*)ptr;
                        std::map<std::string, std::any> m = std::any_cast<std::map<std::string, std::any>>(a);

                        for (const auto& item: m) {
                            mp->insert({item.first, std::any_cast<bool const&>(item.second)});
                        }
                    }),
                    AnyTypeDeSerializer<std::map<std::string, int32_t>>([](void* ptr, std::any const &a){
                        std::map<std::string, int32_t>* mp = (std::map<std::string, int32_t>*)ptr;
                        std::map<std::string, std::any> m = std::any_cast<std::map<std::string, std::any>>(a);

                        // check for any type name, maybe i (int32) or j (uint32)
                        for (const auto& item: m) {
                            mp->insert({item.first, (int32_t)std::any_cast<uint32_t const&>(item.second)});
                        }
                    }),
                    AnyTypeDeSerializer<std::map<std::string, uint32_t>>([](void* ptr, std::any const &a){
                        std::map<std::string, uint32_t>* mp = (std::map<std::string, uint32_t>*)ptr;
                        std::map<std::string, std::any> m = std::any_cast<std::map<std::string, std::any>>(a);

                        for (const auto& item: m) {
                            mp->insert({item.first, std::any_cast<uint32_t const&>(item.second)});
                        }
                    }),
                    AnyTypeDeSerializer<std::map<std::string, int64_t>>([](void* ptr, std::any const &a){
                        std::map<std::string, int64_t>* mp = (std::map<std::string, int64_t>*)ptr;
                        std::map<std::string, std::any> m = std::any_cast<std::map<std::string, std::any>>(a);

                        // check for any type name, maybe i (int32) or j (uint32)
                        for (const auto& item: m) {
                            mp->insert({item.first, (int64_t)std::any_cast<uint64_t const&>(item.second)});
                        }
                    }),
                    AnyTypeDeSerializer<std::map<std::string, uint64_t>>([](void* ptr, std::any const &a){
                        std::map<std::string, uint64_t>* mp = (std::map<std::string, uint64_t>*)ptr;
                        std::map<std::string, std::any> m = std::any_cast<std::map<std::string, std::any>>(a);

                        for (const auto& item: m) {
                            mp->insert({item.first, std::any_cast<uint64_t const&>(item.second)});
                        }
                    }),
                    AnyTypeDeSerializer<std::map<std::string, float>>([](void* ptr, std::any const &a){
                        std::map<std::string, float>* mp = (std::map<std::string, float>*)ptr;
                        std::map<std::string, std::any> m = std::any_cast<std::map<std::string, std::any>>(a);

                        for (const auto& item: m) {
                            mp->insert({item.first, (float)std::any_cast<double const&>(item.second)});
                        }
                    }),
                    AnyTypeDeSerializer<std::map<std::string, double>>([](void* ptr, std::any const &a){
                        std::map<std::string, double>* mp = (std::map<std::string, double>*)ptr;
                        std::map<std::string, std::any> m = std::any_cast<std::map<std::string, std::any>>(a);

                        for (const auto& item: m) {
                            mp->insert({item.first, std::any_cast<double const&>(item.second)});
                        }
                    }),
                    AnyTypeDeSerializer<std::map<std::string, std::string>>([](void* ptr, std::any const &a){
                        std::map<std::string, std::string>* mp = (std::map<std::string, std::string>*)ptr;
                        std::map<std::string, std::any> m = std::any_cast<std::map<std::string, std::any>>(a);

                        for (const auto& item: m) {
                            mp->insert({item.first, std::any_cast<std::string const&>(item.second)});
                        }
                    }),
                };
        }

      void MetaStruct::registerField(AbstractMetaField *field) {
        _fields.push_back(field);
      }

      void MetaStruct::unregisterField(AbstractMetaField *field) {
        std::remove(_fields.begin(), _fields.end(), field);
      }

      std::vector<AbstractMetaField *> MetaStruct::members() const {
        return _fields;
      }

      void MetaStruct::setValue(const std::string &metaFieldName, std::map<std::string, std::any> values) {
        for(auto& pair: values) {
          AbstractMetaField* f = getFieldByMeta(metaFieldName, pair.first);
          if (f == nullptr)
            continue;
          f->setValue(metaFieldName, pair.second);
        }
      }

      AbstractMetaField *MetaStruct::getFieldByMeta(const std::string &metaFieldName, const std::string &metaFieldValue) {
        for (const auto& f: _fields) {
          if (f->meta(metaFieldName) == metaFieldValue)
            return f;
        }
        return nullptr;
      }
    }
}
