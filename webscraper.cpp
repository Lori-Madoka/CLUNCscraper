//g++ -o webscraper webscraper.cpp -lstdc++ -lcurl
//libraries for url fetching
#include <curl/curl.h>
#include <iostream>
#include <string>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string site;
    std::cout << "Enter URL: ";
    std::getline(std::cin, site);
    std::cout << site << std::endl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, site.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        std::cout << readBuffer << std::endl;
    }
    curl_global_cleanup();
    return 0;
}