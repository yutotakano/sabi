#ifndef EPUB_H
#define EPUB_H

#include <filesystem>
#include <string>

#include "epubpackage.h"

class EpubSpine
{
public:
    EpubSpine();
    ~EpubSpine();
};

class EpubToc
{
public:
    EpubToc();
    ~EpubToc();
};

class Epub
{
public:
    Epub(const std::filesystem::path &path);
    ~Epub();

    EpubPackage *package();
    EpubMetadata *metadata();
    EpubManifest *manifest();
    EpubSpine *spine();
    EpubToc *toc();

private:
    EpubPackage *m_package;
    EpubSpine *m_spine;
    EpubToc *m_toc;
};

#endif // EPUB_H
