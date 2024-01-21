set names utf8;
-- use movies;

drop table if exists stg_movie;
create table stg_movie(
    movieId        int,
    title          text,
    genres         text
);