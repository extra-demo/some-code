#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
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

static struct JRC decodeJson(const char *str, struct JRC *data);

static wchar_t *getStrByType(UJObject obj);

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

static struct JRC decodeJson(const char *str, struct JRC *data) {
    void *state;
    size_t cbInput = strlen(str);

    struct JRC jrc;

    UJObject obj = UJDecode(str, cbInput, NULL, &state);

    const wchar_t *keys[] = {L"status", L"data", L"ipAddress", L"warning", L"token"};
    UJObject oState, oData, oIpAddress, oWarning, oToken;

    if (UJObjectUnpack(obj, 5, "SOSsS", keys, &oState, &oData, &oIpAddress, &oWarning, &oToken)) {
        UJObject o[] = {oState, oData, oIpAddress, oWarning, oToken};
        for (int i = 0; i < 5; i++) {
            wprintf(
                    L"\n=====> %ls: %ls : %ls<=====\n",
                    keys[i],
                    UJReadString(o[i], NULL),
                    getStrByType(o[i])
            );
        }

        jrc.ipAddress = oIpAddress;
        jrc.status = oState;
        jrc.warning = oWarning;
        jrc.token = oToken;

        const wchar_t *dataKeys[] = {L"origin", L"content", L"id", L"matchTags", L"popularity", L"recommendedReson", L"cacheAt"};
        UJObject oOrigin, oContent, oId, oMatchTags, oPopularity, oRecommendedReson, oCacheAt;
        if (UJObjectUnpack(oData, 7, "OSSANSS", dataKeys, &oOrigin, &oContent, &oId, &oMatchTags, &oPopularity, &oRecommendedReson, &oCacheAt)) {
            UJObject oo[] = {oOrigin, oContent, oId, oMatchTags, oPopularity, oRecommendedReson, oCacheAt};
            for (int i = 0; i < 7; i++) {
                wprintf(
                        L"\n\n=====> %ls: %ls : %ls<=====\n",
                        dataKeys[i],
                        UJGetType(oo[i]) == UJT_String ? UJReadString(oo[i], NULL) : L"($)",
                        getStrByType(oo[i])
                );
            }
        }

        jrc.data = oData;
    }

    return jrc;
}

wchar_t *getStrByType(UJObject obj) {
    enum UJTypes t[] = {UJT_Null,
                        UJT_True,
                        UJT_False,
                        UJT_Long,
                        UJT_LongLong,
                        UJT_Double,
                        UJT_String,
                        UJT_Array,
                        UJT_Object};
    wchar_t *map[] = {L"NULL",
                      L"True",
                      L"False",
                      L"Long",
                      L"LongLong",
                      L"Double",
                      L"String",
                      L"Array",
                      L"Object"};

    enum UJTypes type = UJGetType(obj);
    for (ushort i = 0; i < 9; i++) {
        if (type == t[i]) {
            return map[i];
        }
    }

    return L"-1";
}

static void requestData() {
    CURL *hd = curl_easy_init();

    if (hd) {
        curl_easy_setopt(hd, CURLOPT_URL, "https://v2.jinrishici.com/one.json");

        _Buffer *_this = malloc(sizeof(_Buffer));
        _this->size = 0;
        _this->buf = malloc(1);
        curl_easy_setopt(hd, CURLOPT_WRITEFUNCTION, write_cb);
        curl_easy_setopt(hd, CURLOPT_WRITEDATA, _this);

        // struct curl_slist *list = NULL;
        // list = curl_slist_append(list, "X-User-Token：XlKfjT4/eYOiehrAdEgwbipKIe6G9sbU");

        // curl_easy_setopt(hd, CURLOPT_HTTPHEADER, list);

//        curl_easy_setopt(hd, CURLOPT_VERBOSE, 1);

        CURLcode ret = curl_easy_perform(hd);

        if (ret != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
        }

        wprintf(L"\n ret string ==> \n %hs \n", _this->buf);
        struct JRC jrc;
        decodeJson(_this->buf, &jrc);

        curl_easy_cleanup(hd);
    }
}

