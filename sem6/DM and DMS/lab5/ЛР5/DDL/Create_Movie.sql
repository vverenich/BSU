set names utf8;
-- use movies;

drop table if exists movie;
create table movie(
    movieId        int,
    title          text,
    genre          text,
    releaseYear    int
);