create table storehouse(
	storehouse_id numeric,
	category varchar(30),
	capacity int
);

alter table storehouse
add constraint "storehouse PK" primary key (storehouse_id);


CREATE SEQUENCE seq_storehouse
START WITH 1
MAXVALUE 1000
increment by 1;

create table transport(
	transport_id numeric,
	transport_type varchar(30),
    load_capacity int,
	storehouse_id numeric
);

alter table transport
add constraint "transport PK" primary key (transport_id);

alter table transport
add constraint transport_foreign_key foreign key
(
	storehouse_id
)
references storehouse
(
	storehouse_id
);

CREATE SEQUENCE seq_transport
START WITH 1
MAXVALUE 1000
increment by 1;

create table product(
	product_id numeric,
	product_name varchar(30),
    volume int,
	weight int,
	transport_id numeric
);

alter table product
add constraint "product PK" primary key (product_id);

alter table product
add constraint product_foreign_key foreign key
(
	transport_id
)
references transport
(
	transport_id
);

CREATE SEQUENCE seq_product
START WITH 1
MAXVALUE 1000
increment by 1;
