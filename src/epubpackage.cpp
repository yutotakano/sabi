#include <iostream>

#include "pugixml.hpp"

#include "epubpackage.h"

EpubPackage::EpubPackage(libzippp::ZipArchive *zip, const std::string &path)
{
    std::cout << "Loading package file: " << path << std::endl;

    package_url = path.substr(0, path.find_last_of('/'));
    if (package_url == path)
    {
        // Handle the case when there was no '/' in path (probs root level package)
        package_url = "";
    }
    else
    {
        package_url = package_url + "/";
    }

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

    std::string tocId = getTocId(manifestNode, spineNode);

    // Epub 2 uses toc attribute in spine, Epub 3 uses nav hint in manifest entry
    std::string tocPath = m_manifest->entryById(tocId)->href();
    m_toc = new EpubToc(zip, package_url + tocPath);
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
    auto entry = zip->getEntry(package_url + path);
    if (entry.isNull())
    {
        throw std::runtime_error("Failed to read content: " + package_url + path);
    }
    return entry.readAsText();
}

std::string EpubPackage::getTocId(pugi::xml_node manifestNode, pugi::xml_node spineNode)
{
    // First try to get toc id from spine toc attribute (Epub 2)
    std::string tocId = spineNode.attribute("toc").value();
    if (!tocId.empty())
    {
        return tocId;
    }

    // If not found, try to find manifest entry with properties="nav" (Epub 3)
    for (pugi::xml_node itemNode : manifestNode.children("item"))
    {
        std::string properties = itemNode.attribute("properties").value();
        if (properties == "nav")
        {
            return itemNode.attribute("id").value();
        }
    }

    throw std::runtime_error("Failed to find TOC");
}
