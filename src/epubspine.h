#ifndef EPUBSPINE_H
#define EPUBSPINE_H

#include <string>
#include <vector>

#include "pugixml.hpp"

#include "epubmanifest.h"

class EpubSpineEntry
{
public:
    EpubSpineEntry(pugi::xml_node itemrefNode, EpubManifest *manifest);
    ~EpubSpineEntry();

    std::string idref() const { return m_idref; }
    bool linear() const { return m_linear; }
    EpubManifestEntry *entry() { return m_entry; }

private:
    std::string m_idref;
    bool m_linear;
    EpubManifestEntry *m_entry;
};

class EpubSpine
{
public:
    EpubSpine(pugi::xml_node spineNode, EpubManifest *manifest);
    ~EpubSpine();

    std::string tocId() const { return m_tocId; }

private:
    std::vector<EpubSpineEntry *> m_entries;
    std::string m_tocId;
};

#endif // EPUBSPINE_H
