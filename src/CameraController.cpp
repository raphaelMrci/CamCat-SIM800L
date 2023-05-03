#include "CameraController.hpp"
#include <EEPROM.h>
#include "Camcat.hpp"
#include "FS.h"               // SD Card ESP32
#include "soc/soc.h"          // Disable brownout problems
#include "SD_MMC.h"           // SD Card ESP32
#include "driver/rtc_io.h"
#include "soc/rtc_cntl_reg.h" // Disable brownout problems

Camcat::CameraController::CameraController()
{
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector

    // Init built-in LED
    pinMode(4, OUTPUT);

    _cameraConfig.ledc_channel = LEDC_CHANNEL_0;
    _cameraConfig.ledc_timer = LEDC_TIMER_0;
    _cameraConfig.pin_d0 = Y2_GPIO_NUM;
    _cameraConfig.pin_d1 = Y3_GPIO_NUM;
    _cameraConfig.pin_d2 = Y4_GPIO_NUM;
    _cameraConfig.pin_d3 = Y5_GPIO_NUM;
    _cameraConfig.pin_d4 = Y6_GPIO_NUM;
    _cameraConfig.pin_d5 = Y7_GPIO_NUM;
    _cameraConfig.pin_d6 = Y8_GPIO_NUM;
    _cameraConfig.pin_d7 = Y9_GPIO_NUM;
    _cameraConfig.pin_xclk = XCLK_GPIO_NUM;
    _cameraConfig.pin_pclk = PCLK_GPIO_NUM;
    _cameraConfig.pin_vsync = VSYNC_GPIO_NUM;
    _cameraConfig.pin_href = HREF_GPIO_NUM;
    _cameraConfig.pin_sccb_sda = SIOD_GPIO_NUM;
    _cameraConfig.pin_sccb_sda = SIOC_GPIO_NUM;
    _cameraConfig.pin_pwdn = PWDN_GPIO_NUM;
    _cameraConfig.pin_reset = RESET_GPIO_NUM;
    _cameraConfig.xclk_freq_hz = 20000000;
    _cameraConfig.pixel_format = PIXFORMAT_JPEG;

    if (psramFound()) {
        _cameraConfig.frame_size =
        FRAMESIZE_UXGA; // FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
        _cameraConfig.jpeg_quality = 10;
        _cameraConfig.fb_count = 2;
    } else {
        _cameraConfig.frame_size = FRAMESIZE_SVGA;
        _cameraConfig.jpeg_quality = 12;
        _cameraConfig.fb_count = 1;
    }

    esp_err_t err = esp_camera_init(&_cameraConfig);
    if (err != ESP_OK) {
        CAMCAT_DEBUG_PRINTF("Camera init failed with error 0x%x", err);
        return;
    }

    // initialize EEPROM with predefined size
    EEPROM.begin(EEPROM_SIZE);
    _pictureNumber = EEPROM.read(0) + 1;
}

void Camcat::CameraController::takePicture()
{
    camera_fb_t *fb = NULL;
    uint8_t cardType = SD_MMC.cardType();
    String path = "/picture" + String(_pictureNumber) + ".jpg";

    if (cardType == CARD_NONE) {
        CAMCAT_DEBUG_PRINTLN("No SD Card attached");
        return;
    }

    fs::FS &fs = SD_MMC;
    File file = fs.open(path.c_str(), FILE_WRITE);
    if (!file) {
        Serial.println("Failed to open file in writing mode");
    } else {
        file.write(fb->buf, fb->len); // payload (image), payload length
        CAMCAT_DEBUG_PRINTF("Saved file to path: %s\n", path.c_str());
        EEPROM.write(0, _pictureNumber);
        EEPROM.commit();
    }
    file.close();
    esp_camera_fb_return(fb);
    digitalWrite(4, LOW);
}
