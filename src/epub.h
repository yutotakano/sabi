#ifndef EPUB_H
#define EPUB_H

#include <string>
#include <filesystem>

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
    EpubMetadata *m_metadata;
    EpubManifest *m_manifest;
    EpubSpine *m_spine;
    EpubToc *m_toc;
};

class EpubPackage
{
public:
    EpubPackage();
    ~EpubPackage();
};

class EpubMetadata
{
public:
    EpubMetadata();
    ~EpubMetadata();
};

class EpubManifest
{
public:
    EpubManifest();
    ~EpubManifest();
};

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

#endif // EPUB_H
