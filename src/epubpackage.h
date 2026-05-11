#ifndef EPUBPACKAGE_H
#define EPUBPACKAGE_H

#include <libzippp.h>

class EpubPackage
{
public:
    EpubPackage(libzippp::ZipArchive &zip, const std::string &path);
    ~EpubPackage();
};

#endif // EPUBPACKAGE_H
