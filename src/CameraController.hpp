#pragma once

#include "esp_camera.h"

#define EEPROM_SIZE 1

namespace Camcat {

    class CameraController {
        public:
            CameraController();

            void takePicture();

        private:
            camera_config_t _cameraConfig;
            int _pictureNumber = 0;
    };
} // namespace Camcat
