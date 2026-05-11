#include "epub.h"
#include "libzippp.h"
#include <iostream>

Epub::Epub(const std::filesystem::path &path)
{
    std::cout << "Opening EPUB file: " << path.string() << std::endl;
    libzippp::ZipArchive zip(path.string());
    zip.open(libzippp::ZipArchive::ReadOnly);
    if (!zip.isOpen())
    {
        throw std::runtime_error("Failed to open EPUB file: " + path.string());
    }

    for (const auto &entry : zip.getEntries())
    {
        std::cout << "Entry: " << entry.getName() << std::endl;
    }

    m_package = new EpubPackage();
    m_metadata = new EpubMetadata();
    m_manifest = new EpubManifest();
    m_spine = new EpubSpine();
    m_toc = new EpubToc();
}

Epub::~Epub()
{
}

EpubPackage *Epub::package()
{
    return m_package;
}

EpubMetadata *Epub::metadata()
{
    return m_metadata;
}

EpubManifest *Epub::manifest()
{
    return m_manifest;
}

EpubSpine *Epub::spine()
{
    return m_spine;
}

EpubToc *Epub::toc()
{
    return m_toc;
}

EpubPackage::EpubPackage()
{
}

EpubPackage::~EpubPackage()
{
}

EpubMetadata::EpubMetadata()
{
}

EpubMetadata::~EpubMetadata()
{
}

EpubManifest::EpubManifest()
{
}

EpubManifest::~EpubManifest()
{
}

EpubSpine::EpubSpine()
{
}

EpubSpine::~EpubSpine()
{
}

EpubToc::EpubToc()
{
}

EpubToc::~EpubToc()
{
}
