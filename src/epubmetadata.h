#ifndef EPUBMETADATA_H
#define EPUBMETADATA_H

#include <string>
#include <vector>

#include "pugixml.hpp"

class EpubMetadata
{
public:
    EpubMetadata(pugi::xml_node metadataNode);
    ~EpubMetadata();

private:
    std::string m_version;
    std::string m_unique_id;
    std::string m_dc_title;
    std::string m_dc_identifier;
    std::string m_dc_language;
    std::vector<std::string> m_dc_creators;
};

#endif // EPUBMETADATA_H
