#include "SIM900.hpp"
#include <Arduino.h>
#include "Camcat.hpp"

Camcat::Sim900::Sim900(Camcat::Config &config)
{
    String response;

    _config = config;

    Serial2.begin(
    9600, SERIAL_8N1, CAMCAT_SIM800L_RX_PIN, CAMCAT_SIM800L_TX_PIN);
    while (!Serial2) {
        delay(10);
    }
    Serial2.println("AT\r");
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("SIM INIT failed");
        return;
    }
    CAMCAT_DEBUG_PRINTLN("SIM INIT OK");
    _setMMSConfig();
}

void Camcat::Sim900::_unlockSIM()
{
    String response;

    _sendATCommand("CPIN?");
    delay(1000);
    response = readSerial();
    if (response.indexOf("READY") == -1) {
        CAMCAT_DEBUG_PRINTLN("SIM PIN required");
        Serial2.printf("AT+CPIN=\"%s\"\r\n", _config.SIMPinCode);
        delay(1000);
        response = readSerial();
        if (response.indexOf("OK") == -1) {
            CAMCAT_DEBUG_PRINTLN("SIM PIN failed");
            return;
        }
        CAMCAT_DEBUG_PRINTLN("SIM PIN OK");
    }
}

void Camcat::Sim900::_setMMSConfig()
{
    // Get the ICCID of the SIM card and parse it to know wich operator we are
    // and set the correct MMS config for it
    _sendATCommand("CCID");
    delay(1000);
    String response = readSerial();

    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("CCID failed");
        return;
    }

    // Stop on the first space or carriage return character
    String iccid = response.substring(
    0, response.indexOf("\n")); // TODO: check if it is not \r
    String operatorPrefix = iccid.substring(0, 6);

    if (operatorPrefix == "893320") { // Bouygues Telecom France
        _mmsConfig.apn = "mmsbouygtel.com";
        _mmsConfig.mmscurl = "http://mms.bouyguestelecom.fr/mms/wapenc";
        _mmsConfig.mmsproto = "62.201.129.226";
    } else if (operatorPrefix == "893301") { // Orange France
        _mmsConfig.apn = "orange.acte";
        _mmsConfig.mmscurl = "http://mms.orange.fr";
        _mmsConfig.mmsproto = "192.168.10.200";
    } else if (operatorPrefix == "883310") { // SFR France
        _mmsConfig.apn = "sl2sfr";
        _mmsConfig.mmscurl = "http://mms1";
        _mmsConfig.mmsproto = "10.151.0.1";
    }
}

void Camcat::Sim900::_sendATCommand(String command)
{
    String result = "AT+" + command + "\r";
    Serial2.println(result);
}

String Camcat::Sim900::readSerial()
{
    String response = "";

    while (Serial2.available()) {
        response += (char) Serial2.read();
    }
    return response;
}

void Camcat::Sim900::sendSMS(String number, String text)
{
    _sendATCommand("CMGF=1");                  // set SMS mode to text
    delay(100);
    _sendATCommand("CMGS=\"" + number + "\""); // send SMS command
    delay(100);
    _sendATCommand(text);                      // message to send
    delay(100);
    Serial2.write(26); // ASCII equivalent of Ctrl+Z (end of message)
    delay(100);
}

void Camcat::Sim900::sendMMS(String number, String text, String image)
{
    String response = "";
    // Envoi de MMS avec paramètre APN La poste mobile
    // Regarder sur le site des opérateurs pour les paramètres APN, MMSCURL,
    // CMMSPROTO

    _sendATCommand("CMMSINIT"); // added \r
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("CMMSINIT failed");
        return;
    }
    _sendATCommand("CMMSCURL=\"" + _mmsConfig.mmscurl + "\"");
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("CMMSCURL failed");
        return;
    }
    _sendATCommand("CMMSCID=1");
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("CMMSCID failed");
        return;
    }
    _sendATCommand("CMMSPROTO=\"" + _mmsConfig.mmsproto + "\",8080");
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("CMMSPROTO failed");
        return;
    }
    _sendATCommand(
    "CMMSSENDCFG=6,3,0,0,2,4,2,0"); // previous config : "6,3,0,0,2,4,1,0"
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("CMMSSENDCFG failed");
        return;
    }
    _sendATCommand("SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("SAPBR CONTYPE failed");
        return;
    }
    _sendATCommand("SAPBR=3,1,\"APN\",\"" + _mmsConfig.apn + "\"");
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("SAPBR APN failed");
        return;
    }
    _sendATCommand("SAPBR=1,1");
    delay(4000);
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("SAPBR 1,1 failed");
        return;
    }
    _sendATCommand("SAPBR=2,1");
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("SAPBR 2,1 failed");
        return;
    }
    _sendATCommand("CMMSEDIT=0"); // Efface le Buffer
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("CMMSEDIT 0 failed");
        return;
    }
    _sendATCommand("CMMSEDIT=1"); // Mode Edition activé
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("CMMSEDIT 1 failed");
        return;
    }
    _sendATCommand("CMMSDOWN=\"PIC\"," + String(image.length())
    + ",20000,\"camcat.jpg\""); // Chargement de l'image
                                // "camcat.jpg" de
                                // taille 'length' octets
                                // stockée dans la carte
                                // SD
    // 20000 représente le temps qu'on laisse au système pour télécharger
    // l'image
    response = readSerial();
    if (response.indexOf("CONNECT") == -1) {
        CAMCAT_DEBUG_PRINTLN("CMMSDOWN failed. ");
        return;
    }
    Serial2.print(image);
    delay(1000);
    response = readSerial();
    _sendATCommand("CMMSRECP=\"" + number + "\""); // Numéro du destinataire
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("CMMSRECP failed");
        return;
    }
    _sendATCommand("CMMSVIEW");
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("CMMSVIEW failed");
        return;
    }
    _sendATCommand("CMMSSEND"); // Envoi du MMS
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("CMMSSEND failed");
        return;
    }
    _sendATCommand("CMMSTERM"); // Fin du MMS
    delay(1000);
    response = readSerial();
    if (response.indexOf("OK") == -1) {
        CAMCAT_DEBUG_PRINTLN("CMMSTERM failed");
        return;
    }
}
