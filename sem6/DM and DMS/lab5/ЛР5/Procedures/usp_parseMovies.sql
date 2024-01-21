set names utf8;
-- use movies;

DELIMITER $$

drop procedure if exists usp_parseMovies;

create procedure usp_parseMovies()
begin
	
	update stg_movie set title = trim(title);
    
    insert into movie (movieId, title, genre, releaseYear)
    with recursive cte_splitTitleAndGenres as
	(
		select movieId,
			   substring(title, 1, length(title) - 6) as title,
			   substring(title, -5, 4) as releaseYear,
			   substring_index(concat(genres, '|'),'|', 1) as genre,
		       substring(concat(genres, '|'), locate('|', concat(genres, '|')) + 1) as remainingGenres
		from stg_movie
        where concat('',substring(title, -5, 4) * 1) = substring(title, -5, 4)
	    union all
        select movieId,
			   title,
			   releaseYear,
			   substring_index(remainingGenres,'|', 1), 
               substring(remainingGenres, locate('|', remainingGenres) + 1)
		from cte_splitTitleAndGenres
        where remainingGenres <> ''
	)
	select movieId,
		   rtrim(title) as title, 
		   genre,
		   releaseYear 
    from cte_splitTitleAndGenres;
    
end$$

#call usp_parseMovies ();