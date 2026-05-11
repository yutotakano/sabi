#ifndef EPUBPACKAGE_H
#define EPUBPACKAGE_H

#include <libzippp.h>

#include "epubmanifest.h"
#include "epubmetadata.h"

class EpubPackage
{
public:
    EpubPackage(libzippp::ZipArchive &zip, const std::string &path);
    ~EpubPackage();

    EpubMetadata *metadata();
    EpubManifest *manifest();

private:
    EpubMetadata *m_metadata;
    EpubManifest *m_manifest;
};

#endif // EPUBPACKAGE_H
