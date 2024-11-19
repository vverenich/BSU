using System;
using System.Data;
using System.Data.OleDb;

namespace DB
{
    class Program
    {
        static void Main(string[] args)
        {
            string connectionString = "Provider=Microsoft.ACE.OLEDB.12.0;" +
                                      "Data Source=online_shop.accdb";
            OleDbConnection OnlineShop = new OleDbConnection(connectionString);
            OnlineShop.Open();
            var ZakazTable = new DataTable();
            var MaxZakazTable = new DataTable();
            Console.WriteLine("Информация о заказе:\n");

            OleDbDataAdapter adapter = new OleDbDataAdapter("select НомерЗаказа, SUM(Цена) AS Цена, COUNT(Количество) AS КоличествоПозиций FROM Состав_заказа  GROUP BY НомерЗаказа ORDER BY COUNT(Количество) DESC", OnlineShop);
            adapter.Fill(MaxZakazTable);
            Console.ForegroundColor = ConsoleColor.Cyan;
            foreach (var column in MaxZakazTable.Columns)
            {
                Console.Write(column.ToString() + "\t");
            }
            Console.WriteLine();
            Console.ForegroundColor = ConsoleColor.White;
            var cellss = MaxZakazTable.Rows[0].ItemArray;
            foreach (var cell in cellss)
                Console.Write(cell.ToString() + "\t\t");
            Console.WriteLine("\n**************************************************************");

            int t = Convert.ToInt32(MaxZakazTable.Rows[0]["НомерЗаказа"]);
            string select = "select ДатаЗаказа, ДатаПоставки FROM Заказ RIGHT JOIN Состояния_заказа ON Заказ.КодСостояния = Состояния_заказа.КодСостояния WHERE Заказ.НомерЗаказа = " + t;
            adapter = new OleDbDataAdapter(select, OnlineShop);
            adapter.Fill(ZakazTable);
            Show(ZakazTable);

            select = "SELECT Товар.НАИМЕНОВАНИЕ AS Товар, Состав_заказа.Количество AS Количво, Состав_заказа.Цена FROM Товар INNER JOIN Состав_заказа ON Товар.КодТовара = Состав_заказа.КодТовара WHERE(((Состав_заказа.НомерЗаказа) = 1))";
            adapter = new OleDbDataAdapter(select, OnlineShop);
            adapter.Fill(ZakazTable);
            Show(ZakazTable);

            select = "SELECT Клиент.НАИМЕНОВАНИЕ AS Клиент, Клиент.АДРЕС AS Адрес, Клиент.КОНТАКТ AS Контакт FROM Клиент INNER JOIN Заказ ON Клиент.КОДКЛИЕНТА = Заказ.КодКлиента WHERE(((Заказ.НомерЗаказа) = 1))";
            adapter = new OleDbDataAdapter(select, OnlineShop);
            adapter.Fill(ZakazTable);
            Show(ZakazTable);

            select = "SELECT Состояния_заказа.НазваниеСостояния AS Состояние, Курьер.ФИО AS Курьер FROM Состояния_заказа INNER JOIN(Курьер INNER JOIN Заказ ON Курьер.КОДКУРЬЕРА = Заказ.КодКурьера) ON Состояния_заказа.КодСостояния = Заказ.КодСостояния WHERE(((Заказ.НомерЗаказа) = 1))";
            adapter = new OleDbDataAdapter(select, OnlineShop);
            adapter.Fill(ZakazTable);
            Show(ZakazTable);
            OnlineShop.Close();

            void Show(DataTable tbl)
            {
                Console.ForegroundColor = ConsoleColor.Cyan;
                foreach (var column in tbl.Columns)
                {
                    Console.Write(column.ToString() + "\t\t");
                }
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine();
                foreach (DataRow row in tbl.Rows)
                {
                    var cells = row.ItemArray;
                    foreach (var cell in cells)
                        Console.Write(cell.ToString() + "\t");
                    Console.WriteLine();
                }
                Console.WriteLine("**************************************************************");
                tbl.Clear();
                tbl.Columns.Clear();
            }
        }
       
    }

}