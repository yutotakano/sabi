#ifndef EPUBTOC_H
#define EPUBTOC_H

#include "libzippp.h"

class EpubToc
{
public:
    EpubToc(libzippp::ZipArchive &zip, const std::string &path);
    ~EpubToc();
};

#endif // EPUBTOC_H
