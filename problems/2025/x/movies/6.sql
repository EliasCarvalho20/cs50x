SELECT
    AVG(r.rating) AS avg_rating
FROM
    ratings r
        JOIN movies m ON m.id = r.movie_id
WHERE
    year = 2012;