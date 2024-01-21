set names utf8;
set global local_infile=true;
use films;

truncate table stg_movie;

load data local infile 'D:\\movies.csv'
into table stg_movie
	fields terminated by ','
	optionally enclosed by '"'
	lines terminated by '\r\n'
	ignore 1 rows;