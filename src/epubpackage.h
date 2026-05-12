#ifndef EPUBPACKAGE_H
#define EPUBPACKAGE_H

#include <libzippp.h>

#include "epubmanifest.h"
#include "epubmetadata.h"
#include "epubspine.h"
#include "epubtoc.h"

class EpubPackage
{
public:
    EpubPackage(libzippp::ZipArchive &zip, const std::string &path);
    ~EpubPackage();

    EpubMetadata *metadata() { return m_metadata; }
    EpubManifest *manifest() { return m_manifest; }
    EpubSpine *spine() { return m_spine; }
    EpubToc *toc() { return m_toc; }

private:
    EpubMetadata *m_metadata;
    EpubManifest *m_manifest;
    EpubSpine *m_spine;
    EpubToc *m_toc;
};

#endif // EPUBPACKAGE_H
