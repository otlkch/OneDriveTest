#include "Test.h"
#include <iostream>
#include <cpr/cpr.h>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;

OneDriveWorker::OneDriveWorker(string login, string password)
{
    string clientId;
    string cliendSecret;
    string redirectUri;
    string authorizationCode;
    cout << login << ' ' << password << endl;
    //getAccessToken(clientId, cliendSecret, redirectUri, authorizationCode);
}

void OneDriveWorker::getAccessToken(
	string clientId,
	string clientSecret,
	string redirectUri,
	string authorizationCode)
{
    auto response = cpr::Post(cpr::Url{
        "https://login.microsoftonline.com/common/oauth2/v2.0/token" },
        cpr::Payload{
            {"grant_type", "authorization_code"},
            {"client_id", clientId},
            {"client_secret", clientSecret},
            {"redirect_uri", redirectUri},
            {"code", authorizationCode}
        },
        cpr::Header{
            {"Content-Type", "application/x-www-form-urlencoded"}
        }
    );
    auto json = nlohmann::json::parse(response.text);
    accessToken = json["access_token"].get<std::string>();
}

void OneDriveWorker::getFile(string accessToken, string fileId, string savePath) {
    auto response = cpr::Get(cpr::Url{
        "https://graph.microsoft.com/v1.0/me/drive/items/" + fileId + "/content" },
        cpr::Header{
            {"Authorization", "Bearer " + accessToken}
        }
    );
    ofstream outFile(savePath, ios::out | ios::binary);
    outFile.write(response.text.c_str(), response.text.size());
    outFile.close();
}

void OneDriveWorker::putFile(
    string accessToken, string fileName, string parentFolderId, string filePath) {
    std::ifstream file(filePath, ios::binary | ios::ate);
    auto size = file.tellg();
    file.seekg(0, ios::beg);
    std::vector<char> buffer(size);
    file.read(buffer.data(), size);
    file.close();

    auto response = cpr::Put(cpr::Url{
        "https://graph.microsoft.com/v1.0/me/drive/items/" + parentFolderId + ":/" + fileName + ":/content" },
        cpr::Header{
            {"Authorization", "Bearer " + accessToken},
            {"Content-Type", "application/octet-stream"}
        },
        cpr::Body{
            buffer.data(),
            buffer.size()
        }
    );
}

void parser(string command, string dst_path, string src_path)
{
    int mode;
    if (command == "get")
        mode = 1;
    else
        if (command == "put")
            mode = 0;
        else
        {
            cout << "Unknown utility call command \"" << command << '\"';
            return;
        }

    if (mode) //get
    {
        ofstream dst;
        dst.open(dst_path); //create file to write on

        dst.close();
    }
    else //put
    {
        ifstream src;
        src.open(src_path); //open file to read from
        if (!src.is_open())
        {
            cout << "File \"" << src_path << "\" not found"; // сообщить об этом
            return;
        }
        char buff[50];
        src.getline(buff, 50);
        cout << buff << '\n';
        src.close();
    }
}