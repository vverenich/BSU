#ifndef PRINTER_H
#define PRINTER_H

#include <fstream>
#include "matrix.h"

class Printer
{
private:
    std::string m_folderName{};
public:
    std::ofstream* m_fout{nullptr};


    Printer();
    ~Printer();

    void setFolderName(const std::string &folder);
    void setFileName(const std::string &);
    void printMatrix(const Matrix &);
};

#endif // PRINTER_H
