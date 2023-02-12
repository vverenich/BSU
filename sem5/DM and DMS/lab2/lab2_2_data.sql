-- insert into m_fitness_accessories

INSERT INTO m_fitness_accessories (fitness_accessory_ID, material, category_ID) VALUES (0, 'some_material', 4);
INSERT INTO m_fitness_accessories (fitness_accessory_ID, material, category_ID) VALUES (1, 'some_material 1', 4);
INSERT INTO m_fitness_accessories (fitness_accessory_ID, material, category_ID) VALUES (2, 'some_material 2', 4);
INSERT INTO m_fitness_accessories (fitness_accessory_ID, material, category_ID) VALUES (3, 'some_material 3', 4);

-- insert into m_sport_gadgets

INSERT INTO m_sport_gadgets (sport_gadget_ID, unique_number, guarantee_period, category_ID) VALUES (0, 2000, 30, 1);
INSERT INTO m_sport_gadgets (sport_gadget_ID, unique_number, guarantee_period, category_ID) VALUES (1, 2001, 90, 2);
INSERT INTO m_sport_gadgets (sport_gadget_ID, unique_number, guarantee_period, category_ID) VALUES (2, 2002, 180, 2);
INSERT INTO m_sport_gadgets (sport_gadget_ID, unique_number, guarantee_period, category_ID) VALUES (3, 2003, 200, 2);

-- insert into m_products

INSERT INTO m_products (product_ID, delivery_date, product_name, number_0f_products, unit_price, brand_name, category_id) VALUES(0, '12.09.22', 'football ball', 10, 200, 'socker', 1);
INSERT INTO m_products (product_ID, delivery_date, product_name, number_0f_products, unit_price, brand_name, category_id) VALUES(1, '13.09.22', 'pulsometer', 20, 300, 'Sportmaster', 2);
INSERT INTO m_products (product_ID, delivery_date, product_name, number_0f_products, unit_price, brand_name, category_id) VALUES(2, '14.09.22', 'pants', 30, 400, 'adidas', 3);
INSERT INTO m_products (product_ID, delivery_date, product_name, number_0f_products, unit_price, brand_name, category_id) VALUES(3, '15.09.22', 'clocks', 40, 500, 'nike', 4);
INSERT INTO m_products (product_ID, delivery_date, product_name, number_0f_products, unit_price, brand_name, category_id) VALUES(4, '17.09.22', 'boots', 40, 500, 'nike', 4);

-- insert into m_category

INSERT INTO m_category (category_id, category_name) VALUES (0, 'toys' );
INSERT INTO m_category (category_id, category_name) VALUES (1, 'balls' );
INSERT INTO m_category (category_id, category_name) VALUES (2, 'sport gadget' );
INSERT INTO m_category (category_id, category_name) VALUES (3, 'clothes' );
INSERT INTO m_category (category_id, category_name) VALUES (4, 'fitness accessories' );

-- insert into m_balls
 
INSERT INTO m_balls (ball_ID, diameter, category_ID) VALUES (0, 20, 1);
INSERT INTO m_balls (ball_ID, diameter, category_ID) VALUES (1, 30, 1);
INSERT INTO m_balls (ball_ID, diameter, category_ID) VALUES (2, 40, 1);
INSERT INTO m_balls (ball_ID, diameter, category_ID) VALUES (3, 50, 1);

-- insert into m_clothes

INSERT INTO m_clothes (clothes_ID, clothes_size, clothes_material, category_ID) VALUES (0, 200, 'leather', 5);
INSERT INTO m_clothes (clothes_ID, clothes_size, clothes_material, category_ID) VALUES (1, 400, 'leather type 1', 3);
INSERT INTO m_clothes (clothes_ID, clothes_size, clothes_material, category_ID) VALUES (2, 450, 'leather type 2', 3);
INSERT INTO m_clothes (clothes_ID, clothes_size, clothes_material, category_ID) VALUES (3, 500, 'leather type 3', 3);

-- insert into m_sales

INSERT INTO m_sales (sale_ID, sale_date, number_of_sold_products, product_id, shop_ID) VALUES (0, '12.09.22', 10, 1, 0);
INSERT INTO m_sales (sale_ID, sale_date, number_of_sold_products, product_id, shop_ID) VALUES (1, '24.09.22', 12, 2, 0);
INSERT INTO m_sales (sale_ID, sale_date, number_of_sold_products, product_id, shop_ID) VALUES (2, '25.09.22', 13, 3, 0);
INSERT INTO m_sales (sale_ID, sale_date, number_of_sold_products, product_id, shop_ID) VALUES (3, '26.09.22', 14, 4, 0);


-- insert into m_shops

INSERT INTO m_shops (shop_ID, shop_name, shop_location) VALUES (0, 'evroopt', 'minsk, building 16');
INSERT INTO m_shops (shop_ID, shop_name, shop_location) VALUES (1, 'evroopt 1', 'minsk, building 17');
INSERT INTO m_shops (shop_ID, shop_name, shop_location) VALUES (2, 'evroopt 2', 'minsk, building 18');
