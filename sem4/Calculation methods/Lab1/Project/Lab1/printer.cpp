#include "printer.h"


Printer::Printer(): m_fout{nullptr}
{

}

Printer::~Printer()
{
    if(m_fout != nullptr)
    {
        delete m_fout;
    }
}

void Printer::setFolderName(const std::string &folder)
{
    m_folderName = folder;
}

void Printer::setFileName(const std::string &fileName)
{
    if(m_fout != nullptr)
    {
        m_fout->close();
        delete m_fout;
    }

    m_fout = new std::ofstream(m_folderName + "\\" + fileName);
}

void Printer::printMatrix(const Matrix &matrix)
{
    *m_fout << matrix;
}
