#ifndef EPUBMETADATA_H
#define EPUBMETADATA_H

#include <string>

class EpubMetadata
{
public:
    EpubMetadata(const std::string &version, const std::string &unique_id);
    ~EpubMetadata();

private:
    std::string version;
    std::string unique_id;
};

#endif // EPUBMETADATA_H
