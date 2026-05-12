#ifndef EPUBMANIFEST_H
#define EPUBMANIFEST_H

#include <string>
#include <unordered_map>
#include <vector>

#include "pugixml.hpp"

class EpubManifestEntry
{
public:
    EpubManifestEntry(pugi::xml_node itemNode);
    ~EpubManifestEntry();

    std::string id() const { return m_id; }
    std::string href() const { return m_href; }
    std::string mediaType() const { return m_media_type; }

private:
    std::string m_id;
    std::string m_href;
    std::string m_media_type;
};

class EpubManifest
{
public:
    EpubManifest(pugi::xml_node manifestNode);
    ~EpubManifest();

    EpubManifestEntry *entryById(const std::string &id);
    EpubManifestEntry *entryByHref(const std::string &href);

private:
    std::vector<EpubManifestEntry *> m_entries;
    std::unordered_map<std::string, size_t> m_idToIndex;
};

#endif // EPUBMANIFEST_H
