#ifndef EPUB_H
#define EPUB_H

#include <filesystem>
#include <string>

#include "epubpackage.h"

class Epub
{
public:
    Epub(const std::filesystem::path &path);
    ~Epub();

    EpubPackage *package() { return m_package; }
    EpubMetadata *metadata() { return m_package->metadata(); }
    EpubManifest *manifest() { return m_package->manifest(); }
    EpubSpine *spine() { return m_package->spine(); }
    EpubToc *toc() { return m_package->toc(); }

    std::string readById(const std::string &id);
    std::string readByHref(const std::string &href);

private:
    EpubPackage *m_package;

    libzippp::ZipArchive *zip;
};

#endif // EPUB_H
