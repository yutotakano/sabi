#include <iostream>

#include "libzippp.h"

#include "epub.h"

Epub::Epub(const std::filesystem::path &path)
{
    std::cout << "Opening EPUB file: " << path.string() << std::endl;
    libzippp::ZipArchive zip(path.string());
    if (!zip.open(libzippp::ZipArchive::ReadOnly))
    {
        throw std::runtime_error("Failed to open EPUB file: " + path.string());
    }

    for (const auto &entry : zip.getEntries())
    {
        std::cout << "Entry: " << entry.getName() << std::endl;
    }

    // Get META-INF/container.xml
    auto containerEntry = zip.getEntry("META-INF/container.xml");
    if (containerEntry.isNull())
    {
        throw std::runtime_error("Failed to find META-INF/container.xml in EPUB file: " + path.string());
    }

    // Read the content of container.xml
    containerEntry.readContent(std::cout);

    zip.getEntry("mimetype").readContent(std::cout);

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
