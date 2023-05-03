#pragma once

#include "EEPROMManager.hpp"
#include "esp_camera.h"

namespace Camcat {

    class CameraController {
        public:
            CameraController();
            ~CameraController();

            void takePicture();

        private:
            camera_config_t _cameraConfig;
            EEPROMManager *_eepromManager;
            int _pictureNumber = 0;
    };
} // namespace Camcat
