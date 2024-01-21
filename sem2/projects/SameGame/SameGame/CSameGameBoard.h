#pragma once
class CSameGameBoard
{
public:

	CSameGameBoard();


	~CSameGameBoard();


	void SetupBoard();


	COLORREF GetBoardSpace(int row, int col);

	// Геттеры для получения информации о параметрах игрового поля
	int GetWidth(void) const { return m_nWidth; }
	int GetHeight(void) const { return m_nHeight; }
	int GetColumns(void) const { return m_nColumns; }
	int GetRows(void) const { return m_nRows; }

	// Функция для удаления игрового поля и освобождения памяти
	void DeleteBoard();
private:
	// Функция для создания игрового поля и выделения памяти под него
	void CreateBoard();

	// Указатель на двумерный массив
	int **m_arrBoard;

	// Список цветов: 0 – это цвет фона, 1-3 – это цвета блоков
	COLORREF m_arrColors[4];

	// Информация о размере игрового поля
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
};

