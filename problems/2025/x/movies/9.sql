SELECT
    DISTINCT(p.name)
FROM
    stars s
        JOIN movies m ON m.id = s.movie_id
        JOIN people p ON p.id = s.person_id
WHERE
    m.year = 2004
ORDER BY
    p.birth;