#include <iostream>

#include "libzippp.h"
#include "pugixml.hpp"

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

    // Sanity check mimetype
    auto mimeEntry = zip.getEntry("mimetype");
    if (mimeEntry.isNull() || mimeEntry.readAsText().compare("application/epub+zip") != 0)
    {
        throw std::runtime_error("No valid mimetype entry in EPUB file");
    }

    // Use only first package for now
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(zip.getEntry("META-INF/container.xml").readAsText().c_str());
    if (!result)
    {
        throw std::runtime_error("Failed to parse container.xml: " + std::string(result.description()));
    }

    pugi::xpath_node_set packageNodes = doc.select_nodes("/container/rootfiles/rootfile");
    if (packageNodes.empty())
    {
        throw std::runtime_error("No rootfile entry in container.xml");
    }

    std::string packagePath = packageNodes[0].node().attribute("full-path").value();

    m_package = new EpubPackage(zip, packagePath);
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
