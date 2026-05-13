#include <iostream>

#include "pugixml.hpp"

#include "epubpackage.h"

EpubPackage::EpubPackage(libzippp::ZipArchive *zip, const std::string &path)
{
    std::cout << "Loading package file: " << path << std::endl;

    package_url = path.substr(0, path.find_last_of('/'));

    zip->getEntry(path).readContent(std::cout);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(zip->getEntry(path).readAsText().c_str());
    if (!result)
    {
        throw std::runtime_error("Failed to parse package file: " + std::string(result.description()));
    }

    std::string version = doc.child("package").attribute("version").value();
    std::string unique_id = doc.child("package").attribute("unique-identifier").value();

    // Metadata *can* be in dc-metadata for Epub 2.0.1
    pugi::xml_node metadataNode = doc.child("package").child("metadata").child("dc-metadata");
    if (metadataNode.empty())
    {
        metadataNode = doc.child("package").child("metadata");
    }

    m_metadata = new EpubMetadata(metadataNode);

    pugi::xml_node manifestNode = doc.child("package").child("manifest");
    m_manifest = new EpubManifest(manifestNode);

    pugi::xml_node spineNode = doc.child("package").child("spine");
    m_spine = new EpubSpine(spineNode, m_manifest);

    // Epub 2 uses toc attribute in spine, Epub 3 uses nav hint in manifest entry
    std::string tocPath = m_manifest->entryById(m_spine->tocId())->href();
    m_toc = new EpubToc(zip, package_url + "/" + tocPath);
}

EpubPackage::~EpubPackage()
{
    delete m_metadata;
    delete m_manifest;
    delete m_spine;
    delete m_toc;
}

/**
 * @brief Read contents of a file in the package, given its path relative to the
 * package root.
 *
 * @param[in] path Relative path to the file to read, e.g. "chapter1.xhtml"
 * @return std::string
 */
std::string EpubPackage::readContent(libzippp::ZipArchive *zip, const std::string &path)
{
    auto entry = zip->getEntry(package_url + "/" + path);
    if (entry.isNull())
    {
        throw std::runtime_error("Failed to read content: " + package_url + "/" + path);
    }
    return entry.readAsText();
}
