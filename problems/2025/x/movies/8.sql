SELECT
    p.name
FROM
    stars s
        JOIN movies m ON m.id = s.movie_id
        JOIN people p ON p.id = s.person_id
WHERE
    m.title LIKE 'Toy Story%';