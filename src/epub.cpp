#include "epub.h"
#include "libzippp.h"
#include <iostream>

Epub::Epub(const std::filesystem::path &path)
{
    libzippp::ZipArchive zip(path.string());
    if (!zip.isOpen())
    {
        throw std::runtime_error("Failed to open EPUB file: " + path.string());
    }
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
