#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
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

static void test();

static void decode(const char *str, struct JRC *data);

int main(int argc, char **argv) {
    test();
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

static void decode(const char *str, struct JRC *data) {
    void *state;
    size_t cbInput = sizeof(str) - 1;

    UJObject obj = UJDecode(str, cbInput, NULL, &state);

    char *keys[] = {"status", "data", "ipAddress", "warning", "token"};
    UJObject oState, oData, oIpAddress, oWarning, oToken;

    if (UJObjectUnpack(obj, 5, "SOSSS", &oState, &oIpAddress, &oWarning, &oToken)) {

    }
}

static void test() {
    CURL *hd = curl_easy_init();

    if (hd) {
        curl_easy_setopt(hd, CURLOPT_URL, "https://v2.jinrishici.com/one.json");

        _Buffer _this;
        curl_easy_setopt(hd, CURLOPT_WRITEFUNCTION, write_cb);
        curl_easy_setopt(hd, CURLOPT_WRITEDATA, &_this);

        CURLcode ret = curl_easy_perform(hd);

        if (ret != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
        }

        wprintf(L"\n\n\nabab ==> %s", _this.buf);

        curl_easy_cleanup(hd);
    }
}

