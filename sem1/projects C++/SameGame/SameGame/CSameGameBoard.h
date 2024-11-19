#pragma once
class CSameGameBoard
{
public:

	CSameGameBoard();


	~CSameGameBoard();


	void SetupBoard();


	COLORREF GetBoardSpace(int row, int col);

	// ������� ��� ��������� ���������� � ���������� �������� ����
	int GetWidth(void) const { return m_nWidth; }
	int GetHeight(void) const { return m_nHeight; }
	int GetColumns(void) const { return m_nColumns; }
	int GetRows(void) const { return m_nRows; }

	// ������� ��� �������� �������� ���� � ������������ ������
	void DeleteBoard();
private:
	// ������� ��� �������� �������� ���� � ��������� ������ ��� ����
	void CreateBoard();

	// ��������� �� ��������� ������
	int **m_arrBoard;

	// ������ ������: 0 � ��� ���� ����, 1-3 � ��� ����� ������
	COLORREF m_arrColors[4];

	// ���������� � ������� �������� ����
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
};

