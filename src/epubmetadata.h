#ifndef EPUBMETADATA_H
#define EPUBMETADATA_H

#include <string>
#include <vector>

class EpubMetadata
{
public:
    EpubMetadata(const std::string &version, const std::string &unique_id, const std::string &dc_title, const std::string &dc_identifier, const std::string &dc_language, const std::vector<std::string> &dc_creators);
    ~EpubMetadata();

private:
    std::string version;
    std::string unique_id;
    std::string dc_title;
    std::string dc_identifier;
    std::string dc_language;
    std::vector<std::string> dc_creators;
};

#endif // EPUBMETADATA_H
