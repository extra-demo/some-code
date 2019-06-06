#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <wchar.h>
#include <wtypes.h>


static void requestData();

int main(int argc, char **argv) {
    requestData();
    return 0;
}

typedef struct {
    size_t size;
    char *buf;
} _Buffer;

static size_t write_cb(char *contents, size_t size, size_t nmemb, void *user_ptr) {
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

static void requestData() {
    CURL *hd = curl_easy_init();

    if (hd) {
        curl_easy_setopt(hd, CURLOPT_URL, "https://v2.jinrishici.com/one.json");

        _Buffer _this;
        curl_easy_setopt(hd, CURLOPT_WRITEFUNCTION, write_cb);
        curl_easy_setopt(hd, CURLOPT_WRITEDATA, &_this);
        //curl_easy_setopt(hd, CURLOPT_VERBOSE, 1);

        CURLcode ret = curl_easy_perform(hd);

        if (ret != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
        }

        wprintf(L"\n\n\n abab ==> %hs \n", _this.buf);

        curl_easy_cleanup(hd);
    }
}

