#pragma once

#ifndef TEST_H
#define TEST_H

#include <string>

using namespace std;

class OneDriveWorker
{
public:
    OneDriveWorker(string login, string password);

    void getFile(string accessToken, string fileId, string savePath);
    void putFile(
        string accessToken, string fileName, string parentFolderId, string filePath);

private:
    void getAccessToken(
        string clientId,
        string clientSecret,
        string redirectUri,
        string authorizationCode);

    string accessToken;

};

void parser(string command, string dst_path, string src_path);

#endif
