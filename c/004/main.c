#include <stdio.h>
#include <curl/curl.h>

void test();

int main(int argc, char **argv)
{
    test();
    return 0;
}

struct withThis {

};

void read_function_cb ()
{

}

void test()
{
    CURL* hd = curl_easy_init();

    if (hd) {
        curl_easy_setopt(hd, CURLOPT_URL, "https://v2.jinrishici.com/one.json");

        struct withThis _this;
        curl_easy_setopt(hd, CURLOPT_READFUNCTION, read_function_cb);
        curl_easy_setopt(hd, CURLOPT_READDATA, &_this);

        CURLcode ret = curl_easy_perform(hd);

        if (ret != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
        }

        curl_easy_cleanup(hd);
    }
}