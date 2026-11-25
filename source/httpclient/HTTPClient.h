#pragma once

#include <string>
#include <map>
#include <functional>
#include <vector>
#include <cstdarg>
#include <curl/curl.h>

class CHTTPClient
{
public:
    struct HttpResponse
    {
        long iCode = 0;
        std::string strBody;
        std::string errMessage;
        std::map<std::string, std::string> mapHeaders;
        std::map<std::string, std::string> mapHeadersLowercase;
        std::map<std::string, std::string> cookies;
    };

    using HeadersMap = std::map<std::string, std::string>;
    using PostFormContent = std::map<std::string, std::string>;

    // multipart 表单字段：普通文本内容或本地文件（fileField 非空时以文件名上传）
    struct FormField
    {
        std::string name;
        std::string content;
        std::string fileField;
    };

    class PostFormInfo
    {
    public:
        void AddFormContent(const std::string &name, const std::string &value)
        {
            FormField field;
            field.name = name;
            field.content = value;
            fields.push_back(field);
        }

        void AddFormField(const std::string &name, const std::string &content, const std::string &fileName)
        {
            FormField field;
            field.name = name;
            field.content = content;
            field.fileField = fileName;
            fields.push_back(field);
        }

        std::vector<FormField> fields;
    };

    struct ProgressFnStruct
    {
        void *pOwner = nullptr;
    };

    enum SettingsFlag
    {
        NO_FLAGS = 0
    };

    using LogFn = std::function<void(const std::string &)>;

    explicit CHTTPClient(LogFn logFn);
    ~CHTTPClient();

    void SetBasicAuth(const std::string &user, const std::string &pass);
    void SetCookie(const std::string &name, const std::string &value);
    void InitSession(bool verifyPeer, SettingsFlag);
    void SetCertificateFile(const std::string &path);

    void SetProgressFnCallback(void *owner, int (*fn)(void *, double, double, double, double));

    bool Head(const std::string &url, const HeadersMap &headers, HttpResponse &out);
    bool Get(const std::string &url, const HeadersMap &headers, HttpResponse &out);
    bool DownloadFile(const std::string &outputPath, const std::string &url, long &status);
    bool UploadFile(const std::string &inputPath, const std::string &url, long &status);
    bool UploadForm(const std::string &url, const HeadersMap &headers, const PostFormInfo &form, HttpResponse &out);
    bool Post(const std::string &url, const HeadersMap &headers, HttpResponse &out);
    bool CustomRequest(const std::string &method, const std::string &url, const HeadersMap &headers, HttpResponse &out);

    void CleanupSession();

    static std::string EncodeUrl(const std::string &url);
    static std::string DecodeUrl(const std::string &url, bool plusAsSpace);

private:
    CURL *curl;
    LogFn logger;

    std::string user;
    std::string pass;
    std::string caFile;
    std::string activeUrl;

    // 手动设置的 Cookie（优先级高于服务器 Set-Cookie）
    std::map<std::string, std::string> cookies;

    ProgressFnStruct progressOwner;
    int (*progressFn)(void *, double, double, double, double) = nullptr;

    void applyCommonOptions(const std::string &url);
    static size_t writeBodyCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
    static size_t writeHeaderCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
    static int progressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
};

