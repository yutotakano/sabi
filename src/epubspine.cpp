#include "epubspine.h"

EpubSpine::EpubSpine(pugi::xml_node spineNode, EpubManifest *manifest)
{
    pugi::xpath_node_set itemrefNodes = spineNode.select_nodes("itemref");
    for (pugi::xpath_node itemrefNode : itemrefNodes)
    {
        m_entries.push_back(new EpubSpineEntry(itemrefNode.node(), manifest));
    }

    m_tocId = spineNode.attribute("toc").value();
}

EpubSpine::~EpubSpine()
{
    for (EpubSpineEntry *entry : m_entries)
    {
        delete entry;
    }
}

EpubSpineEntry::EpubSpineEntry(pugi::xml_node itemrefNode, EpubManifest *manifest)
{
    m_idref = itemrefNode.attribute("idref").value();
    m_linear = itemrefNode.attribute("linear").as_bool(true);
    m_entry = manifest->entryById(m_idref);
}

EpubSpineEntry::~EpubSpineEntry()
{
}
