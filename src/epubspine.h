#ifndef EPUBSPINE_H
#define EPUBSPINE_H

#include <string>
#include <vector>

#include "pugixml.hpp"

#include "epubmanifest.h"

class EpubSpineEntry
{
public:
    EpubSpineEntry(pugi::xml_node itemrefNode);
    ~EpubSpineEntry();

    std::string idref() const { return m_idref; }
    bool linear() const { return m_linear; }

private:
    std::string m_idref;
    bool m_linear;
};

class EpubSpine
{
public:
    EpubSpine(pugi::xml_node spineNode);
    ~EpubSpine();

private:
    std::vector<EpubSpineEntry *> m_entries;
};

#endif // EPUBSPINE_H
