SELECT
    COUNT(title)
FROM
    movies m
        JOIN ratings r ON m.id = r.movie_id
WHERE
    rating = 10.0