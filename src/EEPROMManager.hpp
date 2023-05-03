#pragma once

#include <Arduino.h>

namespace Camcat {
    class EEPROMManager {
        public:
            EEPROMManager() = default;

            void writeString(int addrOffset, String data);
            String readString(int addrOffset);

            void writeInt(int addrOffset, int data);
            int readInt(int addrOffset);

        private:
            int _addrOffset = 0;
    };
} // namespace Camcat
