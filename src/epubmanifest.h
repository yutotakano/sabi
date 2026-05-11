#ifndef EPUBMANIFEST_H
#define EPUBMANIFEST_H

#include "pugixml.hpp"

class EpubManifest
{
public:
    EpubManifest(pugi::xml_node manifestNode);
    ~EpubManifest();
};

#endif // EPUBMANIFEST_H
