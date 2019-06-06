#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <wchar.h>
#include <wtypes.h>
#include "3rdparty/json/ujdecode.h"

struct JRC_ORIGIN {
    wchar_t *author;
    wchar_t *title;
    wchar_t **content;
    wchar_t **translate;
    wchar_t *dynasty;

};

struct JRC_DATA {
    struct JRC_ORIGIN *origin;
    wchar_t *content;
    wchar_t *id;
    wchar_t **matchTags;
    wint_t popularity;
    wchar_t *recommendedReson;
    wchar_t *cacheAt;
};

struct JRC {
    wchar_t *status;
    struct JRC_DATA *data;
    wchar_t *ipAddress;
    wchar_t *warning;
    wchar_t *token;
};

static void requestData();

static void decodeJson(const char *str, struct JRC *data);

int main(int argc, char **argv) {
    requestData();
    return 0;
}

typedef struct {
    size_t size;
    char *buf;
} _Buffer;

static size_t write_cb(void *contents, size_t size, size_t nmemb, void *user_ptr) {
    _Buffer *mem = (_Buffer *) user_ptr;

    size_t buffer_size = size * nmemb;

    char *tmp = realloc(mem->buf, mem->size + buffer_size);
    if (!tmp) {
        printf("申请内存失败\n");
        return 0;
    }

    mem->buf = tmp;
    memcpy(&(mem->buf[mem->size]), contents, buffer_size);
    mem->size += buffer_size;

    return buffer_size;
}

static void decodeJson(const char *str, struct JRC *data) {
    void *state;
    size_t cbInput = sizeof(str) - 1;

    UJObject obj = UJDecode(str, cbInput, NULL, &state);

    const wchar_t *keys[] = {L"status", L"data", L"ipAddress", L"warning", L"token"};
    UJObject oState, oData, oIpAddress, oWarning, oToken;

    printf("===> %d <===", UJGetType(obj));
    if (UJObjectUnpack(obj, 5, "SOSSS", keys, &oState, &oData, &oIpAddress, &oWarning, &oToken)) {

    }
}

static void requestData() {
    CURL *hd = curl_easy_init();

    if (hd) {
        curl_easy_setopt(hd, CURLOPT_URL, "https://v2.jinrishici.com/one.json");

        _Buffer _this;
        curl_easy_setopt(hd, CURLOPT_WRITEFUNCTION, write_cb);
        curl_easy_setopt(hd, CURLOPT_WRITEDATA, &_this);
//        curl_easy_setopt(hd, CURLOPT_VERBOSE, 1);

        CURLcode ret = curl_easy_perform(hd);
        printf("333 %d \n", ret);
        if (ret != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
        }

        wprintf(L"\n\n\n abab ==> %hs \n", _this.buf);
        struct JRC jrc;
        decodeJson(_this.buf, &jrc);

        curl_easy_cleanup(hd);
    }
}

