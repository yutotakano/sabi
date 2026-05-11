#include "epubspine.h"

EpubSpine::EpubSpine(pugi::xml_node spineNode)
{
    pugi::xpath_node_set itemrefNodes = spineNode.select_nodes("itemref");
    for (pugi::xpath_node itemrefNode : itemrefNodes)
    {
        m_entries.push_back(new EpubSpineEntry(itemrefNode.node()));
    }
}

EpubSpine::~EpubSpine()
{
    for (EpubSpineEntry *entry : m_entries)
    {
        delete entry;
    }
}

EpubSpineEntry::EpubSpineEntry(pugi::xml_node itemrefNode)
{
    m_idref = itemrefNode.attribute("idref").value();
    m_linear = itemrefNode.attribute("linear").as_bool(true);
}

EpubSpineEntry::~EpubSpineEntry()
{
}
