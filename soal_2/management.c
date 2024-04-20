#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <curl/curl.h>
#include <archive.h>
#include <archive_entry.h>

#define URL "https://example.com/file.zip"
#define OUTPUT_FILE "file.zip"
#define EXTRACT_DIR "extracted_files"

void downloadFile(const char *url, const char *outputFile) {
    CURL *curl;
    FILE *fp;

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outputFile, "wb");
        if (fp) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_perform(curl);
            fclose(fp);
        }
        curl_easy_cleanup(curl);
    }
}
