#include <iostream>

#include "epubmanifest.h"

EpubManifest::EpubManifest(pugi::xml_node manifestNode)
{
    pugi::xpath_node_set itemNodes = manifestNode.select_nodes("item");
    for (pugi::xpath_node itemNode : itemNodes)
    {
        m_entries.push_back(new EpubManifestEntry(itemNode.node()));
        m_idToIndex[itemNode.node().attribute("id").value()] = m_entries.size() - 1;
    }

    // Debug output
    std::cout << "Manifest entries:" << std::endl;
    for (EpubManifestEntry *entry : m_entries)
    {
        std::cout << "  id: " << entry->id() << ", href: " << entry->href() << ", media-type: " << entry->mediaType() << std::endl;
    }
}

EpubManifest::~EpubManifest()
{
    for (EpubManifestEntry *entry : m_entries)
    {
        delete entry;
    }
}

EpubManifestEntry *EpubManifest::entryById(const std::string &id)
{
    auto it = m_idToIndex.find(id);
    if (it != m_idToIndex.end())
    {
        return m_entries[it->second];
    }
    return nullptr;
}

EpubManifestEntry::EpubManifestEntry(pugi::xml_node itemNode)
{
    m_id = itemNode.attribute("id").value();
    m_href = itemNode.attribute("href").value();
    m_media_type = itemNode.attribute("media-type").value();
}

EpubManifestEntry::~EpubManifestEntry()
{
}
