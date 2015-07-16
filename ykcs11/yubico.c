#include "yubico.h"
#include "pkcs11.h"
#include <string.h>

#define YUBICO_MECHANISMS_NUM 5

// TODO add a type in vendor_t for SLOT | READER
static const CK_UTF8CHAR_PTR slot_description = "YubiKey Virtual Reader";
static const CK_UTF8CHAR_PTR slot_manufacturer = "Yubico";
static const CK_FLAGS slot_flags = CKF_TOKEN_PRESENT | CKF_HW_SLOT;
static const CK_VERSION slot_version = {1, 0};
static const CK_UTF8CHAR_PTR token_label = "YubiKey PIV X";
static const CK_UTF8CHAR_PTR token_manufacturer = "Yubico";
static const CK_UTF8CHAR_PTR token_model = "YubiKey MODEL";
static const CK_FLAGS token_flags = CKF_RNG | CKF_LOGIN_REQUIRED | CKF_USER_PIN_INITIALIZED | CKF_TOKEN_INITIALIZED;
static const CK_BYTE_PTR token_serial = "1234";
static const CK_MECHANISM_TYPE token_mechanisms[] = {
  CKM_RSA_PKCS_KEY_PAIR_GEN,
  CKM_RSA_PKCS,
  // CKM_RSA_PKCS_PSS,
  CKM_RSA_X_509,
  CKM_SHA1_RSA_PKCS,
  CKM_SHA256_RSA_PKCS,
  // CKM_SHA384_RSA_PKCS,
  CKM_SHA512_RSA_PKCS,
  CKM_SHA1_RSA_PKCS_PSS,
  CKM_SHA256_RSA_PKCS_PSS,
  // CKM_SHA384_RSA_PKCS_PSS,
  CKM_SHA256_RSA_PKCS_PSS,
  CKM_EC_KEY_PAIR_GEN,
  //CKM_ECDSA_KEY_PAIR_GEN, Same as CKM_EC_KEY_PAIR_GEN, deprecated in 2.11
  CKM_ECDSA,
  CKM_ECDSA_SHA1,
  CKM_ECDH1_DERIVE,
  // CKM_ECDH1_COFACTOR_DERIVE,
  CKM_SHA_1,
  CKM_SHA256,
  CKM_SHA384,
  CKM_SHA512
  // SUPPORT FOR OATH?
};
static const CK_ULONG token_mechanisms_num = sizeof(token_mechanisms) / sizeof(CK_MECHANISM_TYPE);


CK_RV YUBICO_get_slot_description(CK_UTF8CHAR_PTR str, CK_ULONG len) {

  if (strlen(slot_description) > len)
    return CKR_BUFFER_TOO_SMALL;

  memcpy(str, slot_description, strlen(slot_description));
  return CKR_OK;

}

CK_RV YUBICO_get_slot_manufacturer(CK_UTF8CHAR_PTR str, CK_ULONG len) {

  if (strlen(slot_manufacturer) > len)
    return CKR_BUFFER_TOO_SMALL;

  memcpy(str, slot_manufacturer, strlen(slot_manufacturer));
  return CKR_OK;

}

CK_RV YUBICO_get_slot_flags(CK_FLAGS_PTR flags) {

  *flags = slot_flags;
  return CKR_OK;


}

CK_RV YUBICO_get_slot_version(CK_VERSION_PTR version) {

  version->major = slot_version.major;
  version->minor = slot_version.minor;

  return CKR_OK;

}

CK_RV YUBICO_get_token_label(CK_UTF8CHAR_PTR str, CK_ULONG len) {

  if (strlen(token_label) > len)
    return CKR_BUFFER_TOO_SMALL;

  memcpy(str, token_label, strlen(token_label));
  return CKR_OK;

}

CK_RV YUBICO_get_token_manufacturer(CK_UTF8CHAR_PTR str, CK_ULONG len) {

  if (strlen(token_manufacturer) > len)
    return CKR_BUFFER_TOO_SMALL;

  memcpy(str, token_manufacturer, strlen(token_manufacturer));
  return CKR_OK;

}

CK_RV YUBICO_get_token_model(CK_UTF8CHAR_PTR str, CK_ULONG len) {

  if (strlen(token_model) > len)
    return CKR_BUFFER_TOO_SMALL;

  memcpy(str, token_model, strlen(token_model));
  return CKR_OK;

}

CK_RV YUBICO_get_token_flags(CK_FLAGS_PTR flags) {

  *flags = token_flags;
  return CKR_OK;

}

CK_RV YUBICO_get_token_version(CK_UTF8CHAR_PTR v_str, CK_ULONG len, CK_VERSION_PTR version) {

  CK_VERSION v = {0, 0};
  int i = 0;

  while (i < len && v_str[i] != '.') {
    v.major *= 10;
    v.major += v_str[i++] - '0';
  }

  i++;

  while (i < len && v_str[i] != '.') {
    v.minor *= 10;
    v.minor += v_str[i++] - '0';
  }

  i++;

  while (i < len && v_str[i] != '.') {
    v.minor *= 10;
    v.minor += v_str[i++] - '0';
  }

  version->major = v.major;
  version->minor = v.minor;

  return CKR_OK;
}

CK_RV YUBICO_get_token_serial(CK_CHAR_PTR str, CK_ULONG len) {

  if (strlen(token_serial) > len)
    return CKR_BUFFER_TOO_SMALL;

  memcpy(str, token_serial, strlen(token_serial));
  return CKR_OK;

}

CK_RV YUBICO_get_token_mechanisms_num(CK_ULONG_PTR num) {

  *num = token_mechanisms_num;
  return CKR_OK;

}

/*CK_RV YUBICO_get_token_mechanisms(void) {

}*/
