-- 1. Создать процедуру заполнения склада. Входные параметры – номер склада,
-- перечень товаров, включающий до 10 наименований. Выходной параметр – номера
-- транспортных единиц, на которых будут доставляться указанные товары на склад.

create table storehouses_and_products(
	storehouses_and_products_id numeric,
	storehouse_id numeric,
	product_id numeric,
	number_of_products int
);

alter table storehouses_and_products
add constraint "storehouses_and_products PK" primary key (storehouses_and_products_id);

alter table storehouses_and_products
add constraint storehouses_and_products_foreign_key foreign key
(
	storehouse_id
)
references storehouse
(
	storehouse_id
);

alter table storehouses_and_products
add constraint storehouses_and_products_foreign_key_ foreign key
(
	product_id
)
references product
(
	product_id
);

CREATE SEQUENCE seq_storehouses_and_products
START WITH 1
MAXVALUE 1000
increment by 1;

create or replace procedure fill_storehouse(
	storehouse_id numeric,
	products varchar[],
	out transports numeric[]
)
language plpgsql    
as $$
declare
	product_id_v numeric;
	total_volume_v int;
	volume_of_current_product_v int;
	capacity_of_current_transport_v int;
	transport_row record;
	transport_cur cursor for
		select *
		from transport;
begin

	total_volume_v := 0;
	
  FOR i IN 1..array_length(products, 1) LOOP
  
  	select product_id
	from product
	where product_name = products[i]
	into product_id_v;
	
	select volume
	from product
	where product_name = products[i]
	into volume_of_current_product_v;
	
	total_volume_v := total_volume_v + volume_of_current_product;
  
    insert into storehouses_and_products values(nextval('seq_storehouses_and_products'), storehouse_id, product_id_v, 1);
  END LOOP;
  
  open transport_cur;
  
  loop
      fetch transport_cur into transport_row;
      exit when total_volume_v <= 0;
	  
	  total_volume_v := total_volume_v - transport_cur.load_capacity;
	  
	  transports:= array_append(transports, transport_cur.transport_id);
   end loop;
  
  close transport_cur;
  

end;$$

-- 2. С помощью пользовательской функции определить оставшееся место на
-- складе. Входные параметры – номер склада. Выходной параметр – свободное место
-- на складе (предполагается, что все товары, доставляемые транспортом, остаются на
-- складе).

create or replace procedure get_free_space(
	storehouse_id_p numeric,
	out free_space_p int
)
language plpgsql    
as $$
declare 
	occupied_volume int;
	capacity_of_storehouse int;
begin
	
	select number_of_products * product.volume as sum_volume 
	from storehouses_and_products
	left join product
	on product.product_id = storehouses_and_products.product_id
	where storehouse_id = storehouse_id_p
	into occupied_volume;
	
	select capacity
	from storehouse
	where storehouse.storehouse_id = storehouse_id_p
	into capacity_of_storehouse;
	
	free_space_p := capacity_of_storehouse - occupied_volume;

end;$$

-- 3. С помощью триггера предотвратить перегрузку транспорта. В случае
-- превышения допустимого веса перевозимого груза, подобрать другой свободный
-- транспорт, обслуживающий тот же склад. В случае, если это невозможно,
-- предотвратить операцию и вывести сообщение.

CREATE OR REPLACE FUNCTION add_product_to_transport_fnc() 
RETURNS TRIGGER 
AS $$
BEGIN
	
	IF (new.load_capacity > 1000) THEN
    	RAISE EXCEPTION 'добавить такой вес запрещено';
  	END IF;
  	RETURN NEW;
END;$$ 
LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_add_product_to_transport
BEFORE INSERT ON  transport
FOR EACH ROW
EXECUTE FUNCTION add_product_to_transport_fnc();