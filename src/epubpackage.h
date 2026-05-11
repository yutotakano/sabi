#ifndef EPUBPACKAGE_H
#define EPUBPACKAGE_H

#include <libzippp.h>

#include "epubmetadata.h"

class EpubPackage
{
public:
    EpubPackage(libzippp::ZipArchive &zip, const std::string &path);
    ~EpubPackage();

    EpubMetadata *metadata();

private:
    EpubMetadata *m_metadata;
};

#endif // EPUBPACKAGE_H
