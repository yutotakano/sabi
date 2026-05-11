#include <iostream>

#include "epubmetadata.h"

EpubMetadata::EpubMetadata(pugi::xml_node metadataNode)
{
    // Required elements (Epub 3 = 5.5.1, Epub 2 = 2.2)
    m_dc_title = metadataNode.child("dc:title").child_value();
    m_dc_identifier = metadataNode.child("dc:identifier").child_value();
    m_dc_language = metadataNode.child("dc:language").child_value();

    // doesn't distinguish roles (optional) or file-as (optional) for now
    m_dc_creators.clear();
    for (pugi::xml_node creatorNode : metadataNode.children("dc:creator"))
    {
        m_dc_creators.push_back(creatorNode.child_value());
    }

    std::cout << "Package version: " << m_version << std::endl;
    std::cout << "Package unique identifier: " << m_unique_id << std::endl;
    std::cout << "DC title: " << m_dc_title << std::endl;
    std::cout << "DC identifier: " << m_dc_identifier << std::endl;
    std::cout << "DC language: " << m_dc_language << std::endl;
    std::cout << "DC creators: " << std::endl;
    for (const std::string &creator : m_dc_creators)
    {
        std::cout << "  " << creator << std::endl;
    }
}

EpubMetadata::~EpubMetadata()
{
}
