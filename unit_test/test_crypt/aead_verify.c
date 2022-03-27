/**
 *  Copyright Notice:
 *  Copyright 2021 DMTF. All rights reserved.
 *  License: BSD 3-Clause License. For full text see link: https://github.com/DMTF/libspdm/blob/main/LICENSE.md
 **/

#include "test_crypt.h"

/* AES-GCM test data from NIST public test vectors */

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_gcm_key[] = {
    0xee, 0xbc, 0x1f, 0x57, 0x48, 0x7f, 0x51, 0x92, 0x1c, 0x04, 0x65,
    0x66, 0x5f, 0x8a, 0xe6, 0xd1, 0x65, 0x8b, 0xb2, 0x6d, 0xe6, 0xf8,
    0xa0, 0x69, 0xa3, 0x52, 0x02, 0x93, 0xa5, 0x72, 0x07, 0x8f
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_gcm_iv[] = {
    0x99, 0xaa, 0x3e, 0x68, 0xed, 0x81, 0x73, 0xa0, 0xee, 0xd0, 0x66, 0x84
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_gcm_pt[] = {
    0xf5, 0x6e, 0x87, 0x05, 0x5b, 0xc3, 0x2d, 0x0e,
    0xeb, 0x31, 0xb2, 0xea, 0xcc, 0x2b, 0xf2, 0xa5
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_gcm_aad[] = {
    0x4d, 0x23, 0xc3, 0xce, 0xc3, 0x34, 0xb4, 0x9b,
    0xdb, 0x37, 0x0c, 0x43, 0x7f, 0xec, 0x78, 0xde
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_gcm_ct[] = {
    0xf7, 0x26, 0x44, 0x13, 0xa8, 0x4c, 0x0e, 0x7c,
    0xd5, 0x36, 0x86, 0x7e, 0xb9, 0xf2, 0x17, 0x36
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_gcm_tag[] = {
    0x67, 0xba, 0x05, 0x10, 0x26, 0x2a, 0xe4, 0x87,
    0xd7, 0x37, 0xee, 0x62, 0x98, 0xf7, 0x7e, 0x0c
};

/* CHACHA20-Poly1305 test data */

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_chacha20_poly1305_pt[] = {
    0x4c, 0x61, 0x64, 0x69, 0x65, 0x73, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x47,
    0x65, 0x6e, 0x74, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x20, 0x6f, 0x66, 0x20,
    0x74, 0x68, 0x65, 0x20, 0x63, 0x6c, 0x61, 0x73, 0x73, 0x20, 0x6f, 0x66,
    0x20, 0x27, 0x39, 0x39, 0x3a, 0x20, 0x49, 0x66, 0x20, 0x49, 0x20, 0x63,
    0x6f, 0x75, 0x6c, 0x64, 0x20, 0x6f, 0x66, 0x66, 0x65, 0x72, 0x20, 0x79,
    0x6f, 0x75, 0x20, 0x6f, 0x6e, 0x6c, 0x79, 0x20, 0x6f, 0x6e, 0x65, 0x20,
    0x74, 0x69, 0x70, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x74, 0x68, 0x65, 0x20,
    0x66, 0x75, 0x74, 0x75, 0x72, 0x65, 0x2c, 0x20, 0x73, 0x75, 0x6e, 0x73,
    0x63, 0x72, 0x65, 0x65, 0x6e, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20,
    0x62, 0x65, 0x20, 0x69, 0x74, 0x2e,
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_chacha20_poly1305_aad[] = {
    0x50, 0x51, 0x52, 0x53, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_chacha20_poly1305_key[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a,
    0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95,
    0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_chacha20_poly1305_iv[] = {
    0x07, 0x00, 0x00, 0x00, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_chacha20_poly1305_ct[] = {
    0xd3, 0x1a, 0x8d, 0x34, 0x64, 0x8e, 0x60, 0xdb, 0x7b, 0x86, 0xaf, 0xbc,
    0x53, 0xef, 0x7e, 0xc2, 0xa4, 0xad, 0xed, 0x51, 0x29, 0x6e, 0x08, 0xfe,
    0xa9, 0xe2, 0xb5, 0xa7, 0x36, 0xee, 0x62, 0xd6, 0x3d, 0xbe, 0xa4, 0x5e,
    0x8c, 0xa9, 0x67, 0x12, 0x82, 0xfa, 0xfb, 0x69, 0xda, 0x92, 0x72, 0x8b,
    0x1a, 0x71, 0xde, 0x0a, 0x9e, 0x06, 0x0b, 0x29, 0x05, 0xd6, 0xa5, 0xb6,
    0x7e, 0xcd, 0x3b, 0x36, 0x92, 0xdd, 0xbd, 0x7f, 0x2d, 0x77, 0x8b, 0x8c,
    0x98, 0x03, 0xae, 0xe3, 0x28, 0x09, 0x1b, 0x58, 0xfa, 0xb3, 0x24, 0xe4,
    0xfa, 0xd6, 0x75, 0x94, 0x55, 0x85, 0x80, 0x8b, 0x48, 0x31, 0xd7, 0xbc,
    0x3f, 0xf4, 0xde, 0xf0, 0x8e, 0x4b, 0x7a, 0x9d, 0xe5, 0x76, 0xd2, 0x65,
    0x86, 0xce, 0xc6, 0x4b, 0x61, 0x16,
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_chacha20_poly1305_tag[] = {
    0x1a, 0xe1, 0x0b, 0x59, 0x4f, 0x09, 0xe2, 0x6a,
    0x7e, 0x90, 0x2e, 0xcb, 0xd0, 0x60, 0x06, 0x91,
};

/* SM4-GCM test data */

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_sm4_gcm_pt[] = {
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB,
    0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xEE,
    0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
    0xEE, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_sm4_gcm_aad[] = {
    0xFE, 0xED, 0xFA, 0xCE, 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED,
    0xFA, 0xCE, 0xDE, 0xAD, 0xBE, 0xEF, 0xAB, 0xAD, 0xDA, 0xD2,
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_sm4_gcm_key[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_sm4_gcm_iv[] = {
    0x00, 0x00, 0x12, 0x34, 0x56, 0x78, 0x00, 0x00, 0x00, 0x00, 0xAB, 0xCD,
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_sm4_gcm_ct[] = {
    0x17, 0xF3, 0x99, 0xF0, 0x8C, 0x67, 0xD5, 0xEE, 0x19, 0xD0, 0xDC,
    0x99, 0x69, 0xC4, 0xBB, 0x7D, 0x5F, 0xD4, 0x6F, 0xD3, 0x75, 0x64,
    0x89, 0x06, 0x91, 0x57, 0xB2, 0x82, 0xBB, 0x20, 0x07, 0x35, 0xD8,
    0x27, 0x10, 0xCA, 0x5C, 0x22, 0xF0, 0xCC, 0xFA, 0x7C, 0xBF, 0x93,
    0xD4, 0x96, 0xAC, 0x15, 0xA5, 0x68, 0x34, 0xCB, 0xCF, 0x98, 0xC3,
    0x97, 0xB4, 0x02, 0x4A, 0x26, 0x91, 0x23, 0x3B, 0x8D,
};

GLOBAL_REMOVE_IF_UNREFERENCED uint8_t m_libspdm_sm4_gcm_tag[] = {
    0x83, 0xDE, 0x35, 0x41, 0xE4, 0xC2, 0xB5, 0x81,
    0x77, 0xE0, 0x65, 0xA9, 0xBF, 0x7B, 0x62, 0xEC,
};

/**
 * Validate Crypto AEAD Ciphers Interfaces.
 *
 * @retval  true  Validation succeeded.
 * @retval  false  Validation failed.
 *
 **/
bool libspdm_validate_crypt_aead_cipher(void)
{
    bool status;
    uint8_t OutBuffer[1024];
    size_t OutBufferSize;
    uint8_t OutTag[1024];
    size_t OutTagSize;

    libspdm_my_print("\nCrypto AEAD Testing: ");

    libspdm_my_print("\n- AES-GCM Encryption: ");
    OutBufferSize = sizeof(OutBuffer);
    OutTagSize = sizeof(m_libspdm_gcm_tag);
    status = libspdm_aead_aes_gcm_encrypt(m_libspdm_gcm_key, sizeof(m_libspdm_gcm_key),
                                          m_libspdm_gcm_iv,
                                          sizeof(m_libspdm_gcm_iv), m_libspdm_gcm_aad,
                                          sizeof(m_libspdm_gcm_aad), m_libspdm_gcm_pt,
                                          sizeof(m_libspdm_gcm_pt), OutTag, OutTagSize,
                                          OutBuffer, &OutBufferSize);
    if (!status) {
        libspdm_my_print("[Fail]");
        return false;
    }
    if (OutBufferSize != sizeof(m_libspdm_gcm_ct)) {
        libspdm_my_print("[Fail]");
        return false;
    }
    if (libspdm_const_compare_mem(OutBuffer, m_libspdm_gcm_ct, sizeof(m_libspdm_gcm_ct)) != 0) {
        libspdm_my_print("[Fail]");
        return false;
    }
    if (libspdm_const_compare_mem(OutTag, m_libspdm_gcm_tag, sizeof(m_libspdm_gcm_tag)) != 0) {
        libspdm_my_print("[Fail]");
        return false;
    }
    libspdm_my_print("[Pass]");

    libspdm_my_print("\n- AES-GCM Decryption: ");
    status = libspdm_aead_aes_gcm_decrypt(
        m_libspdm_gcm_key, sizeof(m_libspdm_gcm_key), m_libspdm_gcm_iv, sizeof(m_libspdm_gcm_iv),
        m_libspdm_gcm_aad, sizeof(m_libspdm_gcm_aad), m_libspdm_gcm_ct, sizeof(m_libspdm_gcm_ct),
        m_libspdm_gcm_tag, sizeof(m_libspdm_gcm_tag), OutBuffer, &OutBufferSize);
    if (!status) {
        libspdm_my_print("[Fail]");
        return false;
    }
    if (OutBufferSize != sizeof(m_libspdm_gcm_pt)) {
        libspdm_my_print("[Fail]");
        return false;
    }
    if (libspdm_const_compare_mem(OutBuffer, m_libspdm_gcm_pt, sizeof(m_libspdm_gcm_pt)) != 0) {
        libspdm_my_print("[Fail]");
        return false;
    }

    libspdm_my_print("[Pass]");

    libspdm_my_print("\n- ChaCha20Poly1305 Encryption: ");
    OutBufferSize = sizeof(OutBuffer);
    OutTagSize = sizeof(m_libspdm_chacha20_poly1305_tag);
    status = libspdm_aead_chacha20_poly1305_encrypt(
        m_libspdm_chacha20_poly1305_key, sizeof(m_libspdm_chacha20_poly1305_key),
        m_libspdm_chacha20_poly1305_iv, sizeof(m_libspdm_chacha20_poly1305_iv),
        m_libspdm_chacha20_poly1305_aad, sizeof(m_libspdm_chacha20_poly1305_aad),
        m_libspdm_chacha20_poly1305_pt, sizeof(m_libspdm_chacha20_poly1305_pt), OutTag,
        OutTagSize, OutBuffer, &OutBufferSize);
    if (!status) {
        libspdm_my_print("[Fail]");
        return false;
    }
    if (OutBufferSize != sizeof(m_libspdm_chacha20_poly1305_ct)) {
        libspdm_my_print("[Fail]");
        return false;
    }
    if (libspdm_const_compare_mem(OutBuffer, m_libspdm_chacha20_poly1305_ct,
                                  sizeof(m_libspdm_chacha20_poly1305_ct)) != 0) {
        libspdm_my_print("[Fail]");
        return false;
    }
    if (libspdm_const_compare_mem(OutTag, m_libspdm_chacha20_poly1305_tag,
                                  sizeof(m_libspdm_chacha20_poly1305_tag)) != 0) {
        libspdm_my_print("[Fail]");
        return false;
    }
    libspdm_my_print("[Pass]");

    libspdm_my_print("\n- ChaCha20Poly1305 Decryption: ");
    status = libspdm_aead_chacha20_poly1305_decrypt(
        m_libspdm_chacha20_poly1305_key, sizeof(m_libspdm_chacha20_poly1305_key),
        m_libspdm_chacha20_poly1305_iv, sizeof(m_libspdm_chacha20_poly1305_iv),
        m_libspdm_chacha20_poly1305_aad, sizeof(m_libspdm_chacha20_poly1305_aad),
        m_libspdm_chacha20_poly1305_ct, sizeof(m_libspdm_chacha20_poly1305_ct),
        m_libspdm_chacha20_poly1305_tag, sizeof(m_libspdm_chacha20_poly1305_tag),
        OutBuffer, &OutBufferSize);
    if (!status) {
        libspdm_my_print("[Fail]");
        return false;
    }
    if (OutBufferSize != sizeof(m_libspdm_chacha20_poly1305_pt)) {
        libspdm_my_print("[Fail]");
        return false;
    }
    if (libspdm_const_compare_mem(OutBuffer, m_libspdm_chacha20_poly1305_pt,
                                  sizeof(m_libspdm_chacha20_poly1305_pt)) != 0) {
        libspdm_my_print("[Fail]");
        return false;
    }

    libspdm_my_print("[Pass]");

    libspdm_my_print("\n- SM4-GCM Encryption: ");
    OutBufferSize = sizeof(OutBuffer);
    OutTagSize = sizeof(m_libspdm_sm4_gcm_tag);
    status =
        libspdm_aead_sm4_gcm_encrypt(m_libspdm_sm4_gcm_key, sizeof(m_libspdm_sm4_gcm_key),
                                     m_libspdm_sm4_gcm_iv, sizeof(m_libspdm_sm4_gcm_iv),
                                     m_libspdm_sm4_gcm_aad, sizeof(m_libspdm_sm4_gcm_aad),
                                     m_libspdm_sm4_gcm_pt, sizeof(m_libspdm_sm4_gcm_pt), OutTag,
                                     OutTagSize, OutBuffer, &OutBufferSize);
    if (!status) {
        libspdm_my_print("[Fail]");
        goto Exit;
    }
    if (OutBufferSize != sizeof(m_libspdm_sm4_gcm_ct)) {
        libspdm_my_print("[Fail]");
        goto Exit;
    }
    if (libspdm_const_compare_mem(OutBuffer, m_libspdm_sm4_gcm_ct,
                                  sizeof(m_libspdm_sm4_gcm_ct)) != 0) {
        libspdm_my_print("[Fail]");
        goto Exit;
    }
    if (libspdm_const_compare_mem(OutTag, m_libspdm_sm4_gcm_tag,
                                  sizeof(m_libspdm_sm4_gcm_tag)) != 0) {
        libspdm_my_print("[Fail]");
        goto Exit;
    }
    libspdm_my_print("[Pass]");

    libspdm_my_print("\n- SM4-GCM Decryption: ");
    status = libspdm_aead_sm4_gcm_decrypt(m_libspdm_sm4_gcm_key, sizeof(m_libspdm_sm4_gcm_key),
                                          m_libspdm_sm4_gcm_iv, sizeof(m_libspdm_sm4_gcm_iv),
                                          m_libspdm_sm4_gcm_aad, sizeof(m_libspdm_sm4_gcm_aad),
                                          m_libspdm_sm4_gcm_ct, sizeof(m_libspdm_sm4_gcm_ct),
                                          m_libspdm_sm4_gcm_tag, sizeof(m_libspdm_sm4_gcm_tag),
                                          OutBuffer, &OutBufferSize);
    if (!status) {
        libspdm_my_print("[Fail]");
        goto Exit;
    }
    if (OutBufferSize != sizeof(m_libspdm_sm4_gcm_pt)) {
        libspdm_my_print("[Fail]");
        goto Exit;
    }
    if (libspdm_const_compare_mem(OutBuffer, m_libspdm_sm4_gcm_pt,
                                  sizeof(m_libspdm_sm4_gcm_pt)) != 0) {
        libspdm_my_print("[Fail]");
        goto Exit;
    }

    libspdm_my_print("[Pass]");

Exit:
    libspdm_my_print("\n");

    return true;
}
