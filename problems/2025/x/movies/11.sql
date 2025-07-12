WITH
    movies_cte AS (
        SELECT
            s.movie_id
        FROM
            stars s
        WHERE
            s.person_id = (
                SELECT
                    p.id
                FROM
                    people p
                WHERE
                    p.name = 'Chadwick Boseman'
            )
    )
SELECT
    m.title
FROM
    movies m
        INNER JOIN movies_cte m_cte ON m.id = m_cte.movie_id
        INNER JOIN ratings r ON m.id = r.movie_id
ORDER BY
    r.rating DESC
LIMIT
    5;