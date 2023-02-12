
-- 1. Составьте запрос на выборку данных с использованием рефлексивного 
-- соединения для таблицы (по указанию преподавателя). 

-- Под рефлексивным соединением (self join) подразумевается соединение 
-- таблицы с самой собой за счет использования псевдонимов.

-- В данном примере удалим записи из таблицы m_balls, где ball_ID больше
-- минимального и диаметр совпадает с минимальным.

DELETE FROM m_balls X WHERE ball_id > (SELECT MIN(ball_ID) 
   									   FROM m_balls Y
   									   WHERE X.diameter = Y.diameter);

-- 2. Простой оператор CASE

-- Выдать информацию о продуктах, заменив название категории "balls" 
-- на "balls(changed)" и "pants" на "pants(changed)"

SELECT m_products.product_id, m_products.delivery_date,
		m_products.product_name, m_products.number_0f_products, 
		m_products.unit_price, m_products.brand_name, 
		m_products.category_id, 
		CASE WHEN m_category.category_name = 'balls' THEN 'balls(changed)'
			 WHEN m_category.category_name = 'pants'THEN 'pants(changed)'
			 ELSE m_category.category_name
		END
FROM m_products
LEFT JOIN m_category
ON m_category.category_id = m_products.product_id;

-- 3. Поисковой оператор CASE

-- Вывести информацию о продуктах, причем если цена единицы продукта
-- в промежутке [200; 400] то вывести 500, если >= 500, то вывести 600

SELECT m_products.product_id, m_products.delivery_date,
		m_products.product_name, m_products.number_0f_products,
		m_products.brand_name, m_products.category_id, 
		CASE WHEN m_products.unit_price >= 200 AND m_products.unit_price <= 200 THEN 500
			 WHEN m_products.unit_price >= 500  THEN 600
			 ELSE m_products.unit_price
		END
FROM m_products;

-- 4. Оператор WITH;

-- вывести информацию о продаже, где цена за единицу продукта была максимальной

WITH max_price AS (
  SELECT MAX(m_products.unit_price) AS max_price 
  FROM m_products
)

SELECT m_sales.sale_id, m_sales.sale_date, m_sales.number_of_sold_products,
		m_sales.product_id, m_sales.shop_id, m_products.unit_price
FROM m_sales 
LEFT JOIN m_products
ON m_products.product_id = m_sales.product_id
LEFT JOIN max_price
ON m_products.unit_price = max_price.max_price;

-- 5. Встроенное представление

-- Вывести сведения о продажах, которые были произведены в магазинах, 
-- названия которых начинаются с подстроки 'evroopt'

SELECT m_sales.sale_id, m_sales.sale_date, m_sales.number_of_sold_products,
		m_sales.product_id, m_sales.shop_id, shops.shop_name
FROM m_sales
LEFT JOIN ( SELECT m_shops.shop_id AS shop_id, m_shops.shop_name AS shop_name
			FROM m_shops
			WHERE m_shops.shop_name LIKE 'evroopt%') shops
ON m_sales.shop_id = shops.shop_id

-- 6. Некоррелированный запрос

-- Вывести сведения о продажах, которые были произведены в магазинах, 
-- названия которых начинаются с подстроки 'evroopt'

SELECT m_sales.sale_id, m_sales.sale_date, m_sales.number_of_sold_products,
		m_sales.product_id, m_sales.shop_id, m_shops.shop_name
FROM m_sales
LEFT JOIN m_shops
ON m_shops.shop_id = m_sales.shop_id
WHERE m_shops.shop_id IN ( SELECT m_shops.shop_id
						   FROM m_shops
			               WHERE m_shops.shop_name LIKE 'evroopt%')


-- 7. Коррелированный запрос

-- Вывести данные о тех продажах, где единица товара стоила не 
-- менее средней стоимости всех продуктов

SELECT m_sales.sale_id, m_sales.sale_date, m_sales.number_of_sold_products,
		m_sales.product_id, m_sales.shop_id, m_products.unit_price
FROM m_sales
LEFT JOIN m_products
ON m_products.product_id = m_sales.product_id
WHERE m_products.unit_price > (SELECT AVG(m_products.unit_price)
							   FROM m_products
								)
-- 8. Функции NULLIF;

-- Вывести данные о спортивных гаджетах, однако в строках, где уникальный номер равен 2004,
-- в поле unique_number вывести значение 0

INSERT INTO m_sport_gadgets (sport_gadget_ID, unique_number, category_ID) VALUES (4, 2004, 2);

SELECT m_sport_gadgets.sport_gadget_id,  
		NULLIF(m_sport_gadgets.unique_number, 2004) AS unique_number
FROM m_sport_gadgets;

-- 9. Функции NVL2;

-- Т.к. я использую postgresql, вместо ф-ции NVL2 я буду использовать ф-цию COALESCE
-- Вывести данные о спортивных гаджетах, однако в строках, где гарантия не определена,
-- в поле guarantee_period вывести значение 0

SELECT m_sport_gadgets.sport_gadget_id,  m_sport_gadgets.unique_number, 
		COALESCE(m_sport_gadgets.guarantee_period, 0) AS guarantee_period, m_sport_gadgets.category_ID
FROM m_sport_gadgets;


-- 10. TOP-N анализ

-- Вывести топ-3 самых дорогих продукта

SELECT products.product_name, products.unit_price
FROM (
      SELECT * 
	  FROM m_products
      ORDER BY m_products.unit_price DESC
     ) AS products
LIMIT  3;

-- 11. функция ROLLUP

-- Вывести сведения о продажах, отсортированные по дате продажи(в общем) 
-- и внутри каждой даты по кол-ву проданных товаров, вывести в отдельном
-- столбце общее число проданных товаров

SELECT  m_sales.number_of_sold_products, m_sales.sale_date,
		SUM(m_sales.number_of_sold_products) AS total_number
FROM m_sales
GROUP BY ROLLUP (m_sales.number_of_sold_products, m_sales.sale_date)

