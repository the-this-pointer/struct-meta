#include "metautils.h"

namespace thisptr {
    namespace Utilities {
        std::vector<std::string_view> split(std::string_view str, char delim /* = ',' */)
        {
            std::vector<std::string_view> items{};
            std::size_t start = 0, end = 0;

            for (std::size_t i = 0; end != std::string_view::npos; i++)
            {
                end = std::string_view::npos;
                for (std::size_t j = start; j < str.length(); j++)
                {
                    if (str[j] == delim)
                    {
                        end = j;
                        break;
                    }
                }

                items.push_back(str.substr(start, end - start));
                start = end + 1;
            }

            return items;
        }
    }
}
