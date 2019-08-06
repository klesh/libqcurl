#ifndef TEST_PLAIN_CURL_H
#define TEST_PLAIN_CURL_H

#include <stdio.h>
#include <curl/curl.h>

void test_https_get() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://baidu.com");
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
}

void writeFunction(void *buffer, size_t , size_t , void *) {
    printf("%s\n", static_cast<char*>(buffer));
}

void test_curl_sftp_ls() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
//        curl_easy_setopt(curl, CURLOPT_URL, "sftp://ftpuser:ftppass@127.0.0.1:2222/home/ftpuser/hello.txt");
        curl_easy_setopt(curl, CURLOPT_URL, "sftp://cabinet-demo1.productai.cn:2564/home/klesh/hello.txt");
        curl_easy_setopt(curl, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PUBLICKEY);
        curl_easy_setopt(curl, CURLOPT_USERNAME, "klesh");
        curl_easy_setopt(curl, CURLOPT_SSH_PUBLIC_KEYFILE, "D:/Projects/sshkey/id_rsa.pub");
        curl_easy_setopt(curl, CURLOPT_SSH_PRIVATE_KEYFILE, "D:/Projects/sshkey/id_rsa");
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
//        curl_easy_setopt(curl, CURLOPT_KEYPASSWD, "");

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        else {
            printf("YES OK DONE NICE");
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
}

#endif // TEST_PLAIN_CURL_H
