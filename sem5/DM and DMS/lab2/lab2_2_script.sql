-- Create and add constraints according to individual task
CREATE TABLE m_fitness_accessories
(
	fitness_accessory_ID INT,
	material VARCHAR(30),
	category_ID INT
);

ALTER TABLE m_fitness_accessories
ADD CONSTRAINT fitness_accessories_PK 
PRIMARY KEY (fitness_accessory_ID);

CREATE TABLE m_sport_gadgets
(
	sport_gadget_ID INT,
	unique_number INT,
	guarantee_period INT,
	category_ID INT
);

ALTER TABLE m_sport_gadgets
ADD CONSTRAINT sport_gadgets_PK 
PRIMARY KEY (sport_gadget_ID);

CREATE TABLE m_products
(
	product_ID INT,
	delivery_date DATE,
	product_name VARCHAR(30),
	number_0f_products INT,
	unit_price INT,
	brand_name VARCHAR(30),
	category_id INT
);

ALTER TABLE m_products
ADD CONSTRAINT products_PK 
PRIMARY KEY (product_ID);

CREATE TABLE m_category
(
	category_id INT,
	category_name VARCHAR(30)
);

ALTER TABLE m_category
ADD CONSTRAINT category_PK 
PRIMARY KEY (category_ID);

CREATE TABLE m_balls
(
	ball_ID INT,
	diameter INT,
	category_ID INT
);

ALTER TABLE m_balls
ADD CONSTRAINT balls_PK 
PRIMARY KEY (ball_ID);

CREATE TABLE m_clothes
(
	clothes_ID INT,
	clothes_size INT,
	clothes_material VARCHAR(30),
	category_ID INT
);

ALTER TABLE m_clothes
ADD CONSTRAINT clothes_ID_PK 
PRIMARY KEY (clothes_ID);

CREATE TABLE m_sales
(
	sale_ID INT,
	sale_date DATE,
	number_of_sold_products INT,
	product_id INT,
	shop_ID INT
);

ALTER TABLE m_sales
ADD CONSTRAINT sale_ID_PK 
PRIMARY KEY (sale_ID);

CREATE TABLE m_shops
(
	shop_ID INT,
	shop_name VARCHAR(30),
	shop_location VARCHAR(30)
);

ALTER TABLE m_shops
ADD CONSTRAINT shop_ID_PK 
PRIMARY KEY (shop_ID);

ALTER TABLE m_fitness_accessories
ADD CONSTRAINT category_ID_FK
FOREIGN KEY(category_ID)
REFERENCES m_category(category_ID);

ALTER TABLE m_sport_gadgets
ADD CONSTRAINT category_ID_FK
FOREIGN KEY(category_ID)
REFERENCES m_category(category_ID);

ALTER TABLE m_balls
ADD CONSTRAINT category_ID_FK
FOREIGN KEY(category_ID)
REFERENCES m_category(category_ID);

ALTER TABLE m_clothes
ADD CONSTRAINT category_ID_FK
FOREIGN KEY(category_ID)
REFERENCES m_category(category_ID);

ALTER TABLE m_products
ADD CONSTRAINT category_ID_FK
FOREIGN KEY(category_ID)
REFERENCES m_category(category_ID);

ALTER TABLE m_sales
ADD CONSTRAINT product_ID_FK
FOREIGN KEY(product_ID)
REFERENCES m_products(product_ID);

ALTER TABLE m_sales
ADD CONSTRAINT shop_ID_FK
FOREIGN KEY(shop_ID)
REFERENCES m_shops(shop_ID);


