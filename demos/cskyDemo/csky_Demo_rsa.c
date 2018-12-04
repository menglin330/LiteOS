
#include <stdio.h>
#include <string.h>
#include "soc.h"
#include "drv_rsa.h"
#include "csky_All_Demo.h"
static rsa_handle_t *rsa = NULL;

uint8_t modulus[] = {
    0xdf, 0x83, 0xe4, 0x76, 0x2d, 0x00, 0x61, 0xf6, 0xd0, 0x8d, 0x4a, 0x04, 0x66, 0xb1, 0xd5, 0x55,
    0xef, 0x71, 0xb5, 0xa5, 0x4e, 0x69, 0x44, 0xd3, 0x4f, 0xb8, 0x3d, 0xec, 0xb1, 0x1d, 0x5f, 0x82,
    0x6a, 0x48, 0x21, 0x00, 0x7f, 0xd7, 0xd5, 0xf6, 0x82, 0x35, 0xc2, 0xa6, 0x67, 0xa3, 0x53, 0x2d,
    0x3a, 0x83, 0x9a, 0xba, 0x60, 0xc2, 0x11, 0x22, 0xc2, 0x35, 0x83, 0xe9, 0x10, 0xa1, 0xb4, 0xa6,
    0x74, 0x57, 0x99, 0xd3, 0xa8, 0x6a, 0x21, 0x83, 0x76, 0xc1, 0x67, 0xde, 0xd8, 0xec, 0xdf, 0xf7,
    0xc0, 0x1b, 0xf6, 0xfa, 0x14, 0xa4, 0x0a, 0xec, 0xd1, 0xee, 0xc0, 0x76, 0x4c, 0xcd, 0x4a, 0x0a,
    0x5c, 0x96, 0xf2, 0xc9, 0xa4, 0x67, 0x03, 0x97, 0x2e, 0x17, 0xcd, 0xa9, 0x27, 0x9d, 0xa6, 0x35,
    0x5f, 0x7d, 0xb1, 0x6b, 0x68, 0x0e, 0x99, 0xc7, 0xdd, 0x5d, 0x6f, 0x15, 0xce, 0x8e, 0x85, 0x33
};
static const uint8_t publicExponent[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01
};
static const uint8_t privateExponent[] = {
    0xc6, 0x15, 0x3d, 0x02, 0xfe, 0x1e, 0xb8, 0xb2, 0xe3, 0x60, 0x53, 0x98, 0x52, 0xea, 0x87, 0x06,
    0x01, 0x8d, 0xe4, 0x4c, 0xfb, 0x90, 0x8f, 0x4e, 0x35, 0xf8, 0x31, 0xe8, 0xf1, 0x8d, 0xf6, 0x76,
    0xbd, 0x79, 0xee, 0xc5, 0x62, 0x87, 0x05, 0x37, 0xd1, 0x6d, 0x93, 0x73, 0xa5, 0xa5, 0x38, 0xb1,
    0x7c, 0x89, 0xe5, 0x36, 0x07, 0x49, 0xf5, 0xa5, 0xb8, 0x37, 0x75, 0x0f, 0xb7, 0x8d, 0x97, 0x69,
    0xc4, 0xd4, 0x8a, 0xb7, 0xfe, 0x74, 0x48, 0x45, 0x58, 0x47, 0x29, 0xa3, 0x0b, 0xa7, 0xdc, 0x55,
    0x98, 0x18, 0x8c, 0xd4, 0x52, 0xf5, 0xc9, 0xe8, 0x40, 0xce, 0x97, 0x46, 0x14, 0x1f, 0x62, 0x94,
    0xc3, 0x21, 0x1e, 0x5d, 0x49, 0x59, 0x31, 0xeb, 0xc4, 0x95, 0xf9, 0x33, 0x70, 0xa7, 0x90, 0xc3,
    0x9e, 0x98, 0x58, 0xa4, 0x00, 0xa4, 0x0f, 0xf3, 0x51, 0x80, 0xc6, 0x14, 0xfb, 0xd5, 0x5b, 0x01
};

uint8_t Digest_signature_pkcs1_padding_out[] = {
    0x07, 0x2d, 0x25, 0xde, 0xa5, 0xfd, 0x7c, 0xb0, 0x92, 0xb4, 0xee, 0x57, 0xe8, 0xd3, 0x79, 0x74,
    0x59, 0x25, 0x34, 0xef, 0xfd, 0x2b, 0xda, 0x8b, 0xa4, 0x40, 0x4e, 0xd8, 0x92, 0x6e, 0xee, 0x84,
    0x52, 0xb0, 0xe1, 0x0e, 0xa8, 0xa9, 0x68, 0x62, 0x1b, 0x51, 0xed, 0x50, 0x84, 0x98, 0x6a, 0x97,
    0x98, 0xe8, 0xcf, 0x3f, 0x85, 0xd3, 0x28, 0x26, 0xf3, 0x7a, 0x52, 0x4b, 0x04, 0x95, 0xe6, 0xfd,
    0xfa, 0x41, 0xf3, 0xac, 0x8a, 0x6d, 0x74, 0x91, 0x8c, 0x87, 0x52, 0x38, 0x08, 0x49, 0xf4, 0x60,
    0xcd, 0x4b, 0x1a, 0x9e, 0x52, 0x60, 0xf2, 0x73, 0x60, 0x31, 0x78, 0x37, 0xd9, 0x42, 0xc4, 0x61,
    0x43, 0xcf, 0x6d, 0x55, 0xee, 0x05, 0x19, 0xb7, 0xc3, 0x37, 0xa7, 0xa8, 0xa4, 0xbd, 0xf1, 0xac,
    0x8e, 0x39, 0x20, 0x59, 0xcd, 0xfc, 0x50, 0x16, 0x81, 0x2d, 0xeb, 0xba, 0x95, 0xe9, 0x38, 0xa5,
};

static const uint8_t Digest[] = {
    0xe4, 0x2c, 0x9f, 0x12, 0xf7, 0xd2, 0x67, 0x3a, 0x23, 0xea, 0x85, 0x61, 0xeb, 0xb2, 0xc2, 0x19,
    0xdc, 0xd9, 0xf1, 0xaa
};

uint8_t dst[1024 >> 3] = {0};
uint32_t dst_size = 0;

static void rsa_crypto(int32_t idx, rsa_event_e event)
{
    if (event == RSA_EVENT_ENCRYPT_COMPLETE) {
        printf("[info]rsa encrypt is complete\r\n");
    } else if (event == RSA_EVENT_DECRYPT_COMPLETE) {
        printf("[info]rsa decrypt is cmplete\r\n");
    } else if (event == RSA_EVENT_SIGN_COMPLETE) {
        printf("[info]rsa sign is cmplete\r\n");
    } else if (event == RSA_EVENT_VERIFY_COMPLETE) {
        printf("[info]rsa verify is cmplete\r\n");
    }
}

static void rsa_encrypt_decrypt()
{
    int ret;
    uint8_t i;
    int index;
    rsa_padding_t padding;
    padding.padding_type = RSA_PADDING_MODE_PKCS1;
    padding.hash_type = RSA_HASH_TYPE_SHA1;
    rsa_status_t status;

    index = 1;

    for (i = 0; i < index; i++) {
        rsa = csi_rsa_initialize(i, rsa_crypto);
        ret = csi_rsa_config(rsa, RSA_DATA_BITS_1024, RSA_ENDIAN_MODE_LITTLE, NULL);

        ret = csi_rsa_encrypt(rsa, (void *)modulus, (void *)publicExponent, (void *)Digest, 20, (void *)dst, &dst_size, padding);

        while (1) {
            status = csi_rsa_get_status(rsa);

            if (status.busy == 0) {
                break;
            }
        }

        ret = csi_rsa_decrypt(rsa, (void *)modulus, (void *)privateExponent, (void *)dst, dst_size, (void *)dst, (uint32_t *)&dst_size, padding);

        while (1) {
            status = csi_rsa_get_status(rsa);

            if (status.busy == 0) {
                break;
            }
        }

        if (ret == 0) {
            printf("[info]rsa encrypt and decrypt: %s\n", memcmp(dst, Digest, 20) ? "Fail" : "Pass");
        }

        ret = csi_rsa_uninitialize(rsa);
    }

    printf("[success]test rsa successfully\n");
}

static void rsa_sign_verify()
{
    uint8_t i;
    uint8_t result;
    int index;
    rsa_padding_t padding;
    padding.padding_type = RSA_PADDING_MODE_PKCS1;
    padding.hash_type = RSA_HASH_TYPE_SHA1;
    rsa_status_t status;

    index = 1;

    for (i = 0; i < index; i++) {
        rsa = csi_rsa_initialize(i, rsa_crypto);
        csi_rsa_config(rsa, RSA_DATA_BITS_1024, RSA_ENDIAN_MODE_LITTLE, NULL);

        csi_rsa_sign(rsa, (void *)modulus, (void *)privateExponent, (void *)Digest, 20, (void *)dst, &dst_size, padding);

        while (1) {
            status = csi_rsa_get_status(rsa);

            if (status.busy == 0) {
                break;
            }
        }

        printf("[info]rsa sign: %s\n", memcmp(dst, Digest_signature_pkcs1_padding_out, dst_size) ? "Fail" : "Pass");

        csi_rsa_verify(rsa, (void *)modulus, (void *)publicExponent, (void *)Digest, 20, (void *)dst, dst_size, (void *)&result, padding);

        while (1) {
            status = csi_rsa_get_status(rsa);

            if (status.busy == 0) {
                break;
            }
        }

        printf("[info]rsa verify: %s\n", result ? "Pass" : "Fail");

        csi_rsa_uninitialize(rsa);
    }
}

/*****************************************************************************
test_rsa: main function of the rsa test

INPUT: NULL

RETURN: NULL

*****************************************************************************/
int example_rsa(void)
{
    rsa_sign_verify();
    rsa_encrypt_decrypt();
    return 0;
}

int task_RSA(void)
{
	//开始测试
	HopeRun_printf("开始RSA测试............\n");
    return example_rsa();
}