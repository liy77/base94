//
// Created by liy on 9/4/2023.
//

#include <cstring>
#include <stdexcept>
#include <node_api.h>
const char* CHARSET = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

std::string EncodeInternal(const char *input, std::string &result) {
    size_t len = strlen(input);
    for (size_t i = 0; i < len; i++) {
        char c = input[i];
        if (c < 32 || c >= 126) {
            throw std::runtime_error("Character outside valid range for Base94");
        }
        result += CHARSET[c - 32];
    }

    return result;
}

const char *DecodeInternal(const char* input, std::string &result) {
    size_t len = strlen(input);
    size_t i = 0;
    while (i < len) {
        const char* pos = strchr(CHARSET, input[i]);
        if (pos == nullptr) {
            throw std::runtime_error("Invalid character in Base94 string");
        }
        result += (char)(pos - CHARSET + 32);
        i++;
        if (i % 94 == 0) {
            result += ' ';
        }
    }

    return result.c_str();
}

napi_value Encode(napi_env env, napi_callback_info info) {
    napi_value argv[1];
    size_t argc = 1;
    char input[256];

    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    if (argc != 1) {
        napi_throw_error(env, nullptr, "Missing data");
        return nullptr;
    }

    size_t inputSize;
    napi_status status = napi_get_value_string_utf8(env, argv[0], input, sizeof(input), &inputSize);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "The data must be a string");
        return nullptr;
    }

    std::string str;
    EncodeInternal(input, str);

    napi_value result;
    napi_create_string_utf8(env, str.c_str(), NAPI_AUTO_LENGTH, &result);

    return result;
}

napi_value Decode(napi_env env, napi_callback_info info) {
    napi_value argv[1];
    size_t argc = 1;
    char input[256];

    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    if (argc != 1) {
        napi_throw_error(env, nullptr, "Missing data");
        return nullptr;
    }

    size_t inputSize;
    napi_status status = napi_get_value_string_utf8(env, argv[0], input, sizeof(input), &inputSize);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "The data must be a string");
        return nullptr;
    }

    std::string str;
    DecodeInternal(input, str);

    napi_value result;
    napi_create_string_utf8(env, str.c_str(), NAPI_AUTO_LENGTH, &result);

    return result;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
            {"encode", nullptr, Encode, nullptr, nullptr, nullptr, napi_default, nullptr},
            {"decode", nullptr, Decode, nullptr, nullptr, nullptr, napi_default, nullptr},
    };

    napi_define_properties(env, exports, 2, desc);
    return exports;
}

NAPI_MODULE(NODE_GYPE_MODULE_NAME, Init);