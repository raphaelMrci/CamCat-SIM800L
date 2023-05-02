#include <SD.h>
#include <string>
#include "Camcat.hpp"

namespace Camcat {
    class SDReader {
        public:
            SDReader();

            Camcat::Config readConfig();
            String readFile(String path);

        private:
            std::string _defaultConfig =
            "{\n"
            "    \"ssid\": \"\",\n"
            "    \"password\": \"\",\n"
            "    \"apn\": \"\",\n"
            "    \"mmsc_url\": \"\",\n"
            "    \"mmsc_proxy\": \"\",\n"
            "    \"pin_code\": \"\"\n"
            "}\n";
    };
} // namespace Camcat
