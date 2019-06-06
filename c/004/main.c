#include <stdio.h>
#include <curl/curl.h>
#include <wchar.h>
#include <wctype.h>
#include "3rdparty/json/ujdecode.h"

void test();

int main(int argc, char **argv) {
    test();
    return 0;
}

struct WithThis {
    size_t sizeLeft;
    const wchar_t *read_ptr;
};

static size_t read_function_cb(void *dest, size_t size, size_t nmemb, void *user_ptr) {
    struct WithThis *wt = (struct WithThis *) user_ptr;
    size_t buffer_size = size * nmemb;

    if (wt->sizeLeft) {
        size_t copy_this_much = wt->sizeLeft;
        if (copy_this_much > buffer_size) {
            copy_this_much = buffer_size;
        }
        wmemcpy(dest, wt->read_ptr, copy_this_much);
        wt->read_ptr +=copy_this_much;
        wt->sizeLeft -= copy_this_much;
        return copy_this_much;
    }

    return 0;
}

void test() {
    CURL *hd = curl_easy_init();

    if (hd) {
        curl_easy_setopt(hd, CURLOPT_URL, "https://v2.jinrishici.com/one.json");

        struct WithThis _this;
        curl_easy_setopt(hd, CURLOPT_READFUNCTION, read_function_cb);
        curl_easy_setopt(hd, CURLOPT_READDATA, &_this);
        curl_easy_setopt(hd, CURLOPT_VERBOSE, 1L);

        CURLcode ret = curl_easy_perform(hd);

        if (ret != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
        }

        wprintf(L"\n\n\nabab ==> %s", _this.read_ptr);

        curl_easy_cleanup(hd);
    }
}

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

struct JRC001 {
    wchar_t *status;
    struct JRC_DATA *data;
    wchar_t *ipAddress;
    wchar_t *warning;
    wchar_t *token;
};